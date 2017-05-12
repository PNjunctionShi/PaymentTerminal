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
	//ON_WM_SIZE()
END_MESSAGE_MAP()



// CPaymentTabs ��Ϣ�������




int CPaymentTabs::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCTabCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
	if (!m_wndOrderList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("δ�ܴ����������\n");
		//return -1;      // δ�ܴ���
	}

	m_wndOrderList.InsertColumn(0, _T("����ʱ��"),0,150);
	m_wndOrderList.InsertColumn(1, _T("������"), 0, 150);
	m_wndOrderList.InsertColumn(2, _T("����Ա"), 0, 150);
	m_wndOrderList.InsertColumn(3, _T("֧������"), 0, 150);
	m_wndOrderList.InsertColumn(4, _T("����״̬"), 0, 150);
	m_wndOrderList.InsertColumn(5, _T("֧��ʱ��"), 0, 150);

	//======================================================================================================
	m_wndOrderList.InsertItem(0, _T("2017/5/12 21:06:24"));
	m_wndOrderList.SetItemText(0, 1, _T("AA000001"));
	m_wndOrderList.SetItemText(0, 2, _T("С��"));
	m_wndOrderList.SetItemText(0, 3, _T("֧����"));
	m_wndOrderList.SetItemText(0, 4, _T("δ֧��"));

	m_wndOrderList.InsertItem(1, _T("2017/5/12 21:18:21"));
	m_wndOrderList.SetItemText(1, 1, _T("AA000002"));
	m_wndOrderList.SetItemText(1, 2, _T("С��"));
	m_wndOrderList.SetItemText(1, 3, _T("΢��"));
	m_wndOrderList.SetItemText(1, 4, _T("δ֧��"));
	//======================================================================================================


	if (!m_wndMemberList.Create(dwStyle, rectEmpty, this, ID_LIST_MEMBER))
	{
		TRACE0("δ�ܴ�����Ա���\n");
		//return -1;      // δ�ܴ���
	}
	m_wndMemberList.InsertColumn(0, _T("����ʱ��"), 0, 150);

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


//void CPaymentTabs::OnSize(UINT nType, int cx, int cy)
//{
//	CMFCTabCtrl::OnSize(nType, cx, cy);
//	// TODO: �ڴ˴������Ϣ����������
//}
