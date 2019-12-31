// MainFrm.h : interface of the CMainFrame class
//


#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifdef _WINDOWS
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:  // control bar embedded members
#ifdef _WINDOWS
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
#else
	CCommandBar m_wndCommandBar;
#endif

// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()
public:
	virtual void ActivateFrame(int nCmdShow = -1);
	afx_msg void OnClose();
private:
#ifdef _WINDOWS
	LPCTSTR m_pszSection;
	LPCTSTR m_pszWindowPos;
	bool ReadWindowPlacement(WINDOWPLACEMENT* pWP);
	void WriteWindowPlacement(WINDOWPLACEMENT* pWP);
#endif
};


