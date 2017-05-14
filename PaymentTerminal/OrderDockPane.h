#pragma once
#include "OrderView.h"
// COrderDockPane

class COrderDockPane : public CDockablePane
{
	DECLARE_DYNAMIC(COrderDockPane)
private:
	COrderView* m_pBaseplate;

public:
	COrderDockPane();
	virtual ~COrderDockPane();
	virtual BOOL Create(CWnd* pParentWnd);
protected:
	DECLARE_MESSAGE_MAP()
public:
	//afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


