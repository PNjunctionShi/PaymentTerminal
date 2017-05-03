#pragma once

// CMember ÃüÁîÄ¿±ê

class CMember : public CObject
{
protected:
	DECLARE_SERIAL(CMember)
public:
	CMember();
	virtual ~CMember();
};


