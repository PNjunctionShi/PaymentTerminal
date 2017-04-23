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
#endif //_DEBUG


// CPaymentTerminalView ��Ϣ�������
