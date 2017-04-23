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

// PaymentTerminalView.cpp : CPaymentTerminalView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPaymentTerminalView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CPaymentTerminalView 构造/析构

CPaymentTerminalView::CPaymentTerminalView()
{
	// TODO: 在此处添加构造代码

}

CPaymentTerminalView::~CPaymentTerminalView()
{
}

BOOL CPaymentTerminalView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CPaymentTerminalView 绘制

void CPaymentTerminalView::OnDraw(CDC* /*pDC*/)
{
	CPaymentTerminalDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CPaymentTerminalView 打印


void CPaymentTerminalView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPaymentTerminalView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPaymentTerminalView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPaymentTerminalView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
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


// CPaymentTerminalView 诊断

#ifdef _DEBUG
void CPaymentTerminalView::AssertValid() const
{
	CView::AssertValid();
}

void CPaymentTerminalView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPaymentTerminalDoc* CPaymentTerminalView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPaymentTerminalDoc)));
	return (CPaymentTerminalDoc*)m_pDocument;
}
#endif //_DEBUG


// CPaymentTerminalView 消息处理程序
