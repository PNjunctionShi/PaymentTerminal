// OrderView.cpp : ʵ���ļ�
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
	if (!CDockablePane::Create(_T("����"), pParentWnd, CSize(100,100), TRUE, ID_ORDER_VIEW, WS_CHILD | WS_VISIBLE | CBRS_RIGHT | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, AFX_CBRS_REGULAR_TABS, AFX_DEFAULT_DOCKING_PANE_STYLE))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return FALSE;      // δ�ܴ���
	}
	EnableDocking(CBRS_ALIGN_ANY);
	((CFrameWndEx*)pParentWnd)->DockPane(this);
	return TRUE;
	
}

BEGIN_MESSAGE_MAP(COrderView, CDockablePane)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// COrderView ��Ϣ�������




void COrderView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()
	CMemDC memDC(dc, this);
	CDC* pDC = &memDC.GetDC();

	dc.GetClipBox(&m_rectCurrClip);

	//OnDraw(pDC);

	//if (memDC.IsMemDC())
	//{
	//	dc.ExcludeClipRect(m_rectWndArea);
	//}
}
