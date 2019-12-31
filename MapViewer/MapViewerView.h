// MapViewerView.h : interface of the CMapViewerView class
//


#pragma once


class CMapViewerView : public CView
{
protected: // create from serialization only
	CMapViewerView();
	DECLARE_DYNCREATE(CMapViewerView)

// Attributes
public:
	CMapViewerDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CMapViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifdef _WINDOWS
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMoveLeft();
	afx_msg void OnUpdateMoveLeft(CCmdUI *pCmdUI);
	afx_msg void OnMoveUp();
	afx_msg void OnUpdateMoveUp(CCmdUI *pCmdUI);
	afx_msg void OnMoveDown();
	afx_msg void OnUpdateMoveDown(CCmdUI *pCmdUI);
	afx_msg void OnMoveRight();
	afx_msg void OnUpdateMoveRight(CCmdUI *pCmdUI);
	afx_msg void OnZoomIn();
	afx_msg void OnUpdateZoomIn(CCmdUI *pCmdUI);
	afx_msg void OnZoomOut();
	afx_msg void OnUpdateZoomOut(CCmdUI *pCmdUI);
private:
	int m_nMoveX;
	int m_nMoveY;
	int m_nZoomExp;
	CRect GetViewerRect(void);
};

#ifndef _DEBUG  // debug version in MapViewerView.cpp
inline CMapViewerDoc* CMapViewerView::GetDocument() const
   { return reinterpret_cast<CMapViewerDoc*>(m_pDocument); }
#endif

