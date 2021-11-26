#define _CRT_SECURE_NO_WARNINGS
#include<string>
#include<time.h>
#ifndef HUMAN_H
#define HUMAN_H

using namespace std;

class Human
{
	string m_name;
	string m_signupTime;

public:
	Human();
	Human(string name, string signupTime);
	static string currentDateTime();
	string GetName();
	string GetSignupTime();
};

#endif