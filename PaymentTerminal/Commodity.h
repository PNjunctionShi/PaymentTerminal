#pragma once

// CCommodity 命令目标

class CCommodity : public CObject
{
public:
	CCommodity(CString strName=_T("Goods"), DOUBLE dPrice=0, DOUBLE dQuantity=0);
	virtual ~CCommodity();

protected:
	CString m_strName; //商品名称
	DOUBLE m_dPrice; //商品价格
	DOUBLE m_dQuantity; //商品数量
	DECLARE_SERIAL(CCommodity)

public:
	DOUBLE GetSubtotal(); //计算小计
	virtual void Serialize(CArchive& ar);
};


