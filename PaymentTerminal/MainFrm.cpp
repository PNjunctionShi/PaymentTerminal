// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.cpp : CMainFrame 类的实现
//

#include "stdafx.h"
#include "PaymentTerminal.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWndEx)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWndEx)
	ON_WM_CREATE()
	ON_COMMAND_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnApplicationLook)
	ON_UPDATE_COMMAND_UI_RANGE(ID_VIEW_APPLOOK_WIN_2000, ID_VIEW_APPLOOK_WINDOWS_7, &CMainFrame::OnUpdateApplicationLook)
	ON_COMMAND(ID_VIEW_CAPTION_BAR, &CMainFrame::OnViewCaptionBar)
	ON_UPDATE_COMMAND_UI(ID_VIEW_CAPTION_BAR, &CMainFrame::OnUpdateViewCaptionBar)
	ON_COMMAND(ID_TOOLS_OPTIONS, &CMainFrame::OnOptions)
	ON_COMMAND(ID_FILE_PRINT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CMainFrame::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnFilePrintPreview)
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT_PREVIEW, &CMainFrame::OnUpdateFilePrintPreview)
	ON_COMMAND(ID_Order, &CMainFrame::OnOrder)
	ON_UPDATE_COMMAND_UI(ID_Order, &CMainFrame::OnUpdateOrder)
	ON_COMMAND(ID_Coupon, &CMainFrame::OnCoupon)
	ON_UPDATE_COMMAND_UI(ID_Coupon, &CMainFrame::OnUpdateCoupon)
	ON_COMMAND(ID_Membership, &CMainFrame::OnMembership)
	ON_UPDATE_COMMAND_UI(ID_Membership, &CMainFrame::OnUpdateMembership)
	ON_COMMAND(ID_NEW_ORDER, &CMainFrame::OnNewOrder)
	ON_COMMAND(ID_NEW_COMMODITY, &CMainFrame::OnNewCommodity)
	ON_COMMAND(ID_COMMODITY_NAME, &CMainFrame::OnCommodityName)
	ON_COMMAND(ID_COMMODITY_PRICE, &CMainFrame::OnCommodityPrice)
	ON_COMMAND(ID_COMMODITY_QUANTITY, &CMainFrame::OnCommodityQuantity)
	ON_COMMAND(ID_TOTAL, &CMainFrame::OnTotal)
	ON_COMMAND(ID_DELETE_COMMODITY, &CMainFrame::OnDeleteCommodity)
	ON_UPDATE_COMMAND_UI(ID_DELETE_COMMODITY, &CMainFrame::OnUpdateDeleteCommodity)
END_MESSAGE_MAP()

// CMainFrame 构造/析构

CMainFrame::CMainFrame():m_Operator(_T("喜羊羊"),COperator::OperatorType::Cashier)
{
	// TODO: 在此添加成员初始化代码
	m_strShopName = _T("牛逼店铺");
	m_strShopAddr = _T("牛逼店的地址");
	m_strTelephone = _T("021-1234567");
	m_pOrderDockPane = (COrderDockPane*)RUNTIME_CLASS(COrderDockPane)->CreateObject();
	m_pOrderDockPane->m_pBaseplate->m_pMainFrame = this;
	m_pMembershipView = (CMembershipView*)RUNTIME_CLASS(CMembershipView)->CreateObject();
	m_pCouponView = (CCouponView*)RUNTIME_CLASS(CCouponView)->CreateObject();
	m_pSelectedOrder = (COrder*)RUNTIME_CLASS(COrder)->CreateObject();
	m_pSelectedCommodity = NULL;
	theApp.m_nAppLook = theApp.GetInt(_T("ApplicationLook"), ID_VIEW_APPLOOK_OFF_2007_BLUE);
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWndEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	BOOL bNameValid;

	m_wndRibbonBar.Create(this);
	m_wndRibbonBar.LoadFromResource(IDR_RIBBON);

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("未能创建状态栏\n");
		return -1;      // 未能创建
	}

	if (!m_pOrderDockPane->Create(this))
	{
		TRACE0("未能创建订单视图\n");
		return -1;      // 未能创建
	}

	if (!m_pMembershipView->Create(this))
	{
		TRACE0("未能创建会员视图\n");
		return -1;      // 未能创建
	}

	if (!m_pCouponView->Create(this))
	{
		TRACE0("未能创建卡券视图\n");
		return -1;      // 未能创建
	}

	CDockablePane* pTabbedBar = NULL;
	m_pMembershipView->AttachToTabWnd(m_pOrderDockPane, DM_SHOW, TRUE, &pTabbedBar);
	m_pCouponView->AttachToTabWnd(m_pOrderDockPane, DM_SHOW, TRUE, &pTabbedBar);
	CString strTitlePane1;
	CString strTitlePane2;
	bNameValid = strTitlePane1.LoadString(IDS_STATUS_PANE1);
	ASSERT(bNameValid);
	bNameValid = strTitlePane2.LoadString(IDS_STATUS_PANE2);
	ASSERT(bNameValid);
	m_wndStatusBar.AddElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE1, strTitlePane1, TRUE), strTitlePane1);
	m_wndStatusBar.AddExtendedElement(new CMFCRibbonStatusBarPane(ID_STATUSBAR_PANE2, strTitlePane2, TRUE), strTitlePane2);

	// 启用 Visual Studio 2005 样式停靠窗口行为
	CDockingManager::SetDockingMode(DT_SMART);
	// 启用 Visual Studio 2005 样式停靠窗口自动隐藏行为
	EnableAutoHidePanes(CBRS_ALIGN_ANY);

	// 创建标题栏: 
	if (!CreateCaptionBar())
	{
		TRACE0("未能创建标题栏\n");
		return -1;      // 未能创建
	}
	// 基于持久值设置视觉管理器和样式
	OnApplicationLook(theApp.m_nAppLook);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWndEx::PreCreateWindow(cs) )
		return FALSE;
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return TRUE;
}

BOOL CMainFrame::CreateCaptionBar()
{
	if (!m_wndCaptionBar.Create(WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS, this, ID_VIEW_CAPTION_BAR, -1, TRUE))
	{
		TRACE0("未能创建标题栏\n");
		return FALSE;
	}

	BOOL bNameValid;

	CString strTemp, strTemp2;
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButton(strTemp, ID_TOOLS_OPTIONS, CMFCCaptionBar::ALIGN_LEFT, FALSE);
	bNameValid = strTemp.LoadString(IDS_CAPTION_BUTTON_TIP);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetButtonToolTip(strTemp);

	bNameValid = strTemp.LoadString(IDS_CAPTION_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetText(strTemp, CMFCCaptionBar::ALIGN_LEFT);

	m_wndCaptionBar.SetBitmap(IDB_INFO, RGB(255, 255, 255), FALSE, CMFCCaptionBar::ALIGN_LEFT);
	bNameValid = strTemp.LoadString(IDS_CAPTION_IMAGE_TIP);
	ASSERT(bNameValid);
	bNameValid = strTemp2.LoadString(IDS_CAPTION_IMAGE_TEXT);
	ASSERT(bNameValid);
	m_wndCaptionBar.SetImageToolTip(strTemp, strTemp2);

	return TRUE;
}

// CMainFrame 诊断

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWndEx::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWndEx::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 消息处理程序

void CMainFrame::OnApplicationLook(UINT id)
{
	CWaitCursor wait;

	theApp.m_nAppLook = id;

	switch (theApp.m_nAppLook)
	{
	case ID_VIEW_APPLOOK_WIN_2000:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManager));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_XP:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOfficeXP));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WIN_XP:
		CMFCVisualManagerWindows::m_b3DTabsXPTheme = TRUE;
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_OFF_2003:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2003));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2005:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2005));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_VS_2008:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerVS2008));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
		break;

	case ID_VIEW_APPLOOK_WINDOWS_7:
		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows7));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(TRUE);
		break;

	default:
		switch (theApp.m_nAppLook)
		{
		case ID_VIEW_APPLOOK_OFF_2007_BLUE:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_BLACK:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_ObsidianBlack);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_SILVER:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Silver);
			break;

		case ID_VIEW_APPLOOK_OFF_2007_AQUA:
			CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_Aqua);
			break;
		}

		CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
		CDockingManager::SetDockingMode(DT_SMART);
		m_wndRibbonBar.SetWindows7Look(FALSE);
	}

	RedrawWindow(NULL, NULL, RDW_ALLCHILDREN | RDW_INVALIDATE | RDW_UPDATENOW | RDW_FRAME | RDW_ERASE);

	theApp.WriteInt(_T("ApplicationLook"), theApp.m_nAppLook);
}

void CMainFrame::OnUpdateApplicationLook(CCmdUI* pCmdUI)
{
	pCmdUI->SetRadio(theApp.m_nAppLook == pCmdUI->m_nID);
}

void CMainFrame::OnViewCaptionBar()
{
	m_wndCaptionBar.ShowWindow(m_wndCaptionBar.IsVisible() ? SW_HIDE : SW_SHOW);
	RecalcLayout(FALSE);
}

void CMainFrame::OnUpdateViewCaptionBar(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(m_wndCaptionBar.IsVisible());
}

void CMainFrame::OnOptions()
{
	CMFCRibbonCustomizeDialog *pOptionsDlg = new CMFCRibbonCustomizeDialog(this, &m_wndRibbonBar);
	ASSERT(pOptionsDlg != NULL);

	pOptionsDlg->DoModal();
	delete pOptionsDlg;
}


void CMainFrame::OnFilePrint()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_PRINT);
	}
}

void CMainFrame::OnFilePrintPreview()
{
	if (IsPrintPreview())
	{
		PostMessage(WM_COMMAND, AFX_ID_PREVIEW_CLOSE);  // 强制关闭“打印预览”模式
	}
}

void CMainFrame::OnUpdateFilePrintPreview(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(IsPrintPreview());
}


void CMainFrame::OnOrder()
{
	m_pOrderDockPane->ShowPane(m_pOrderDockPane->IsVisible()?FALSE:TRUE, FALSE, TRUE);
	RecalcLayout(FALSE);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateOrder(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_pOrderDockPane->IsVisible());
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnCoupon()
{
	m_pCouponView->ShowPane(m_pCouponView->IsVisible() ? FALSE : TRUE, FALSE, TRUE);
	RecalcLayout(FALSE);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateCoupon(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_pCouponView->IsVisible());
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnMembership()
{
	m_pMembershipView->ShowPane(m_pMembershipView->IsVisible() ? FALSE : TRUE, FALSE, TRUE);
	RecalcLayout(FALSE);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateMembership(CCmdUI *pCmdUI)
{
	pCmdUI->SetCheck(m_pMembershipView->IsVisible());
	// TODO: 在此添加命令更新用户界面处理程序代码
}


void CMainFrame::OnNewOrder()
{
	if (!(m_pSelectedOrder->m_bArchived))
		delete m_pSelectedOrder;
	m_pSelectedOrder = (COrder*)(RUNTIME_CLASS(COrder)->CreateObject());
	m_pSelectedOrder->m_timOrderTime = COleDateTime::GetCurrentTime();
	m_pSelectedOrder->m_strSeries = GenerateSeries();
	m_pSelectedOrder->m_strCashier = m_Operator.m_strName;
	m_pSelectedOrder->m_ePayType = EPaymentType::Cash;
	m_pSelectedOrder->m_eOrderStatus = EOrderStatus::UNPAIED;
	m_pSelectedOrder->m_timPayTime = time(NULL);
	m_pSelectedOrder->m_listCommodity.RemoveAll();
	m_pSelectedOrder->m_dTotal = 0.00;
	m_pSelectedOrder->m_dCharge = 0;
	m_pSelectedOrder->m_dChange = 0;
	m_pOrderDockPane->m_pBaseplate->m_wndCommodityList.SetItemCount((int)(m_pSelectedOrder->m_listCommodity.GetCount()));
	m_wndRibbonBar.ShowContextCategories(ID_CNTX_ORDER,TRUE);
	m_wndRibbonBar.ActivateContextCategory(ID_CNTX_ORDER);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
	m_pOrderDockPane->m_pBaseplate->ReCalcLayout();
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	m_wndRibbonBar.UpdateData(FALSE);
	// TODO: 在此添加命令处理程序代码
}


CString CMainFrame::GenerateSeries()
{
	COleDateTime now = COleDateTime::GetCurrentTime();
	if (now.GetYear() == m_timeLasttime.GetYear() &&
		now.GetMonth() == m_timeLasttime.GetMonth() &&
		now.GetDay() == m_timeLasttime.GetDay())
	{
		m_nSubSeries++;
	}
	else
	{
		m_timeLasttime = now;
		m_nSubSeries = 0;
	}
	CString strSubSeries;
	strSubSeries.Format(_T("%04d"), m_nSubSeries);
	CString strDate = now.Format(_T("%y%m%d"));
	return strDate+ strSubSeries;
}


void CMainFrame::OnNewCommodity()
{
	m_pSelectedCommodity = (CCommodity*)(RUNTIME_CLASS(CCommodity)->CreateObject());
	ASSERT(m_pSelectedOrder);
	m_pSelectedOrder->m_listCommodity.AddTail(m_pSelectedCommodity);

	m_pSelectedOrder->GetTotal();
	m_wndRibbonBar.ShowContextCategories(ID_CNTX_COMMODITY, TRUE);
	m_wndRibbonBar.ActivateContextCategory(ID_CNTX_COMMODITY);
	m_wndRibbonBar.UpdateData(FALSE);

	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->m_wndCommodityList.SetItemCount((int)(m_pSelectedOrder->m_listCommodity.GetCount()));
	m_pOrderDockPane->m_pBaseplate->ReCalcLayout();
	int iIndex = m_pOrderDockPane->m_pBaseplate->m_wndCommodityList.GetItemCount()-1;
	m_pOrderDockPane->m_pBaseplate->m_wndCommodityList.SetItemState(iIndex, LVNI_FOCUSED | LVIS_SELECTED, LVNI_FOCUSED | LVIS_SELECTED);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);

	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnCommodityName()
{
	m_wndRibbonBar.UpdateData(TRUE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnCommodityPrice()
{
	m_wndRibbonBar.UpdateData(TRUE);
	m_pSelectedOrder->GetTotal();
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnCommodityQuantity()
{
	m_wndRibbonBar.UpdateData(TRUE);
	m_pSelectedOrder->GetTotal();
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnTotal()
{
	m_pSelectedOrder->m_bCustomedTotal = TRUE;
	m_wndRibbonBar.UpdateData(TRUE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
	m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
	m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnDeleteCommodity()
{
	if (m_pSelectedCommodity != NULL)
	{
		POSITION pos = m_pSelectedOrder->m_listCommodity.Find(m_pSelectedCommodity);
		delete m_pSelectedCommodity;
		POSITION pos_back = pos;
		m_pSelectedOrder->m_listCommodity.GetNext(pos);
		if (pos == NULL)
		{
			pos = pos_back;
			m_pSelectedOrder->m_listCommodity.GetPrev(pos);
			if (pos == NULL)
			{
				m_pSelectedCommodity = NULL;
			}
			else
			{
				m_pSelectedCommodity = m_pSelectedOrder->m_listCommodity.GetPrev(pos);
			}
		}
		else
		{
			m_pSelectedCommodity = m_pSelectedOrder->m_listCommodity.GetNext(pos);
		}
		m_pSelectedOrder->m_listCommodity.RemoveAt(pos_back);
		m_pSelectedOrder->GetTotal();
		m_wndRibbonBar.UpdateData(FALSE);
		m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_HIDE);
		m_pOrderDockPane->m_pBaseplate->m_wndCommodityList.SetItemCount((int)(m_pSelectedOrder->m_listCommodity.GetCount()));
		m_pOrderDockPane->m_pBaseplate->ReCalcLayout();
		m_pOrderDockPane->m_pBaseplate->UpdateData(FALSE);
		m_pOrderDockPane->m_pBaseplate->ShowWindow(SW_SHOW);
	
	}
	// TODO: 在此添加命令处理程序代码
}


void CMainFrame::OnUpdateDeleteCommodity(CCmdUI *pCmdUI)
{
	BOOL enableDelete;
	if (m_pSelectedCommodity == NULL)
	{
		enableDelete = FALSE;
	}
	else
	{
		enableDelete = TRUE;
	}
	pCmdUI->Enable(enableDelete);
	// TODO: 在此添加命令更新用户界面处理程序代码
}
