#pragma once


// COrderView

class COrderView : public CDockablePane
{
	DECLARE_DYNAMIC(COrderView)
private:
	CRect m_rectCurrClip;
public:
	COrderView();
	virtual ~COrderView();
	virtual BOOL Create(CWnd* pParentWnd);

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};


