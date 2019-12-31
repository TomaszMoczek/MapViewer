// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "MapViewer.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef _WINDOWS
#define TOOLBAR_HEIGHT 24
const DWORD dwAdornmentFlags = 0; // exit button
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
	ON_WM_CLOSE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame construction/destruction

CMainFrame::CMainFrame()
#ifdef _WINDOWS
: m_pszSection(_T("Settings")), m_pszWindowPos(_T("WindowPos"))
#endif

{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
#ifdef _WINDOWS
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
#else
	if (!m_wndCommandBar.Create(this) ||
	    !m_wndCommandBar.InsertMenuBar(IDR_MAINFRAME) ||
	    !m_wndCommandBar.AddAdornments(dwAdornmentFlags))
	{
		TRACE0("Failed to create CommandBar\n");
		return -1;      // fail to create
	}

	m_wndCommandBar.SetBarStyle(m_wndCommandBar.GetBarStyle() | CBRS_SIZE_FIXED);
#endif

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;

	cs.style &= ~FWS_ADDTOTITLE;

	return TRUE;
}


// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}
#ifdef _WINDOWS
void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif
#endif //_DEBUG


// CMainFrame message handlers




void CMainFrame::ActivateFrame(int nCmdShow)
{
#ifdef _WINDOWS
	if (nCmdShow == -1)
	{
		if (!IsWindowVisible())
			nCmdShow = SW_SHOWNORMAL;
		else if (IsIconic())
			nCmdShow = SW_RESTORE;
	}

	BringToTop(nCmdShow);

	if (nCmdShow != -1)
	{
		WINDOWPLACEMENT wp;

		if (!ReadWindowPlacement(&wp))
		{
			ShowWindow(nCmdShow);
		}
		else
		{
			if ( nCmdShow != SW_SHOWNORMAL )  
				wp.showCmd = nCmdShow;

			SetWindowPlacement(&wp);
		}

		BringToTop(nCmdShow);
	}
#else
	CFrameWnd::ActivateFrame(nCmdShow);
#endif
}

void CMainFrame::OnClose()
{
#ifdef _WINDOWS
	WINDOWPLACEMENT    wp;

	wp.length = sizeof wp;

	if ( GetWindowPlacement(&wp) )
	{
		if (IsIconic())
			wp.showCmd = SW_SHOW ;

		if ((wp.flags & WPF_RESTORETOMAXIMIZED) != 0)
			wp.showCmd = SW_SHOWMAXIMIZED ;

		WriteWindowPlacement(&wp);
	}
#endif

	CFrameWnd::OnClose();
}

#ifdef _WINDOWS
bool CMainFrame::ReadWindowPlacement(WINDOWPLACEMENT* pWP)
{
	int nRead ;
	CString strBuffer;
	char szFormat[] = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d";

	strBuffer = AfxGetApp()->GetProfileString(m_pszSection, m_pszWindowPos);

	if ( strBuffer.IsEmpty() )  return false;

	nRead = sscanf_s((const char*)strBuffer.GetBuffer(), szFormat,
				&pWP->flags, &pWP->showCmd,
				&pWP->ptMinPosition.x, &pWP->ptMinPosition.y,
				&pWP->ptMaxPosition.x, &pWP->ptMaxPosition.y,
				&pWP->rcNormalPosition.left,  &pWP->rcNormalPosition.top,
				&pWP->rcNormalPosition.right, &pWP->rcNormalPosition.bottom);

	if ( nRead != 10 )  return false;

	pWP->length = sizeof(WINDOWPLACEMENT);

	return true;
}

void CMainFrame::WriteWindowPlacement(WINDOWPLACEMENT* pWP)
{
	char szBuffer[sizeof("-32767")*8 + sizeof("65535")*2];
	char szFormat[] = "%u,%u,%d,%d,%d,%d,%d,%d,%d,%d";

	sprintf_s(szBuffer, szFormat,
			pWP->flags, pWP->showCmd,
			pWP->ptMinPosition.x, pWP->ptMinPosition.y,
			pWP->ptMaxPosition.x, pWP->ptMaxPosition.y,
			pWP->rcNormalPosition.left, pWP->rcNormalPosition.top,
			pWP->rcNormalPosition.right, pWP->rcNormalPosition.bottom);

	AfxGetApp()->WriteProfileString(m_pszSection, m_pszWindowPos, (LPCTSTR)szBuffer);
}
#endif