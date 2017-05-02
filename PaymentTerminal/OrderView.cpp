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
END_MESSAGE_MAP()



// COrderView 消息处理程序


