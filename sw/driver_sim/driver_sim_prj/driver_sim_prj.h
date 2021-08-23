// driver_sim_prj.h : main header file for the driver_sim_prj application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols


// Cdriver_sim_prjApp:
// See driver_sim_prj.cpp for the implementation of this class
//

class Cdriver_sim_prjApp : public CWinApp
{
public:
	Cdriver_sim_prjApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern Cdriver_sim_prjApp theApp;