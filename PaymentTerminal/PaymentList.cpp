// PaymentList.cpp : ʵ���ļ�
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



// CPaymentList ��Ϣ�������




int CPaymentList::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCListCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	// TODO:  �ڴ������ר�õĴ�������

	return 0;
}
