
// DS25_127RN_Nikola_KrstićDoc.h : interface of the CDS25127RNNikolaKrstićDoc class
//


#pragma once


class CDS25127RNNikolaKrstićDoc : public CDocument
{
protected: // create from serialization only
	CDS25127RNNikolaKrstićDoc() noexcept;
	DECLARE_DYNCREATE(CDS25127RNNikolaKrstićDoc)

// Attributes
public:

// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CDS25127RNNikolaKrstićDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
