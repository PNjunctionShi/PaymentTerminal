// StaticEx.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "StaticEx.h"


// CStaticEx

IMPLEMENT_DYNAMIC(CStaticEx, CStatic)

CStaticEx::CStaticEx()
{
}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
END_MESSAGE_MAP()



// CStaticEx 消息处理程序



HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  在此更改 DC 的任何特性
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
}

BOOL CStaticEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CRect rectClient;
	GetClientRect(rectClient);
	CBrush WHITE(RGB(255, 255, 255));
	pDC->FillRect(rectClient, &WHITE);
	return TRUE;
	//return CDockablePane::OnEraseBkgnd(pDC);
}

int CStaticEx::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CStatic::OnCreate(lpCreateStruct) == -1)
		return -1;
	m_Font.CreateFont(24, 0, 0, 0, 700, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("arial"));
	SetFont(&m_Font, TRUE);
	// TODO:  在此添加您专用的创建代码

	return 0;
}


void CStaticEx::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(rectClient);
	InvalidateRect(rectClient);
	// TODO: 在此处添加消息处理程序代码
}
