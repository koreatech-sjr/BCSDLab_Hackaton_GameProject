#ifndef CHARACTER
#define CHARACTER

#include "Common.h"

class Character {
public:
	Character() {
		m_myCharacter = 1;
		m_stress = 100;
		m_tiredness = 100;
		m_maxStress = 100;
		m_maxTiredness = 100;
		m_money = 400000;

		m_hour = 8;
		m_time = 0;
		m_year = 2017;
		m_month = 3;
		m_day = 2;
		m_week[0] = "화";
		m_week[1] = "수";
		m_week[2] = "목";
		m_week[3] = "금";
		m_week[4] = "토";
		m_week[5] = "일";
		m_week[6] = "월";

	}
	~Character() {

	}

	int		getMyCharacter()			{ return m_myCharacter; }
	void	setMyCharacter(int value)	{ m_myCharacter = value; }
	int		getStress()					{ return m_stress; }
	void	setStress(int value)		{ m_stress = value; }
	void	addStress(int value)		{ m_stress += value; }
	int		getMaxStress()				{ return m_maxStress; }
	void	setMaxStress(int value)		{ m_maxStress = value; }
	int		getTiredness()				{ return m_tiredness; }
	void	setTiredness(int value)		{ m_tiredness = value; }
	int		getMaxTiredness()			{ return m_maxTiredness; }
	void	setMaxTiredness(int value)	{ m_maxTiredness = value; }
	int		getMoney()					{ return m_money; }
	void	setMoney(int value)			{ m_money = value; }
	void	addMoney(int value)			{ m_money += value; }


	int		getTime()					{ return m_time; }
	void	setTime(int value)			{ m_time = value; }
	int		getHour()					{ return m_hour; }
	void	addHour(int value)			{
		m_hour += value; 
		if(m_hour >= 24) {
			m_hour = 0;
			addDay();
		}

	}
	void	addTime(int value) {
		m_time += value;
		if(m_time > 59 ) {
			m_time = 0;
			addHour(1);
		}
	}
	void	goHour(int value) {
		while(m_hour != value) m_hour += 1;
	}
	void	goTime(int value) {
		if(m_time < value) m_time = value;
		else {
			m_hour += 1;
			m_time = value;
		}
	}
	int		getYear()					{ return m_year; }
	int		getMonth()					{ return m_month; }
	int		getDay()					{ return m_day; }
	std::string	getWeek()				{ return m_week[m_day%7]; }


	void	addYear() {
		m_year++;
	}
	void	addMonth() { 
		m_month++;
		if(m_month > 12) addYear();
		m_month%=12;
	}
	void	addDay() { 
		m_day++; 
		if(m_day > 31) addMonth();
		m_day%=31; 
	}

protected:
	int m_myCharacter;
	int m_stress;
	int m_tiredness;
	int m_maxStress;
	int m_maxTiredness;
	int m_money;


	int m_time;
	int m_hour;
	int m_year;
	int m_month;
	int m_day;
	std::string m_week[7];


};

#endif CHARACTER