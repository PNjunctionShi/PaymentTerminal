#pragma once

// COperator ÃüÁîÄ¿±ê
class COperator : public CObject
{
public:
	enum OperatorType {
		Cashier = 0,
		Shopkeeper = 1,
		Boss = 2
	};
	CString m_strName;
	OperatorType m_enuType;
public:
	COperator(CString strName, OperatorType enuType);
	virtual ~COperator();
};


