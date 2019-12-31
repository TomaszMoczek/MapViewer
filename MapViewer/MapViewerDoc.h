// MapViewerDoc.h : interface of the CMapViewerDoc class
//


#pragma once

#include <vector>

typedef struct MapSegmentPoint
{
	int x;
	int y;

	MapSegmentPoint() : x(0), y(0) {}
} CMapSegmentPoint;

typedef struct MapSegment
{
	int m_nRoadClass;
	std::vector<CMapSegmentPoint*> m_cMapSegmentPointColl;
	std::vector<CMapSegmentPoint*>::iterator m_cIterator;

	MapSegment() : m_nRoadClass(0) {}
} CMapSegment;

typedef struct MapData
{
	int m_nMaxX;
	int m_nMaxY;
	std::vector<CMapSegment*> m_cMapSegmentColl;
	std::vector<CMapSegment*>::iterator m_cIterator;

	MapData() : m_nMaxX(0), m_nMaxY(0) {};
} CMapData;

class CMapViewerDoc : public CDocument
{
protected: // create from serialization only
	CMapViewerDoc();
	DECLARE_DYNCREATE(CMapViewerDoc)

// Attributes
private:
	struct sort_class {
		bool operator() (CMapSegment* pX, CMapSegment* pY) { return (pX->m_nRoadClass < pY->m_nRoadClass); }
	} sort_object;

	CMapData m_cMapData;

public:

// Operations
public:
	CMapData& GetMapData();

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// Implementation
public:
	virtual ~CMapViewerDoc();
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
};


