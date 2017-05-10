// PaymentTabs.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentTabs.h"


// CPaymentTabs

IMPLEMENT_DYNAMIC(CPaymentTabs, CMFCTabCtrl)

CPaymentTabs::CPaymentTabs()
{

}

CPaymentTabs::~CPaymentTabs()
{
}


BEGIN_MESSAGE_MAP(CPaymentTabs, CMFCTabCtrl)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaymentTabs 消息处理程序




int CPaymentTabs::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;
	if (!m_wndOrderList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("未能创建订单表格\n");
		//return -1;      // 未能创建
	}

	if (!m_wndMemberList.Create(dwStyle, rectEmpty, this, ID_LIST_MEMBER))
	{
		TRACE0("未能创建会员表格\n");
		//return -1;      // 未能创建
	}

	if (!m_wndCouponList.Create(dwStyle, rectEmpty, this, ID_LIST_COUPON))
	{
		TRACE0("未能创建卡券表格\n");
		//return -1;      // 未能创建
	}

	// 将列表窗口附加到选项卡: 
	CString strTabName;
	BOOL bNameValid;
	bNameValid = strTabName.LoadString(IDS_TAB_ORDERLIST);
	ASSERT(bNameValid);
	AddTab(&m_wndOrderList, strTabName, (UINT)0);
	bNameValid = strTabName.LoadString(IDS_TAB_MEMBERLIST);
	ASSERT(bNameValid);
	AddTab(&m_wndMemberList, strTabName, (UINT)1);
	bNameValid = strTabName.LoadString(IDS_TAB_COUPONLIST);
	ASSERT(bNameValid);
	AddTab(&m_wndCouponList, strTabName, (UINT)2);
	return 0;
}


void CPaymentTabs::OnSize(UINT nType, int cx, int cy)
{
	CMFCTabCtrl::OnSize(nType, cx, cy);
	CRect rectClient;
	CRect rectDummy;
	GetWindowRect(rectDummy);
	GetClientRect(rectClient);
	rectClient.top += 19;
	m_wndOrderList.MoveWindow(rectClient);
	m_wndMemberList.MoveWindow(rectClient);
	m_wndCouponList.MoveWindow(rectClient);
	// TODO: 在此处添加消息处理程序代码
}
