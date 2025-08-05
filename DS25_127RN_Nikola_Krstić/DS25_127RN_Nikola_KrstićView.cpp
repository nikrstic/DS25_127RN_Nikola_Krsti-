
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

#include "Akvarijum.h"
#include "RibicaFactory.h"
#include "Hranilica.h"
#include "StatistikaVisitor.h"
// CDS25127RNNikolaKrstićView

IMPLEMENT_DYNCREATE(CDS25127RNNikolaKrstićView, CView)

BEGIN_MESSAGE_MAP(CDS25127RNNikolaKrstićView, CView)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_WM_MBUTTONUP()
	ON_WM_KEYDOWN()
	ON_WM_DESTROY()
END_MESSAGE_MAP()

// CDS25127RNNikolaKrstićView construction/destruction

CDS25127RNNikolaKrstićView::CDS25127RNNikolaKrstićView() noexcept :timer(NULL)
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

void CDS25127RNNikolaKrstićView::OnDraw(CDC* pDC)
{
	CDS25127RNNikolaKrstićDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if (timer == NULL)
		timer = SetTimer(1, 30, NULL);

	Akvarijum::instance().crtaj(pDC);
	
	// TODO: add draw code for native data here
}

void CDS25127RNNikolaKrstićView::OnRButtonUp(UINT nFlags , CPoint point)
{
	//ClientToScreen(&point);
	if (Hranilica::getInstance()==nullptr) {
		Akvarijum::instance().postaviHranilicu(Hranilica::getInstance(point.x, point.y));
	}
	else {
		Hranilica::getInstance()->promeniPoz(point.x, point.y);
	}

	//OnContextMenu(this, point);
}
void CDS25127RNNikolaKrstićView::OnMButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	/*int xHranilice = Hranilica::getInstance()->getX();
	int yHranilice = Hranilica::getInstance()->getY();
	int velicinaHranilice = Hranilica::getVelicina();*/
	
	//if(point.x >= (xHranilice-velicinaHranilice/2) && point.x <=(xHranilice+=velicinaHranilice/2)  )
		//if (point.y >= (yHranilice - velicinaHranilice / 2) && point.y <= (yHranilice += velicinaHranilice / 2))
		//{
	
	Hranilica::unistiHranilicu();
	Akvarijum::instance().hranilica = nullptr;
	
	//delete Hranilica::getInstance();
		//}
	CView::OnMButtonUp(nFlags, point);
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

void CDS25127RNNikolaKrstićView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	auto NovaRibica = RibicaFactory::napravi_ribicu(point.x, point.y);
	


	Akvarijum::instance().dodaj(move(NovaRibica));
	
	CView::OnLButtonUp(nFlags, point);
}

void CDS25127RNNikolaKrstićView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDS25127RNNikolaKrstićDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	for (auto &ribica : Akvarijum::instance().ribice) {
		ribica.get()->pokreni(this);
	}
	
	if (Hranilica::getInstance()) {
		// mi smo sad u ..View i this je pokazivac na njega 
		Hranilica::getInstance()->pokreni(this);
	}

	Invalidate();
	CView::OnTimer(nIDEvent);
}

void CDS25127RNNikolaKrstićView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	
	if (nChar == VK_SPACE) {
		CString s;
		StatistikaVisitor visitor;
		
		Hranilica* hranilica = Hranilica::getInstance();
		int broj_paketa = hranilica->accept(visitor);
		
		Akvarijum& akvarijum = Akvarijum::instance();

		vector<float> ribicaStat = akvarijum.accept(visitor);
		int a = ribicaStat.at(0);
		s.Format(_T("Najveca ribica: %.2f \nNajmanja ribica: %.2f \nProsecna ribica: %.2f \nPaketi hrane:%d"),ribicaStat.at(0), ribicaStat.at(1), ribicaStat.at(2), broj_paketa);
		AfxMessageBox(s, MB_OK);

	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CDS25127RNNikolaKrstićView::OnDestroy()
{
	CView::OnDestroy();
	Hranilica::unistiHranilicu();
	// TODO: Add your message handler code here
}
