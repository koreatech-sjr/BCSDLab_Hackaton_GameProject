#include "DataSingleton.h"
#include "Character.h"


CDataSingleton::CDataSingleton() {}
CDataSingleton::~CDataSingleton() {}

CDataSingleton* CDataSingleton::getInstance() {
	if (!pInstance) {
		pInstance = new CDataSingleton;
	}
	return pInstance;
}

Character*		CDataSingleton::getCharacter() {
	if (!pCharacter) {
		pCharacter = new Character;
	}
	return pCharacter;
}
void CDataSingleton::setCharacter(Character* p) {
	pCharacter = p;
}

CDataSingleton*		CDataSingleton::pInstance = NULL;
Character*			CDataSingleton::pCharacter = NULL;