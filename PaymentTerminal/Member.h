#pragma once

// CMember ����Ŀ��

class CMember : public CObject
{
protected:
	DECLARE_SERIAL(CMember)
public:
	CMember();
	virtual ~CMember();
};


