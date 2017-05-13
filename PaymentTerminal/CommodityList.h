#pragma once


// CCommodityList

class CCommodityList : public CMFCListCtrl
{
	DECLARE_DYNAMIC(CCommodityList)

public:
	CCommodityList();
	virtual ~CCommodityList();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};


