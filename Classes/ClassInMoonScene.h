#ifndef CLASS_INMOON_SCENE
#define CLASS_INMOON_SCENE

#include "Common.h"
#include "DialogueSprite.h"
#include "Character.h"
#include "DataSingleton.h"

class ClassInMoonScene : public cocos2d::Layer
{
	// [ 기본 ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = ClassInMoonScene::create();
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
		cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("map4a.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// 터치 초기화
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(ClassInMoonScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(ClassInMoonScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(ClassInMoonScene::onTouchesEnded, this);
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

		// 싱글톤
		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();

		// 랜덤 시드
		srand((unsigned)time(NULL));

		// 변수 초기화
		typeIndex = 0;
		skip = false;
		typeEnd = false;
		progress = 0;



		return true;
	}
	CREATE_FUNC(ClassInMoonScene);

	void update(float dt) {
		static int cnt = 0;
		cnt++;

		if (progress == 0) {
			if (cnt % 5 == 0) {
				int t = pCharacter->getHour();
				int m = pCharacter->getTime();
				int w = pCharacter->getDay()%7;
				if(((t == 15 && m>=50) || (t ==  16 && m==0)) && w == 6) {
					typeText("제시간에  수업시간에  도착했다.");
					mode = 1;
				}
				else if(((t == 10 && m>=50) || (t ==  11 && m==0)) && w == 2) {
					typeText("제시간에  수업시간에  도착했다.");
					mode = 2;
				}
				else if(((t ==  16 && m >= 10) && w == 6)) {
					typeText("제시간에  도착하지  못하였다.\n지각처리가  되었다.");
					mode = 3;
				}
				else if(((t ==  11 && m >= 10) && w == 2)) {
					typeText("제시간에  도착하지  못하였다.\n지각처리가  되었다.");
					mode = 4;
				}
				else if ((t == 12 && m>00) && w == 2) {
					typeText("너무  늦게  도착하였다.\n결석처리가  되었다.");
						mode = 5;
				}
				else {
					typeText("지금은  수업시간이  아니다.");
				}
			}
		}
		if (progress == 1) {
			std::string str = "▶수업듣기 :스트레스+15 피로도+10\n▶딴짓하기 :스트레스+5 피로도+5\n▶도망가기 :스트레스-5";
			removeChild(pDialogueSprite->getTextLabel(), true);
			pDialogueSprite->setText(str);
			pDialogueSprite->setTextLabel();
			addChild(pDialogueSprite->getTextLabel(), 4);
			typeEnd = true;
		}
		if (progress == 2) {
			if (cnt % 5 == 0) {
				int random = rand() % 10;
				pCharacter->addMoney(-2200);
				if(random < 2) {
					if(typeText("수업이  이해가  잘  된다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+9);
					pCharacter->addTiredness(+12);
				}
				else if(random < 8) {
					if(typeText("뭐라고  하는지  모르겠다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+15);
					pCharacter->addTiredness(+10);
				}
				else {
					if(typeText("죽고  싶다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+18);
					pCharacter->addTiredness(+6);
				}
			}
		}

		if (progress == 3) {
			if (cnt % 5 == 0) {
				int random = rand() % 10;
				pCharacter->addMoney(-3000);
				if(random < 2) {
					if(typeText("교수님이  전혀  신경을  쓰지 않는다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+3);
					pCharacter->addTiredness(+3);
				}
				else if(random < 8) {
					if(typeText("딴짓을  들키지  않았다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+5);
					pCharacter->addTiredness(+5);
				}
				else {
					if(typeText("교수님께  지적을  받았다.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+6);
					pCharacter->addTiredness(+6);
				}
			}
		}
		if (progress == 4) {
			int random = rand() % 10;
			pCharacter->addMoney(-3000);
			if(random < 8) {
				pCharacter->addStress(-5);
				if(typeText("성공적으로  도망갔다.\n")) {
					progress = 5;
				}

			}
			else {
				pCharacter->addStress(+10);
				if(typeText("교수님께서  출석을  다시  부르셨다고  한다.\n결석처리가  되었다.")) {
					progress = 5;
				}
			}

		}
	}

protected:
	Character* pCharacter;
	CDataSingleton* pDataSingleton;
	CDialogueSprite* pDialogueSprite;
	int typeIndex;
	bool skip;
	bool typeEnd;
	bool buttonMode;
	int progress;
	int m_time;
	int mode;

	bool typeText(std::string str) {
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
			return true;
		}
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

		if (!typeEnd) {
			skip = true;
			return;
		}
		if (typeEnd && progress == 0) {
			typeEnd = false;
			skip = false;
			int t = pCharacter->getHour();
			if(mode == 1) {
				progress = 1;
				pCharacter->goTime(50);
			}
			else if(mode == 2) {
				progress = 1;
				pCharacter->goTime(50);
				pCharacter->goTime(50);
			} 
			else if(mode == 3) {
				progress = 1;
				pCharacter->goTime(50);
			} else if(mode == 4) {
				progress = 1;
				pCharacter->goTime(50);
				pCharacter->goTime(50);
			} 
			else if(mode == 5) {
				progress = 1;
				pCharacter->goTime(50);
				pCharacter->goTime(50);
			}else {
				Director::getInstance()->popScene();
			}
			//else
			//Director::getInstance()->popScene();
			return;
		}

		// 선택지 ----------------------
		if (isInButton1(point) && progress == 1) {
			skip = false;
			progress = 2;
			return;
		}
		if (isInButton2(point) && progress == 1) {
			skip = false;
			progress = 3;
			return;
		}
		if (isInButton3(point) && progress == 1) {
			skip = false;
			progress = 4;
			if( mode == 1 || mode == 3) {
				pCharacter->setTime(10);
			}
			if( mode == 2 || mode == 4 || mode == 5) {
				pCharacter->setTime(10);
				pCharacter->addHour(-1);
			}
			return;
		}
		// end of 선택지 ---------------

		if (typeEnd && progress == 5) {
			Director::getInstance()->popScene();
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
#endif CLASS_INMOON_SCENE