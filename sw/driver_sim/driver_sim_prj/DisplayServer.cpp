#include "StdAfx.h"
#include ".\displayserver.h"

CDisplayServer::CDisplayServer(void)
{
	int i;

	for (i=0 ; i<59 ; i += 2) {
		screen[i] = 0x55;
		screen[i+1] = 0xAA;
		mem[i] = 0x55;
		mem[i+1] = 0xAA;
	}
	for (i=59 ; i<64 ; i += 2) {
		mem[i] = 0x55;
		mem[i+1] = 0xAA;
	}

	m_index = 0;
	m_busy = 0;
}

CDisplayServer::~CDisplayServer(void)
{
}

void	CDisplayServer::InsertByte(char c)
{
	if (m_index < 64) mem[m_index++] = c;
   else {
//      CString msg;
//      msg.Format("Attempt to write outside of mem, index: %d", m_index); 
//      MessageBox(NULL, msg, "Error", MB_OK | MB_ICONEXCLAMATION);
      ASSERT(FALSE);
   }
}

void	CDisplayServer::Overread( void )
{
	m_busy <= 1;		// Dummy write actually

	int i;

	for (i=0 ; i<59 ; i++) {
		screen[i] = mem[i];
	}
	m_index = 0;
	m_busy = 0;

}

