// StaticEx.cpp : ʵ���ļ�
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



// CStaticEx ��Ϣ�������



HBRUSH CStaticEx::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	pDC->SetBkMode(TRANSPARENT);
	return (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
}

BOOL CStaticEx::OnEraseBkgnd(CDC* pDC)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
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
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}


void CStaticEx::OnSize(UINT nType, int cx, int cy)
{
	CStatic::OnSize(nType, cx, cy);
	CRect rectClient;
	GetClientRect(rectClient);
	InvalidateRect(rectClient);
	// TODO: �ڴ˴������Ϣ����������
}
