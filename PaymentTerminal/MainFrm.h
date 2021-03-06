// 这段 MFC 示例源代码演示如何使用 MFC Microsoft Office Fluent 用户界面 
// (“Fluent UI”)。该示例仅供参考，
// 用以补充《Microsoft 基础类参考》和 
// MFC C++ 库软件随附的相关电子文档。  
// 复制、使用或分发 Fluent UI 的许可条款是单独提供的。  
// 若要了解有关 Fluent UI 许可计划的详细信息，请访问 
// http://go.microsoft.com/fwlink/?LinkId=238214。
//
// 版权所有(C) Microsoft Corporation
// 保留所有权利。

// MainFrm.h : CMainFrame 类的接口
//

#pragma once
#include "PaymentRibbon.h"
#include "CouponView.h"
#include "MembershipView.h"
#include "OrderDockPane.h"
#include "Order.h"
#include "Operator.h"

class COrderDockPane;

class CMainFrame : public CFrameWndEx
{

friend class COrderView;

public:
	COrder* m_pSelectedOrder;
	CCommodity* m_pSelectedCommodity;
	COleDateTime m_timeLasttime;
	int m_nSubSeries;
	COperator m_Operator;
	CString m_strShopName;
	CString m_strShopAddr;
	CString m_strTelephone;

protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CPayRibbonBar     m_wndRibbonBar;
	CPayRibbonUserButton m_MainButton;
	CMFCToolBarImages m_PanelImages;
	CMFCRibbonStatusBar  m_wndStatusBar;
	CMFCCaptionBar    m_wndCaptionBar;
	CCouponView* m_pCouponView;
	COrderDockPane* m_pOrderDockPane;
	CMembershipView* m_pMembershipView;

// 生成的消息映射函数
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
	afx_msg void OnNewCommodity();
	afx_msg void OnCommodityName();
	afx_msg void OnCommodityPrice();
	afx_msg void OnCommodityQuantity();
	afx_msg void OnTotal();
	afx_msg void OnDeleteCommodity();
	afx_msg void OnUpdateDeleteCommodity(CCmdUI *pCmdUI);
	afx_msg void OnCharge();
	afx_msg void OnChange();
	afx_msg void OnBtnCash();
};


