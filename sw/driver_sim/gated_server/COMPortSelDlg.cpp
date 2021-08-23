// COMPortSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "gated_server.h"
#include "COMPortSelDlg.h"


// CCOMPortSelDlg dialog

IMPLEMENT_DYNAMIC(CCOMPortSelDlg, CDialog)
CCOMPortSelDlg::CCOMPortSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCOMPortSelDlg::IDD, pParent)
   , m_comPort(8)
{
}

CCOMPortSelDlg::~CCOMPortSelDlg()
{
}

void CCOMPortSelDlg::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Radio(pDX, IDC_COM_PORTS, m_comPort);
}


BEGIN_MESSAGE_MAP(CCOMPortSelDlg, CDialog)
END_MESSAGE_MAP()


// CCOMPortSelDlg message handlers
