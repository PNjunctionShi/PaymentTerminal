// OrderView.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "OrderView.h"


// COrderView

IMPLEMENT_DYNAMIC(COrderView, CDockablePane)

COrderView::COrderView()
{

}

COrderView::~COrderView()
{
}

BOOL COrderView::Create(CWnd* pParentWnd)
{
	if (!CDockablePane::Create(_T("订单"), pParentWnd, CSize(100,100), TRUE, ID_ORDER_VIEW, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, AFX_CBRS_REGULAR_TABS, AFX_DEFAULT_DOCKING_PANE_STYLE))
	{
		TRACE0("未能创建状态栏\n");
		return FALSE;      // 未能创建
	}
	EnableDocking(CBRS_ALIGN_ANY);
	((CFrameWndEx*)pParentWnd)->DockPane(this);
	return TRUE;
	
}

BEGIN_MESSAGE_MAP(COrderView, CDockablePane)
	//ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COrderView 消息处理程序




//void COrderView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: 在此处添加消息处理程序代码
//					   // 不为绘图消息调用 CDockablePane::OnPaint()
//	CMemDC memDC(dc, this);
//	CDC* pDC = &memDC.GetDC();
//
//	dc.GetClipBox(&m_rectCurrClip);
//
//	//OnDraw(pDC);
//
//	//if (memDC.IsMemDC())
//	//{
//	//	dc.ExcludeClipRect(m_rectWndArea);
//	//}
//}


int COrderView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectEmpty;
	rectEmpty.SetRectEmpty();

	if (m_wndShopNameStatic.Create(_T("天上人间"),WS_CHILD|WS_VISIBLE, rectEmpty,this,1)==0 ||
		m_wndShopAddrStatic.Create(_T("天鹅座，开普勒-186F"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 || 
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
	CDockablePane::OnSize(nType, cx, cy);
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
