// OrderDockPane.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "OrderDockPane.h"


// COrderDockPane

IMPLEMENT_DYNCREATE(COrderDockPane, CDockablePane)

COrderDockPane::COrderDockPane()
{
	m_pBaseplate = (COrderView*)(RUNTIME_CLASS(COrderView)->CreateObject());
}

COrderDockPane::~COrderDockPane()
{
}

BOOL COrderDockPane::Create(CWnd* pParentWnd)
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

BEGIN_MESSAGE_MAP(COrderDockPane, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COrderDockPane 消息处理程序


int COrderDockPane::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;
	CRect rectDummy;
	rectDummy.SetRectEmpty();
	m_pBaseplate->Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rectDummy, this, IDD_ORDERVIEW, NULL);
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void COrderDockPane::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(rectClient);
	m_pBaseplate->MoveWindow(rectClient);
	// TODO: 在此处添加消息处理程序代码
}
