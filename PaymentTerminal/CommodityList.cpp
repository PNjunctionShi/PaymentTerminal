// CommodityList.cpp : 实现文件
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



// CCommodityList 消息处理程序




int CCommodityList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	InitializeFlatSB(this->m_hWnd);
	FlatSB_EnableScrollBar(this->m_hWnd, SB_BOTH, ESB_DISABLE_BOTH);
	// TODO:  在此添加您专用的创建代码
	return 0;
}


void CCommodityList::OnNcCalcSize(BOOL bCalcValidRects, NCCALCSIZE_PARAMS* lpncsp)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ModifyStyle(WS_HSCROLL | WS_VSCROLL, 0); // 去掉水平滚动条和竖直滚动条
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