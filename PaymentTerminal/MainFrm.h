// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ������� 
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once
#include "PaymentRibbon.h"
#include "CouponView.h"
#include "MembershipView.h"
#include "OrderDockPane.h"
#include "Order.h"
#include "Operator.h"

class CMainFrame : public CFrameWndEx
{
public:
	COrder* m_pSelectedOrder;
	CTime m_timeLasttime;
	int m_nSubSeries;
	COperator m_Operator;
	CString m_strShopName;
	CString m_strShopAddr;

protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CPayRibbonBar     m_wndRibbonBar;
	CPayRibbonUserButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCCaptionBar    m_wndCaptionBar;
	CCouponView m_wndCouponView;
	COrderDockPane m_wndOrderDockPane;
	CMembershipView m_wndMembershipView;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnApplicationLook(UINT id);
	afx_msg void OnUpdateApplicationLook(CCmdUI* pCmdUI);
	afx_msg void OnViewCaptionBar();
	afx_msg void OnUpdateViewCaptionBar(CCmdUI* pCmdUI);
	afx_msg void OnOptions();
	afx_msg void OnFilePrint();
	afx_msg void OnFilePrintPreview();
	afx_msg void OnUpdateFilePrintPreview(CCmdUI* pCmdUI);
	DECLARE_MESSAGE_MAP()

	BOOL CreateCaptionBar();
public:
	afx_msg void OnOrder();
	afx_msg void OnUpdateOrder(CCmdUI *pCmdUI);
	afx_msg void OnCoupon();
	afx_msg void OnUpdateCoupon(CCmdUI *pCmdUI);
	afx_msg void OnMembership();
	afx_msg void OnUpdateMembership(CCmdUI *pCmdUI);
	afx_msg void OnNewOrder();
	CString GenerateSeries();
};


