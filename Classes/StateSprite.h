#ifndef STATE_SPRITE
#define STATE_SPRITE

#include "Common.h"
#include "Character.h"
#include "DataSingleton.h"


class CStateSprite : public Sprite {
	// [ 기본 ]
	// ==============================================================================================================
public:
	CStateSprite() {
		m_picture = NULL;
		m_stressLabel = NULL;

		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();
	}
	virtual ~CStateSprite() {}

	static CStateSprite* Create() {
		static std::string SliderNames ="state.png";

		CStateSprite* pDialogueSprite = CStateSprite::create(SliderNames.c_str(),
			CCRectMake(0, 0, 1300, 900));
		return pDialogueSprite;
	}



protected:
	static CStateSprite* create(const char* pszFileName, const CCRect& rect) {
		CStateSprite* pDialogueSprite = new CStateSprite();
		if (pDialogueSprite && pDialogueSprite->initWithFile(pszFileName, rect)) {
			pDialogueSprite->autorelease();
			return pDialogueSprite;
		}
		CC_SAFE_DELETE(pDialogueSprite);
		return NULL;
	}

	Character* pCharacter;
	CDataSingleton* pDataSingleton;

	// ==============================================================================================================





	// [ 데이터 ]
	// ==============================================================================================================
public:
	void		setState() {
		setPicture();
		setStressLabel();
		setTirednessLabel();
		setMoneyLabel();
	}


protected:
	LabelTTF* m_stressLabel;
	LabelTTF* m_tirednessLabel;
	LabelTTF* m_moneyLabel;
	cocos2d::Sprite* m_picture;

	void	setPicture() {
		int myCharacter = pCharacter->getMyCharacter();

		if(myCharacter == 1)
			m_picture = cocos2d::Sprite::create("char1.png");
		else
			m_picture = cocos2d::Sprite::create("unknownChar.png");

		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)30, (float)620));
		addChild(m_picture, 3);
	}
	void setStressLabel()		{
		std::string str = "";
		str += std::to_string(pCharacter->getStress());
		str += "/";
		str += std::to_string(pCharacter->getMaxStress());

		m_stressLabel = LabelTTF::create(str, "Arial", 45,
			Size(300, 200), TextHAlignment::LEFT, TextVAlignment::TOP);


		m_stressLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_stressLabel->setPosition(ccp(550, 665));
		m_stressLabel->setColor(Color3B(255, 255, 255));
		addChild(m_stressLabel, 3);
	}
	void setTirednessLabel()		{
		std::string str = "";
		str += std::to_string(pCharacter->getTiredness());
		str += "/";
		str += std::to_string(pCharacter->getMaxTiredness());

		m_tirednessLabel = LabelTTF::create(str, "Arial", 45,
			Size(300, 200), TextHAlignment::LEFT, TextVAlignment::TOP);


		m_tirednessLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_tirednessLabel->setPosition(ccp(550,577));
		m_tirednessLabel->setColor(Color3B(255, 255, 255));
		addChild(m_tirednessLabel, 3);
	}
	void setMoneyLabel()		{
		std::string str = "";
		str += Common::FormatWithCommas(pCharacter->getMoney());
		str += "원";

		m_moneyLabel = LabelTTF::create(str, "Arial", 45,
			Size(300, 200), TextHAlignment::LEFT, TextVAlignment::TOP);


		m_moneyLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_moneyLabel->setPosition(ccp(550, 493));
		m_moneyLabel->setColor(Color3B(255, 255, 255));
		addChild(m_moneyLabel, 3);
	}

	// ==============================================================================================================
};
#endif STATE_SPRITE