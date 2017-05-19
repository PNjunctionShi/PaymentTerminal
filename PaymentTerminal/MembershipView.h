#pragma once


// CMembershipView

class CMembershipView : public CDockablePane
{
	DECLARE_DYNCREATE(CMembershipView)

public:
	CMembershipView();
	virtual ~CMembershipView();
	virtual BOOL Create(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
};


