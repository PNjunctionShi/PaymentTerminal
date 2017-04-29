// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"
#include "afxwinverapi.h"

static const int nMinRibbonWidth = 300;

static const int nTooltipMinWidthDefault = 210;
static const int nTooltipWithImageMinWidthDefault = 318;
static const int nTooltipMaxWidth = 640;

static const int nXTabMargin = 14;
static const int nYTabMargin = 5;

static const int nXMargin = 2;
static const int nYMargin = 2;

static const int nIdToolTipClient = 1;
static const int nIdToolTipCaption = 2;

static const UINT idCut = (UINT)-10002;
static const UINT idCopy = (UINT)-10003;
static const UINT idPaste = (UINT)-10004;
static const UINT idSelectAll = (UINT)-10005;

// CUserButton

CPayRibbonUserButton::CPayRibbonUserButton()
{
}

CPayRibbonUserButton::~CPayRibbonUserButton()
{
}


// CUserButton 成员函数
// E:\Documents\Visual Studio 2015\Projects\PaymentTerminal\PaymentTerminal\PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonConstructor

CPayRibbonConstructor::CPayRibbonConstructor(const CMFCRibbonInfo& info) : CMFCRibbonConstructor(info)
{
}

CPayRibbonConstructor::~CPayRibbonConstructor()
{
}

CMFCRibbonApplicationButton* CPayRibbonConstructor::CreateApplicationButton(CMFCRibbonBar& bar) const
{
	//bar.m_bAutoDestroyMainButton = TRUE;
	CPayRibbonBar *pPayBar =(CPayRibbonBar *) &bar;
	pPayBar->m_bAutoDestroyMainButton=TRUE;
	bar.SetApplicationButton(new CPayRibbonUserButton, CSize(80, 115));

	return bar.GetApplicationButton();
}
// CPayRibbonConstructor 成员函数
// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"
#include "afxribboninfoloader.h"

// CPayRibbonBar

IMPLEMENT_DYNAMIC(CPayRibbonBar, CMFCRibbonBar)

CPayRibbonBar::CPayRibbonBar()
{

}

CPayRibbonBar::~CPayRibbonBar()
{
}

BOOL CPayRibbonBar::LoadFromResource(UINT uiXMLResID, LPCTSTR lpszResType, HINSTANCE hInstance)
{
	ASSERT_VALID(this);
	return LoadFromResource(MAKEINTRESOURCE(uiXMLResID), lpszResType, hInstance);
}

BOOL CPayRibbonBar::LoadFromResource(LPCTSTR lpszXMLResID, LPCTSTR lpszResType, HINSTANCE hInstance)
{
	ASSERT_VALID(this);

	CMFCRibbonInfo info;
	CMFCRibbonInfoLoader loader(info);

	if (!loader.Load(lpszXMLResID, lpszResType, hInstance))
	{
		TRACE0("Cannot load ribbon from resource\n");
		return FALSE;
	}

	CPayRibbonConstructor constr(info);
	constr.ConstructRibbonBar(*this);

	return TRUE;
}

void CPayRibbonBar::RecalcLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	DeactivateKeyboardFocus();

	m_bIsTransparentCaption = FALSE;

	if (m_pPrintPreviewCategory == NULL && m_bIsPrintPreview)
	{
		AddPrintPreviewCategory();
		ASSERT_VALID(m_pPrintPreviewCategory);
	}

	m_nTabTruncateRatio = 0;

	CPane::RecalcLayout();

	const BOOL bHideAll = m_dwHideFlags & AFX_RIBBONBAR_HIDE_ALL;
	const int nCategoryHeight = (m_dwHideFlags & AFX_RIBBONBAR_HIDE_ELEMENTS) ? 0 : m_nCategoryHeight;
	const int cyFrameBorder = GetSystemMetrics(SM_CYSIZEFRAME);

	int i = 0;

	CRect rect;
	GetClientRect(rect);
	CClientDC dc(this);

	CFont* pOldFont = dc.SelectObject(GetFont());
	ENSURE(pOldFont != NULL);

	CString strCaption;
	GetWindowText(strCaption);

	const int nCaptionTextWidth = dc.GetTextExtent(strCaption).cx;

	for (i = 0; i < (int)m_arContextCaptions.GetSize(); i++)
	{
		ASSERT_VALID(m_arContextCaptions[i]);
		m_arContextCaptions[i]->SetRect(CRect(0, 0, 0, 0));
	}

	// Reposition caption and caption buttons:
	int xSysButtonsLeft = 0;
	m_rectSysButtons.SetRectEmpty();

	if (!m_bReplaceFrameCaption)
	{
		m_rectCaption.SetRectEmpty();
		m_rectCaptionText.SetRectEmpty();

		for (i = 0; i < AFX_RIBBON_CAPTION_BUTTONS; i++)
		{
			m_CaptionButtons[i].SetRect(CRect(0, 0, 0, 0));
		}
	}
	else
	{
		m_rectCaption = rect;
		m_rectCaption.bottom = m_rectCaption.top + m_nCaptionHeight;

		int x = m_rectCaption.right;
		int nCaptionOffsetY = 0;

		if (GetGlobalData()->IsDwmCompositionEnabled())
		{
			if (GetParent()->IsZoomed())
			{
				rect.top += cyFrameBorder / 2 + nYMargin;
				m_rectCaption.OffsetRect(0, cyFrameBorder / 2 + nYMargin);
			}

			// Hide our buttons:
			for (i = 0; i < AFX_RIBBON_CAPTION_BUTTONS; i++)
			{
				m_CaptionButtons[i].SetRect(CRect(0, 0, 0, 0));
			}

			// Get system buttons size:
			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(ncm);
			GetGlobalData()->GetNonClientMetrics(ncm);

			int nSysButtonsWidth = 3 * ncm.iCaptionWidth;

			x -= nSysButtonsWidth;

			m_rectSysButtons = m_rectCaption;
			m_rectSysButtons.left = x;
			xSysButtonsLeft = x;
		}
		else
		{
			NONCLIENTMETRICS ncm;
			ncm.cbSize = sizeof(ncm);
			GetGlobalData()->GetNonClientMetrics(ncm);

			int nSysBtnEdge = min(ncm.iCaptionHeight, m_rectCaption.Height() - nYMargin);

			const CSize sizeCaptionButton(nSysBtnEdge, nSysBtnEdge);
			const int yOffsetCaptionButton = max(0,
				(m_rectCaption.Height() - sizeCaptionButton.cy) / 2);

			for (i = AFX_RIBBON_CAPTION_BUTTONS - 1; i >= 0; i--)
			{
				if ((m_CaptionButtons[i].GetID() == SC_RESTORE || m_CaptionButtons[i].GetID() == SC_MAXIMIZE) && (GetParent()->GetStyle() & WS_MAXIMIZEBOX) == 0)
				{
					m_CaptionButtons[i].SetRect(CRect(0, 0, 0, 0));
					continue;
				}

				if (m_CaptionButtons[i].GetID() == SC_MINIMIZE && (GetParent()->GetStyle() & WS_MINIMIZEBOX) == 0)
				{
					m_CaptionButtons[i].SetRect(CRect(0, 0, 0, 0));
					continue;
				}

				CRect rectCaptionButton(CPoint(x - sizeCaptionButton.cx, m_rectCaption.top + yOffsetCaptionButton), sizeCaptionButton);

				m_CaptionButtons[i].SetRect(rectCaptionButton);

				x -= sizeCaptionButton.cx;

				if (m_CaptionButtons[i].GetID() == SC_RESTORE || m_CaptionButtons[i].GetID() == SC_MAXIMIZE)
				{
					m_CaptionButtons[i].SetID(GetParent()->IsZoomed() ? SC_RESTORE : SC_MAXIMIZE);
				}
			}
		}

		m_rectCaptionText = m_rectCaption;

		if (GetGlobalData()->IsDwmCompositionEnabled())
		{
			m_rectCaptionText.top += GetSystemMetrics(SM_CYSIZEFRAME) / 2;
		}

		m_rectCaptionText.right = x - nXMargin;
		m_rectCaptionText.OffsetRect(0, nCaptionOffsetY);

		xSysButtonsLeft = m_rectCaptionText.right;
	}

	// Reposition main button:
	CSize sizeMainButton = m_sizeMainButton;
	double scale = GetGlobalData()->GetRibbonImageScale();
	if (scale > 1.)
	{
		sizeMainButton.cx = (int)(.5 + scale * sizeMainButton.cx);
		sizeMainButton.cy = (int)(.5 + scale * sizeMainButton.cy);
	}

	if (m_pMainButton != NULL)
	{
		ASSERT_VALID(m_pMainButton);

		if (bHideAll)
		{
			m_pMainButton->SetRect(CRect(0, 0, 0, 0));
		}
		else
		{
			int yOffset = nYMargin;

			if (GetGlobalData()->IsDwmCompositionEnabled())
			{
				yOffset += GetSystemMetrics(SM_CYSIZEFRAME) / 2;
			}

			m_pMainButton->SetRect(CRect(CPoint(rect.left, rect.top + yOffset), sizeMainButton));//yOffset

			if (0)//!IsWindows7Look())
			{
				m_rectCaptionText.left = m_pMainButton->GetRect().right + nXMargin;
			}
			else
			{
				CRect rectMainBtn = rect;
				rectMainBtn.top = m_rectCaption.IsRectEmpty() ? rect.top : m_rectCaption.bottom;
				rectMainBtn.bottom = rectMainBtn.top + m_nTabsHeight+ nCategoryHeight;
				rectMainBtn.right = rectMainBtn.left + m_sizeMainButton.cx;

				m_pMainButton->SetRect(rectMainBtn);

				if (IsQuickAccessToolbarOnTop())
				{
					m_rectCaptionText.left = m_rectCaption.left + ::GetSystemMetrics(SM_CXSMICON) + 4 * nXMargin;
				}
			}
		}
	}

	CRect rectCategory = rect;

	// Reposition quick access toolbar:
	int nQAToolbarHeight = 0;
	CPayRibbonQAT * p_QAToolbar = (CPayRibbonQAT *)&m_QAToolbar;
	CPayRibbonButtonsGroup *p_TabElements = (CPayRibbonButtonsGroup *)&m_TabElements;
	CPayRibbonTabsGroup* p_Tabs = (CPayRibbonTabsGroup *)&m_Tabs;
	if (bHideAll)
	{
		p_QAToolbar->m_rect.SetRectEmpty();
		p_TabElements->SetRect(CRect(0, 0, 0, 0));
	}
	else
	{
		CSize sizeAQToolbar = p_QAToolbar->GetRegularSize(&dc);

		if (IsQuickAccessToolbarOnTop())
		{
			m_QAToolbar.SetRect(m_rectCaptionText);

			const int yOffset = max(0, (m_rectCaptionText.Height() - sizeAQToolbar.cy) / 2);

			p_QAToolbar->m_rect.top += yOffset;
			p_QAToolbar->m_rect.bottom = p_QAToolbar->m_rect.top + sizeAQToolbar.cy;

			if (GetGlobalData()->IsDwmCompositionEnabled())
			{
				p_QAToolbar->m_rect.top += nYMargin;
			}

			p_QAToolbar->m_rect.right = min(p_QAToolbar->m_rect.left + sizeAQToolbar.cx, m_rectCaptionText.right - 50);

			p_QAToolbar->OnAfterChangeRect(&dc);

			int nQAActualWidth = p_QAToolbar->GetActualWidth();
			int nQARight = p_QAToolbar->m_rect.left + nQAActualWidth + nXMargin;

			if (nQARight < p_QAToolbar->m_rect.right)
			{
				p_QAToolbar->m_rect.right = nQARight;
			}

			m_rectCaptionText.left = p_QAToolbar->m_rect.right;
			if (!IsWindows7Look())
			{
				m_rectCaptionText.left += CMFCVisualManager::GetInstance()->GetRibbonQuickAccessToolBarRightMargin();
			}
			else
			{
				m_rectCaptionText.left += 3 * nXMargin;
			}
		}
		else
		{
			p_QAToolbar->m_rect = rect;
			p_QAToolbar->m_rect.top = p_QAToolbar->m_rect.bottom - sizeAQToolbar.cy;
			nQAToolbarHeight = sizeAQToolbar.cy;

			rectCategory.bottom = p_QAToolbar->m_rect.top;
		}
	}

	p_QAToolbar->OnAfterChangeRect(&dc);

	if (!bHideAll)
	{
		const int yTabTop = m_rectCaption.IsRectEmpty() ? rect.top : m_rectCaption.bottom;
		const int yTabBottom = rect.bottom - nCategoryHeight - nQAToolbarHeight;

		// Reposition tab elements:
		CSize sizeTabElemens = m_TabElements.GetCompactSize(&dc);

		const int yOffset = max(0, (yTabBottom - yTabTop - sizeTabElemens.cy) / 2);
		const int nTabElementsHeight = min(m_nTabsHeight, sizeTabElemens.cy);

		p_TabElements->m_rect = CRect(CPoint(rect.right - sizeTabElemens.cx, yTabTop + yOffset), CSize(sizeTabElemens.cx, nTabElementsHeight));

		// Reposition tabs:

		const int nTabs = GetVisibleCategoryCount();

		if (nTabs > 0)
		{
			const int nTabLeftOffset = sizeMainButton.cx + 5;
			const int cxTabsArea = rect.Width() - nTabLeftOffset - sizeTabElemens.cx - nXMargin;
			const int nMaxTabWidth = cxTabsArea / nTabs;

			int x = rect.left + nTabLeftOffset;
			BOOL bIsFirstContextTab = TRUE;
			BOOL bCaptionOnRight = FALSE;

			p_Tabs->m_rect.SetRect(x, yTabTop, cxTabsArea, yTabBottom);

			int cxTabs = 0;

			for (i = 0; i < (int)m_arCategories.GetSize(); i++)
			{
				CPayRibbonCategory* pCategory = (CPayRibbonCategory *)m_arCategories[i];
				ASSERT_VALID(pCategory);

				if (pCategory->IsVisible())
				{
					CRect rectTabText(0, 0, nMaxTabWidth, m_nTabsHeight);

					dc.DrawText(pCategory->m_strName, rectTabText, DT_CALCRECT | DT_SINGLELINE | DT_VCENTER);

					int nTextWidth = rectTabText.Width();
					int nCurrTabMargin = nXTabMargin + nTextWidth / 40;

					pCategory->m_Tab.m_nFullWidth = nTextWidth + 2 * nCurrTabMargin;

					const UINT uiContextID = pCategory->GetContextID();

					if (uiContextID != 0 && m_bReplaceFrameCaption)
					{
						// If the current tab is last in current context, and there is no space
						// for category caption width, add extra space:
						BOOL bIsSingle = TRUE;

						for (int j = 0; j < (int)m_arCategories.GetSize(); j++)
						{
							CMFCRibbonCategory* pCategoryNext = m_arCategories[j];
							ASSERT_VALID(pCategoryNext);

							if (i != j && pCategoryNext->GetContextID() == uiContextID)
							{
								bIsSingle = FALSE;
								break;
							}
						}

						if (bIsSingle)
						{
							CMFCRibbonContextCaption* pCaption = FindContextCaption(uiContextID);
							if (pCaption != NULL)
							{
								ASSERT_VALID(pCaption);

								const int nMinCaptionWidth = dc.GetTextExtent(pCaption->GetText()).cx + 2 * nXTabMargin;

								if (nMinCaptionWidth > pCategory->m_Tab.m_nFullWidth)
								{
									pCategory->m_Tab.m_nFullWidth = nMinCaptionWidth;
								}
							}
						}
					}

					cxTabs += pCategory->m_Tab.m_nFullWidth;
				}
				else
				{
					pCategory->m_Tab.m_nFullWidth = 0;
				}
			}

			BOOL bNoSpace = cxTabs > cxTabsArea;

			for (i = 0; i < (int)m_arCategories.GetSize(); i++)
			{
				CPayRibbonCategory* pCategory =(CPayRibbonCategory *) m_arCategories[i];
				ASSERT_VALID(pCategory);

				if (!pCategory->IsVisible())
				{
					pCategory->m_Tab.SetRect(CRect(0, 0, 0, 0));
					continue;
				}

				int nTabWidth = pCategory->m_Tab.m_nFullWidth;

				if (nTabWidth > nMaxTabWidth && bNoSpace)
				{
					pCategory->m_Tab.m_bIsTruncated = TRUE;

					if (nTabWidth > 0)
					{
						m_nTabTruncateRatio = max(m_nTabTruncateRatio, (int)(100 - 100. * nMaxTabWidth / nTabWidth));
					}

					nTabWidth = nMaxTabWidth;
				}
				else
				{
					pCategory->m_Tab.m_bIsTruncated = FALSE;
				}

				pCategory->m_Tab.SetRect(CRect(x, yTabTop, x + nTabWidth, yTabBottom));

				const UINT uiContextID = pCategory->GetContextID();

				if (uiContextID != 0 && m_bReplaceFrameCaption)
				{
					CPayRibbonContextCaption* pCaption = (CPayRibbonContextCaption*)FindContextCaption(uiContextID);
					if (pCaption != NULL)
					{
						ASSERT_VALID(pCaption);

						int nCaptionWidth = max(nTabWidth, dc.GetTextExtent(pCaption->m_strText).cx);

						CRect rectOld = pCaption->GetRect();
						CRect rectCaption = m_rectCaption;

						rectCaption.left = rectOld.left == 0 ? x : rectOld.left;
						rectCaption.right = min(xSysButtonsLeft, x + nCaptionWidth);

						if (bIsFirstContextTab)
						{
							if (IsQuickAccessToolbarOnTop() && rectCaption.left - nXTabMargin < p_QAToolbar->m_rect.right)
							{
								p_QAToolbar->m_rect.right = rectCaption.left - nXTabMargin;

								if (p_QAToolbar->m_rect.right <= p_QAToolbar->m_rect.left)
								{
									p_QAToolbar->m_rect.SetRectEmpty();
								}

								p_QAToolbar->OnAfterChangeRect(&dc);

								m_rectCaptionText.left = rectCaption.right + nXTabMargin;
								bCaptionOnRight = TRUE;
							}
							else
							{
								const int yCaptionRight = min(m_rectCaptionText.right, x);
								const int nCaptionWidthLeft = yCaptionRight - m_rectCaptionText.left;
								const int nCaptionWidthRight = m_rectCaption.right - rectCaption.right - nXTabMargin;

								if (nCaptionTextWidth > nCaptionWidthLeft && nCaptionWidthLeft < nCaptionWidthRight)
								{
									m_rectCaptionText.left = rectCaption.right + nXTabMargin;
									bCaptionOnRight = TRUE;
								}
								else
								{
									m_rectCaptionText.right = yCaptionRight;
								}
							}

							bIsFirstContextTab = FALSE;
						}
						else if (bCaptionOnRight)
						{
							m_rectCaptionText.left = rectCaption.right + nXTabMargin;
						}

						pCaption->SetRect(rectCaption);

						pCaption->m_nRightTabX = pCategory->m_Tab.m_bIsTruncated ? -1 : pCategory->m_Tab.GetRect().right;
					}
				}

				x += nTabWidth;
			}
		}

		rectCategory.top = yTabBottom;
		rectCategory.left = sizeMainButton.cx + 1;;
	}

	p_TabElements->OnAfterChangeRect(&dc);

	CRect rectCategoryRedraw = rectCategory;

	if (m_pActiveCategory != NULL)
	{
		ASSERT_VALID(m_pActiveCategory);

		((CPayRibbonCategory*)m_pActiveCategory)->m_rect = bHideAll ? CRect(0, 0, 0, 0) : rectCategory;

		if (nCategoryHeight > 0)
		{
			int nLastPanelIndex = m_pActiveCategory->GetPanelCount() - 1;

			CRect rectLastPaneOld;
			rectLastPaneOld.SetRectEmpty();

			if (nLastPanelIndex >= 0)
			{
				rectLastPaneOld = m_pActiveCategory->GetPanel(nLastPanelIndex)->GetRect();
			}

			m_pActiveCategory->RecalcLayout(&dc);

			if (nLastPanelIndex >= 0 && m_pActiveCategory->GetPanel(nLastPanelIndex)->GetRect() == rectLastPaneOld)
			{
				rectCategoryRedraw.left = rectLastPaneOld.right;
			}
		}
	}

	dc.SelectObject(pOldFont);

	if (GetGlobalData()->IsDwmCompositionEnabled() && m_bReplaceFrameCaption)
	{
		GetParent()->ModifyStyleEx(0, WS_EX_WINDOWEDGE);

		MARGINS margins;
		margins.cxLeftWidth = 0;
		margins.cxRightWidth = 0;
		margins.cyTopHeight = m_rectCaption.bottom;
		margins.cyBottomHeight = 0;

		if (_AfxDwmExtendFrameIntoClientArea(GetParent()->GetSafeHwnd(), &margins) == S_OK)
		{
			m_bIsTransparentCaption = TRUE;
		}
	}

	if (m_bForceRedraw)
	{
		RedrawWindow();
		m_bForceRedraw = FALSE;
	}
	else
	{
		InvalidateRect(m_rectCaption);

		CRect rectTabs = rect;
		rectTabs.top = m_rectCaption.IsRectEmpty() ? rect.top : m_rectCaption.bottom;
		rectTabs.bottom = rectTabs.top + m_nTabsHeight + 2 * nYTabMargin;

		InvalidateRect(rectTabs);
		InvalidateRect(p_QAToolbar->m_rect);
		InvalidateRect(rectCategoryRedraw);

		UpdateWindow();
	}

	CMenu* pSysMenu = GetParent()->GetSystemMenu(FALSE);

	if (m_bReplaceFrameCaption && pSysMenu->GetSafeHmenu() != NULL && !m_bIsTransparentCaption)
	{
		for (i = 0; i < AFX_RIBBON_CAPTION_BUTTONS; i++)
		{
			CString strName;
			pSysMenu->GetMenuString(m_CaptionButtons[i].GetID(), strName, MF_BYCOMMAND);

			strName = strName.SpanExcluding(_T("\t"));
			strName.Remove(_T('&'));

			m_CaptionButtons[i].SetToolTipText(strName);
		}
	}

	UpdateToolTipsRect();
	if (!m_bSingleLevelAccessibilityMode)
	{
		m_Tabs.UpdateTabs(m_arCategories);
	}
}

CSize CPayRibbonBar::CalcFixedLayout(BOOL, BOOL /*bHorz*/)
{
	ASSERT_VALID(this);

	CClientDC dc(this);

	CFont* pOldFont = dc.SelectObject(GetFont());
	ENSURE(pOldFont != NULL);

	TEXTMETRIC tm;
	dc.GetTextMetrics(&tm);

	m_nCaptionHeight = 0;

	if (m_bReplaceFrameCaption)
	{
		m_nCaptionHeight = GetSystemMetrics(SM_CYCAPTION) + 1;

		if (GetGlobalData()->IsDwmCompositionEnabled())
		{
			m_nCaptionHeight += GetSystemMetrics(SM_CYSIZEFRAME);
		}
	}

	int cy = 0;

	CSize sizeMainButton = m_sizeMainButton;
	double scale = GetGlobalData()->GetRibbonImageScale();
	if (scale > 1.)
	{
		sizeMainButton.cx = (int)(.5 + scale * sizeMainButton.cx);
		sizeMainButton.cy = (int)(.5 + scale * sizeMainButton.cy);
	}

	if (m_dwHideFlags & AFX_RIBBONBAR_HIDE_ALL)
	{
		cy = m_nCaptionHeight;
	}
	else
	{
		if (m_bRecalcCategoryHeight)
		{
			m_nCategoryHeight = 0;
		}

		m_nTabsHeight = tm.tmHeight + 2 * nYTabMargin;

		if (m_bRecalcCategoryHeight)
		{
			for (int i = 0; i < (int)m_arCategories.GetSize(); i++)
			{
				CMFCRibbonCategory* pCategory = m_arCategories[i];
				ASSERT_VALID(pCategory);

				m_nCategoryHeight = max(m_nCategoryHeight, pCategory->GetMaxHeight(&dc));
			}
			m_bRecalcCategoryHeight = FALSE;
		}
		CPayRibbonQAT * p_QAToolbar = (CPayRibbonQAT *)&m_QAToolbar;
		const CSize sizeAQToolbar = p_QAToolbar->GetRegularSize(&dc);

		if (IsQuickAccessToolbarOnTop())
		{
			m_nCaptionHeight = max(m_nCaptionHeight, sizeAQToolbar.cy + (IsWindows7Look() ? 0 : (2 * nYMargin)));
		}

		const int nQuickAceesToolbarHeight = IsQuickAccessToolbarOnTop() ? 0 : sizeAQToolbar.cy;
		const int nCategoryHeight = (m_dwHideFlags & AFX_RIBBONBAR_HIDE_ELEMENTS) ? 0 : m_nCategoryHeight;

		cy = nQuickAceesToolbarHeight + m_nCaptionHeight + max(nCategoryHeight + m_nTabsHeight, m_sizeMainButton.cy + nYMargin);
	}

	if (GetGlobalData()->IsDwmCompositionEnabled())
	{
		if (GetParent()->IsZoomed() && m_bReplaceFrameCaption)
		{
			cy += ::GetSystemMetrics(SM_CYSIZEFRAME) - 2;
		}
	}

	dc.SelectObject(pOldFont);
	return CSize(32767, cy);
}

BEGIN_MESSAGE_MAP(CPayRibbonBar, CMFCRibbonBar)
END_MESSAGE_MAP()



// CPayRibbonBar 消息处理程序


// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonQAT

IMPLEMENT_DYNAMIC(CPayRibbonQAT, CMFCRibbonQuickAccessToolBar)

CPayRibbonQAT::CPayRibbonQAT()
{

}

CPayRibbonQAT::~CPayRibbonQAT()
{
}


BEGIN_MESSAGE_MAP(CPayRibbonQAT, CMFCRibbonQuickAccessToolBar)
END_MESSAGE_MAP()



// CPayRibbonQAT 消息处理程序


// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonButtonsGroup

CPayRibbonButtonsGroup::CPayRibbonButtonsGroup()
{
}

CPayRibbonButtonsGroup::~CPayRibbonButtonsGroup()
{
}


// CPayRibbonButtonsGroup 成员函数
// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonTabsGroup

CPayRibbonTabsGroup::CPayRibbonTabsGroup()
{
}

CPayRibbonTabsGroup::~CPayRibbonTabsGroup()
{
}


// CPayRibbonTabsGroup 成员函数
// PaymentRibbon.cpp : 实现文件
//
// PaymentRibbon.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonCategory

CPayRibbonCategory::CPayRibbonCategory()
{
}

CPayRibbonCategory::~CPayRibbonCategory()
{
}


// CPayRibbonCategory 成员函数
#include "stdafx.h"
#include "PaymentTerminal.h"
#include "PaymentRibbon.h"


// CPayRibbonCategory

CPayRibbonContextCaption::CPayRibbonContextCaption()
{
}

CPayRibbonContextCaption::~CPayRibbonContextCaption()
{
}


// CPayRibbonCategory 成员函数