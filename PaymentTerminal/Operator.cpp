// Operator.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PaymentTerminal.h"
#include "Operator.h"


// COperator

COperator::COperator(CString strName, OperatorType enuType)
{
	m_strName = strName;
	m_enuType = enuType;
}

COperator::~COperator()
{
}


// COperator ��Ա����
