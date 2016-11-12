#ifndef SELECT_CHAR_SCENE
#define SELECT_CHAR_SCENE

#include "Common.h"
#include "Character.h"
#include "DataSingleton.h"
#include "MainScene.h"

#define SELECT		0
#define PREVIEW		1

class SelectCharScene : public cocos2d::Layer
{
	// [ 기본 ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = SelectCharScene::create();
		scene->addChild(layer);

		return scene;
	}
	virtual bool init() {
		if (!Layer::init())
		{
			return false;
		}

		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();


		// 배경 이미지 출력
		cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("selectChar.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// 버튼 생성
		{
			cocos2d::Sprite* p = cocos2d::Sprite::create("char1.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)100, (float)500));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)450, (float)500));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)800, (float)500));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)1150, (float)500));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)1500, (float)500));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)100, (float)100));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)450, (float)100));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)800, (float)100));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)1150, (float)100));
			addChild(p, 1);

			p = cocos2d::Sprite::create("unknownChar.png");
			p->setPosition(cocos2d::CCPointZero);
			p->setAnchorPoint(ccp((float)0, (float)0));
			p->setPosition(ccp((float)1500, (float)100));
			addChild(p, 1);
		}

		// 터치 초기화
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(SelectCharScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(SelectCharScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(SelectCharScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		m_bTouchStarted = false;
		m_bTouchMoved = false;


		// 키보드 초기화
		this->setKeypadEnabled(true);
		m_EndKeyStack = 0;

		// 타이머
		this->scheduleUpdate();

		// 싱글톤
		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();

		// 변수 초기화
		mode = PREVIEW;

		return true;
	}
	CREATE_FUNC(SelectCharScene);


	void update(float dt) {
		static int cnt = 0;
		cnt++;

		
	}

protected:
	Character* pCharacter;
	CDataSingleton* pDataSingleton;
	// ==============================================================================================================





	// [ 터치 제어 ]
	// ==============================================================================================================
public:
	void onTouchesBegan(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {

	}
	void onTouchesMoved(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {

	}
	void onTouchesEnded(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {
		Touch* pTouch = (Touch*)pTouches.back();
		Point point = pTouch->getLocation();


		if (isButton1(point) && mode == PREVIEW) {
			pBack = cocos2d::Sprite::create("char1pre.png");
			pBack->setPosition(cocos2d::CCPointZero);
			pBack->setAnchorPoint(ccp((float)0, (float)0));
			pBack->setPosition(ccp((float)0, (float)0));
		
			addChild(pBack, 2);
			myCharacter = 1;
			mode = SELECT;
		}
		if (isBack(point) && mode == SELECT) {
			removeChild(pBack, true);
			mode = PREVIEW;
		}
		if (isNext(point) && mode == SELECT) {
			removeChild(pBack, true);
			pCharacter->setMyCharacter(myCharacter);
			
			auto scene = MainScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(2.0, scene, Color3B(0, 0, 0)));
		}
	}

protected:
	int myCharacter;
	bool mode;
	int m_EnableTouch;		// 터치 on/off
	bool m_bTouchStarted;	// 터치가 시작되었는지
	bool m_bTouchMoved;		// 드래그한 적이 있는지
	Point m_gestureStartPoint;	// 터치가 시작된 좌표
	Point m_gestureStartOrigin;
	cocos2d::Sprite* pBack;

	bool isNext(Point point) {
		if (point.x < 1670 || point.x > 1920) return false;
		if (point.y < 830 || point.y > 1080) return false;
		return true;
	}
	bool isBack(Point point) {
		if (point.x < 0 || point.x > 250) return false;
		if (point.y < 830 || point.y > 1080) return false;
		return true;
	}
	bool isButton1(Point point) {
		if (point.x < 100 || point.x > 350) return false;
		if (point.y < 500 || point.y > 750) return false;
		return true;
	}
	bool isButton2(Point point) {
		if (point.x < 450 || point.x >700) return false;
		if (point.y < 500 || point.y > 750) return false;
		return true;
	}
	bool isButton3(Point point) {
		if (point.x < 800 || point.x >1050) return false;
		if (point.y < 500 || point.y > 750) return false;
		return true;
	}
	bool isButton4(Point point) {
		if (point.x <1150 || point.x >1400) return false;
		if (point.y < 500 || point.y > 750) return false;
		return true;
	}
	bool isButton5(Point point) {
		if (point.x < 1500 || point.x >1750) return false;
		if (point.y < 500 || point.y > 750) return false;
		return true;
	}
	bool isButton6(Point point) {
		if (point.x < 100 || point.x > 350) return false;
		if (point.y < 100 || point.y > 350) return false;
		return true;
	}
	bool isButton7(Point point) {
		if (point.x < 450|| point.x >700) return false;
		if (point.y < 100 || point.y > 350) return false;
		return true;
	}
	bool isButton8(Point point) {
		if (point.x < 800|| point.x >1050) return false;
		if (point.y < 100 || point.y > 350) return false;
		return true;
	}
	bool isButton9(Point point) {
		if (point.x <1150 || point.x >1400) return false;
		if (point.y < 100 || point.y > 350) return false;
		return true;
	}
	bool isButton10(Point point) {
		if (point.x < 1500|| point.x >1750) return false;
		if (point.y < 100 || point.y > 350) return false;
		return true;
	}
	
	// ==============================================================================================================





	// [ 키보드 제어 ]
	// ==============================================================================================================
public:
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
			if (m_EndKeyStack > 0)
				Director::getInstance()->end();
			m_EndKeyStack++;
		}
	}


protected:
	int m_EndKeyStack;

	// ==============================================================================================================
};

#endif SELECT_CHAR_SCENE
