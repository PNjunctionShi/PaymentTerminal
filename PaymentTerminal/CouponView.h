#pragma once


// CCouponView

class CCouponView : public CDockablePane
{
	DECLARE_DYNCREATE(CCouponView)

public:
	CCouponView();
	virtual ~CCouponView();
	virtual BOOL Create(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
};


