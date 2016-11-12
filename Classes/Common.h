#ifndef common
#define common

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <locale>

USING_NS_CC;

#define DESIGN_WIDTH	1920.0f
#define DESIGN_HEIGHT	1080.0f

class Common {
public:
	// ¼ýÀÚ format - ÄÞ¸¶
	static std::string FormatWithCommas(int value) {
		std::string strValueTS;

		int j, i = 0, k = 0;
		int temp = value;
		int p = 1;
		while (temp > 0) {
			temp /= 10;
			p *= 10;
			i++;
		}
		j = i % 3;
		p /= 10;

		while (i > 0) {
			strValueTS += char((value / p) + '0');
			value %= p;
			p /= 10;
			i--;
			k++;
			j--;
			if ((k % 3 == 0 && i > 0) || (j == 0 && i > 2)) {
				strValueTS += ",";
				k = 0;
			}
		}
		return strValueTS;
	}

	static std::string timeFormat(int value) {
		std::string str = "";

		if(value < 10) {
			str += "0";
			str += std::to_string(value);
		}
		else
			str += std::to_string(value);

		return str;
	}

	static Animation* setAnim() {
		SpriteFrame* animDownFrame1;
		SpriteFrame* animDownFrame2;
		SpriteFrame* animDownFrame3;
		SpriteFrame* animDownFrame4;

		animDownFrame1 = SpriteFrame::create("anim/warning1.png", Rect(0, 0, 1920, 1080));
		animDownFrame2 = SpriteFrame::create("anim/warning2.png", Rect(0, 0, 1920, 1080));
		animDownFrame3 = SpriteFrame::create("anim/warning3.png", Rect(0, 0, 1920, 1080));
		animDownFrame4 = SpriteFrame::create("anim/warning4.png", Rect(0, 0, 1920, 1080));

		Animation* anim = Animation::create();
		anim->setDelayPerUnit(0.06f);
		anim->addSpriteFrame(animDownFrame1);
		anim->addSpriteFrame(animDownFrame2);
		anim->addSpriteFrame(animDownFrame3);
		anim->addSpriteFrame(animDownFrame4);
		anim->addSpriteFrame(animDownFrame4);
		anim->addSpriteFrame(animDownFrame4);
		anim->addSpriteFrame(animDownFrame3);
		anim->addSpriteFrame(animDownFrame2);
		anim->addSpriteFrame(animDownFrame1);

		return anim;
	}

};

#endif