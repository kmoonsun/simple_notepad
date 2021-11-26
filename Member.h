#pragma once
#include<list>
#include<vector>
#include "Nodepad.h"
#include "Human.h"

#ifndef MEMBER_H
#define MEMBER_H

class Member : public Human
{
	string m_id;
	string m_password;
	list<Notepad> notes;

	friend class DataManager;

	// list 순회를 위해 선언한 변수.
	list<Notepad>::iterator iter;
public:
	Member();
	Member(string name, string signupTime, string id, string password);
	string GetId();
	string GetPassword();
	size_t CountNotes();

	void NewNote(string name, string text);
	bool DeleteNote(string name);
	Notepad FindNote(string name);
	list<Notepad> GetAllNote();
};

#endif