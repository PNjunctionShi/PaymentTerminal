#pragma once
#include "CommodityList.h"
#include "StaticEx.h"

// COrderView

class COrderView : public CDockablePane
{
	DECLARE_DYNAMIC(COrderView)
private:
	CRect m_rectCurrClip;
	CStaticEx m_wndShopNameStatic;
	CStaticEx m_wndShopAddrStatic;
	CStaticEx m_wndDevider1Static;
	CStaticEx m_wndDevider2Static;
	CStaticEx m_wndDevider3Static;
	CStaticEx m_wndOrderTimeStatic;
	CStaticEx m_wndSeriesStatic;
	CStaticEx m_wndTotalStatic;
	CStaticEx m_wndChargeStatic;
	CStaticEx m_wndChangeStatic;
	CStaticEx m_wndCashier;
	CStaticEx m_wndTelephone;
	CCommodityList m_wndCommodityList;
public:
	COrderView();
	virtual ~COrderView();
	virtual BOOL Create(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


