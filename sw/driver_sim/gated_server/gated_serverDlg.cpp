// gated_serverDlg.cpp : implementation file
//

#include "stdafx.h"

#include "gated_server.h"
#include "gated_serverDlg.h"
#include ".\gated_serverdlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CR  0x0D
#define EOT 0x04
#define TIMER_ID_EVENT  12

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CGATEDServer dialog



CGATEDServer::CGATEDServer(CWnd* pParent /*=NULL*/)
	: CDialog(CGATEDServer::IDD, pParent)
   , m_path(_T(""))
   , m_status(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   m_text = NULL;
   m_comOk = false;
}

CGATEDServer::~CGATEDServer( void )
{
   if (m_text != NULL) {
      free(m_text);
      m_text = NULL;
   }
}

void CGATEDServer::DoDataExchange(CDataExchange* pDX)
{
   CDialog::DoDataExchange(pDX);
   DDX_Text(pDX, IDC_FILE_PATH, m_path);
   DDX_Text(pDX, IDC_STATUS, m_status);
}

BEGIN_MESSAGE_MAP(CGATEDServer, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
   ON_BN_CLICKED(IDC_SELECT_FILE, OnBnClickedSelectFile)
   ON_WM_TIMER()
   ON_BN_CLICKED(IDC_COM_SETUP, OnBnClickedComSetup)
   ON_MESSAGE(WM_COMM_RXCHAR, OnRxChar)
   ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
END_MESSAGE_MAP()


// CGATEDServer message handlers

BOOL CGATEDServer::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
   if (m_myComPort.InitPort((CWnd*) this, m_comSelDlg.m_comPort+1, /*19200*/ 2400, 'N', 8, 1, EV_RXCHAR, 512)) {
      m_myComPort.StartMonitoring();
      m_status.Format("Connected to COM%d", m_comSelDlg.m_comPort+1);
      UpdateData(FALSE);
      m_comOk = true;
   } else {
      m_status.Format("Not connected to COM port");
      UpdateData(FALSE);
      m_comOk = false;
   }
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGATEDServer::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGATEDServer::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGATEDServer::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGATEDServer::OnBnClickedSelectFile()
{
   // TODO: Add your control notification handler code here
   CFileDialog fileSel(TRUE, "*,txt", 0, OFN_HIDEREADONLY, "Text file (*.txt)|*.txt||", this, 0);
   if (fileSel.DoModal() == IDOK) {
      m_path = fileSel.GetPathName();
      UpdateData(FALSE);
      ParseFile();
      m_timer = SetTimer(TIMER_ID_EVENT, 2000, NULL);
   }
}


void CGATEDServer::ParseFile( void )
{
   struct _stat  fileStat;

   FILE* fp;

   fp = fopen(m_path, "rt");

   if (fp) {

      if (m_text != NULL) {
         free(m_text);
         m_text = NULL;
      }
      _stat(m_path, &fileStat);
      m_text = (char*) malloc(fileStat.st_size + 2); // Make room for eot character

      if (m_text == NULL) {
         MessageBox("Could not allocate enough memory", "Error", MB_OK | MB_ICONEXCLAMATION);
         return;
      }

      int i = 0;
      char c;

      while (!feof(fp)) {
         c = fgetc(fp);
         if (c == 0x0A) { /* Carrige return, eat next line feed character */
            c = 0x0D;
         }

         if (!feof(fp)) m_text[i++] = c;
      }

      if ((i>0) && (m_text[i-1] != 0x0D)) {   /* Check that the last character is a carrige return */
         m_text[i++] = 0x0D;                 /* Add it if not */
      }

      m_text[i] = EOT;  /* Indicate end of file with End of transmission */
      m_fileIndex = 0;
      m_fileModTime = fileStat.st_mtime;
      fclose(fp);
   }
}


void CGATEDServer::OnTimer(UINT nIDEvent)
{
   struct _stat  fileStat;

   if (nIDEvent == TIMER_ID_EVENT) {
      KillTimer(m_timer);
      _stat(m_path, &fileStat);
      if (fileStat.st_mtime != m_fileModTime) {
         ParseFile();
      }
      m_timer = SetTimer(TIMER_ID_EVENT, 2000, NULL);
   }
}


void CGATEDServer::OnBnClickedComSetup()
{
   if (m_comSelDlg.DoModal() == IDOK) {
      if (m_comOk) {
         m_myComPort.StopMonitoring();
      }
      if (m_myComPort.InitPort((CWnd*) this, m_comSelDlg.m_comPort+1, /*19200*/ 2400, 'N', 8, 1, EV_RXCHAR, 512)) {
         m_myComPort.StartMonitoring();
         m_status.Format("Connected to COM%d", m_comSelDlg.m_comPort+1);
         UpdateData(FALSE);
         m_comOk = true;
      } else {
         m_status.Format("Not connected to COM port");
         UpdateData(FALSE);
         m_comOk = false;
      }
   }
}


LONG CGATEDServer::OnRxChar(WPARAM ch, LPARAM port)
{
   CString  msg;
   char     t[2];

   msg.Format("Character received: %d", ch);
   MessageBox(msg, "Hello");

   return 0;

   t[1] = 0;      //String termination
   
	if (port <= 0 || port > 4)
		return -1;
  
   if (ch == 'F') {
     if (m_text != NULL) {
      
         if (m_text[m_fileIndex] == EOT) {   //EOT character isn't sent, only restart file
            m_fileIndex = 0;
         }
         t[0] = m_text[m_fileIndex++];
         m_myComPort.WriteToPort(t);
      } else {
         t[0] = EOT;                      // No File opened, send EOT character
         m_myComPort.WriteToPort(t);
      }
   } else if (ch == 'D') {
      m_status = "Driver Device connected";
      UpdateData(FALSE);
   } else {
      m_status = "Illegal command received";
      UpdateData(FALSE);
   }
   return 0;
}

void CGATEDServer::OnBnClickedButton1()
{
   char at[] = {'A', 'T', 0xD};

   m_myComPort.WriteToPort(at);
}
