// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// PaymentTerminalView.cpp : CPaymentTerminalView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "PaymentTerminal.h"
#endif

#include "PaymentTerminalDoc.h"
#include "PaymentTerminalView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPaymentTerminalView

IMPLEMENT_DYNCREATE(CPaymentTerminalView, CView)

BEGIN_MESSAGE_MAP(CPaymentTerminalView, CView)
	// ��׼��ӡ����
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPaymentTerminalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPaymentTerminalView ����/����

CPaymentTerminalView::CPaymentTerminalView()
{
	// TODO: �ڴ˴���ӹ������

}

CPaymentTerminalView::~CPaymentTerminalView()
{
}

BOOL CPaymentTerminalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CPaymentTerminalView ����

void CPaymentTerminalView::OnDraw(CDC* /*pDC*/)
{
	CPaymentTerminalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);


	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CPaymentTerminalView ��ӡ


void CPaymentTerminalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPaymentTerminalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CPaymentTerminalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CPaymentTerminalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CPaymentTerminalView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPaymentTerminalView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPaymentTerminalView ���

#ifdef _DEBUG
void CPaymentTerminalView::AssertValid() const
{
	CView::AssertValid();
}

void CPaymentTerminalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaymentTerminalDoc* CPaymentTerminalView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaymentTerminalDoc)));
	return (CPaymentTerminalDoc*)m_pDocument;
}

int CPaymentTerminalView::OnCreate(LPCREATESTRUCT lpcs)
{
	if (CView::OnCreate(lpcs) == -1)
		return -1;

	CRect rectEmpty;
	rectEmpty.SetRectEmpty();
	// ����ѡ�����: 
	if (!m_wndTabs.Create(CMFCTabCtrl::STYLE_3D_VS2005, rectEmpty, this, 1))
	{
		TRACE0("δ�ܴ������ѡ�����\n");
		return -1;      // δ�ܴ���
	}

	m_wndTabs.EnableAutoColor(FALSE);
	m_wndTabs.SetTabBorderSize(0);
	m_wndTabs.HideSingleTab(FALSE);
	m_wndTabs.EnableTabSwap(FALSE);
	m_wndTabs.ShowWindow(SW_SHOW);
	m_wndTabs.SetActiveTabBoldFont(TRUE);
	return 0;
}

void CPaymentTerminalView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// ѡ��ؼ�Ӧ��������������: 
	CRect rectClient;
	GetClientRect(rectClient);
	m_wndTabs.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), rectClient.Height(), SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);
}
#endif //_DEBUG


// CPaymentTerminalView ��Ϣ�������


void CPaymentTerminalView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	//viewѡ��������
	//m_wndTabs.SetLocation(CMFCTabCtrl::LOCATION_TOP);


	//// TODO: �ڴ����ר�ô����/����û���
}
