#ifndef K
#define K
#include <string>
#include <vector>

using namespace std;

struct Key{
	Key();
	Note mainTone; // Тоника
	string lad;    // Мажорный(dur), минорный(min), фригийский(frg) и прочие.
	char mod;      // Натуральный(n), гармонический (g), мелодический (m), хроматический (h).
	
	int dTones[7] = {2,2,1,2,2,2}; // dur - Мажорный (ионийский)
	int oTones[7] = {2,1,2,2,2,1}; // mol - Дорийский
	int fTones[7] = {1,2,2,2,1,2}; // frg - Фригийский
	int lTones[7] = {2,2,2,1,2,2}; // lid - Лидийский
	int iTones[7] = {2,2,1,2,2,1}; // mks - Миксолидийский
	int mTones[7] = {2,1,2,2,1,2}; // mol - Минорный (эолийский)
	int kTones[7] = {1,2,2,1,2,2}; // lks - Локрийский

	void change(string);        // Лады, кроме dur и mol задаются вручную

	Scale getScale(bool);       // 0 - нисходящее движение, 1 - восходящее.

	int whereIs(Note, bool);     // Поиск структуры в тональности
	int whereIs(Interval, bool); // Первый аргумент - структура
	int whereIs(Accord, bool);   // Второй - направление звукоряда
};

#endif // K
