#ifndef CHARACTER
#define CHARACTER

#include "Common.h"

class Character {
public:
	Character() {
		//ĳ���� �⺻ ���� �ʱ�ȭ
		m_myCharacter = 1;
		m_stress = 100;
		m_tiredness = 100;
		m_maxStress = 100;
		m_maxTiredness = 100;
		m_money = 400000;
		//�ð� �ʱ�ȭ
		m_hour = 8;
		m_time = 0;
		m_year = 2017;
		m_month = 3;
		m_day = 2;
		m_week[0] = "ȭ";
		m_week[1] = "��";
		m_week[2] = "��";
		m_week[3] = "��";
		m_week[4] = "��";
		m_week[5] = "��";
		m_week[6] = "��";
		
		m_homework_total_number = 100; //�ϴ� 100���� �ʱ�ȭ��Ŵ ��Ȯ�ϰ� ��ȸ ������ �������� ���� (�������� �� + msc���� ��) * ��¥
		m_achievement_number = 0;
		m_unsubmission_number = 0;
		m_absent_number = 0;
		m_drinking_number = 0;
		m_club_number = 0;
		m_game_number = 0;
		m_tiredness_count = 0;
	}
	~Character() { }

	int		getMyCharacter()			{ return m_myCharacter; }
	//ĳ������ ����Ư�� ����
	void	setMyCharacter(int value)	{ 
		m_myCharacter = value;
	switch ( m_myCharacter ) {
			//����ξ�
		case 1: m_myCharacter = 1;

			//�������� �ʱ�ȭ 
			m_drinking = 1;
			m_tolerance_tired = 1;
			m_tolerance_ill = 1;
			m_tolerance_stress = 1;
			m_ability_coding = 3;
			m_ability_memory = 3;
			m_ability_math = 3;
			m_creativity = 2;
			m_concentration = 3;
			m_ability_speaking = 1;
			m_inhibition = 3;
			m_appearance = 1;
			m_reliability = 2;
			m_cravenness = 3;
			m_selfish = 3;
			m_preparation = 3;
			m_sincerity = 3;
			m_militancy = 1;
			m_will = 3;
			break;
			//���θƾ�
		case 2:
			//�������� �ʱ�ȭ 
			m_drinking = 3;
			m_tolerance_tired = 3;
			m_tolerance_ill = 3;
			m_tolerance_stress = 3;
			m_ability_coding = 1;
			m_ability_memory = 2;
			m_ability_math = 1;
			m_creativity = 2;
			m_concentration = 1;
			m_ability_speaking = 3;
			m_inhibition = 1;
			m_appearance = 3;
			m_reliability = 3;
			m_cravenness = 1;
			m_selfish = 1;
			m_preparation = 2;
			m_sincerity = 2;
			m_militancy = 1;
			m_will = 2;

			break;
			//�����
		case 3:
			//�������� �ʱ�ȭ 
			m_drinking = 3;
			m_tolerance_tired = 2;
			m_tolerance_ill = 2;
			m_tolerance_stress = 2;
			m_ability_coding = 3;
			m_ability_memory = 3;
			m_ability_math = 1;
			m_creativity = 1;
			m_concentration = 1;
			m_ability_speaking = 2;
			m_inhibition = 2;
			m_appearance = 2;
			m_reliability = 2;
			m_cravenness = 1;
			m_selfish = 2;
			m_preparation = 1;
			m_sincerity = 1;
			m_militancy = 3;
			m_will = 1;
			break;
			//���ι���
		case 4:
			//�������� �ʱ�ȭ 
			m_drinking = 2;
			m_tolerance_tired = 3;
			m_tolerance_ill = 2;
			m_tolerance_stress = 3;
			m_ability_coding = 1;
			m_ability_memory = 3;
			m_ability_math = 3;
			m_creativity = 2;
			m_concentration = 3;
			m_ability_speaking = 2;
			m_inhibition = 2;
			m_appearance = 2;
			m_reliability = 3;
			m_cravenness = 2;
			m_selfish = 2;
			m_preparation = 3;
			m_sincerity = 3;
			m_militancy = 1;
			m_will = 3;
			break;
			//�躸�뾾
		case 5:
			//�������� �ʱ�ȭ 
			m_drinking = 3;
			m_tolerance_tired = 2;
			m_tolerance_ill = 2;
			m_tolerance_stress = 2;
			m_ability_coding = 2;
			m_ability_memory = 2;
			m_ability_math = 2;
			m_creativity = 2;
			m_concentration = 2;
			m_ability_speaking = 2;
			m_inhibition = 2;
			m_appearance = 2;
			m_reliability = 2;
			m_cravenness = 2;
			m_selfish = 2;
			m_preparation = 2;
			m_sincerity = 2;
			m_militancy = 2;
			m_will = 2;
			break;
		}
	}
	//�⺻���� ������
	int		getStress()					{ return m_stress; }
	void	setStress(int value)		{ m_stress = value; }
	void	addStress(int value)		{ 
		m_stress += value;
		if(m_stress < 0) m_stress = 0;
		if(m_stress > m_maxStress ) m_stress = m_maxStress;
	}
	int		getMaxStress()				{ return m_maxStress; }
	void	setMaxStress(int value)		{ m_maxStress = value; }
	int		getTiredness()				{ return m_tiredness; }
	void	setTiredness(int value)		{ m_tiredness = value; }
	void	addTiredness(int value)		{ 
		m_tiredness += value;
		if(m_tiredness < 0) m_tiredness = 0;
		if(m_tiredness > m_maxTiredness ) m_tiredness = m_maxTiredness;
	}
	int		getMaxTiredness()			{ return m_maxTiredness; }
	void	setMaxTiredness(int value)	{ m_maxTiredness = value; }
	int		getMoney()					{ return m_money; }
	void	setMoney(int value)			{ m_money = value; }
	bool	addMoney(int value)			{ 
		if(m_money < m_money + value) {
			return false;
		}
		else {
			m_money += value;
			return true;
		}
	}
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

	//���� ���� ����
	int getM_drinking() { return m_drinking; }
	void setM_drinking(int value) { m_drinking = value; }
	void	addM_drinking(int value) { m_drinking += value; }

	int getM_tolerance_tired() { return m_tolerance_tired; }
	void setM_tolerance_tired(int value) { m_tolerance_tired = value; }
	void	addM_tolerance_tired(int value) { m_tolerance_tired += value; }

	int getM_tolerance_ill() { return m_tolerance_ill; }
	void setM_tolerance_ill(int value) { m_tolerance_ill = value; }
	void	addM_tolerance_ill(int value) { m_tolerance_ill += value; }

	int getM_tolerance_stress() { return m_tolerance_stress; }
	void setM_tolerance_stress(int value) { m_tolerance_stress = value; }
	void	addM_tolerance_stress(int value) { m_tolerance_stress += value; }


	int getM_ability_coding() { return m_ability_coding; }
	void setM_ability_coding(int value) { m_ability_coding = value; }
	void	addM_ability_coding(int value) { m_ability_coding += value; }

	int getM_ability_memory() { return m_ability_memory; }
	void setM_ability_memory(int value) { m_ability_memory = value; }
	void	addM_ability_memory(int value) { m_ability_memory += value; }

	int getM_ability_math() { return m_ability_math; }
	void setM_ability_math(int value) { m_ability_math = value; }
	void	addM_ability_math(int value) { m_ability_math += value; }

	int getM_creativity() { return m_creativity; }
	void setM_creativity(int value) { m_creativity = value; }
	void	addM_creativity(int value) { m_creativity += value; }

	int getM_concentration() { return m_concentration; }
	void setM_concentration(int value) { m_concentration = value; }
	void	addM_concentration(int value) { m_concentration += value; }

	int getM_ability_speaking() { return m_ability_speaking; }
	void setM_ability_speaking(int value) { m_ability_speaking = value; }
	void	addM_ability_speaking(int value) { m_ability_speaking += value; }

	int getM_inhibition() { return m_inhibition; }
	void setM_inhibition(int value) { m_inhibition = value; }
	void	addM_inhibition(int value) { m_inhibition += value; }

	int getM_appearance() { return m_appearance; }
	void setM_appearance(int value) { m_appearance = value; }
	void	addM_appearance(int value) { m_appearance += value; }

	int getM_reliability() { return m_reliability; }
	void setM_reliability(int value) { m_reliability = value; }
	void	addM_reliability(int value) { m_reliability += value; }

	int getM_cravenness() { return m_cravenness; }
	void setM_cravenness(int value) { m_cravenness = value; }


	int getM_selfish() { return m_selfish; }
	void setM_selfish(int value) { m_selfish = value; }
	void	addM_selfish(int value) { m_selfish += value; }

	int getM_preparation() { return m_preparation; }
	void setM_preparation(int value) { m_preparation = value; }
	void	addM_preparation(int value) { m_preparation += value; }

	int getM_sincerity() { return m_sincerity; }
	void setM_sincerity(int value) { m_sincerity = value; }
	void	addM_sincerity(int value) { m_sincerity += value; }

	int getM_militancy() { return m_militancy; }
	void setM_militancy(int value) { m_militancy = value; }
	void	addM_militancy(int value) { m_militancy += value; }

	int getM_will() { return m_will; }
	void setM_will(int value) { m_will = value; }
	void	addM_will(int value) { m_will += value; }

protected:
	
	int m_myCharacter;
	int m_stress;
	int m_tiredness;
	int m_maxStress;
	int m_maxTiredness;
	int m_money;

	int m_homework_total_number; //�� ������
	int m_achievement_number; //�о����뵵
	int m_unsubmission_number;//���� ������ Ƚ��
	int m_absent_number;	//�Ἦ Ƚ��
	int m_drinking_number;  //<< �ش罺���� �ڰ� �Ͼ��� �ʱ�ȭ �ؾ���
	int m_club_number;		//���Ƹ� �� Ƚ��
	int m_game_number;		//���� ī��Ʈ
	int m_tiredness_count;//���� �Ƿε� ��ġ << 100�� �������� �� ���++ ������ �Ƿε� ���� ���ҽ� 0���� �ʱ�ȭ

	//ĳ���� ���� ����
	int	m_drinking;				   //�ַ�
	int	m_tolerance_tired;		   //�Ƿγ���
	int	m_tolerance_ill;		   //��������
	int	m_tolerance_stress;		   //��Ʈ���� ����
	int	m_ability_coding;		   //�ڵ��ɷ�
	int	m_ability_memory;		   //�ϱ�ɷ�
	int	m_ability_math;			   //���дɷ�
	int	m_creativity;			   //â�Ǽ�
	int	m_concentration;		   //���߷�
	int	m_ability_speaking;		   //������
	int	m_inhibition;			   //������
	int	m_appearance;			   //�ܸ�
	int	m_reliability;			   //�ŷڼ�
	int	m_cravenness;			   //�ҽ���
	int	m_selfish;				   //�̱��
	int	m_preparation;			   //�غ�
	int	m_sincerity;			   //���Ǽ�
	int m_militancy;			   //ȣ����
	int	m_will;					   //����

	int m_time;
	int m_hour;
	int m_year;
	int m_month;
	int m_day;
	std::string m_week[7];

};

#endif CHARACTER