// StaticEx.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "StaticEx.h"


// CStaticEx

IMPLEMENT_DYNAMIC(CStaticEx, CStatic)

CStaticEx::CStaticEx(UINT nFontSize, ALIGN sAlign)
{
	m_Font.CreateFont(nFontSize, 0, 0, 0, 700, 0, 0, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		_T("arial"));
	m_Align = sAlign;
}

CStaticEx::~CStaticEx()
{
}


BEGIN_MESSAGE_MAP(CStaticEx, CStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
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
	// TODO:  在此添加您专用的创建代码
	SetFont(&m_Font, TRUE);
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

int CStaticEx::CalcHeight(int nWidth)
{
	CDC *pDC = GetDC();
	pDC->SelectObject(&m_Font);
	CString strText;
	GetWindowText(strText);
	CRect rectText;
	rectText.SetRect(0, 0, nWidth, 0);
	return pDC->DrawText(strText, &rectText, DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT);
}

int CStaticEx::FitDevider3(int nWidth, char Infilling, LPCTSTR Content)
{
	int nDeviderWidth = nWidth - 20;
	CDC *pDC = GetDC();
	pDC->SelectObject(&m_Font);
	CString strInfilling(Infilling,1);
	CString strContent(Content);
	CString strVoid(' ',1);
	CSize sizeInfilling=pDC->GetTextExtent(strInfilling);
	CSize sizeContent = pDC->GetTextExtent(strContent);
	CSize sizeVoid= pDC->GetTextExtent(strVoid);
	int cntInfilling = nDeviderWidth / sizeInfilling.cx;
	int cntVoid=(nDeviderWidth -sizeContent.cx)/ sizeVoid.cx/2 -1;
	CString strDevider1(Infilling, cntInfilling);
	CString strDevider2(' ', cntVoid);
	CString strDevider;
	strDevider = strDevider1 +'\n'+ Infilling+ strDevider2+ strContent+ strDevider2+ Infilling+'\n'+ strDevider1;
	CRect rectText;
	rectText.SetRect(0, 0, nWidth, 0);
	SetWindowText(strDevider);
	return pDC->DrawText(strDevider, &rectText, DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT);
}

int CStaticEx::FitDevider1(int nWidth, char Infilling)
{
	int nDeviderWidth = nWidth - 20;
	CDC *pDC = GetDC();
	pDC->SelectObject(&m_Font);
	CString strInfilling(Infilling, 1);
	CSize sizeInfilling = pDC->GetTextExtent(strInfilling);
	int cntInfilling = nDeviderWidth / sizeInfilling.cx;
	CString strDevider(Infilling, cntInfilling);
	CRect rectText;
	rectText.SetRect(0, 0, nWidth, 0);
	SetWindowText(strDevider);
	return pDC->DrawText(strDevider, &rectText, DT_EDITCONTROL | DT_WORDBREAK | DT_CALCRECT);
}

void CStaticEx::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CStatic::OnPaint()
	dc.SelectObject(&m_Font);
	CRect   rectClient;
	GetClientRect(rectClient);

	CString   strText;
	GetWindowText(strText);
	dc.DrawText(strText, &rectClient, DT_EDITCONTROL | DT_WORDBREAK| m_Align);
	
}
