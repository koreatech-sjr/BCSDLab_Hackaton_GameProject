#ifndef CCLOCK
#define CCLOCK

#include "Common.h"
#include "Character.h"
#include "DataSingleton.h"

class CClock : public Sprite {
	// [ 기본 ]
	// ==============================================================================================================
public:
	CClock() {
		m_textLabel = NULL;

		pDataSingleton->getInstance();
		pCharacter = pDataSingleton->getCharacter();
	}
	virtual ~CClock() {}

	static CClock* Create() {
		static std::string SliderNames ="DiaLogueBox.png";

		CClock* pCClock = CClock::create(SliderNames.c_str(),
			CCRectMake(0, 0, 350, 250));
		return pCClock;
	}

protected:
	static CClock* create(const char* pszFileName, const CCRect& rect) {
		CClock* pCClock = new CClock();
		if (pCClock && pCClock->initWithFile(pszFileName, rect)) {
			pCClock->autorelease();
			return pCClock;
		}
		CC_SAFE_DELETE(pCClock);
		return NULL;
	}

	Character* pCharacter;
	CDataSingleton* pDataSingleton;
	// ==============================================================================================================





	// [ 데이터 ]
	// ==============================================================================================================
public:
	void		setClock() {
		setTextLabel();
	}

	protected:
	LabelTTF* m_textLabel; 


	void setTextLabel() {
		std::string str = "";
		

		int time = (pCharacter->getHour());
		int minute = (pCharacter->getTime());
		str += Common::timeFormat(time);
		str += " : ";
		str += Common::timeFormat(minute);
		str += "\n";
		str += std::to_string(pCharacter->getYear());
		str += ".";
		str += Common::timeFormat(pCharacter->getMonth());
		str += ".";
		str += Common::timeFormat(pCharacter->getDay());
		str += " ";
		str += pCharacter->getWeek();


		m_textLabel = LabelTTF::create(str, "Arial", 55,
			Size(350, 200), TextHAlignment::CENTER, TextVAlignment::TOP);

		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(0, 0));
		m_textLabel->setColor(Color3B(255, 255, 255));
		addChild(m_textLabel, 1);
	}
};

#endif CCLOCK