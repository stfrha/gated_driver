#pragma once


// CCOMPortSelDlg dialog

class CCOMPortSelDlg : public CDialog
{
	DECLARE_DYNAMIC(CCOMPortSelDlg)

public:
	CCOMPortSelDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCOMPortSelDlg();

// Dialog Data
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
   int m_comPort;
};
