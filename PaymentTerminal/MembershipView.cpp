// MembershipView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "MembershipView.h"


// CMembershipView

IMPLEMENT_DYNCREATE(CMembershipView, CDockablePane)

CMembershipView::CMembershipView()
{

}

CMembershipView::~CMembershipView()
{
}

BOOL CMembershipView::Create(CWnd* pParentWnd)
{
	if (!CDockablePane::Create(_T("��Ա"), pParentWnd, CSize(100, 100), TRUE, ID_MEMBERSHIP_VIEW, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, AFX_CBRS_REGULAR_TABS, AFX_DEFAULT_DOCKING_PANE_STYLE))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return FALSE;      // δ�ܴ���
	}
	EnableDocking(CBRS_ALIGN_ANY);
	((CFrameWndEx*)pParentWnd)->DockPane(this);
	return TRUE;

}

BEGIN_MESSAGE_MAP(CMembershipView, CDockablePane)
END_MESSAGE_MAP()



// CMembershipView ��Ϣ�������


