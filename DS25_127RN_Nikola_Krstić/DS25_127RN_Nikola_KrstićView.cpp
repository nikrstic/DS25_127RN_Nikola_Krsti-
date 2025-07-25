
// DS25_127RN_Nikola_KrstićView.cpp : implementation of the CDS25127RNNikolaKrstićView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DS25_127RN_Nikola_Krstić.h"
#endif

#include "DS25_127RN_Nikola_KrstićDoc.h"
#include "DS25_127RN_Nikola_KrstićView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDS25127RNNikolaKrstićView

IMPLEMENT_DYNCREATE(CDS25127RNNikolaKrstićView, CView)

BEGIN_MESSAGE_MAP(CDS25127RNNikolaKrstićView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CDS25127RNNikolaKrstićView construction/destruction

CDS25127RNNikolaKrstićView::CDS25127RNNikolaKrstićView() noexcept
{
	// TODO: add construction code here

}

CDS25127RNNikolaKrstićView::~CDS25127RNNikolaKrstićView()
{
}

BOOL CDS25127RNNikolaKrstićView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CDS25127RNNikolaKrstićView drawing

void CDS25127RNNikolaKrstićView::OnDraw(CDC* /*pDC*/)
{
	CDS25127RNNikolaKrstićDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}

void CDS25127RNNikolaKrstićView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CDS25127RNNikolaKrstićView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CDS25127RNNikolaKrstićView diagnostics

#ifdef _DEBUG
void CDS25127RNNikolaKrstićView::AssertValid() const
{
	CView::AssertValid();
}

void CDS25127RNNikolaKrstićView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDS25127RNNikolaKrstićDoc* CDS25127RNNikolaKrstićView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDS25127RNNikolaKrstićDoc)));
	return (CDS25127RNNikolaKrstićDoc*)m_pDocument;
}
#endif //_DEBUG


// CDS25127RNNikolaKrstićView message handlers
