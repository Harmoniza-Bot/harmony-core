#include "headers.h"

using namespace std;

Scale::Scale(){
}

void Scale::transport(int halfTones){
}

int Scale::whereIs(Note n){
	int t = noteScale.size();
	for(int x=0; x<t; ++x){
		if(n.name == noteScale[x].name){
			if(n.sygn == noteScale[x].sygn){
				return x;
			}
		}
	}
	return -1;
}
