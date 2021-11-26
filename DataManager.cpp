#include "DataManager.h"
#include<iostream>

DataManager::DataManager(list<Member> _members)
{
	members = _members;
}

// 생성되면서 파일 실행 경로에 저장되어 있는 txt파일 불러옴.
DataManager::DataManager()
{
	//members = LoadMemberData();
}

bool DataManager::SaveMemberData(list<Member> _members)
{
	members = _members;

	// [MemberData] 파일 쓰기 모드로 열기.
	ofstream fout(memberFilePath, ios::out);
	if (!fout)
	{
		cout << "error :: file write." << endl;
		return false;
	}
	
	list<Member>::iterator iter;
	for (iter = members.begin(); iter != members.end(); ++iter)
	{
		// 이름, 생성일, ID, Password
		fout << iter->Human::GetName() << ',';
		fout << iter->Human::GetSignupTime() << ',';
		fout << iter->GetId() << ',';
		fout << iter->GetPassword() << '\n';
	} 
	fout.close();
	return true;
}

bool DataManager::SaveNoteData(Member _member)
{
	Member target = _member;
	// [MemberData] 파일 쓰기 모드로 열기.
	ofstream fout(noteFilePath, ios::out);
	if (!fout)
	{
		cout << "error :: file write." << endl;
		return false;
	}

	list<Notepad>::iterator iter;
	for (iter = target.notes.begin(); iter != target.notes.end(); ++iter)
	{
		// 이름, 제목, 생성일, 내용
		fout << target.GetId() << ',';
		fout << iter->GetNoteName() << ',';
		fout << iter->GetCreateDate() << ',';
		fout << iter->GetText() << '\n';
	}
	fout.close();
	return true;
}

/*
	MySpilt 
	매개 변수로 받은 string에서 ',' 을 제거한다.
	불러온 txt 파일의 구분자가 ',' 이기 때문에 사용한다.
*/
// C#의 out과 같은 기능. (복수 값 retrun 가능)
template<typename Out>
void DataManager::MySplit(const string &param, char delim, Out result)
{
	stringstream ss(param);
	string item;

	while (getline(ss, item, delim))
		*(result++) = item;
}

vector<string> DataManager::MySplit(const string &param, const char delim)
{
	vector<string> elements;
	MySplit(param, delim, back_inserter(elements));

	return elements;
}
// ~ MySplit.

list<Member> DataManager::LoadMemberData()
{
	ifstream fin(memberFilePath);
	if (!fin)
	{
		SaveMemberData(members);
	}

	vector<string> data;
	string line;
	while (getline(fin, line))
	{
		data = MySplit(line, ',');
		Member member(data.at(0), data.at(1), data.at(2), data.at(3));
		members.push_back(member);
	}

	fin.close();
	return members;
}

void DataManager::LoadNoteData(Member &_member)
{
	ifstream fin(noteFilePath, ios::out);
	if (!fin)
	{
		SaveNoteData(_member);
	} 

	vector<string> data;
	string line;
	while (getline(fin, line))
	{
		data = MySplit(line, ',');

		if (data.at(0) == _member.GetId())
		{
			//Notepad note(data.at(0), data.at(1), data.at(2), data.at(3));
			_member.NewNote(data.at(1), data.at(3));
		}	 
	}
	fin.close();
}

/*
	IsVaildLogin
	매개변수로 받은 id, password와 일치하는 Member가 있는지
	확인하는 함수.
*/
bool DataManager::IsValidLogin(string id, string password)
{
	list<Member>::iterator iter;
	for (iter = members.begin(); iter != members.end(); iter++)
	{
		if (iter->GetId() == id && iter->GetPassword() == password)
			return true;
	}
	return false;
}

/*
	FindMember
	Id가 일치하는 Member를 찾고 return하는 함수. 
*/
Member DataManager::FindMember(string id)
{
	list<Member>::iterator iter;
	for (iter = members.begin(); iter != members.end(); iter++)
	{
		if (iter->GetId() == id)
			return *iter;
	}
	// 알맞는 Member를 찾지 못하면 허수값 return.
	return Member("0", "0", "0", "0");
}