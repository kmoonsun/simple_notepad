#include "Human.h"

/*
* Human class
* 메모장을 사용하는 Member의 상위 클래스
* 이름과 생성시간을 멤버변수로 가지며, 
* 생성시간의 기본값은 현재 시간이다.
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

// 플랫폼에 독립적으로 현재 시간을 return해주는 함수.
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
