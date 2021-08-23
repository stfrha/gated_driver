

#define MICROCONTROLLER_SAB80517A     /* Infineon / Siemens SAB80517 */
#include "mcs51reg.h"
#include "characters.h"


/** Local definitions ***********************************************/
#define GATED_STROBE    P1_3
#define GATED_BUSY      P1_4
#define GATED_OVERREAD  P1_0
#define PUT_GATED_DATA(x)   P4 = x & 0x1F | 0xC0; P5 = (x >> 4) & 0xE | 0xF1
#define SCREEN_BUFFER_SIZE 2000

/** Global variables ************************************************/
code  char  SPLASH_SCREEN[64] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                                
code  char  VERSION_STR[77] =   
   "G.A.T.E.D.1 Graphic Alphanumeric and Text Electronic Display, version 01.01\0";

code char CHARACTERS[2048] = CHAR_BITMAPS;


xdata char msg[SCREEN_BUFFER_SIZE];                 /* Buffer for display data */

/** Local functions *************************************************/

/* Buffer functions */

char  build_character(char c, xdata char** dst)
{
   char  i;
   char* ptr;
   char  len;
   
   ptr = CHARACTERS + (c << 3);           /* Get pointer to first byte of character bitmap */
   len = *ptr;                            /* First byte is length of character */
   
   for (i=0 ; i<len ; i++) {               /* Copy bitmap data */
      *(*dst++) = *(ptr++);
   }
   *(*dst) = 0;                            /* End with a space zero */
   
   return len + 1;
}

unsigned int  build_message(char* str)
/* Only for building messages from the code. Real messages are built on the fly
   one characters at a time */
{
   idata char c;
   xdata char*  dst;
   idata unsigned int   msg_len = 0;
   
   dst = msg;
   
   while (((c = *(str++)) != '\0') && (msg_len < SCREEN_BUFFER_SIZE-8)) {
      msg_len += build_character(c, &dst);
   }   
     
   return msg_len;
}


/* Screen functions */

void  display_screen(unsigned int offset, unsigned int bitmap_len)
/* offset is the start of the part to put on screen. */
{
   idata char i;
   idata char len;

   while (GATED_BUSY);                    /* Wait for old overread sequence */

   if (offset < 64) {                     /* Is pre blank scrolling required? */
      for (i=0 ; i < 64 - offset ; i++) { /* Yes... */
         PUT_GATED_DATA(0);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
      }

      if (offset > bitmap_len) {    /* Is post blank scrolling required? */
         for (i=0 ; i < bitmap_len ; i++) { /* Yes... */
            PUT_GATED_DATA(msg[i]);
            GATED_STROBE = 1;
            GATED_STROBE = 0;
         }

         for (i=0 ; i < bitmap_len ; i++) { /* Now, do post scroll data */
            PUT_GATED_DATA(0);
            GATED_STROBE = 1;
            GATED_STROBE = 0;
         }
         
         
      } else {
         for (i=0 ; i < offset ; i++) { /* No... */
            PUT_GATED_DATA(msg[i]);
            GATED_STROBE = 1;
            GATED_STROBE = 0;
         }
      }

      len = (64 < 64+bitmap_len-offset) ? 64 : 64+bitmap_len-offset;
      for (i=0 ; i < len ; i++) {
         PUT_GATED_DATA(msg[offset+64-i]);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
      }
      
      if (offset > bitmap_len) {
         for (i=0 ; i < offset - bitmap_len ; i++) { /* Now, do post scroll data */
            PUT_GATED_DATA(0);
            GATED_STROBE = 1;
            GATED_STROBE = 0;
         }
      }
   }
      
   GATED_OVERREAD = 1;
   GATED_OVERREAD = 0;
}

/* Message functions */

void display_message(unsigned int msg_len)
{
   idata unsigned int   i;
   idata unsigned int   pre_post_len;
   
   pre_post_len = msg_len + 128;     /* Add pre and post scroll blank area */
   for (i=0 ; i<pre_post_len ; i++) {
      display_screen(i, msg_len);
   }
}


/* RS232 Functions */
 
char    query_rs232( void )
/* Returns true if a character is available in the input buffer */
{    
   return RI0;
}        

char  get_char( void )
/* Returns a character from the input buffer, also clear receive flag */
{
   idata char c;
   
   c = S0BUF;
   RI0 = 0;
   return c;
}

void  put_char(char c)
{
    while(TI0 == 0);                                /* Wait for old transmission */
    TI0 = 0;                                        /* Clear transmitt flag */
    S0BUF = c;                                          /* Begin the transmission */
}

void initialize_rs232( void )
{ 
   S0CON = 0x58;       /* Mode = 1, 8-bit UART, variabel baudrate, clear flags, enable reception */
 
   PCON |= 1<<7;       /* Deactivate half baudrate */

   S0RELH = 0x03;
   S0RELL = 0xEE;      /* Baudrate 19200 bytes/s (11.0592 MHz clock) */
 
   ES0 = 0;            /* Disables interrupt from serial port */

   ADCON0 = 0x80;      /* Starts baudrate generator */
   
   S0BUF = 'D';        /* Sends a dummy character */
}

void    initialize_mcu( void )
{
   SYSCON = 0;         /* Enables internal XRAM */
   WDTREL = 0x80;      /* Puts watchdog timeout to max */
}

void main( void )
{
   idata char i, j;
   idata char offset = 0;
   
   initialize_mcu();
   initialize_rs232();

   GATED_STROBE = 0;
   GATED_OVERREAD = 0;
   
   for (i=0 ; i<100 ; i++) {
      display_message( build_message(VERSION_STR) );
   }
   
   while (1) {
      while (GATED_BUSY);
   
      for (j=offset ; j<offset + 63 ; j++) {
         if (j > 63) i = j-64;
         else i = j;
         PUT_GATED_DATA(SPLASH_SCREEN[i]);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
      }
   
      offset += 1;
      
      if (offset > 63) offset = 0;
      
      GATED_OVERREAD = 1;
      GATED_OVERREAD = 0;
      
      if (query_rs232()) {
         put_char(get_char());
      }
   
   }
} 

