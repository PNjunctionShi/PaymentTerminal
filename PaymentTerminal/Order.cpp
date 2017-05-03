// Order.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "Order.h"


// COrder

COrder::COrder(CString strSeries , CString strCashier, EPaymentType ePayType)
{
	m_timOrderTime = ::GetCurrentTime();
	m_strSeries = strSeries;
	m_strCashier = strCashier;
	m_ePayType = ePayType;
	m_eOrderStatus = EOrderStatus::UNPAIED;
	m_timPayTime = 0;
	m_listCommodity.RemoveAll();
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

IMPLEMENT_SERIAL(COrder, CObject, 0)