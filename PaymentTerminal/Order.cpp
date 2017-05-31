// Order.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "Order.h"

// COrder

COrder::COrder()
{
	m_timOrderTime=time(NULL);
	m_strSeries = _T("");
	m_strCashier = _T("");
	m_ePayType = EPaymentType::Cash;
	m_eOrderStatus = EOrderStatus::UNPAIED;
	m_timPayTime = time(NULL);
	m_listCommodity.RemoveAll();
	m_dTotal = 0;
	m_bArchived = FALSE;
	m_bCustomedTotal = FALSE;
}

COrder::~COrder()
{
}


// COrder 成员函数


void COrder::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_timOrderTime;
		ar << m_strSeries;
		ar << m_strCashier;
		INT tmp;
		tmp = m_ePayType;
		ar << tmp;
		tmp = m_eOrderStatus;
		ar << tmp;
		ar << m_timPayTime;
		m_listCommodity.Serialize(ar);
	}
	else
	{	// loading code
		ar >> m_timOrderTime;
		ar >> m_strSeries;
		ar >> m_strCashier;
		INT tmp;
		ar >> tmp;
		m_ePayType = (EPaymentType)tmp;
		ar >> tmp;
		m_eOrderStatus = (EOrderStatus)tmp;
		ar >> m_timPayTime;
		m_listCommodity.Serialize(ar);
	}
}


DOUBLE COrder::GetTotal()
{
	if (!m_bCustomedTotal)
	{
		m_dTotal = 0;
		POSITION pos = m_listCommodity.GetHeadPosition();
		CCommodity* tmp;
		while (pos != NULL)
		{
			tmp= m_listCommodity.GetNext(pos);
			m_dTotal += tmp->GetSubtotal();
		}
	}
	return m_dTotal;
}

IMPLEMENT_SERIAL(COrder, CObject, 0)