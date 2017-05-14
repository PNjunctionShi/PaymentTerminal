// OrderView.cpp : 实现文件
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


// COrderView 诊断

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


// COrderView 消息处理程序


int COrderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	//m_wndBaseplate.Create(_T("小票"),
	if (m_wndShopNameStatic.Create(_T("天上人间"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, 1) == 0 ||
		m_wndShopAddrStatic.Create(_T("天鹅座，开普勒-186F"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, 1) == 0 ||
		m_wndDevider1Static.Create(_T("*******************"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndDevider2Static.Create(_T("*      结账联     *"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndDevider3Static.Create(_T("*******************"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndOrderTimeStatic.Create(_T("2017/5/13 17:07:15"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndSeriesStatic.Create(_T("AA00000003"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndTotalStatic.Create(_T("合计： ￥1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndChargeStatic.Create(_T("支付宝收取： ￥1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndChangeStatic.Create(_T("支付宝找零： ￥0.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndCashier.Create(_T("收银员： 习近平"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 ||
		m_wndTelephone.Create(_T("联系电话：000-1234567"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0)
	{
		TRACE0("未能创建小票表头\n");
		return -1;      // 未能创建
	}

	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL;
	if (!m_wndCommodityList.Create(dwStyle, rectEmpty, this, ID_LIST_ORDER))
	{
		TRACE0("未能创建商品列表\n");
		return -1;      // 未能创建
	}
	//m_wndCommodityList.SetScrollInfo()
	m_wndCommodityList.InsertColumn(0, _T("序号"), 0, 100);
	m_wndCommodityList.InsertColumn(1, _T("商品名称"), 0, 100);
	m_wndCommodityList.InsertColumn(2, _T("单价"), 0, 100);
	m_wndCommodityList.InsertColumn(3, _T("数量"), 0, 100);
	m_wndCommodityList.InsertColumn(4, _T("小计"), 0, 100);

	//======================================================================================================
	m_wndCommodityList.InsertItem(0, _T("1"));
	m_wndCommodityList.SetItemText(0, 1, _T("盖浇饭"));
	m_wndCommodityList.SetItemText(0, 2, _T("15.00"));
	m_wndCommodityList.SetItemText(0, 3, _T("2.0"));
	m_wndCommodityList.SetItemText(0, 4, _T("30.00"));
	// TODO:  在此添加您专用的创建代码

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
	// TODO: 在此处添加消息处理程序代码
}


BOOL COrderView::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext)
{
	// TODO: 在此添加专用代码和/或调用基类

	return CFormView::Create(lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, pContext);
}


int COrderView::OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
