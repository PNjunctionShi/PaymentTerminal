#pragma once
#include "StaticEx.h"
#include "CommodityList.h"
#include "Order.h"
#include "MainFrm.h"

class CMainFrame;
// COrderView 窗体视图

class COrderView : public CFormView
{
	DECLARE_DYNCREATE(COrderView)
	
public:
	CStaticEx m_wndShopNameStatic;
	CStaticEx m_wndShopAddrStatic;
	CStaticEx m_wndDevider1Static;
	CStaticEx m_wndDevider2Static;
	CStaticEx m_wndOrderTimeStatic;
	CStaticEx m_wndSeriesStatic;
	CStaticEx m_wndTotalStatic;
	CStaticEx m_wndChargeStatic;
	CStaticEx m_wndChangeStatic;
	CStaticEx m_wndCashier;
	CStaticEx m_wndTelephone;
	CCommodityList m_wndCommodityList;
	CRect m_rectOutline;
	int m_nMinWidth=500;
protected:
	COrderView();           // 动态创建所使用的受保护的构造函数
	virtual ~COrderView();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ORDERVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
	virtual void ReCalcLayout();
	virtual void OnDraw(CDC* pDC);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	void DDXEx_Text(CDataExchange *pDX, int nIDC, double &value, LPCTSTR lpszFormat);
	void DDX_OrderTotal(CDataExchange *pDX, int nIDC, COrder* pOrder);
	CMainFrame* m_pMainFrame;
	afx_msg void OnLvnGetdispinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchanged(NMHDR *pNMHDR, LRESULT *pResult);
};


