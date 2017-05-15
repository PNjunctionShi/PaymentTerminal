#pragma once
enum ALIGN
{
	CENTER = DT_CENTER,
	LEFT=DT_LEFT,
	RIGHT=DT_RIGHT
};

// CStaticEx

class CStaticEx : public CStatic
{
	DECLARE_DYNAMIC(CStaticEx)
private:
	CFont m_Font;
	ALIGN m_Align;
public:
	CStaticEx(UINT nFontSize,ALIGN sAlign);
	virtual ~CStaticEx();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual int CalcHeight(int nWidth);
	virtual int FitDevider3(int nWidth, char Infilling, LPCTSTR Content);
	virtual int FitDevider1(int nWidth, char Infilling);
	afx_msg void OnPaint();
};


