// gated_server.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols


// CGATEDServerApp:
// See gated_server.cpp for the implementation of this class
//

class CGATEDServerApp : public CWinApp
{
public:
	CGATEDServerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CGATEDServerApp theApp;