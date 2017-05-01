#pragma once


// COrderView

class COrderView : public CDockablePane
{
	DECLARE_DYNAMIC(COrderView)

public:
	COrderView();
	virtual ~COrderView();
	virtual BOOL Create(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
};


