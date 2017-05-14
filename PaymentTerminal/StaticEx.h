#pragma once


// CStaticEx

class CStaticEx : public CStatic
{
	DECLARE_DYNAMIC(CStaticEx)
private:
	CFont m_Font;

public:
	CStaticEx();
	virtual ~CStaticEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
};


