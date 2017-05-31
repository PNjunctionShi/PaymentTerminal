// OrderView.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "OrderView.h"
#include "MainFrm.h"
// COrderView

IMPLEMENT_DYNCREATE(COrderView, CFormView)

COrderView::COrderView()
	: CFormView(IDD_ORDERVIEW), 
	m_wndShopNameStatic(30,ALIGN::CENTER),
	m_wndShopAddrStatic(20, ALIGN::CENTER),
	m_wndDevider1Static(20, ALIGN::CENTER),
	m_wndDevider2Static(20, ALIGN::CENTER),
	m_wndOrderTimeStatic(20, ALIGN::LEFT),
	m_wndSeriesStatic(20, ALIGN::RIGHT),
	m_wndTotalStatic(25, ALIGN::LEFT),
	m_wndChargeStatic(20, ALIGN::LEFT),
	m_wndChangeStatic(20, ALIGN::LEFT),
	m_wndCashier(20, ALIGN::CENTER),
	m_wndTelephone(20, ALIGN::CENTER)
{
}

COrderView::~COrderView()
{
}

void COrderView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_STATIC_SHOPNAME, m_pMainFrame->m_strShopName);
	DDX_Text(pDX, IDC_STATIC_SHOPADDR, m_pMainFrame->m_strShopAddr);
	DDX_Text(pDX, IDC_STATIC_ORDERTIME, m_pMainFrame->m_pSelectedOrder->m_timOrderTime);
	DDX_Text(pDX, IDC_STATIC_CASHIER, m_pMainFrame->m_pSelectedOrder->m_strCashier);
	DDX_Text(pDX, IDC_STATIC_SERIES, m_pMainFrame->m_pSelectedOrder->m_strSeries);
	DDX_OrderTotal(pDX, IDC_STATIC_TOTAL, m_pMainFrame->m_pSelectedOrder);
	/*DDXEx_Text(pDX, IDC_STATIC_TOTAL, m_pMainFrame->m_pSelectedOrder->m_dTotal,_T("总计: ￥%.2f"));*/
	CString tmp;
	if (m_pMainFrame->m_pSelectedOrder->m_ePayType == 1)
		tmp = _T("现金");
	if (m_pMainFrame->m_pSelectedOrder->m_ePayType == 2)
		tmp = _T("微信");
	if (m_pMainFrame->m_pSelectedOrder->m_ePayType == 3)
		tmp = _T("支付宝");
	DDXEx_Text(pDX, IDC_STATIC_CHARGE, m_pMainFrame->m_pSelectedOrder->m_dCharge, tmp + _T("收银: ￥%.2f"));
	DDXEx_Text(pDX, IDC_STATIC_CHANGE, m_pMainFrame->m_pSelectedOrder->m_dChange, tmp + _T("找零: ￥%.2f"));
	DDX_Text(pDX, IDC_STATIC_TELEPHONE, m_pMainFrame->m_strTelephone);

	if (!pDX->m_bSaveAndValidate)
		ReCalcLayout();

}

BEGIN_MESSAGE_MAP(COrderView, CFormView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEACTIVATE()
	ON_WM_ERASEBKGND()
	ON_NOTIFY(LVN_GETDISPINFO, ID_LIST_COMMODITY, &COrderView::OnLvnGetdispinfo)
	ON_NOTIFY(LVN_ITEMCHANGED, ID_LIST_COMMODITY, &COrderView::OnLvnItemchanged)
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
	if (m_wndShopNameStatic.Create(_T("天上人间"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this,IDC_STATIC_SHOPNAME) == 0 ||
		m_wndShopAddrStatic.Create(_T("天鹅座，开普勒-186F，东经253度北纬46度，伽利略区，星际大道，4259号"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, IDC_STATIC_SHOPADDR) == 0 ||
		m_wndDevider1Static.Create(_T("*******************\n*      结账联     *\n*******************"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, IDC_STATIC_DEVIDER1) == 0 ||
		m_wndDevider2Static.Create(_T("------------------"), WS_CHILD | WS_VISIBLE | SS_CENTER | SS_CENTERIMAGE, rectEmpty, this, IDC_STATIC_DEVIDER2) == 0 ||
		m_wndOrderTimeStatic.Create(_T("2017/5/13 17:07:15"), WS_CHILD | WS_VISIBLE|SS_LEFT, rectEmpty, this, IDC_STATIC_ORDERTIME) == 0 ||
		m_wndSeriesStatic.Create(_T("AA00000003"), WS_CHILD | WS_VISIBLE|SS_RIGHT, rectEmpty, this, IDC_STATIC_ORDERSERIES) == 0 ||
		m_wndTotalStatic.Create(_T("合计： ￥1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, IDC_STATIC_TOTAL) == 0 ||
		m_wndChargeStatic.Create(_T("支付宝收取： ￥1000000.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, IDC_STATIC_CHARGE) == 0 ||
		m_wndChangeStatic.Create(_T("支付宝找零： ￥0.00"), WS_CHILD | WS_VISIBLE, rectEmpty, this, IDC_STATIC_CHANGE) == 0 ||
		m_wndCashier.Create(_T("收银员： 习近平"), WS_CHILD | WS_VISIBLE|SS_CENTER, rectEmpty, this, IDC_STATIC_CASHIER) == 0 ||
		m_wndTelephone.Create(_T("联系电话：000-1234567"), WS_CHILD | WS_VISIBLE, rectEmpty, this, IDC_STATIC_TELEPHONE) == 0)
	{
		TRACE0("未能创建小票表头\n");
		return -1;      // 未能创建
	}

	const DWORD dwStyle = WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | LVS_SINGLESEL | LVS_OWNERDATA;
	if (!m_wndCommodityList.Create(dwStyle, rectEmpty, this, ID_LIST_COMMODITY))
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
	//m_wndCommodityList.InsertItem(0, _T("1"));
	//m_wndCommodityList.SetItemText(0, 1, _T("盖浇饭"));
	//m_wndCommodityList.SetItemText(0, 2, _T("15.00"));
	//m_wndCommodityList.SetItemText(0, 3, _T("2.0"));
	//m_wndCommodityList.SetItemText(0, 4, _T("30.00"));
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void COrderView::OnSize(UINT nType, int cx, int cy)
{
	//CFormView::OnSize(nType, cx, cy);
	ReCalcLayout();
	Invalidate();
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

void COrderView::ReCalcLayout()
{
	CSize sizeScroll;
	GetScrollBarSizes(sizeScroll);
	CRect rectClient;
	GetClientRect(rectClient);

	CPoint ptScroll;
	if (m_nMapMode)
		ptScroll = GetScrollPosition();
	else
		ptScroll = CPoint(0, 0);

	if (rectClient.Width()<m_nMinWidth)
	{
		sizeScroll.cx = m_nMinWidth;
	}
	else if (rectClient.Width() >= m_nMinWidth)
	{
		sizeScroll.cx = rectClient.Width();
	}
	sizeScroll.cy = 0;

	int margin = 30;
	int nReceiptWidth = sizeScroll.cx-margin*2;
	int nShopNameHeight = m_wndShopNameStatic.CalcHeight(nReceiptWidth);
	
	int Xoffset = margin- ptScroll.x;
	int Yoffset = margin- ptScroll.y;
	
	m_wndShopNameStatic.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nShopNameHeight, TRUE);

	Yoffset += nShopNameHeight + 7;
	int nShopAddrHeight = m_wndShopAddrStatic.CalcHeight(nReceiptWidth);
	m_wndShopAddrStatic.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nShopAddrHeight, TRUE);

	Yoffset += nShopAddrHeight + 7;
	int nDevider1Height = m_wndDevider1Static.FitDevider3(nReceiptWidth, '*', _T("结账联"));
	m_wndDevider1Static.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nDevider1Height, TRUE);

	Yoffset += nDevider1Height + 10;
	int nOrderTimeWidth = nReceiptWidth / 3+40;
	int nOrderTimeHeight = m_wndOrderTimeStatic.CalcHeight(nOrderTimeWidth);
	m_wndOrderTimeStatic.MoveWindow(Xoffset, Yoffset, nOrderTimeWidth, nOrderTimeHeight, TRUE);

	Xoffset += nOrderTimeWidth;
	int nCashierWidth = nReceiptWidth / 3;
	int nCashierHeight = m_wndCashier.CalcHeight(nCashierWidth);
	m_wndCashier.MoveWindow(Xoffset, Yoffset, nCashierWidth, nCashierHeight, TRUE);

	Xoffset += nCashierWidth;
	int nSeriesWidth = nReceiptWidth / 3-40;
	int nSeriesHeight = m_wndSeriesStatic.CalcHeight(nSeriesWidth);
	m_wndSeriesStatic.MoveWindow(Xoffset, Yoffset, nSeriesWidth, nSeriesHeight, TRUE);

	Yoffset += max(nOrderTimeHeight, max(nCashierHeight, nSeriesHeight))+7;
	Xoffset = margin - ptScroll.x;
	int nCommodityListHeight=m_wndCommodityList.CalcHeight();
	m_wndCommodityList.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nCommodityListHeight, TRUE);

	Yoffset += nCommodityListHeight+10;
	int nTotalHeight = m_wndTotalStatic.CalcHeight(nReceiptWidth);
	m_wndTotalStatic.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nTotalHeight, TRUE);

	Yoffset += nTotalHeight+10;
	int nChargeHeight = m_wndChargeStatic.CalcHeight(nReceiptWidth);
	m_wndChargeStatic.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nChargeHeight, TRUE);

	Yoffset += nChargeHeight+7;
	int nChangeHeight = m_wndChangeStatic.CalcHeight(nReceiptWidth);
	m_wndChangeStatic.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nChangeHeight, TRUE);

	Yoffset += nChangeHeight+7;
	int nDevider2Height = m_wndDevider2Static.FitDevider1(nReceiptWidth, '-');
	m_wndDevider2Static.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nDevider2Height, TRUE);

	Yoffset += nDevider2Height;
	int nTelephoneHeight = m_wndTelephone.CalcHeight(nReceiptWidth);
	m_wndTelephone.MoveWindow(Xoffset, Yoffset, nReceiptWidth, nTelephoneHeight, TRUE);
	
	Yoffset += nTelephoneHeight;

	sizeScroll.cy = Yoffset+margin + ptScroll.y;
	SetScrollSizes(MM_TEXT, sizeScroll);


	m_rectOutline.left = 10;
	m_rectOutline.top = 10;
	m_rectOutline.right = sizeScroll.cx - 10;
	m_rectOutline.bottom = sizeScroll.cy - 10;
}

void COrderView::OnDraw(CDC* pDC)
{
	// TODO: 在此添加专用代码和/或调用基类

	CBrush brushBack(RGB(100, 100, 100));
	CBrush brushFore(RGB(255, 255, 255));
	CPen penOutline(PS_SOLID, 1, RGB(0, 0, 0));
	//Invalidate();
	CRect rectClient;
	GetClientRect(rectClient);

	CPoint ptScroll = GetScrollPosition();
	rectClient.OffsetRect(ptScroll);
	pDC->FillRect(rectClient, &brushBack);
	pDC->SelectObject(&penOutline);
	pDC->SelectObject(&brushFore);
	pDC->Rectangle(m_rectOutline);
}



BOOL COrderView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return TRUE;
	/*return CFormView::OnEraseBkgnd(pDC);*/
}

extern void AFXAPI AfxTextFloatFormat(CDataExchange* pDX, int nIDC,
	void* pData, double value, int nSizeGcvt);

void COrderView::DDXEx_Text(CDataExchange *pDX, int nIDC, double &value, LPCTSTR lpszFormat)
{
	if (pDX->m_bSaveAndValidate) {
		AfxTextFloatFormat(pDX, nIDC, &value, value, DBL_DIG);
	}
	else {
		HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
		
		CString str;
		str.Format(lpszFormat, value);
		::SetWindowText(hWndCtrl, str);
	}
}


void COrderView::DDX_OrderTotal(CDataExchange *pDX, int nIDC, COrder* pOrder)
{
	HWND hWndCtrl = pDX->PrepareEditCtrl(nIDC);
	if (pDX->m_bSaveAndValidate) {
	}
	else {
		CString str;
		str.Format(_T("总计: ￥%.2f"), pOrder->GetTotal());
		if (pOrder->m_bCustomedTotal)
			str = str + _T(" *");
		::SetWindowText(hWndCtrl, str);
	}
}

void COrderView::OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult)
{

	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if (pDispInfo->item.mask & LVIF_COLUMNS){}
	if (pDispInfo->item.mask & LVIF_DI_SETITEM){}
	if (pDispInfo->item.mask & LVIF_GROUPID){}
	if (pDispInfo->item.mask & LVIF_IMAGE){}
	if (pDispInfo->item.mask & LVIF_INDENT){}
	if (pDispInfo->item.mask & LVIF_NORECOMPUTE){}
	if (pDispInfo->item.mask & LVIF_PARAM){}
	if (pDispInfo->item.mask & LVIF_STATE){}
	if (pDispInfo->item.mask & LVIF_TEXT)
	{
		int iIndex= pDispInfo->item.iItem;
		POSITION pos= m_pMainFrame->m_pSelectedOrder->m_listCommodity.FindIndex(iIndex);
		CCommodity* p_com = m_pMainFrame->m_pSelectedOrder->m_listCommodity.GetAt(pos);
		CString tmp;
		switch (pDispInfo->item.iSubItem)
		{
		case 0:
			tmp.Format(_T("%d"), iIndex);
			lstrcpy(pDispInfo->item.pszText, tmp);
			break;
		case 1:
			lstrcpy(pDispInfo->item.pszText, p_com->m_strName);
			break;
		case 2:
			tmp.Format(_T("%.2f"), p_com->m_dPrice);
			lstrcpy(pDispInfo->item.pszText, tmp);
			break;
		case 3:
			tmp.Format(_T("%.2f"), p_com->m_dQuantity);
			lstrcpy(pDispInfo->item.pszText, tmp);
			break;
		case 4:
			tmp.Format(_T("%.2f"), p_com->GetSubtotal());
			lstrcpy(pDispInfo->item.pszText, tmp);
			break;
		}
	}
	*pResult = 0;
}


void COrderView::OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	if ((pNMLV->uNewState & LVIS_FOCUSED) == LVIS_FOCUSED &&
		(pNMLV->uOldState & LVIS_FOCUSED) == 0)
	{
		int iIndex=pNMLV->iItem;
		POSITION pos = m_pMainFrame->m_pSelectedOrder->m_listCommodity.FindIndex(iIndex);
		m_pMainFrame->m_pSelectedCommodity = m_pMainFrame->m_pSelectedOrder->m_listCommodity.GetAt(pos);
		m_pMainFrame->m_wndRibbonBar.UpdateData(FALSE);
	}
	*pResult = 0;
}