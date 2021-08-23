// driver_sim_prjDoc.cpp : implementation of the Cdriver_sim_prjDoc class
//

#include "stdafx.h"
#include "driver_sim_prj.h"

#include "driver_sim_prjDoc.h"
#include ".\driver_sim_prjdoc.h"

#include "driver_sim_prjView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/** Global variables ************************************************/
unsigned char  SPLASH_SCREEN[64] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,\
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,   \
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   \
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,   \
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   \
                                 0x18, 0x3c, 0x7e, 0xff, 0xff, 0x7e, 0x3c, 0x18,   \
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,   \
                                 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
                                
unsigned char  VERSION_STR[77] =   
   "G.A.T.E.D.1 Graphic Alphanumeric and Text Electronic Display, version 01.01\0"; 
     /*"cool\0";*/
unsigned char CHARACTERS[2048] = CHAR_BITMAPS;

unsigned char msg[SCREEN_BUFFER_SIZE];                 /* Buffer for display data */

int   g_offset = 0;
int   g_len = 0;


// Cdriver_sim_prjDoc

IMPLEMENT_DYNCREATE(Cdriver_sim_prjDoc, CDocument)

BEGIN_MESSAGE_MAP(Cdriver_sim_prjDoc, CDocument)
   ON_COMMAND(ID_SCROLL_SPLASH, OnScrollSplash)
   ON_COMMAND(ID_SELECT_TEXT, OnSelectText)
END_MESSAGE_MAP()


// Cdriver_sim_prjDoc construction/destruction

Cdriver_sim_prjDoc::Cdriver_sim_prjDoc()
{
   m_fileContents = NULL;
   m_file = "";
}

Cdriver_sim_prjDoc::~Cdriver_sim_prjDoc()
{
//   if (m_fileContents != NULL) free(m_file);
}

BOOL Cdriver_sim_prjDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// Cdriver_sim_prjDoc serialization

void Cdriver_sim_prjDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// Cdriver_sim_prjDoc diagnostics

#ifdef _DEBUG
void Cdriver_sim_prjDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void Cdriver_sim_prjDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// Cdriver_sim_prjDoc commands
char  Cdriver_sim_prjDoc::build_character(unsigned char c, unsigned char** dst)
{
   unsigned char  i;
   unsigned char* ptr;
   unsigned char  len;
   
   ptr = CHARACTERS + (c << 3);           /* Get pointer to first byte of character bitmap */
   len = *(ptr++);                            /* First byte is length of character */
   
   for (i=0 ; i<len ; i++) {               /* Copy bitmap data */
      *((*dst)++) = *(ptr++);
   }
   *((*dst)++) = 0;                            /* End with a space zero */
   
   return len + 1;
}

unsigned int  Cdriver_sim_prjDoc::build_message(unsigned char* str)
/* Only for building messages from the code. Real messages are built on the fly
   one characters at a time */
{
   unsigned char c;
   unsigned char*  dst;
   unsigned int   msg_len = 0;
   
   dst = msg;
   
   while (((c = *(str++)) != '\0') && (msg_len < SCREEN_BUFFER_SIZE-8)) {
      msg_len += build_character(c, &dst);
   }   
     
   return msg_len;
}


/* Screen functions */

void  Cdriver_sim_prjDoc::display_screen(unsigned int offset, unsigned int bitmap_len)
/* offset is the start of the part to put on screen. */
{
   unsigned char i;
   unsigned char len;

   while (m_myDisplay.IsBusy());                    /* Wait for old overread sequence */

   if (offset < 64) {                     /* Is pre blank scrolling required? */
      for (i=0 ; i < 64 - offset ; i++) { /* Yes... */
		   m_myDisplay.InsertByte(0);
/*		 PUT_GATED_DATA(0);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
	   }

      if (offset > bitmap_len) {    /* Is post blank scrolling required? */
         for (i=0 ; i < bitmap_len ; i++) { /* Yes... */
            m_myDisplay.InsertByte(msg[i]);
/*		 PUT_GATED_DATA(msg[i]);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
         }

         for (i=0 ; i < offset - bitmap_len ; i++) { /* Now, do post scroll data */
      		m_myDisplay.InsertByte(0);
/*		 PUT_GATED_DATA(0);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
         }
         
         
      } else {
         for (i=0 ; i < offset ; i++) { /* No... */
            m_myDisplay.InsertByte(msg[i]);
/*		 PUT_GATED_DATA(msg[i]);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
         }
      }

   } else {

      len = (64 < 64+bitmap_len-offset) ? 64 : 64+bitmap_len-offset;
      for (i=0 ; i < len ; i++) {
            m_myDisplay.InsertByte(msg[offset-64+i]);
/*		 PUT_GATED_DATA(msg[offset-64+i]);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
      }
      
      if (offset > bitmap_len) {
         for (i=0 ; i < offset - bitmap_len ; i++) { /* Now, do post scroll data */
      		m_myDisplay.InsertByte(0);
/*		 PUT_GATED_DATA(0);
         GATED_STROBE = 1;
         GATED_STROBE = 0;
*/
         }
      }
   }
     
   m_myDisplay.Overread();
   UpdateAllViews(NULL);

/*   GATED_OVERREAD = 1;
   GATED_OVERREAD = 0;
   */
}

/* Message functions */

void Cdriver_sim_prjDoc::display_message(unsigned int msg_len)
{
   unsigned int   i;
   unsigned int   pre_post_len;
   
   pre_post_len = msg_len + 128;     /* Add pre and post scroll blank area */
   for (i=0 ; i<pre_post_len ; i++) {
      display_screen(i, msg_len);
   }
}

bool Cdriver_sim_prjDoc::NextScrollPos( void )
{
   display_screen(g_offset++, g_len);
   if (g_offset > g_len+64) return false;
   return true;
}

void Cdriver_sim_prjDoc::NextMessage( void )
{
   // TODO: get next message
   g_offset = 0;
   g_len = build_message(VERSION_STR);
   CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
   Cdriver_sim_prjView* pView = (Cdriver_sim_prjView*) pFrame->GetActiveView();
   pView->StartScroll();

}


void Cdriver_sim_prjDoc::OnScrollSplash()
{  
   g_offset = 0;
   g_len = build_message(VERSION_STR);
   CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
   Cdriver_sim_prjView* pView = (Cdriver_sim_prjView*) pFrame->GetActiveView();
   pView->StartScroll();
}

void Cdriver_sim_prjDoc::OnSelectText()
{

}
