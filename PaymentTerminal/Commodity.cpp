// Commodity.cpp : 实现文件
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "Commodity.h"


// CCommodity

CCommodity::CCommodity(CString strName, DOUBLE dPrice, DOUBLE dQuantity)
{
	m_strName = strName;
	m_dPrice = dPrice;
	m_dQuantity = dQuantity;
}

CCommodity::~CCommodity()
{
}

DOUBLE CCommodity::GetSubtotal()
{
	return m_dPrice * m_dQuantity;
}
// CCommodity 成员函数


void CCommodity::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_strName;
		ar << m_dPrice;
		ar << m_dQuantity;
	}
	else
	{	// loading code
		ar >> m_strName;
		ar >> m_dPrice;
		ar >> m_dQuantity;
	}
}

IMPLEMENT_SERIAL(CCommodity,CObject,0)