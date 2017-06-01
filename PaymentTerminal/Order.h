#pragma once
#include "Commodity.h"
enum EPaymentType
{
	Cash = 1,
	Alipay=2,
	Wechat=3
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
	friend class CMainFrame;
	friend class COrderView;
public:
	COrder();
	virtual ~COrder();
public:
	COleDateTime m_timOrderTime; //��������ʱ��
	CString  m_strSeries; //�������к�
	CString m_strCashier; //��������������Ա����
	EPaymentType m_ePayType; //֧�����ͣ�֧������΢��
	EOrderStatus m_eOrderStatus; //����״̬��δ֧������֧����������
	COleDateTime m_timPayTime; //��������ʱ��
	CTypedPtrList<CObList,CCommodity*> m_listCommodity; //��Ʒ�嵥
	double m_dCharge; //������ȡ
	double m_dChange; //��������
	double m_dTotal;//�����ܼ�
	BOOL m_bCustomedTotal; //�ֶ����ö��Ǽ�������Ķ����ܼ�
	BOOL m_bArchived;
	DECLARE_SERIAL(COrder)
public:
	BOOL PayOff(); //֧��
	BOOL SetPayType(); //����֧������
	BOOL SetSeries(); //���ö������к�
	BOOL AddCommodity(CCommodity* pCommodity); //�����Ʒ
	BOOL DeleteCommodity(CCommodity* pCommodity); //ɾ����Ʒ
	DOUBLE GetTotal(BOOL bForceCalc = FALSE);
	virtual void Serialize(CArchive& ar);
};


