#ifndef A
#define A

#include <vector>
#include <string>
#include "scale.h"
using namespace std;

struct Accord{
	Accord();

	vector<Note> notes; // хранит ноты аккорда

	void buildKeyAccord(string, string, int); // строит указанный аккорд в указанной тональности от указанной ноты 
	Scale getArpeggio(); // возвращает арпеджио этого аккорда

        string getName(); // возвращает имя аккорда
};

#endif // A
