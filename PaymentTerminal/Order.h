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
// COrder 命令目标

class COrder : public CObject
{
	friend class CMainFrame;
	friend class COrderView;
public:
	COrder();
	virtual ~COrder();
public:
	COleDateTime m_timOrderTime; //订单生成时间
	CString  m_strSeries; //订单序列号
	CString m_strCashier; //创建订单的收银员名称
	EPaymentType m_ePayType; //支付类型，支付宝或微信
	EOrderStatus m_eOrderStatus; //订单状态，未支付，已支付，已入账
	COleDateTime m_timPayTime; //订单付账时间
	CTypedPtrList<CObList,CCommodity*> m_listCommodity; //商品清单
	double m_dCharge; //订单收取
	double m_dChange; //订单找零
	double m_dTotal;//订单总计
	BOOL m_bCustomedTotal; //手动设置而非计算得来的订单总计
	BOOL m_bArchived;
	DECLARE_SERIAL(COrder)
public:
	BOOL PayOff(); //支付
	BOOL SetPayType(); //设置支付类型
	BOOL SetSeries(); //设置订单序列号
	BOOL AddCommodity(CCommodity* pCommodity); //添加商品
	BOOL DeleteCommodity(CCommodity* pCommodity); //删除商品
	DOUBLE GetTotal(BOOL bForceCalc = FALSE);
	virtual void Serialize(CArchive& ar);
};


