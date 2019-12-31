// MapViewerDoc.cpp : implementation of the CMapViewerDoc class
//

#include "stdafx.h"
#include "MapViewer.h"

#include "MapViewerDoc.h"
#include <algorithm>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMapViewerDoc

IMPLEMENT_DYNCREATE(CMapViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMapViewerDoc, CDocument)
END_MESSAGE_MAP()


// CMapViewerDoc construction/destruction

CMapViewerDoc::CMapViewerDoc()
{
	// TODO: add one-time construction code here

}

CMapViewerDoc::~CMapViewerDoc()
{
	for (m_cMapData.m_cIterator=m_cMapData.m_cMapSegmentColl.begin()
		; m_cMapData.m_cIterator!=m_cMapData.m_cMapSegmentColl.end()
		; m_cMapData.m_cIterator++)
	{
		CMapSegment* pMapSegment = *m_cMapData.m_cIterator;

		for (pMapSegment->m_cIterator=pMapSegment->m_cMapSegmentPointColl.begin()
			; pMapSegment->m_cIterator!=pMapSegment->m_cMapSegmentPointColl.end()
			; pMapSegment->m_cIterator++)
		{
			CMapSegmentPoint* pMapSegmentPoint = *pMapSegment->m_cIterator;

			delete pMapSegmentPoint;
		}

		pMapSegment->m_cMapSegmentPointColl.clear();

		delete pMapSegment;
	}

	m_cMapData.m_cMapSegmentColl.clear();
}

BOOL CMapViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

    int nSegmentsCount;
	int nPointsCount;
	BOOL bReadFile = FALSE;
	DWORD dwBytesRead = 0;

    HANDLE hFile = CreateFile(
#ifdef _WINDOWS
		_T("mapa.dat")
#else
		_T("\\Program Files\\MapViewer\\mapa.dat")
#endif
        , GENERIC_READ
		, FILE_SHARE_READ
		, NULL
		, OPEN_EXISTING
		, FILE_ATTRIBUTE_NORMAL
		, NULL);
 
	ASSERT(hFile != INVALID_HANDLE_VALUE);

    bReadFile = ReadFile(hFile, &nSegmentsCount, 4, &dwBytesRead, NULL);

	ASSERT(bReadFile && dwBytesRead == 4);

	for (int i=0; i<nSegmentsCount; i++)
	{
		CMapSegment* pMapSegment = new CMapSegment();

		bReadFile = ReadFile(hFile, &pMapSegment->m_nRoadClass, 4, &dwBytesRead, NULL);

		ASSERT(bReadFile && dwBytesRead == 4);

		bReadFile = ReadFile(hFile, &nPointsCount, 4, &dwBytesRead, NULL);

		ASSERT(bReadFile && dwBytesRead == 4);

		for (int j=0; j<nPointsCount; j++)
		{
			CMapSegmentPoint* pMapSegmentPoint = new CMapSegmentPoint();

			bReadFile = ReadFile(hFile, &pMapSegmentPoint->x, 4, &dwBytesRead, NULL);

			ASSERT(bReadFile && dwBytesRead == 4);

			if (pMapSegmentPoint->x > m_cMapData.m_nMaxX) m_cMapData.m_nMaxX = pMapSegmentPoint->x;

			bReadFile = ReadFile(hFile, &pMapSegmentPoint->y, 4, &dwBytesRead, NULL);

			ASSERT(bReadFile && dwBytesRead == 4);

			if (pMapSegmentPoint->y > m_cMapData.m_nMaxY) m_cMapData.m_nMaxY = pMapSegmentPoint->y;

			pMapSegment->m_cMapSegmentPointColl.push_back(pMapSegmentPoint);
		}

		m_cMapData.m_cMapSegmentColl.push_back(pMapSegment);
	}

    CloseHandle(hFile);

	std::sort(m_cMapData.m_cMapSegmentColl.begin(), m_cMapData.m_cMapSegmentColl.end(), sort_object);

	return TRUE;
}

CMapData& CMapViewerDoc::GetMapData()
{
	return m_cMapData;
}


// CMapViewerDoc serialization

void CMapViewerDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}


// CMapViewerDoc diagnostics

#ifdef _DEBUG
void CMapViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

#ifdef _WINDOWS
void CMapViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif
#endif //_DEBUG

// CMapViewerDoc commands
