#ifndef INTRO_SCENE
#define INTRO_SCENE

#include "Common.h"
#include "DialogueScene.h"
#include "DialogueSprite.h"
#include "SelectCharScene.h"

class IntroScene : public DialogueScene
{
	// [ 기본 ]
	// ==============================================================================================================
public:
	
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = IntroScene::create();
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
		pBackgroundSprite = cocos2d::Sprite::create("intro0.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// 터치 초기화
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(IntroScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(IntroScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(IntroScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		m_bTouchStarted = false;
		m_bTouchMoved = false;

		// 대화 상자 출력
		pDialogueSprite = CDialogueSprite::Create();
		pDialogueSprite->setPosition(cocos2d::CCPointZero);
		pDialogueSprite->setAnchorPoint(ccp((float)0.5, (float)0));
		pDialogueSprite->setPosition(ccp((float)DESIGN_WIDTH / 2, (float)50));
		pDialogueSprite->setTextLabel();
		addChild(pDialogueSprite, 3);

		// 키보드 초기화
		this->setKeypadEnabled(true);
		m_EndKeyStack = 0;

		// 타이머
		this->scheduleUpdate();


		// 변수 초기화
		typeIndex = 0;
		skip = false;
		typeEnd = false;
		progress = 0;

		return true;
	}
	CREATE_FUNC(IntroScene);

	void update(float dt) {
		static int cnt = 0;
		cnt++;

		if (progress == 0) {
			if (cnt % 5 == 0) {
				typeText("당신은  컴퓨터공학부  신입생입니다. \n1학기  동안  학교생활을  열심히  해서  살아남으십니오.");	
			}
		}
		if (progress == 1) {
			if (cnt % 5 == 0) {
				changePicture("intro1.png");
				typeText("당신의  선택에  따라  미래가  바뀝니다.\n올바른  선택을  기대하겠습니다.\n멋진  신입생이  되십시오.");
			}
		}
		if (progress == 2) {
			if (cnt % 5 == 0) {
				changePicture("intro2.png");
				typeText("2017년 3월 2일  목요일 \n당신은  즐거운  대학생활을  꿈꾸며  입학하게  되었습니다.");

			}
		}

	}

protected:
	CDialogueSprite* pDialogueSprite;
	cocos2d::Sprite* pBackgroundSprite;
	int typeIndex;
	bool skip;
	bool typeEnd;
	bool buttonMode;
	int progress;

	void typeText(std::string str) {
		int length = str.length();
		if (!skip) {
			str = str.substr(0, typeIndex);
			typeEnd = false;
		}
		removeChild(pDialogueSprite->getTextLabel(), true);
		pDialogueSprite->setText(str);
		pDialogueSprite->setTextLabel();
		addChild(pDialogueSprite->getTextLabel(), 4);


		typeIndex += 2;


		if (typeIndex >= length) {
			typeEnd = true;
		}
	}
	void changePicture(char* fname) {
		removeChild(pBackgroundSprite);
		pBackgroundSprite = cocos2d::Sprite::create(fname);
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);
	}
	/*
	bool isInASCIIset(char ch) {
		for (int i = 0; i < 127; i++) {
			if (ch == i) return true;
		}
		return false;
	}
	*/

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

		
		if (!typeEnd) {
			skip = true;
			return;
		}
		
		
		if (typeEnd && progress == 0) {
			progress = 1; 
			typeEnd = false;
			skip = false;
			typeIndex = 0;
			return;
		}
		if (typeEnd && progress == 1) {
			progress = 2;
			typeEnd = false;
			skip = false;
			typeIndex = 0;
			return;
		}
		if (typeEnd && progress == 2) {
			auto scene = SelectCharScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0, scene, Color3B(0, 0, 0)));
			return;
		}
		
		

		
	}

protected:
	int m_EnableTouch;		// 터치 on/off
	bool m_bTouchStarted;	// 터치가 시작되었는지
	bool m_bTouchMoved;		// 드래그한 적이 있는지
	Point m_gestureStartPoint;	// 터치가 시작된 좌표
	Point m_gestureStartOrigin;

	bool isInButton1(Point point) {
		if (point.x < 110 || point.x > 1810) return false;
		if (point.y < 216 || point.y > 300) return false;
		return true;
	}
	bool isInButton2(Point point) {
		if (point.x < 110 || point.x > 1810) return false;
		if (point.y < 133 || point.y > 216) return false;
		return true;
	}
	bool isInButton3(Point point) {
		if (point.x < 110 || point.x > 1810) return false;
		if (point.y < 50 || point.y > 133) return false;
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
#endif INTRO_SCENE