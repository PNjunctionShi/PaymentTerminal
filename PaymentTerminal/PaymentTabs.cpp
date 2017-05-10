// PaymentTabs.cpp : ʵ���ļ�
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



// CPaymentTabs ��Ϣ�������




int CPaymentTabs::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT;
	if (!m_wndOrderList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("δ�ܴ����������\n");
		//return -1;      // δ�ܴ���
	}

	if (!m_wndMemberList.Create(dwStyle, rectEmpty, this, ID_LIST_MEMBER))
	{
		TRACE0("δ�ܴ�����Ա���\n");
		//return -1;      // δ�ܴ���
	}

	if (!m_wndCouponList.Create(dwStyle, rectEmpty, this, ID_LIST_COUPON))
	{
		TRACE0("δ�ܴ�����ȯ���\n");
		//return -1;      // δ�ܴ���
	}

	// ���б��ڸ��ӵ�ѡ�: 
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
	// TODO: �ڴ˴������Ϣ����������
}
