#pragma once
#include "afxribbonconstructor.h"


// CUserButton ����Ŀ��

class CPayRibbonUserButton : public CMFCRibbonApplicationButton
{
public:
	CPayRibbonUserButton();
	virtual ~CPayRibbonUserButton();
};


#pragma once

// CPayRibbonConstructor ����Ŀ��

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
	virtual void RecalcLayout();
	virtual CMFCRibbonBaseElement* HitTest(CPoint point, BOOL bCheckActiveCategory = FALSE, BOOL bCheckPanelCaption = FALSE);

protected:
	virtual CSize CalcFixedLayout(BOOL bStretch, BOOL bHorz);

	DECLARE_MESSAGE_MAP()
	virtual void DoDataExchange(CDataExchange* pDX);
};


#pragma once


// CPayRibbonQAT

class CPayRibbonQAT : public CMFCRibbonQuickAccessToolBar
{
	friend class CPayRibbonBar;
	DECLARE_DYNAMIC(CPayRibbonQAT)

public:
	CPayRibbonQAT();
	virtual ~CPayRibbonQAT();

protected:
	DECLARE_MESSAGE_MAP()
};

#pragma once

// CPayRibbonButtonsGroup ����Ŀ��

class CPayRibbonButtonsGroup : public CMFCRibbonButtonsGroup
{
	friend class CPayRibbonBar;
public:
	CPayRibbonButtonsGroup();
	virtual ~CPayRibbonButtonsGroup();
};


#pragma once

// CPayRibbonTabsGroup ����Ŀ��

class CPayRibbonTabsGroup : public CMFCRibbonTabsGroup
{
	friend class CPayRibbonBar;

public:
	CPayRibbonTabsGroup();
	virtual ~CPayRibbonTabsGroup();
};



#pragma once

// CPayRibbonCategory ����Ŀ��

class CPayRibbonCategory : public CMFCRibbonCategory
{
	friend class CPayRibbonBar;

public:
	CPayRibbonCategory();
	virtual ~CPayRibbonCategory();
};


#pragma once

// CPayRibbonContextCaption ����Ŀ��

class CPayRibbonContextCaption : public CMFCRibbonContextCaption
{
	friend class CPayRibbonBar;

public:
	CPayRibbonContextCaption();
	virtual ~CPayRibbonContextCaption();
};
