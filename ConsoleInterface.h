#pragma once
#include<iostream>
#include<conio.h>
#include "DataManager.h"
#include "Member.h"

#ifndef CONSOLEINTERFACE_H
#define CONSOLEINTEFACE_H

using namespace std;

class ConsoleInterface
{
	list<Member> members;	// MemberData.txt에서 불러온 Member 정보.
	DataManager manager;
    Member currentMember;		// 현재 로그인중인 ID
	
public:
	ConsoleInterface(DataManager _manager);

	const inline void HeadLine(string head, int tab);
	const string noTabLine = "\t───────────────────────";
	const string TabLine = "\t\t────────────────────────";
	const string getValueSign = "\t>> ";
	const string wrongMenu = "\n\tError :: Please choose the correct menu!";

	const inline void ClearLineInterface();
	inline const void EntryMenu();
	inline const void NotepadMenu();
	void PrintNotesName();

	Member CreateMember();
	void Write();
	void Read();
	void Delete();
	void Login();
};

#endif