#ifndef CAFETERIA_SCENE
#define CAFETERIA_SCENE

#include "Common.h"
#include "DialogueSprite.h"
#include "Character.h"
#include "DataSingleton.h"

class CafeteriaScene : public cocos2d::Layer
{
	// [ �⺻ ]
	// ==============================================================================================================
public:
	static cocos2d::Scene* createScene() {
		auto scene = Scene::create();
		auto layer = CafeteriaScene::create();
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


		// ��� �̹��� ���
		cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("map2a.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// ��ġ �ʱ�ȭ
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(CafeteriaScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(CafeteriaScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(CafeteriaScene::onTouchesEnded, this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
		m_bTouchStarted = false;
		m_bTouchMoved = false;

		// ��ȭ ���� ���
		pDialogueSprite = CDialogueSprite::Create();
		pDialogueSprite->setPosition(cocos2d::CCPointZero);
		pDialogueSprite->setAnchorPoint(ccp((float)0.5, (float)0));
		pDialogueSprite->setPosition(ccp((float)DESIGN_WIDTH / 2, (float)50));
		pDialogueSprite->setTextLabel();
		addChild(pDialogueSprite, 3);

		// Ű���� �ʱ�ȭ
		this->setKeypadEnabled(true);
		m_EndKeyStack = 0;

		// Ÿ�̸�
		this->scheduleUpdate();

		// �̱���
		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();

		// ���� �õ�
		srand((unsigned)time(NULL));

		// ���� �ʱ�ȭ
		typeIndex = 0;
		skip = false;
		typeEnd = false;
		progress = 0;



		return true;
	}
	CREATE_FUNC(CafeteriaScene);

	void update(float dt) {
		static int cnt = 0;
		cnt++;
		
		if (progress == 0) {
			if (cnt % 5 == 0) {
					int t= pCharacter->getHour();
					if(t== 8 || t == 13 || t == 18) 
						typeText("�нĿ�  �����ߴ�.\n�޴���  �����ϼ���.");
					else {
						typeText("�н���  ��������  �ʴ�.");
					}
			}
		}
		if (progress == 1) {
			std::string str = "��1.�ѽ� - 2,000��  ��Ʈ���� -10\n��2.��ǰ - 3,000��  ��Ʈ���� -10\n��3.��� -3,000��  ��Ʈ���� -20";
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
					if(typeText("���ְ�  �Ծ���.\nȿ�� 120% ����")) {
						progress = 5;
					}
					pCharacter->addStress(-12);
				}
				else if(random < 8) {
					if(typeText("�谡  �θ���.\nȿ�� 100% ����")) {
						progress = 5;
					}
					pCharacter->addStress(-10);
				}
				else {
					if(typeText("����  ������.\nȿ�� 60%  ����")) {
						progress = 5;
					}
					pCharacter->addStress(-6);
				}
			}


		}

		if (progress == 3) {
			if (cnt % 5 == 0) {
				int random = rand() % 10;
				pCharacter->addMoney(-3000);
				if(random < 2) {
					pCharacter->addStress(-18);
					if(typeText("���ְ�  �Ծ���.\nȿ�� 120% ����")) {
						progress = 5;
					}
				}
				else if(random < 8) {
					pCharacter->addStress(-15);
					if(typeText("�谡  �θ���.\nȿ�� 100% ����")) {
						progress = 5;
					}
				}
				else {
					pCharacter->addStress(-9);
					if(typeText("����  ������.\nȿ�� 60%  ����")) {
						progress = 5;
					}
				}
			}
		}
		if (progress == 4) {
			int random = rand() % 10;
				pCharacter->addMoney(-3000);
				if(random < 2) {
					pCharacter->addStress(-24);
					if(typeText("���ְ�  �Ծ���.\nȿ�� 120% ����")) {
						progress = 5;
					}
					
				}
				else if(random < 8) {
					pCharacter->addStress(-20);
					if(typeText("�谡  �θ���.\nȿ�� 100% ����")) {
						progress = 5;
					}
				}
				else {
					pCharacter->addStress(-12);
					if(typeText("����  ������.\nȿ�� 60%  ����")) {
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





	// [ ��ġ ���� ]
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
			if(t== 8 || t == 13 || t == 18)
				progress = 1; 
			else
				Director::getInstance()->popScene();
			return;
		}

		// ������ ----------------------
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
			return;
		}
		// end of ������ ---------------

		if (typeEnd && progress == 5) {
			pCharacter->goTime(50);
			Director::getInstance()->popScene();
			return;
		}
	}

protected:
	int m_EnableTouch;		// ��ġ on/off
	bool m_bTouchStarted;	// ��ġ�� ���۵Ǿ�����
	bool m_bTouchMoved;		// �巡���� ���� �ִ���
	Point m_gestureStartPoint;	// ��ġ�� ���۵� ��ǥ
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






	// [ Ű���� ���� ]
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
#endif CAFETERIA_SCENE