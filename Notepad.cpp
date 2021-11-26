#include "Nodepad.h"
#include <algorithm>

Notepad::Notepad() {}

Notepad::Notepad(string id, string name, string create, string text)
{
	m_id = id;
	m_noteName = name;
	m_createdDate = create;
	m_text = text;
}

string Notepad::GetNoteId() { return m_id; }
string Notepad::GetNoteName() { return m_noteName; }
string Notepad::GetCreateDate() { return m_createdDate; }
string Notepad::GetText() { return m_text; }

void Notepad::SetText(string _text)
{
	m_text = _text;
}

void Notepad::SetName(string _name)
{
	m_text = _name;
}