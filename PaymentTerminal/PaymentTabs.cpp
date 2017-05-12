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
	//ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaymentTabs 消息处理程序




int CPaymentTabs::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
	if (!m_wndOrderList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("未能创建订单表格\n");
		//return -1;      // 未能创建
	}

	m_wndOrderList.InsertColumn(0, _T("创建时间"),0,150);
	m_wndOrderList.InsertColumn(1, _T("订单号"), 0, 150);
	m_wndOrderList.InsertColumn(2, _T("收银员"), 0, 150);
	m_wndOrderList.InsertColumn(3, _T("支付类型"), 0, 150);
	m_wndOrderList.InsertColumn(4, _T("订单状态"), 0, 150);
	m_wndOrderList.InsertColumn(5, _T("支付时间"), 0, 150);

	//======================================================================================================
	m_wndOrderList.InsertItem(0, _T("2017/5/12 21:06:24"));
	m_wndOrderList.SetItemText(0, 1, _T("AA000001"));
	m_wndOrderList.SetItemText(0, 2, _T("小红"));
	m_wndOrderList.SetItemText(0, 3, _T("支付宝"));
	m_wndOrderList.SetItemText(0, 4, _T("未支付"));

	m_wndOrderList.InsertItem(1, _T("2017/5/12 21:18:21"));
	m_wndOrderList.SetItemText(1, 1, _T("AA000002"));
	m_wndOrderList.SetItemText(1, 2, _T("小明"));
	m_wndOrderList.SetItemText(1, 3, _T("微信"));
	m_wndOrderList.SetItemText(1, 4, _T("未支付"));
	//======================================================================================================


	if (!m_wndMemberList.Create(dwStyle, rectEmpty, this, ID_LIST_MEMBER))
	{
		TRACE0("未能创建会员表格\n");
		//return -1;      // 未能创建
	}
	m_wndMemberList.InsertColumn(0, _T("创建时间"), 0, 150);

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


//void CPaymentTabs::OnSize(UINT nType, int cx, int cy)
//{
//	CMFCTabCtrl::OnSize(nType, cx, cy);
//	// TODO: 在此处添加消息处理程序代码
//}
