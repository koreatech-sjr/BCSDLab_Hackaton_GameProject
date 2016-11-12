#ifndef MAIN_SCENE
#define MAIN_SCENE

#include "Common.h"
#include "StateSprite.h"
#include "MoveSprite.h"
#include "Clock.h";
#include "Character.h"
#include "DataSingleton.h"
#include "CafeteriaScene.h"

#define	NORMAL		0
#define STATE		1
#define SCHEDULE	2
#define	MOVE		3
#define ENTER		4

class MainScene : public cocos2d::Layer
{
// [ 기본 ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = MainScene::create();
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

		// 싱글톤
		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();
		
		// 배경 이미지 출력
		pBackgroundSprite = cocos2d::Sprite::create("map1.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// 터치 초기화
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		m_bTouchPresented = false;
		m_bTouchMoved = false;

		// UI 버튼
		cocos2d::Sprite* pButton1 = cocos2d::Sprite::create("UiButton1.png");
		pButton1->setPosition(cocos2d::CCPointZero);
		pButton1->setAnchorPoint(ccp((float)0, (float)0));
		pButton1->setPosition(ccp((float)50, (float)750));
		addChild(pButton1, 1);

		cocos2d::Sprite* pButton2 = cocos2d::Sprite::create("UiButton2.png");
		pButton2->setPosition(cocos2d::CCPointZero);
		pButton2->setAnchorPoint(ccp((float)0, (float)0));
		pButton2->setPosition(ccp((float)50, (float)450));
		addChild(pButton2, 1);


		cocos2d::Sprite* pButton3 = cocos2d::Sprite::create("UiButton3.png");
		pButton3->setPosition(cocos2d::CCPointZero);
		pButton3->setAnchorPoint(ccp((float)0, (float)0));
		pButton3->setPosition(ccp((float)50, (float)150));
		addChild(pButton3, 1);


		// UI 버튼 텍스트
		LabelTTF* ButtonText1 = LabelTTF::create("상태창", "Arial", 40,
			Size(150, 100), TextHAlignment::CENTER, TextVAlignment::BOTTOM);
		ButtonText1->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		ButtonText1->setPosition(ccp((float)50, (float)700));
		ButtonText1->setColor(Color3B(255, 255, 255));
		addChild(ButtonText1, 1);

		LabelTTF* ButtonText2 = LabelTTF::create("일정관리", "Arial", 40,
			Size(150, 100), TextHAlignment::CENTER, TextVAlignment::BOTTOM);
		ButtonText2->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		ButtonText2->setPosition(ccp((float)50, (float)400));
		ButtonText2->setColor(Color3B(255, 255, 255));
		addChild(ButtonText2, 1);

		LabelTTF* ButtonText3 = LabelTTF::create("이동하기", "Arial", 40,
			Size(150, 100), TextHAlignment::CENTER, TextVAlignment::BOTTOM);
		ButtonText3->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		ButtonText3->setPosition(ccp((float)50, (float)100));
		ButtonText3->setColor(Color3B(255, 255, 255));
		addChild(ButtonText3, 1);

		// 추가 버튼
		setButton4(550, 600, "생활관");
		
		// UI 시계
		pClock = CClock::Create();
			pClock->setPosition(cocos2d::CCPointZero);
			pClock->setAnchorPoint(ccp((float)0, (float)0));
			pClock->setPosition(ccp((float)DESIGN_WIDTH-350, (float)DESIGN_HEIGHT-250));
			pClock->setClock();
			addChild(pClock, 2);
			

		// 키보드 초기화
		this->setKeypadEnabled(true);
		m_EndKeyStack = 0;

		// 변수 초기화
		mode = NORMAL;
		location = 1;

		// 타이머
		this->scheduleUpdate();

		return true;
	}
	CREATE_FUNC(MainScene);


	void update(float dt) {
		static int cnt = 0;
		cnt++;

		releaseClock();

		if (cnt == 1) {
			//auto scene = StartScene::createScene();
			//Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(255, 255, 255)));
			
		}
	}

protected:
	Character* pCharacter;
	CDataSingleton* pDataSingleton;

	std::string m_clock;
	LabelTTF* m_clockLabel;
	cocos2d::Sprite* pBackgroundSprite;
	int location;
	cocos2d::Sprite*	pButton4;
	cocos2d::Sprite*	pButton5;
	LabelTTF*			ButtonText4;
	LabelTTF*			ButtonText5;

	void setButton4(float x, float y, std::string str) {
		pButton4 = cocos2d::Sprite::create("UiButton4.png");
		pButton4->setPosition(cocos2d::CCPointZero);
		pButton4->setAnchorPoint(ccp((float)0, (float)0));
		pButton4->setPosition(ccp((float)x, (float)y));
		addChild(pButton4, 1);

		ButtonText4 = LabelTTF::create(str, "Arial", 40,
			Size(150, 100), TextHAlignment::CENTER, TextVAlignment::BOTTOM);
		ButtonText4->setAnchorPoint(ccp((float)0, (float)0));
		ButtonText4->setPosition(ccp((float)x, (float)y-50));
		ButtonText4->setColor(Color3B(255, 255, 255));
		addChild(ButtonText4, 1);
	}
	void setButton5(float x, float y, std::string str) {
		pButton5 = cocos2d::Sprite::create("UiButton4.png");
		pButton5->setPosition(cocos2d::CCPointZero);
		pButton5->setAnchorPoint(ccp((float)0.0, (float)0.0));
		pButton5->setPosition(ccp((float)x, (float)y));
		addChild(pButton5, 1);
		ButtonText5 = LabelTTF::create(str, "Arial", 40,
			Size(150, 100), TextHAlignment::CENTER, TextVAlignment::BOTTOM);
		ButtonText5->setAnchorPoint(ccp((float)0.0, (float)0.0));
		ButtonText5->setPosition(ccp((float)x, (float)y-50));
		ButtonText5->setColor(Color3B(255, 255, 255));
		addChild(ButtonText5, 1);
	}
	void removeButton() {
		removeChild(pButton4, true);
		removeChild(pButton5, true);
		removeChild(ButtonText4, true);
		removeChild(ButtonText5, true);
	}
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


		// UI 버튼
		if(isButton1(point) && mode!=STATE) {
			removeAllPopUp();

			pStateSprite = CStateSprite::Create();
			pStateSprite->setPosition(cocos2d::CCPointZero);
			pStateSprite->setAnchorPoint(ccp((float)0, (float)0));
			pStateSprite->setPosition(ccp((float)250, (float)50));
			pStateSprite->setState();
			addChild(pStateSprite, 2);

			mode = STATE;
		}
		else if(isButton1(point) && mode == STATE) {
			removeAllPopUp();	
			mode = NORMAL;
		}

		if(isButton2(point) && mode!=SCHEDULE) {
			removeAllPopUp();
			pPopUp = cocos2d::Sprite::create("schedule.png");
			pPopUp->setPosition(cocos2d::CCPointZero);
			pPopUp->setAnchorPoint(ccp((float)0, (float)0));
			pPopUp->setPosition(ccp((float)250, (float)50));
			addChild(pPopUp, 2);

			mode = SCHEDULE;
		}
		else if(isButton2(point) && mode == SCHEDULE) {
			removeAllPopUp();
			mode = NORMAL;
		}

		if(isButton3(point) && mode!=MOVE) {
			removeAllPopUp();

			pMoveSprite = CMoveSprite::Create();
			pMoveSprite->setPosition(cocos2d::CCPointZero);
			pMoveSprite->setAnchorPoint(ccp((float)0, (float)0));
			pMoveSprite->setPosition(ccp((float)250, (float)50));
			pMoveSprite->setState();
			addChild(pMoveSprite, 2);

			mode = MOVE;
		}
		else if(isButton3(point) && mode == MOVE) {
			removeAllPopUp();
			mode = NORMAL;
		}

		// 생활관 입장 버튼
		if(isButton11(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 1) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 학식 입장 버튼
		if(isButton21(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 2) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 동방 입장 버튼
		if(isButton22(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 2) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 4공 강의실 입장 버튼
		if(isButton31(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 3) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 인경 강의실 입장 버튼
		if(isButton41(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 4) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 담헌 강의실 입장 버튼
		if(isButton51(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 5) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 신한은행 입장 버튼
		if(isButton61(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 6) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}
		// 우체국 입장 버튼
		if(isButton62(point) && mode!=MOVE) {
			removeAllPopUp();
			if(location == 6) {
				auto scene = CafeteriaScene::createScene();
				Director::getInstance()->pushScene(TransitionFade::create(1.5, scene, Color3B(0, 0, 0)));
				releaseClock();
			}
			mode = NORMAL;
		}

		


		// 이동 버튼
		if(isMoveButton1(point) && mode == MOVE) {
			location = 1;
			moveMap("map1.png");
			removeButton();
			setButton4(550, 600, "생활관");
			mode = NORMAL;
		}
		if(isMoveButton2(point) && mode == MOVE) {
			location = 2;
			moveMap("map2.png");
			removeButton();
			setButton4(1200, 500, "동아리방");
			setButton5(600, 400, "학생식당");
			mode = NORMAL;
		}
		if(isMoveButton3(point) && mode == MOVE) {
			location = 3;
			moveMap("map3.png");
			setButton4(600, 400, "강의실");
			removeButton();
			mode = NORMAL;
		}
		if(isMoveButton4(point) && mode == MOVE) {
			location = 4;
			moveMap("map4.png");
			removeButton();
			setButton4(600, 600, "강의실");
			mode = NORMAL;
		}
		if(isMoveButton5(point) && mode == MOVE) {
			location = 5;
			moveMap("map5.png");
			removeButton();
			setButton4(350, 600, "강의실");
			mode = NORMAL;
		}
		if(isMoveButton6(point) && mode == MOVE) {
			location = 6;
			moveMap("map6.png");
			removeButton();
			setButton4(350, 400, "신한은행");
			setButton5(700, 400, "우체국");
			mode = NORMAL;
		}
		if(isMoveButton7(point) && mode == MOVE) {
			location = 7;
			moveMap("map7.png");
			removeButton();
			mode = NORMAL;
		}
		if(isMoveButton8(point) && mode == MOVE) {
			location = 8;
			moveMap("map8.png");
			removeButton();
			mode = NORMAL;
		}

	}

protected:
	int mode;
	cocos2d::Sprite*	pPopUp;
	CStateSprite*		pStateSprite;
	CMoveSprite*		pMoveSprite;
	CClock*				pClock;


	int m_EnableTouch;		// 터치 on/off
	bool m_bTouchPresented;	// 터치가 시작되었는지
	bool m_bTouchMoved;		// 드래그한 적이 있는지
	Point m_gesturePresentPoint;	// 터치가 시작된 좌표
	Point m_gesturePresentOrigin;

	void moveMap(char* fname) {
			removeAllPopUp();
			removeChild(pBackgroundSprite, true);
			mode = NORMAL;
			pBackgroundSprite = cocos2d::Sprite::create(fname);
			pBackgroundSprite->setPosition(cocos2d::CCPointZero);
			pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
			pBackgroundSprite->setPosition(ccp((float)0, (float)0));
			addChild(pBackgroundSprite, 0);

			pCharacter->addTime(10);
			releaseClock();
	}

	void releaseClock() {
		removeChild(pClock);
		pClock = CClock::Create();
			pClock->setPosition(cocos2d::CCPointZero);
			pClock->setAnchorPoint(ccp((float)0, (float)0));
			pClock->setPosition(ccp((float)DESIGN_WIDTH-350, (float)DESIGN_HEIGHT-250));
			pClock->setClock();
			addChild(pClock, 2);
	}
	void removeAllPopUp() {
		// 상태창 제거
		removeChild(pStateSprite);
		// 시간표 제거
		removeChild(pPopUp);
		// 이동하기 제거
		removeChild(pMoveSprite);

		mode = NORMAL;
	}
	bool isButton1(Point point) {
		if (point.x < 50 || point.x > 200) return false;
		if (point.y < 750 || point.y > 900) return false;
		return true;
	}
	bool isButton2(Point point) {
		if (point.x < 50 || point.x > 200) return false;
		if (point.y < 450 || point.y > 600) return false;
		return true;
	}
	bool isButton3(Point point) {
		if (point.x < 50 || point.x > 200) return false;
		if (point.y < 150 || point.y > 300) return false;
		return true;
	}
	bool isButton11(Point point) {
		int xx = 550;
		int yy = 600;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton21(Point point) {
		int xx = 600;
		int yy = 400;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton22(Point point) {
		int xx = 600;
		int yy = 400;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton31(Point point) {
		int xx = 1200;
		int yy = 500;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton41(Point point) {
		int xx = 600;
		int yy = 400;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton51(Point point) {
		int xx = 350;
		int yy = 600;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton61(Point point) {
		int xx = 350;
		int yy = 400;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}
	bool isButton62(Point point) {
		int xx = 700;
		int yy = 400;
		if (point.x < xx || point.x > xx+150) return false;
		if (point.y < yy || point.y > yy+150) return false;
		return true;
	}

	// -----------------------
	bool isMoveButton7(Point point) {
		if (point.x < 300 || point.x > 750) return false;
		if (point.y < 120 || point.y > 220) return false;
		return true;
	}
	bool isMoveButton8(Point point) {
		if (point.x < 1000 || point.x > 1400) return false;
		if (point.y < 120 || point.y > 220) return false;
		return true;
	}
	bool isMoveButton5(Point point) {
		if (point.x < 300 || point.x > 750) return false;
		if (point.y < 320 || point.y > 420) return false;
		return true;
	}
	bool isMoveButton6(Point point) {
		if (point.x < 1000 || point.x > 1400) return false;
		if (point.y < 320 || point.y > 420) return false;
		return true;
	}
	bool isMoveButton3(Point point) {
		if (point.x < 300 || point.x > 750) return false;
		if (point.y < 520 || point.y > 620) return false;
		return true;
	}
	bool isMoveButton4(Point point) {
		if (point.x < 1000 || point.x > 1400) return false;
		if (point.y < 520 || point.y > 620) return false;
		return true;
	}
	bool isMoveButton1(Point point) {
		if (point.x < 300 || point.x > 750) return false;
		if (point.y < 720 || point.y > 820) return false;
		return true;
	}
	bool isMoveButton2(Point point) {
		if (point.x < 1000 || point.x > 1400) return false;
		if (point.y < 720 || point.y > 820) return false;
		return true;
	}
	
	// ==============================================================================================================





	// [ 키보드 제어 ]
	// ==============================================================================================================
public:
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keycode, cocos2d::Event *event)
	{
		if (keycode == EventKeyboard::KeyCode::KEY_BACK) {
			if(mode != NORMAL) {
				mode = NORMAL;
				removeChild(pPopUp);
			}
			else if (m_EndKeyStack > 0)
				Director::getInstance()->end();
			m_EndKeyStack++;
		}
	}
	protected:
	int m_EndKeyStack;

	// ==============================================================================================================
};

#endif MAIN_SCENE