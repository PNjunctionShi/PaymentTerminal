// PaymentList.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentList.h"


// CPaymentList

IMPLEMENT_DYNAMIC(CPaymentList, CMFCListCtrl)

CPaymentList::CPaymentList()
{
}

CPaymentList::~CPaymentList()
{
}


BEGIN_MESSAGE_MAP(CPaymentList, CMFCListCtrl)
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CPaymentList 消息处理程序




int CPaymentList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// TODO:  在此添加您专用的创建代码

	return 0;
}
