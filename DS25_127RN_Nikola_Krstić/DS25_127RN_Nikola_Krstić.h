
// DS25_127RN_Nikola_Krstić.h : main header file for the DS25_127RN_Nikola_Krstić application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDS25127RNNikolaKrstićApp:
// See DS25_127RN_Nikola_Krstić.cpp for the implementation of this class
//

class CDS25127RNNikolaKrstićApp : public CWinAppEx
{
public:
	CDS25127RNNikolaKrstićApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation
	UINT  m_nAppLook;
	BOOL  m_bHiColorIcons;

	virtual void PreLoadState();
	virtual void LoadCustomState();
	virtual void SaveCustomState();

	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDS25127RNNikolaKrstićApp theApp;
