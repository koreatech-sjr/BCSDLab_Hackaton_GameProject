#ifndef START_SCENE
#define START_SCENE

#include "Common.h"
#include "IntroScene.h"

class StartScene : public cocos2d::Layer
{
	// [ 기본 ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = StartScene::create();
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
		cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("background.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// 터치 초기화
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(StartScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(StartScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(StartScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		m_bTouchStarted = false;
		m_bTouchMoved = false;


		// 키보드 초기화
		this->setKeypadEnabled(true);
		m_EndKeyStack = 0;

		// 타이머
		this->scheduleUpdate();

		return true;
	}
	CREATE_FUNC(StartScene);


	void update(float dt) {
		static int cnt = 0;
		cnt++;

		// 일정 시간 마다 "터치하여 시작하기" 점멸
		if (cnt % 20 == 0) {
			static int frip = 1;
			frip = 1 - frip;

			cocos2d::Sprite* pStartBack = cocos2d::Sprite::create("startBack.png");
			cocos2d::Sprite* pStartText = cocos2d::Sprite::create("startText.png");

			if (frip == 0) {
				removeChild(pStartText);
				pStartBack->setPosition(cocos2d::CCPointZero);
				pStartBack->setAnchorPoint(ccp((float)0, (float)0));
				pStartBack->setPosition(ccp((float)0, (float)0));
				addChild(pStartBack, 1);
			}
			else {
				removeChild(pStartBack);
				pStartText->setPosition(cocos2d::CCPointZero);
				pStartText->setAnchorPoint(ccp((float)0, (float)0));
				pStartText->setPosition(ccp((float)0, (float)0));
				addChild(pStartText, 1);
			}
		}
	}

protected:
	// ==============================================================================================================





	// [ 터치 제어 ]
	// ==============================================================================================================
public:
	void onTouchesBegan(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {

	}
	void onTouchesMoved(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {

	}
	void onTouchesEnded(const std::vector<cocos2d::Touch*>&pTouches, cocos2d::Event* pEvent) {
		auto scene = IntroScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
	}

protected:

	int m_EnableTouch;		// 터치 on/off
	bool m_bTouchStarted;	// 터치가 시작되었는지
	bool m_bTouchMoved;		// 드래그한 적이 있는지
	Point m_gestureStartPoint;	// 터치가 시작된 좌표
	Point m_gestureStartOrigin;
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

#endif START_SCENE
