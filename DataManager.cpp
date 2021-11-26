#include "DataManager.h"
#include<iostream>

DataManager::DataManager(list<Member> _members)
{
	members = _members;
}

// �����Ǹ鼭 ���� ���� ��ο� ����Ǿ� �ִ� txt���� �ҷ���.
DataManager::DataManager()
{
	//members = LoadMemberData();
}

bool DataManager::SaveMemberData(list<Member> _members)
{
	members = _members;

	// [MemberData] ���� ���� ���� ����.
	ofstream fout(memberFilePath, ios::out);
	if (!fout)
	{
		cout << "error :: file write." << endl;
		return false;
	}
	
	list<Member>::iterator iter;
	for (iter = members.begin(); iter != members.end(); ++iter)
	{
		// �̸�, ������, ID, Password
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
	// [MemberData] ���� ���� ���� ����.
	ofstream fout(noteFilePath, ios::out);
	if (!fout)
	{
		cout << "error :: file write." << endl;
		return false;
	}

	list<Notepad>::iterator iter;
	for (iter = target.notes.begin(); iter != target.notes.end(); ++iter)
	{
		// �̸�, ����, ������, ����
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
	�Ű� ������ ���� string���� ',' �� �����Ѵ�.
	�ҷ��� txt ������ �����ڰ� ',' �̱� ������ ����Ѵ�.
*/
// C#�� out�� ���� ���. (���� �� retrun ����)
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
	�Ű������� ���� id, password�� ��ġ�ϴ� Member�� �ִ���
	Ȯ���ϴ� �Լ�.
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
	Id�� ��ġ�ϴ� Member�� ã�� return�ϴ� �Լ�. 
*/
Member DataManager::FindMember(string id)
{
	list<Member>::iterator iter;
	for (iter = members.begin(); iter != members.end(); iter++)
	{
		if (iter->GetId() == id)
			return *iter;
	}
	// �˸´� Member�� ã�� ���ϸ� ����� return.
	return Member("0", "0", "0", "0");
}