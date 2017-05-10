#pragma once
#include "PaymentList.h"

// CPaymentTabs

class CPaymentTabs : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CPaymentTabs)

protected:
	CPaymentList m_wndOrderList;
	CPaymentList m_wndMemberList;
	CPaymentList m_wndCouponList;
public:
	CPaymentTabs();
	virtual ~CPaymentTabs();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


