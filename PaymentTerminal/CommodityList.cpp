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
END_MESSAGE_MAP()



// CCommodityList 消息处理程序




int CCommodityList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// TODO:  在此添加您专用的创建代码

	return 0;
}
