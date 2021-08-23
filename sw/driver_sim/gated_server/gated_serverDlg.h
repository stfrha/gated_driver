// gated_serverDlg.h : header file
//

#pragma once

#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "COMPortSelDlg.h"
#include "SerialPort.h"

// CGATEDServer dialog
class CGATEDServer : public CDialog
{
// Construction
public:
	CGATEDServer(CWnd* pParent = NULL);	// standard constructor
   ~CGATEDServer( void );

// Dialog Data
	enum { IDD = IDD_GATED_SERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
   void        ParseFile( void );
   CCOMPortSelDlg m_comSelDlg;
   bool           m_comOk;
   CSerialPort    m_myComPort;

   char*       m_text;
   int         m_fileIndex;
   time_t      m_fileModTime;
   int         m_timer;


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
   afx_msg void OnBnClickedSelectFile();
   CString m_path;
   afx_msg void OnTimer(UINT nIDEvent);
   afx_msg void OnBnClickedComSetup();
   LONG OnRxChar(WPARAM ch, LPARAM port);
   CString m_status;
   afx_msg void OnBnClickedButton1();
};
