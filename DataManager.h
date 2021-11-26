#pragma once

#include<stdlib.h>
#include<direct.h>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<iterator>
#include "Member.h"

using namespace std;

#ifndef DATAMANAGER_H
#define DATAMANAGER_H

class DataManager
{
	string memberFilePath = "MemberData.txt";
	string noteFilePath = "NoteData.txt";
	list<Member> members;
public:
	DataManager(list<Member> _members);
	DataManager();
	bool IsValidLogin(string id, string password);
	bool SaveMemberData(list<Member>);
	bool SaveNoteData(Member _meber);
	Member FindMember(string id);
	list<Member> LoadMemberData();
	void LoadNoteData(Member &_member);

	template<typename Out>
	void MySplit(const string &s, char delim, Out result);
	vector<string> MySplit(const string &param, const char delim);

};

#endif