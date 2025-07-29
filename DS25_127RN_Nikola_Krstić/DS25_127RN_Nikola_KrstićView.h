
// DS25_127RN_Nikola_KrstićView.h : interface of the CDS25127RNNikolaKrstićView class
//

#pragma once


class CDS25127RNNikolaKrstićView : public CView
{
protected: // create from serialization only
	CDS25127RNNikolaKrstićView() noexcept;
	DECLARE_DYNCREATE(CDS25127RNNikolaKrstićView)

// Attributes
public:
	CDS25127RNNikolaKrstićDoc* GetDocument() const;
	UINT_PTR timer;
// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CDS25127RNNikolaKrstićView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnMButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in DS25_127RN_Nikola_KrstićView.cpp
inline CDS25127RNNikolaKrstićDoc* CDS25127RNNikolaKrstićView::GetDocument() const
   { return reinterpret_cast<CDS25127RNNikolaKrstićDoc*>(m_pDocument); }
#endif

