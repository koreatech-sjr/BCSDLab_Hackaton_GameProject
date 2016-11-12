#ifndef MOVE_SPRITE
#define MOVE_SPRITE

#include "Common.h"
#include "Character.h"
#include "DataSingleton.h"

class CMoveSprite : public Sprite {
	// [ �⺻ ]
	// ==============================================================================================================
public:
	CMoveSprite() {
		m_picture = NULL;
		m_textLabel = NULL;

		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();
	}
	virtual ~CMoveSprite() {}

	static CMoveSprite* Create() {
		static std::string SliderNames ="move.png";

		CMoveSprite* pDialogueSprite = CMoveSprite::create(SliderNames.c_str(),
			CCRectMake(0, 0, 1300, 900));
		return pDialogueSprite;
	}



protected:
	static CMoveSprite* create(const char* pszFileName, const CCRect& rect) {
		CMoveSprite* pDialogueSprite = new CMoveSprite();
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





	// [ ������ ]
	// ==============================================================================================================
public:
	void		setState() {
		setButtonSprite();
		setTextLabel();

	}


protected:
	LabelTTF* m_textLabel;
	cocos2d::Sprite* m_picture;

	void	setButtonSprite() {
		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)150, (float)70));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)750, (float)70));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)150, (float)270));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)750, (float)270));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)150, (float)470));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)750, (float)470));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)150, (float)670));
		addChild(m_picture, 3);

		m_picture = cocos2d::Sprite::create("moveButton.png");
		m_picture->setPosition(cocos2d::CCPointZero);
		m_picture->setAnchorPoint(ccp((float)0, (float)0));
		m_picture->setPosition(ccp((float)750, (float)670));
		addChild(m_picture, 3);
	}
	void setTextLabel() {
		std::string str = "�����";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(200, 670));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "�н�";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(800, 670));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "4���а�";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(200, 470));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "�ι��濵��";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(800, 470));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "������а�";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(200, 270));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "������";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(800, 270));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "����";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(200, 70));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		str = "���";
		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(400, 100), TextHAlignment::LEFT, TextVAlignment::CENTER);
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(800, 70));
		m_textLabel->setColor(Color3B(0, 0, 0));
		addChild(m_textLabel, 4);

		
	}

	// ==============================================================================================================
};
#endif MOVE_SPRITE