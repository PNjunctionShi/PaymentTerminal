// CommodityList.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "CommodityList.h"


// CCommodityList

IMPLEMENT_DYNAMIC(CCommodityList, CMFCListCtrl)

CCommodityList::CCommodityList()
{

}

CCommodityList::~CCommodityList()
{
}


BEGIN_MESSAGE_MAP(CCommodityList, CMFCListCtrl)
	ON_WM_CREATE()
	ON_WM_NCCALCSIZE()
END_MESSAGE_MAP()



// CCommodityList ��Ϣ�������




int CCommodityList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	InitializeFlatSB(this->m_hWnd);
	FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);
	// TODO:  �ڴ������ר�õĴ�������
	return 0;
}


void CCommodityList::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0); // ȥ��ˮƽ����������ֱ������
	CMFCListCtrl::OnNcCalcSize(bCalcValidRects, lpncsp);
}

int CCommodityList::CalcHeight()
{
	CRect rectHeader;
	GetHeaderCtrl().GetWindowRect(rectHeader);
	CRect rectItem;
	GetItemRect(0, rectItem, LVIR_BOUNDS);
	int nItem;
	nItem = GetItemCount();
	return rectHeader.Height() + nItem*rectItem.Height();
}