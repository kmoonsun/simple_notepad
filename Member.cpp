#include "Member.h"

using namespace std;

Member::Member() { }

Member::Member(string name, string signupTime, string id, string password) : Human(name, signupTime)
{
	m_id = id;
	m_password = password;
}

string Member::GetId() { return m_id; }
string Member::GetPassword() { return m_password; }

// 현재 작성된 메모의 수를 리턴하는 함수.
size_t Member::CountNotes()
{
	// return of size()'s value is size_t.
	return notes.size();
}

// 새로운 메모를 추가하는 함수.
void Member::NewNote(string name, string text)
{
	// Notepad(생성자 아이디, 메모이름, 생성시간, 내용)
	notes.push_back(Notepad(m_id, name, Human::currentDateTime(), text));
}

// 메모를 삭제하는 함수.
bool Member::DeleteNote(string name)
{
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		// 삭제하고자 하는 메모가 있다면 삭제 후 return true.
		if (iter->GetNoteName() == name)
		{
			notes.erase(iter);
			return true;
		}
	}
	return false;
}

// 메모를 찾는 함수.
Notepad Member::FindNote(string name)
{
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		if (iter->GetNoteName() == name)
			return *iter;
	}

	// 알맞은 메모가 없으면 허수값 리턴.
	return Notepad("","", "", "");
}

// 모든 메모를 리턴하는 함수.
list<Notepad> Member::GetAllNote()
{
	list<Notepad> findedNotes;
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		findedNotes.push_back(*iter);
	}

	return findedNotes;
}