// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CUserButton

CPayRibbonUserButton::CPayRibbonUserButton()
{
}

CPayRibbonUserButton::~CPayRibbonUserButton()
{
}


// CUserButton 成员函数
// E:\Documents\Visual Studio 2015\Projects\PaymentTerminal\PaymentTerminal\PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonConstructor

CPayRibbonConstructor::CPayRibbonConstructor(const CMFCRibbonInfo& info) : CMFCRibbonConstructor(info)
{
}

CPayRibbonConstructor::~CPayRibbonConstructor()
{
}

CMFCRibbonApplicationButton* CPayRibbonConstructor::CreateApplicationButton(CMFCRibbonBar& bar) const
{
	//bar.m_bAutoDestroyMainButton = TRUE;
	CPayRibbonBar *pPayBar =(CPayRibbonBar *) &bar;
	pPayBar->SetAutoDestroyMainButton();
	bar.SetApplicationButton(new CPayRibbonUserButton, CSize(45, 45));

	return bar.GetApplicationButton();
}
// CPayRibbonConstructor 成员函数
// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"
#include "afxribboninfoloader.h"

// CPayRibbonBar

IMPLEMENT_DYNAMIC(CPayRibbonBar, CMFCRibbonBar)

CPayRibbonBar::CPayRibbonBar()
{

}

CPayRibbonBar::~CPayRibbonBar()
{
}

BOOL CPayRibbonBar::LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType, HINSTANCE hInstance)
{
	ASSERT_VALID(this);
	return LoadFromResource(MAKEINTRESOURCE(uiXMLResID), lpszResType, hInstance);
}

BOOL CPayRibbonBar::LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType, HINSTANCE hInstance)
{
	ASSERT_VALID(this);

	CMFCRibbonInfo info;
	CMFCRibbonInfoLoader loader(info);

	if (!loader.Load(lpszXMLResID, lpszResType, hInstance))
	{
		TRACE0("Cannot load ribbon from resource\n");
		return FALSE;
	}

	CPayRibbonConstructor constr(info);
	constr.ConstructRibbonBar(*this);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CPayRibbonBar, CMFCRibbonBar)
END_MESSAGE_MAP()



// CPayRibbonBar 消息处理程序


