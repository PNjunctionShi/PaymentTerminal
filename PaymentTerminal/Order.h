#pragma once
#include "Commodity.h"
enum EPaymentType
{
	Alipay=1,
	Wechat=2
};

enum EOrderStatus
{
	UNPAIED=1,
	PAIED=2,
	ACCOUNTED=3
};
// COrder ����Ŀ��

class COrder : public CObject
{
public:
	COrder(CString strSeries=_T(""), CString strCashier=_T(""), EPaymentType ePayType=EPaymentType::Alipay );
	virtual ~COrder();
protected:
	CTime m_timOrderTime; //��������ʱ��
	CString  m_strSeries; //�������к�
	CString m_strCashier; //��������������Ա����
	EPaymentType m_ePayType; //֧�����ͣ�֧������΢��
	EOrderStatus m_eOrderStatus; //����״̬��δ֧������֧����������
	CTime m_timPayTime; //��������ʱ��
	CTypedPtrList<CObList,CCommodity*> m_listCommodity; //��Ʒ�嵥
	DECLARE_SERIAL(COrder)
public:
	BOOL PayOff(); //֧��
	BOOL SetPayType(); //����֧������
	BOOL SetSeries(); //���ö������к�
	BOOL AddCommodity(CCommodity* pCommodity); //�����Ʒ
	BOOL DeleteCommodity(CCommodity* pCommodity); //ɾ����Ʒ
	DOUBLE GetTotal();
	virtual void Serialize(CArchive& ar);
};


