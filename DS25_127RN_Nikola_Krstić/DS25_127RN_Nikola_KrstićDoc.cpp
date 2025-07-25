
// DS25_127RN_Nikola_KrstićDoc.cpp : implementation of the CDS25127RNNikolaKrstićDoc class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DS25_127RN_Nikola_Krstić.h"
#endif

#include "DS25_127RN_Nikola_KrstićDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDS25127RNNikolaKrstićDoc

IMPLEMENT_DYNCREATE(CDS25127RNNikolaKrstićDoc, CDocument)

BEGIN_MESSAGE_MAP(CDS25127RNNikolaKrstićDoc, CDocument)
END_MESSAGE_MAP()


// CDS25127RNNikolaKrstićDoc construction/destruction

CDS25127RNNikolaKrstićDoc::CDS25127RNNikolaKrstićDoc() noexcept
{
	// TODO: add one-time construction code here

}

CDS25127RNNikolaKrstićDoc::~CDS25127RNNikolaKrstićDoc()
{
}

BOOL CDS25127RNNikolaKrstićDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CDS25127RNNikolaKrstićDoc serialization

void CDS25127RNNikolaKrstićDoc::Serialize(CArchive& ar)
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

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CDS25127RNNikolaKrstićDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CDS25127RNNikolaKrstićDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CDS25127RNNikolaKrstićDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDS25127RNNikolaKrstićDoc diagnostics

#ifdef _DEBUG
void CDS25127RNNikolaKrstićDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDS25127RNNikolaKrstićDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDS25127RNNikolaKrstićDoc commands
