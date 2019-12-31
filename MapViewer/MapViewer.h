// MapViewer.h : main header file for the MapViewer application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#ifdef _WINDOWS
#include "resource.h"       // main symbols
#else
#include "resourceppc.h"
#endif


// CMapViewerApp:
// See MapViewer.cpp for the implementation of this class
//

class CMapViewerApp : public CWinApp
{
public:
	CMapViewerApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMapViewerApp theApp;