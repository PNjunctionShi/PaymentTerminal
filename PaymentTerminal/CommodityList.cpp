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
END_MESSAGE_MAP()



// CCommodityList ��Ϣ�������




int CCommodityList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
