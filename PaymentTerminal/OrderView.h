#pragma once
#include "StaticEx.h"
#include "CommodityList.h"

// COrderView ������ͼ

class COrderView : public CFormView
{
	DECLARE_DYNCREATE(COrderView)
	
private:
	CStaticEx m_wndShopNameStatic;
	CStaticEx m_wndShopAddrStatic;
	CStaticEx m_wndDevider1Static;
	CStaticEx m_wndDevider2Static;
	CStaticEx m_wndDevider3Static;
	CStaticEx m_wndOrderTimeStatic;
	CStaticEx m_wndSeriesStatic;
	CStaticEx m_wndTotalStatic;
	CStaticEx m_wndChargeStatic;
	CStaticEx m_wndChangeStatic;
	CStaticEx m_wndCashier;
	CStaticEx m_wndTelephone;
	CCommodityList m_wndCommodityList;
protected:
	COrderView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	afx_msg int OnMouseActivate(CWnd* pDesktopWnd, UINT nHitTest, UINT message);
};


