#include "Human.h"

/*
* Human class
* �޸����� ����ϴ� Member�� ���� Ŭ����
* �̸��� �����ð��� ��������� ������, 
* �����ð��� �⺻���� ���� �ð��̴�.
*
* SubClass -> Member
*/

// Constructor
Human::Human(string name, string signUpTime)
{
	m_name = name;
	m_signupTime = signUpTime;
}

Human::Human() {}

// �÷����� ���������� ���� �ð��� return���ִ� �Լ�.
string Human::currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	char buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
	
	return buf;
}

string Human::GetName()
{
	return m_name;
}

string Human::GetSignupTime()
{
	return m_signupTime;
}
