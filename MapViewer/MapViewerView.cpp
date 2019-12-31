// MapViewerView.cpp : implementation of the CMapViewerView class
//

#include "stdafx.h"
#include "MapViewer.h"

#include "MapViewerDoc.h"
#include "MapViewerView.h"

#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapViewerView

IMPLEMENT_DYNCREATE(CMapViewerView, CView)

BEGIN_MESSAGE_MAP(CMapViewerView, CView)
	ON_COMMAND(ID_MOVE_LEFT, &CMapViewerView::OnMoveLeft)
	ON_UPDATE_COMMAND_UI(ID_MOVE_LEFT, &CMapViewerView::OnUpdateMoveLeft)
	ON_COMMAND(ID_MOVE_UP, &CMapViewerView::OnMoveUp)
	ON_UPDATE_COMMAND_UI(ID_MOVE_UP, &CMapViewerView::OnUpdateMoveUp)
	ON_COMMAND(ID_MOVE_DOWN, &CMapViewerView::OnMoveDown)
	ON_UPDATE_COMMAND_UI(ID_MOVE_DOWN, &CMapViewerView::OnUpdateMoveDown)
	ON_COMMAND(ID_MOVE_RIGHT, &CMapViewerView::OnMoveRight)
	ON_UPDATE_COMMAND_UI(ID_MOVE_RIGHT, &CMapViewerView::OnUpdateMoveRight)
	ON_COMMAND(ID_ZOOM_IN, &CMapViewerView::OnZoomIn)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_IN, &CMapViewerView::OnUpdateZoomIn)
	ON_COMMAND(ID_ZOOM_OUT, &CMapViewerView::OnZoomOut)
	ON_UPDATE_COMMAND_UI(ID_ZOOM_OUT, &CMapViewerView::OnUpdateZoomOut)
END_MESSAGE_MAP()

// CMapViewerView construction/destruction

CMapViewerView::CMapViewerView() : m_nMoveX(0), m_nMoveY(0), m_nZoomExp(0)
{
}

CMapViewerView::~CMapViewerView()
{
}

BOOL CMapViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

void CMapViewerView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CRect cClientRect;
	GetClientRect(&cClientRect);

	double nVal = (GetDocument()->GetMapData().m_nMaxX + GetDocument()->GetMapData().m_nMaxY) / (cClientRect.Width() + cClientRect.Height());
	m_nZoomExp = (int)floor(log10(nVal) / log10(2.0));
}

// CMapViewerView drawing

void CMapViewerView::OnDraw(CDC* pDC)
{
	CMapViewerDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect cClientRect;
	GetClientRect(&cClientRect);

	CRect cViewerRect = GetViewerRect();

	CBrush brush(RGB(255, 251, 240));
	CBrush *pBrush = (CBrush *)pDC->SelectObject(&brush);
	pDC->Rectangle(&cClientRect);
	pDC->SelectObject(pBrush);
	brush.DeleteObject();

	CMapData& cMapData = pDoc->GetMapData();

	for (cMapData.m_cIterator=cMapData.m_cMapSegmentColl.begin()
		; cMapData.m_cIterator!=cMapData.m_cMapSegmentColl.end()
		; cMapData.m_cIterator++)
	{
		CMapSegment* pMapSegment = *cMapData.m_cIterator;

		COLORREF cColorRef;
		int nPenWidth;
		
		switch (pMapSegment->m_nRoadClass)
		{
		case 5:
			cColorRef = RGB(166, 202, 240);
			nPenWidth = (7 / (m_nZoomExp + 1));
			break;
		case 6:
			cColorRef = RGB(160, 160, 164);
			nPenWidth = (12 / (m_nZoomExp + 1));
			break;
		case 7:
			cColorRef = RGB(255, 0, 0);
			nPenWidth = (18 / (m_nZoomExp + 1));
			break;
		default:
			cColorRef = RGB(0, 0, 0);
			nPenWidth = 1;
		}
	
		bool bIsMapSegmentBegin = true;
		CPen newPen(PS_SOLID, nPenWidth, cColorRef);
		CPen* pOldPen = pDC->SelectObject(&newPen);

		for (pMapSegment->m_cIterator=pMapSegment->m_cMapSegmentPointColl.begin()
			; pMapSegment->m_cIterator!=pMapSegment->m_cMapSegmentPointColl.end()
			; pMapSegment->m_cIterator++)
		{
			CMapSegmentPoint* pMapSegmentPoint = *pMapSegment->m_cIterator;
			
			if (pMapSegmentPoint->x >= 0 && pMapSegmentPoint->y >= 0)
			{
				if (pMapSegmentPoint->x >= cViewerRect.left 
					&& pMapSegmentPoint->x <= cViewerRect.right
					&& pMapSegmentPoint->y >= cViewerRect.top
					&& pMapSegmentPoint->y <= cViewerRect.bottom)
				{
					int nX = (int)(((double)(pMapSegmentPoint->x - cViewerRect.left) / cViewerRect.Width()) * cClientRect.Width());
					int nY = (int)(((double)(pMapSegmentPoint->y - cViewerRect.top) / cViewerRect.Height()) * cClientRect.Height());

					if (bIsMapSegmentBegin)
					{
						pDC->MoveTo(nX, nY);
						bIsMapSegmentBegin = false;
					}

					pDC->LineTo(nX, nY);
				}
			}
		}

		pDC->SelectObject(pOldPen);
		newPen.DeleteObject();
	}
}


// CMapViewerView diagnostics

#ifdef _DEBUG
void CMapViewerView::AssertValid() const
{
	CView::AssertValid();
}

#ifdef _WINDOWS
void CMapViewerView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif

CMapViewerDoc* CMapViewerView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMapViewerDoc)));
	return (CMapViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CMapViewerView message handlers

void CMapViewerView::OnMoveLeft()
{
	m_nMoveX --;
	Invalidate();
}

void CMapViewerView::OnUpdateMoveLeft(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_nMoveX > 0);
}

void CMapViewerView::OnMoveUp()
{
	m_nMoveY --;
	Invalidate();
}

void CMapViewerView::OnUpdateMoveUp(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_nMoveY > 0);
}

void CMapViewerView::OnMoveDown()
{
	m_nMoveY ++;
	Invalidate();
}

void CMapViewerView::OnUpdateMoveDown(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetViewerRect().bottom < GetDocument()->GetMapData().m_nMaxY);
}

void CMapViewerView::OnMoveRight()
{
	m_nMoveX ++;
	Invalidate();
}

void CMapViewerView::OnUpdateMoveRight(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(GetViewerRect().right < GetDocument()->GetMapData().m_nMaxX);
}

void CMapViewerView::OnZoomIn()
{
	m_nZoomExp --;
	m_nMoveX *= 2;
	m_nMoveY *= 2;
	Invalidate();
}

void CMapViewerView::OnUpdateZoomIn(CCmdUI *pCmdUI)
{
	pCmdUI->Enable(m_nZoomExp > 0);
}

void CMapViewerView::OnZoomOut()
{
	m_nZoomExp ++;
	m_nMoveX /= 2;
	m_nMoveY /= 2;
	Invalidate();
}

void CMapViewerView::OnUpdateZoomOut(CCmdUI *pCmdUI)
{
	CRect cClientRect;
	GetClientRect(&cClientRect);

	double nVal = (GetDocument()->GetMapData().m_nMaxX + GetDocument()->GetMapData().m_nMaxY) / (cClientRect.Width() + cClientRect.Height());
	double nMaxZoomExp = floor(log10(nVal) / log10(2.0));

	pCmdUI->Enable(m_nZoomExp < (int)nMaxZoomExp);
}

CRect CMapViewerView::GetViewerRect(void)
{
	CRect cClientRect;
	GetClientRect(&cClientRect);

	SIZE cSize;
	cSize.cx = (int)pow(2.0, m_nZoomExp) * cClientRect.Width();
	cSize.cy = (int)pow(2.0, m_nZoomExp) * cClientRect.Height();

	POINT cPoint;
	cPoint.x = (int)(m_nMoveX * cSize.cx * 0.5); 
	cPoint.y = (int)(m_nMoveY * cSize.cy * 0.5); 

	return CRect(cPoint, cSize);
}
