#include <iostream>
#include <string>
#include <ncurses.h>
//#include "core.h"

using namespace std;

/////////////////////////////////////////////////////////////
Note note;
void testNote(){
	char command;
	cin >> command;
	if(command == 'r'){
		system("clear");
		testNote();
	} else if (command == 'q'){
		return;
	} else if(command == 'h'){
		cout << "'r' - restart console\n'c' - change note\n";
		cout << "'e' - enharmony change\n't' - tell notes parametres\n";
		cout << "'p' - prepared notes parameters\n's' - resolution note\n";
		cout << "'q' - quit\n";
		testNote();
	} else if(command == 'c'){
		cout << "enter new note name\n";
		string n;
		cin >> n;
		note.change(n);
		cout << "note changet to " << n << endl;
		testNote();
	} else if(command == 'e'){
		cout << "enter enharmony change direction\n";
		bool dir;
		cin >> dir;
		note.enharmonyChange(dir);
		cout << "enharmony change completed\n";
		testNote();
	} else if(command == 't'){
		cout << "note name: " << note.getName() << endl;
		cout << "---------------------" << endl;
		cout << "note height: " << note.getHeight() << endl;
		cout << "note name (obj): " << note.name << endl;
		cout << "note sygn: " << note.sygn << endl;
		cout << "note octave: " << note.octave << endl;
		testNote();
	} else if(command == 'p'){
		cout << "enter notes name, sygn and octave\n";
		char n;
		cin >> n;
		note.name = n;
		int t;
		cin >> t;
		note.sygn = t;
		cin >> t;
		note.octave = t;
		cout << "notes parametres changed\n";
		testNote();
	} else if(command == 's'){
		cout << "enter key and direction to resolution\n";
		string k;
		cin >> k;
		bool dir;
		cin >> dir;
		cout << "resolution complete to tone " << note.resolution(k,dir) << endl;
		testNote();
	}
	else {
		cout << "unknown command...\n";
		testNote();
	}
}
//--------------------------------------------------------
Interval interval;
void testInterval(){
    char command;
    cin >> command;

    if(command == 'h'){
        cout << "'r' - restart\n'c' - change notes params\n";
        cout << "'d' - get distance of notes\n't' - tell parans\n'q' - quit\n";
        testInterval();
    } else if(command == 'r'){
        system("clear");
        testInterval();
    } else if(command == 'c'){
        cout << "enter 1st note name and octave (or 'n' to set next note)\n";
        string n;
        int t;
        cin >> n;
        while(1){
            if(n == "n") break;
            interval.low.change(n);
            cin >> t;
            interval.low.octave = t;
            break;
        }
        cout << "enter 2st notes name and octave (or 'n' to finish)\n";
        cin >> n;
        while(1){
            if(n == "n") break;
            interval.high.change(n);
            cin >> t;
            interval.high.octave = t;
            break;
        }
        cout << "interval setting finished\n";
        testInterval();
    } else if(command == 'd'){
        cout << "distance betwen notes: " << interval.getDistance() << " h.t.\n";
        testInterval();
    } else if(command == 'q'){
        return;
    } else if(command == 't'){
        cout << "low note name: " << interval.low.getName() << endl;
        cout << "octave: " << interval.low.octave << endl;
        cout << "----------------\n";
        cout << "high note name: " << interval.high.getName() << endl;
        cout << "octave: " << interval.high.octave << endl;
        testInterval();
    }
    else {
        cout << "unknown command...\n";
        testInterval();
    }

}
//--------------------------------------------------------
void testScale(){
	Note n;
	cout << "scale test started..." << endl;
	cout << "enter note,s size and note names to included to the scale" << endl;
	Scale scale;
	int size;
	cin >> size;
	for (int x=0; x<size; ++x){
		scale.noteScale.push_back(n);
		string in;
		cin >> in;
		scale.noteScale[x].change(in);
	}
	cout << "Scale note names: ";
	for(int x=0; x<scale.noteScale.size(); ++x){
		cout << scale.noteScale[x].getName();
		if(x != scale.noteScale.size() - 1){
			cout << ", ";
		}
	}
	cout << endl;
}
//--------------------------------------------------------
void testKey(){
	Key key;
	cout << "key test started..." << endl;
	cout << "enter key name" << endl;
	string name;
	cin >> name;
	key.change(name);

	cout << "enter key lad (dor, frg, lid, mks, lks) or '-' to continiue" << endl;
	cin >> name;
	if((name != "-") && (name == "dor" || name == "frg" || name == "lid" || name == "mks" || name == "lks")){
		key.lad = name;
	}

	cout << "enter key specification: natural(n), garmony(g), melody(m) or chromatic (h)" << endl;
	char m;
	cin >> m;
	key.mod = m;

	cout << "key setting finished. Enter scale direction (0 - down, 1 - up)" << endl;
	bool dir;
	cin >> dir;
	Scale s = key.getScale(dir);
	int t = s.noteScale.size();

	cout << "key scale: ";
	for(int x=0; x<t; ++x){
		cout << s.noteScale[x].getName() << ' ';
	}
	cout << endl;
    cout << "enter intervals notes to search interval in this key\n";
    Interval i;
    cin >> name;
    i.low.change(name);
    cin >> name;
    i.high.change(name);

    cout << "interval defined in "<< key.whereIs(i, 1) << endl;//дописать
}
/////////////////////////////////////////////////////////////
void interface() {
    // Инициализация ncurses
    initscr();
    noecho();        // Отключаем эхо символов ввода
    cbreak();        // Включаем режим немедленного чтения символов
    keypad(stdscr, TRUE);   // Включение режима чтения функциональных клавиш

    int choice = 0;   // Индекс текущего выбора


//-------  Сюда добавить слово-идентификатор функции -------
    const char* options[] = {"Exit", "Note", "Interval", "Scale", "Key"};
//----------------------------------------------------------

    int num_options = sizeof(options) / sizeof(char*);

    while(true) {
        clear();      // Очищаем экран

        for(int i = 0; i < num_options; ++i) {
            if(i == choice)
                attron(A_STANDOUT);  // Подсвечиваем текущий выбор
            mvprintw(i + 1, 1, "%s", options[i]);
            attroff(A_STANDOUT);
        }

        refresh();    // Обновляем экран

        int c = getch();   // Читаем символ с клавиатуры

        switch(c) {
            case KEY_UP:
                choice = (choice > 0) ? choice - 1 : num_options - 1;
                break;
            case KEY_DOWN:
                choice = (choice + 1) % num_options;
                break;
            case '\n':   // Нажатие Enter
                endwin();     // Завершаем работу ncurses
                system("clear");  // Очищаем терминал



				if(choice == 0) return;
//-------  Сюда добавить функции тестирования  --------
				else if(choice == 1) testNote();
				else if(choice == 2) testInterval();
				else if(choice == 3) testScale();
				else if(choice == 4) testKey();
//------------------------------------------------------

                return;
            default:
                continue;
        }
    }
    return;
}
/////////////////////////////////////////////////////////

int main(){
	interface();
}
