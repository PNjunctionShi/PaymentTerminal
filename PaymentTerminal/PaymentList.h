#pragma once


// CPaymentList

class CPaymentList : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CPaymentList)

public:
	CPaymentList();
	virtual ~CPaymentList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


