#ifndef DIALOGUE_SCENE
#define DIALOGUE_SCENE

#include "Common.h"
#include "DialogueSprite.h"

class DialogueScene : public cocos2d::Layer
{
	// [ 기본 ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = DialogueScene::create();
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
		listener->onTouchesBegan = CC_CALLBACK_2(DialogueScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(DialogueScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(DialogueScene::onTouchesEnded, this);
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
	CREATE_FUNC(DialogueScene);

	void update(float dt) {
		static int cnt = 0;
		cnt++;

		if (progress == 0) {
			if (cnt % 5 == 0) {
				typeText("한글한글 \n대사를 \n이  곳에  입력합니다.");
			}
		}
		if (progress == 1) {
				std::string str = "▶버튼1 \n▶버튼2 \n▶버튼3";
				removeChild(pDialogueSprite->getTextLabel(), true);
				pDialogueSprite->setText(str);
				pDialogueSprite->setTextLabel();
				addChild(pDialogueSprite->getTextLabel(), 4);
				typeEnd = true;
		}
		if (progress == 2) {
			if (cnt % 5 == 0) {

				typeText("버튼1 눌렸음");
			}
		}
		if (progress == 3) {
			if (cnt % 5 == 0) {
				typeText("버튼2 눌렸음");
			}
		}
		if (progress == 4) {
			if (cnt % 5 == 0) {
				typeText("버튼3 눌렸음");
			}
		}

	}

protected:
	CDialogueSprite* pDialogueSprite;
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

		if (typeIndex >= length) typeEnd = true;
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
			progress = 1; 
			return;
		}
		
		// 선택지 ----------------------
		if (isInButton1(point) && progress == 1) {
			typeEnd = false;
			progress = 2;
			return;
		}
		if (isInButton2(point) && progress == 1) {
			typeEnd = false;
			progress = 3;
			return;
		}
		if (isInButton3(point) && progress == 1) {
			typeEnd = false;
			progress = 4;
			return;
		}
		// end of 선택지 ---------------
		
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
#endif DIALOGUE_SCENE