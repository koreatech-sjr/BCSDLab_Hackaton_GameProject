#ifndef CLASS_INMOON_SCENE
#define CLASS_INMOON_SCENE

#include "Common.h"
#include "DialogueSprite.h"
#include "Character.h"
#include "DataSingleton.h"

class ClassInMoonScene : public cocos2d::Layer
{
	// [ �⺻ ]
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


		// ��� �̹��� ���
		cocos2d::Sprite* pBackgroundSprite = cocos2d::Sprite::create("map4a.png");
		pBackgroundSprite->setPosition(cocos2d::CCPointZero);
		pBackgroundSprite->setAnchorPoint(ccp((float)0, (float)0));
		pBackgroundSprite->setPosition(ccp((float)0, (float)0));
		addChild(pBackgroundSprite, 0);

		// ��ġ �ʱ�ȭ
		EventListenerTouchAllAtOnce* listener = EventListenerTouchAllAtOnce::create();
		listener->onTouchesBegan = CC_CALLBACK_2(ClassInMoonScene::onTouchesBegan, this);
		listener->onTouchesMoved = CC_CALLBACK_2(ClassInMoonScene::onTouchesMoved, this);
		listener->onTouchesEnded = CC_CALLBACK_2(ClassInMoonScene::onTouchesEnded, this);
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
					typeText("���ð���  �����ð���  �����ߴ�.");
					mode = 1;
				}
				else if(((t == 10 && m>=50) || (t ==  11 && m==0)) && w == 2) {
					typeText("���ð���  �����ð���  �����ߴ�.");
					mode = 2;
				}
				else if(((t ==  16 && m >= 10) && w == 6)) {
					typeText("���ð���  ��������  ���Ͽ���.\n����ó����  �Ǿ���.");
					mode = 3;
				}
				else if(((t ==  11 && m >= 10) && w == 2)) {
					typeText("���ð���  ��������  ���Ͽ���.\n����ó����  �Ǿ���.");
					mode = 4;
				}
				else if ((t == 12 && m>00) && w == 2) {
					typeText("�ʹ�  �ʰ�  �����Ͽ���.\n�Ἦó����  �Ǿ���.");
						mode = 5;
				}
				else {
					typeText("������  �����ð���  �ƴϴ�.");
				}
			}
		}
		if (progress == 1) {
			std::string str = "��������� :��Ʈ����+15 �Ƿε�+10\n�������ϱ� :��Ʈ����+5 �Ƿε�+5\n���������� :��Ʈ����-5";
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
					if(typeText("������  ���ذ�  ��  �ȴ�.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+9);
					pCharacter->addTiredness(+12);
				}
				else if(random < 8) {
					if(typeText("�����  �ϴ���  �𸣰ڴ�.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+15);
					pCharacter->addTiredness(+10);
				}
				else {
					if(typeText("�װ�  �ʹ�.\n")) {
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
					if(typeText("��������  ����  �Ű���  ���� �ʴ´�.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+3);
					pCharacter->addTiredness(+3);
				}
				else if(random < 8) {
					if(typeText("������  ��Ű��  �ʾҴ�.\n")) {
						progress = 5;
					}
					pCharacter->addStress(+5);
					pCharacter->addTiredness(+5);
				}
				else {
					if(typeText("�����Բ�  ������  �޾Ҵ�.\n")) {
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
				if(typeText("����������  ��������.\n")) {
					progress = 5;
				}

			}
			else {
				pCharacter->addStress(+10);
				if(typeText("�����Բ���  �⼮��  �ٽ�  �θ��̴ٰ�  �Ѵ�.\n�Ἦó����  �Ǿ���.")) {
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
			if( mode == 1 || mode == 3) {
				pCharacter->setTime(10);
			}
			if( mode == 2 || mode == 4 || mode == 5) {
				pCharacter->setTime(10);
				pCharacter->addHour(-1);
			}
			return;
		}
		// end of ������ ---------------

		if (typeEnd && progress == 5) {
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
#endif CLASS_INMOON_SCENE