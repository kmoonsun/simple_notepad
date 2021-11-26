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

// ���� �ۼ��� �޸��� ���� �����ϴ� �Լ�.
size_t Member::CountNotes()
{
	// return of size()'s value is size_t.
	return notes.size();
}

// ���ο� �޸� �߰��ϴ� �Լ�.
void Member::NewNote(string name, string text)
{
	// Notepad(������ ���̵�, �޸��̸�, �����ð�, ����)
	notes.push_back(Notepad(m_id, name, Human::currentDateTime(), text));
}

// �޸� �����ϴ� �Լ�.
bool Member::DeleteNote(string name)
{
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		// �����ϰ��� �ϴ� �޸� �ִٸ� ���� �� return true.
		if (iter->GetNoteName() == name)
		{
			notes.erase(iter);
			return true;
		}
	}
	return false;
}

// �޸� ã�� �Լ�.
Notepad Member::FindNote(string name)
{
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		if (iter->GetNoteName() == name)
			return *iter;
	}

	// �˸��� �޸� ������ ����� ����.
	return Notepad("","", "", "");
}

// ��� �޸� �����ϴ� �Լ�.
list<Notepad> Member::GetAllNote()
{
	list<Notepad> findedNotes;
	for (iter = notes.begin(); iter != notes.end(); ++iter)
	{
		findedNotes.push_back(*iter);
	}

	return findedNotes;
}