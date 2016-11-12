#ifndef DIALOGUE_SPRITE
#define DIALOGUE_SPRITE

#include "Common.h"

class CDialogueSprite : public Sprite {
	// [ 기본 ]
	// ==============================================================================================================
public:
	CDialogueSprite() {
		m_textLabel = NULL;
		m_text = "";

	}
	virtual ~CDialogueSprite() {}

	static CDialogueSprite* Create() {
		static std::string SliderNames ="DiaLogueBox.png";

		CDialogueSprite* pDialogueSprite = CDialogueSprite::create(SliderNames.c_str(),
			CCRectMake(0, 0, 1700, 250));
		return pDialogueSprite;
	}


protected:
	static CDialogueSprite* create(const char* pszFileName, const CCRect& rect) {
		CDialogueSprite* pDialogueSprite = new CDialogueSprite();
		if (pDialogueSprite && pDialogueSprite->initWithFile(pszFileName, rect)) {
			pDialogueSprite->autorelease();
			return pDialogueSprite;
		}
		CC_SAFE_DELETE(pDialogueSprite);
		return NULL;
	}

	// ==============================================================================================================





	// [ 데이터 ]
	// ==============================================================================================================
public:
	std::string getText()						{ return m_text; }
	void		setText(std::string text)		{ m_text = text; }
	int			getLength()						{ return m_text.length(); }

	LabelTTF*	getTextLabel()		{ return (m_textLabel) ? m_textLabel : NULL; }
	void		setTextLabel()		{
		std::string strtext = m_text;

			m_textLabel = LabelTTF::create(strtext, "Arial", 65,
			Size(1700, 300), TextHAlignment::LEFT, TextVAlignment::TOP);

			
		m_textLabel->setAnchorPoint(ccp((float)0.0f, (float)0.0f));
		m_textLabel->setPosition(ccp(150, -15));
		m_textLabel->setColor(Color3B(255, 255, 255));
	}

	void clone(CDialogueSprite* p) {
		m_text = p->getText();
	}

protected:
	std::string m_text;
	LabelTTF* m_textLabel;
	// ==============================================================================================================
};
#endif