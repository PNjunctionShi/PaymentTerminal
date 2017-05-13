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
	//ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// COrderView ��Ϣ�������




//void COrderView::OnPaint()
//{
//	CPaintDC dc(this); // device context for painting
//					   // TODO: �ڴ˴������Ϣ����������
//					   // ��Ϊ��ͼ��Ϣ���� CDockablePane::OnPaint()
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

	if (m_wndShopNameStatic.Create(_T("�����˼�"),WS_CHILD|WS_VISIBLE, rectEmpty,this,1)==0 ||
		m_wndShopAddrStatic.Create(_T("�������������-186F"), WS_CHILD | WS_VISIBLE, rectEmpty, this, 1) == 0 || 
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
	// TODO: �ڴ˴������Ϣ����������
}
