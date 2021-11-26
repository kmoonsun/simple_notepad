#include "ConsoleInterface.h"

using namespace std;

// 생성되면서 main.members 리스트를 받아온다.
ConsoleInterface::ConsoleInterface(DataManager _manager)
{
	// main에 선언된 manager 객체.
	manager = _manager;
	members = manager.LoadMemberData();
}

// Consle User Interface 구현을 위한 문자열 정의 부분.
const void ConsoleInterface:: HeadLine(string head, int tab)
{
	if (tab == 1)
		cout << "\n\t─────  " << head << " ─────\n" << endl;
	else 
		cout << "\n\t\t─────  " << head << " ─────\n" << endl;
}
	
// 사용자에게 키보드 입력을 받은 뒤, 콘솔 화면을 지워주는 함수.
const void ConsoleInterface::ClearLineInterface()
{
	cout << "\n\tPress any key to continue...\n";
	_getch();
	system("cls");
}

// 회원가입을 위한 함수.
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

	// Member 객체를 생성하여 return.
	return Member(name, signupTime, id, password);
}

// 로그인 함수
void ConsoleInterface::Login()
{
	string id, password;
	HeadLine("Login", 2);
	cout << "\t\tID	>> ";
	cin >> id;
	cout << "\t\tPW	>> ";
	cin >> password;

	// MemberData.txt에서 매게변수에 해당하는 id, password를 찾는다.
	if (manager.IsValidLogin(id, password))
	{
		currentMember = manager.FindMember(id);
		manager.LoadNoteData(currentMember);
		// 메모를 볼 수 있는 NotepadMenu로 이동.
		NotepadMenu();
	}
	else
	{
		// 일치하는 id, password를 찾지 못하면 Entry menu로 돌아간다.
		cout << "\n\t\tLogin failed" << endl;
		ClearLineInterface();
		EntryMenu();
	}
	return;
}

// 현재 로그인중인 Member의 노트 목록을 출력하는 함수.
void ConsoleInterface::PrintNotesName()
{
	if (currentMember.CountNotes() == 0)
		cout << "\tPlease create a new note" << endl;

	list<Notepad> temp_notes = currentMember.GetAllNote();

	list<Notepad>::iterator iter;
	for (iter = temp_notes.begin(); iter != temp_notes.end(); iter++)
	{
		//              노트이름                         생성일자
		cout << "\t" <<iter->GetNoteName() << " : " << iter->GetCreateDate() << endl;
	}
}

// 새 메모를 작성하는 UI 함수 
void ConsoleInterface::Write()
{
	string name, text, getText;
	system("cls");
	HeadLine("Write note", 1);
	cout << "\t!!w + enter: save, !!q + enter : exit(no save)" << endl;
	cout << "\n\t제목 : ";
	getline(cin, name); // 버퍼에 \n이 남아 있어 제거하기 위해 삽입.
	getline(cin, name, '\n');
	HeadLine("TEXT", 1);

	do
	{
		getline(cin, getText);
		text += getText;

		// 저장하지 않고 종료
		if (getText.find("!!q") != -1)
			return;

		// 저장하고 종료
		if (getText.find('!!w') != -1)
		{
			text = text.substr(0, text.find("!!w"));

			// 새 메모 생성
			currentMember.NewNote(name, text);
			// 저장
			manager.SaveNoteData(currentMember);
			return;
		}
	} while (true);
}


// 작성된 메모를 읽는 UI 함수.
void ConsoleInterface::Read()
{
	string getName;
	HeadLine("Select note", 1);
	cout << "\n\t\tName >> ";
	getline(cin, getName);
	getline(cin, getName, '\n');

	// 찾는 노트가 없으면 "" return.
	Notepad note = currentMember.FindNote(getName);

	// 입력한 이름의 메모가 없는 경우 이전 메뉴로 돌아간다.
	if (note.GetNoteName() == "")
	{
		cout << "\n\t\tNot found" << endl;
		ClearLineInterface();
		NotepadMenu();
		return;
	}
	// 입력한 메모가 있는 경우 메모를 출력한다.
	else
	{
		string getValue;
		system("cls");
		HeadLine(getName, 1);
		cout << note.GetText() << endl;
		
		ClearLineInterface();
		
	}
}

// 메모를 지우는 UI 함수.
void ConsoleInterface::Delete()
{
	string getName;
	HeadLine("Delete note", 2);
	cout << "\n\t\tName >> ";
	getline(cin, getName);
	getline(cin, getName, '\n');
	
	// 메모를 찾은 경우
	if (currentMember.DeleteNote(getName))
	{
		cout << "\t\tcomplete!" << endl;
		// 삭제 후 save.
		manager.SaveNoteData(currentMember);
		ClearLineInterface();
	}
	else
	{
		cout << "\t\tThe note can not be found." << endl;
		ClearLineInterface();
	}
}

// Notepad 관리 메뉴. (로그인 이후 메뉴.)
// EntryMenu(login) -> NotepaddMenu.
const void ConsoleInterface::NotepadMenu()
{
	int userSelection;
	// 메뉴 전환 후, 화면을 지워준다.
	system("cls");

	HeadLine("Notepad", 1);
	cout << "\tuser :" << currentMember.GetName() << endl;
	PrintNotesName();
	cout << noTabLine << endl << endl;
	cout << "\t1. 새 메모\n\n";
	cout << "\t2. 메모 읽기\n\n";
	cout << "\t3. 메모 삭제\n\n";
	cout << "\t4. 로그아웃\n\n";
	cout << noTabLine << endl;
	cout << getValueSign;
	cin >> userSelection;
	
	switch (userSelection)
	{
	case 1: // 새 메모 작성
		Write();
		NotepadMenu();
		break;
	case 2: // 메모 읽기 및 수정
		Read();
		NotepadMenu();
		break;
	case 3: // 메모 삭제
		Delete();
		NotepadMenu();
		break;
	case 4: // 로그아웃
		system("cls");
		currentMember = Member("0","0","0","0");
		EntryMenu();
	case -999*12^32: // 무한 재귀로 인한 warning 제거.
		break;
	default: // 예외발생시, 다시 Notepad menu를 띄운다.
		cout << wrongMenu << endl;
		ClearLineInterface();
		NotepadMenu();
		return;
	}
	return;
}

// 로그인, 회원가입 메뉴. (첫 시작 메뉴)
const void ConsoleInterface::EntryMenu()
{	
	int userSelection;
	DataManager manager(members);
	HeadLine("notepad++", 1);
	cout << "\t1. 로그인\n\n";
	cout << "\t2. 회원가입\n\n";
	cout << "\t3. 종료\n\n";
	cout << noTabLine << endl;
	cout << getValueSign;
	cin >> userSelection;

	switch (userSelection)
	{
	case 1: // 로그인
		Login();
		break;
	case 2: // 회원가입
		members.push_back(CreateMember());
		manager.SaveMemberData(members);
		manager.LoadMemberData();
		EntryMenu();
		return;
		break;
	case 3: // 종료
		exit(0);
		break;
	default: // 예외발생시, 다시 Entry menu를 띄운다.
		cout << wrongMenu << endl;
		ClearLineInterface();
		EntryMenu();
		return;
		break;
	}
	return;
}
