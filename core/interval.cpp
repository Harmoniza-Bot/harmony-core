#include <string>
#include "headers.h"

using namespace std;

Interval::Interval(){
    Note n;
    low = n;
    high = n;
}

int Interval::getDistance(){
	return high.getHeight() - low.getHeight();
}

string getName(){
    string answer;
    return answer;
}

vector<string> Interval::getResolutionsList(){
        vector<string> answer;

	return answer;
}
void resolution(string keyName){
}
