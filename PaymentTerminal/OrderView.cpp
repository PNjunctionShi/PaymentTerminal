// OrderView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "OrderView.h"


// COrderView

IMPLEMENT_DYNCREATE(COrderView, CFormView)

COrderView::COrderView()
	: CFormView(IDD_ORDERVIEW)
{

}

COrderView::~COrderView()
{
}

void COrderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(COrderView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
END_MESSAGE_MAP()


// COrderView ���

#ifdef _DEBUG
void COrderView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void COrderView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// COrderView ��Ϣ�������


int COrderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	//m_wndBaseplate.Create(_T("СƱ"),
	if (m_wndShopNameStatic.Create(_T("�����˼�"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, 1) == 0 ||
		m_wndShopAddrStatic.Create(_T("�������������-186F"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, 1) == 0 ||
		m_wndDevider1Static.Create(_T("*******************"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndDevider2Static.Create(_T("*      ������     *"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndDevider3Static.Create(_T("*******************"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndOrderTimeStatic.Create(_T("2017/5/13 17:07:15"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndSeriesStatic.Create(_T("AA00000003"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndTotalStatic.Create(_T("�ϼƣ� ��1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndChargeStatic.Create(_T("֧������ȡ�� ��1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndChangeStatic.Create(_T("֧�������㣺 ��0.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndCashier.Create(_T("����Ա�� ϰ��ƽ"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndTelephone.Create(_T("��ϵ�绰��000-1234567"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0)
	{
		TRACE0("δ�ܴ���СƱ��ͷ\n");
		return -1;      // δ�ܴ���
	}

	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
	if (!m_wndCommodityList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("δ�ܴ�����Ʒ�б�\n");
		return -1;      // δ�ܴ���
	}
	//m_wndCommodityList.SetScrollInfo()
	m_wndCommodityList.InsertColumn(0, _T("���"), 0, 100);
	m_wndCommodityList.InsertColumn(1, _T("��Ʒ����"), 0, 100);
	m_wndCommodityList.InsertColumn(2, _T("����"), 0, 100);
	m_wndCommodityList.InsertColumn(3, _T("����"), 0, 100);
	m_wndCommodityList.InsertColumn(4, _T("С��"), 0, 100);

	//======================================================================================================
	m_wndCommodityList.InsertItem(0, _T("1"));
	m_wndCommodityList.SetItemText(0, 1, _T("�ǽ���"));
	m_wndCommodityList.SetItemText(0, 2, _T("15.00"));
	m_wndCommodityList.SetItemText(0, 3, _T("2.0"));
	m_wndCommodityList.SetItemText(0, 4, _T("30.00"));
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void COrderView::OnSize(UINT nType, int cx, int cy)
{
	CFormView::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(&rectClient);

	CRect rectHeader;
	rectHeader = rectClient;
	rectHeader.left += 20;
	rectHeader.right -= 20;
	rectHeader.bottom = 100;
	m_wndShopNameStatic.MoveWindow(rectHeader);


	rectClient.top += 100;
	rectClient.bottom -= 100;
	rectClient.left += 20;
	rectClient.right -= 20;
	m_wndCommodityList.MoveWindow(rectClient);
	// TODO: �ڴ˴������Ϣ����������
}


BOOL COrderView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int COrderView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	int nResult = 0;

	CFrameWnd* pParentFrame = GetParentFrame();

	if (pParentFrame == pDesktopWnd)
	{
		// When this is docked
		nResult = CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	else
	{
		// When this is not docked

		BOOL isMiniFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CMiniFrameWnd));
		BOOL isPaneFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CPaneFrameWnd));
		BOOL isMultiPaneFrameWnd = pDesktopWnd->IsKindOf(RUNTIME_CLASS(CMultiPaneFrameWnd));

		// pDesktopWnd is the frame window for CDockablePane

		nResult = CWnd::OnMouseActivate(pDesktopWnd, nHitTest, message);
		//return CFormView::OnMouseActivate(pDesktopWnd, nHitTest, message);
	}
	return nResult;
}
