#include "ConsoleInterface.h"

using namespace std;

// �����Ǹ鼭 main.members ����Ʈ�� �޾ƿ´�.
ConsoleInterface::ConsoleInterface(DataManager _manager)
{
	// main�� ����� manager ��ü.
	manager = _manager;
	members = manager.LoadMemberData();
}

// Consle User Interface ������ ���� ���ڿ� ���� �κ�.
const void ConsoleInterface:: HeadLine(string head, int tab)
{
	if (tab == 1)
		cout << "\n\t����������  " << head << " ����������\n" << endl;
	else 
		cout << "\n\t\t����������  " << head << " ����������\n" << endl;
}
	
// ����ڿ��� Ű���� �Է��� ���� ��, �ܼ� ȭ���� �����ִ� �Լ�.
const void ConsoleInterface::ClearLineInterface()
{
	cout << "\n\tPress any key to continue...\n";
	_getch();
	system("cls");
}

// ȸ�������� ���� �Լ�.
Member ConsoleInterface::CreateMember()
{
	string name, signupTime = Human::currentDateTime(), id, password;
	HeadLine("Sign up", 2);
	cout << "\t\tNAME	>> ";
	cin >> name;
	cout << "\t\tID	>> ";
	cin >> id;
	cout << "\t\tPW	>> ";
	cin >> password;
	cout << TabLine << endl;
	cout << "\t\tcomplete!" << endl;
	cout << "\t\tPlease restart program to login" << endl;
	ClearLineInterface();

	// Member ��ü�� �����Ͽ� return.
	return Member(name, signupTime, id, password);
}

// �α��� �Լ�
void ConsoleInterface::Login()
{
	string id, password;
	HeadLine("Login", 2);
	cout << "\t\tID	>> ";
	cin >> id;
	cout << "\t\tPW	>> ";
	cin >> password;

	// MemberData.txt���� �ŰԺ����� �ش��ϴ� id, password�� ã�´�.
	if (manager.IsValidLogin(id, password))
	{
		currentMember = manager.FindMember(id);
		manager.LoadNoteData(currentMember);
		// �޸� �� �� �ִ� NotepadMenu�� �̵�.
		NotepadMenu();
	}
	else
	{
		// ��ġ�ϴ� id, password�� ã�� ���ϸ� Entry menu�� ���ư���.
		cout << "\n\t\tLogin failed" << endl;
		ClearLineInterface();
		EntryMenu();
	}
	return;
}

// ���� �α������� Member�� ��Ʈ ����� ����ϴ� �Լ�.
void ConsoleInterface::PrintNotesName()
{
	if (currentMember.CountNotes() == 0)
		cout << "\tPlease create a new note" << endl;

	list<Notepad> temp_notes = currentMember.GetAllNote();

	list<Notepad>::iterator iter;
	for (iter = temp_notes.begin(); iter != temp_notes.end(); iter++)
	{
		//              ��Ʈ�̸�                         ��������
		cout << "\t" <<iter->GetNoteName() << " : " << iter->GetCreateDate() << endl;
	}
}

// �� �޸� �ۼ��ϴ� UI �Լ� 
void ConsoleInterface::Write()
{
	string name, text, getText;
	system("cls");
	HeadLine("Write note", 1);
	cout << "\t!!w + enter: save, !!q + enter : exit(no save)" << endl;
	cout << "\n\t���� : ";
	getline(cin, name); // ���ۿ� \n�� ���� �־� �����ϱ� ���� ����.
	getline(cin, name, '\n');
	HeadLine("TEXT", 1);

	do
	{
		getline(cin, getText);
		text += getText;

		// �������� �ʰ� ����
		if (getText.find("!!q") != -1)
			return;

		// �����ϰ� ����
		if (getText.find('!!w') != -1)
		{
			text = text.substr(0, text.find("!!w"));

			// �� �޸� ����
			currentMember.NewNote(name, text);
			// ����
			manager.SaveNoteData(currentMember);
			return;
		}
	} while (true);
}


// �ۼ��� �޸� �д� UI �Լ�.
void ConsoleInterface::Read()
{
	string getName;
	HeadLine("Select note", 1);
	cout << "\n\t\tName >> ";
	getline(cin, getName);
	getline(cin, getName, '\n');

	// ã�� ��Ʈ�� ������ "" return.
	Notepad note = currentMember.FindNote(getName);

	// �Է��� �̸��� �޸� ���� ��� ���� �޴��� ���ư���.
	if (note.GetNoteName() == "")
	{
		cout << "\n\t\tNot found" << endl;
		ClearLineInterface();
		NotepadMenu();
		return;
	}
	// �Է��� �޸� �ִ� ��� �޸� ����Ѵ�.
	else
	{
		string getValue;
		system("cls");
		HeadLine(getName, 1);
		cout << note.GetText() << endl;
		
		ClearLineInterface();
		
	}
}

// �޸� ����� UI �Լ�.
void ConsoleInterface::Delete()
{
	string getName;
	HeadLine("Delete note", 2);
	cout << "\n\t\tName >> ";
	getline(cin, getName);
	getline(cin, getName, '\n');
	
	// �޸� ã�� ���
	if (currentMember.DeleteNote(getName))
	{
		cout << "\t\tcomplete!" << endl;
		// ���� �� save.
		manager.SaveNoteData(currentMember);
		ClearLineInterface();
	}
	else
	{
		cout << "\t\tThe note can not be found." << endl;
		ClearLineInterface();
	}
}

// Notepad ���� �޴�. (�α��� ���� �޴�.)
// EntryMenu(login) -> NotepaddMenu.
const void ConsoleInterface::NotepadMenu()
{
	int userSelection;
	// �޴� ��ȯ ��, ȭ���� �����ش�.
	system("cls");

	HeadLine("Notepad", 1);
	cout << "\tuser :" << currentMember.GetName() << endl;
	PrintNotesName();
	cout << noTabLine << endl << endl;
	cout << "\t1. �� �޸�\n\n";
	cout << "\t2. �޸� �б�\n\n";
	cout << "\t3. �޸� ����\n\n";
	cout << "\t4. �α׾ƿ�\n\n";
	cout << noTabLine << endl;
	cout << getValueSign;
	cin >> userSelection;
	
	switch (userSelection)
	{
	case 1: // �� �޸� �ۼ�
		Write();
		NotepadMenu();
		break;
	case 2: // �޸� �б� �� ����
		Read();
		NotepadMenu();
		break;
	case 3: // �޸� ����
		Delete();
		NotepadMenu();
		break;
	case 4: // �α׾ƿ�
		system("cls");
		currentMember = Member("0","0","0","0");
		EntryMenu();
	case -999*12^32: // ���� ��ͷ� ���� warning ����.
		break;
	default: // ���ܹ߻���, �ٽ� Notepad menu�� ����.
		cout << wrongMenu << endl;
		ClearLineInterface();
		NotepadMenu();
		return;
	}
	return;
}

// �α���, ȸ������ �޴�. (ù ���� �޴�)
const void ConsoleInterface::EntryMenu()
{	
	int userSelection;
	DataManager manager(members);
	HeadLine("notepad++", 1);
	cout << "\t1. �α���\n\n";
	cout << "\t2. ȸ������\n\n";
	cout << "\t3. ����\n\n";
	cout << noTabLine << endl;
	cout << getValueSign;
	cin >> userSelection;

	switch (userSelection)
	{
	case 1: // �α���
		Login();
		break;
	case 2: // ȸ������
		members.push_back(CreateMember());
		manager.SaveMemberData(members);
		manager.LoadMemberData();
		EntryMenu();
		return;
		break;
	case 3: // ����
		exit(0);
		break;
	default: // ���ܹ߻���, �ٽ� Entry menu�� ����.
		cout << wrongMenu << endl;
		ClearLineInterface();
		EntryMenu();
		return;
		break;
	}
	return;
}
