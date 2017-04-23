#pragma once
#include "afxribbonconstructor.h"

// CUserButton 命令目标

class CPayRibbonUserButton : public CMFCRibbonApplicationButton
{
public:
	CPayRibbonUserButton();
	virtual ~CPayRibbonUserButton();
};


#pragma once

// CPayRibbonConstructor 命令目标

class CPayRibbonConstructor : public CMFCRibbonConstructor
{
public:
	CPayRibbonConstructor(const CMFCRibbonInfo& info);
	virtual ~CPayRibbonConstructor();

protected:
	virtual CMFCRibbonApplicationButton* CreateApplicationButton(CMFCRibbonBar& bar) const;
};


#pragma once


// CPayRibbonBar

class CPayRibbonBar : public CMFCRibbonBar
{
	friend class CPayRibbonConstructor;
	DECLARE_DYNAMIC(CPayRibbonBar)

public:
	CPayRibbonBar();
	virtual ~CPayRibbonBar();

public:
	virtual BOOL LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL);
	virtual BOOL LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType = RT_RIBBON, HINSTANCE hInstance = NULL);

protected:
	void SetAutoDestroyMainButton(){ m_bAutoDestroyMainButton = TRUE; }
		
	DECLARE_MESSAGE_MAP()
};


