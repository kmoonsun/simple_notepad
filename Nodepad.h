#pragma once
#include<string>
#include<list>

using namespace std;

#ifndef NOTEPAD_H
#define NOTEPAD_H

class Notepad
{
	string m_id;
	string m_noteName;
	string m_createdDate;
	string m_text;
public:
	Notepad();
	Notepad(string id, string name, string create, string text);
	
	string GetNoteId();
	string GetNoteName();
	string GetCreateDate();
	string GetText();

	void SetText(string _text);
	void SetName(string _name);
};

#endif