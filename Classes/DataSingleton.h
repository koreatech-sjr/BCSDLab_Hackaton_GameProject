#pragma once

#include "Common.h"

class Character;

class CDataSingleton {
private:
	static CDataSingleton*	pInstance;
	static Character*		pCharacter;

public:
	CDataSingleton();
	~CDataSingleton();

	static CDataSingleton*	getInstance();
	static Character*		getCharacter();
	static void				setCharacter(Character* p);

};