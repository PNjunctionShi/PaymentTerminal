#pragma once

// CCommodity ����Ŀ��

class CCommodity : public CObject
{
public:
	CCommodity(CString strName=_T("Goods"), DOUBLE dPrice=0, DOUBLE dQuantity=0);
	virtual ~CCommodity();

protected:
	CString m_strName; //��Ʒ����
	DOUBLE m_dPrice; //��Ʒ�۸�
	DOUBLE m_dQuantity; //��Ʒ����
	DECLARE_SERIAL(CCommodity)

public:
	DOUBLE GetSubtotal(); //����С��
	virtual void Serialize(CArchive& ar);
};


