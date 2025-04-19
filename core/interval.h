#ifndef I
#define I

#include <string>
#include <vector>
using namespace std;

struct Interval{
	Interval();

	Note high; // высокая нота интервала
	Note low; // низкая нота интервала
	
    int getDistance(); // получить расстояние между нотами
    
    string getName(); // получить имя интервала

    vector<string> getResolutionsList(); // получить список тональностей 
    void resolution(string); // разрешить в указанную тональность
    
};

#endif //I
