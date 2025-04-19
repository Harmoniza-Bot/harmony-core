#include "headers.h"

using namespace std;

Note::Note() {
    name = 'a';
    octave = 5;
    sygn = 0;
}

void Note::enharmonyChange(bool dir){
    int noteHeight = getHeight();
    Note n;
    n.name = name;
    n.octave = octave;
    n.sygn = sygn;
    if(dir){
        ++name;
        if(name > 'g'){
            name = 'a';
            ++octave;
        }
        while(getHeight() != noteHeight){
            --sygn;
        }
    } else {
        --name;
        if(name < 'a'){
            name = 'g';
            --octave;
            if(octave < 0){
                name = 'a';
                octave = 1;
                sygn = 0;
                return;
            }
        }
        while(getHeight() != noteHeight){
            ++sygn;
        }
    }
    if(sygn > 2 || sygn < -2){
	    name = n.name;
	    octave = n.octave;
	    sygn = n.sygn;
    }
}

int Note::getHeight(){
    int answer = (octave - 1) * 12;
    char test = 'a';
    for(int x=0; x<7; ++x){
        if(test == name) {
            break;
        }
        if(test == 'b' || test == 'e'){
            ++answer;
        } else {
            answer += 2;
        }
        ++test;
    }
    return answer + sygn;
}

void Note::change(string n){
	if(n[0] > 'g' || n[0] < 'a') return;
	name = n[0];
	if(n.length() == 1){
        	sygn = 0;
        	return;
	}
	sygn = 0;
	for(int x=1; x< n.length();){
		if(n[x] == 's' && x == 1){
			--sygn;
			++x;
			continue;
		}
        	if(n.substr(x, 2) == "is"){
			++sygn;
			x+=2;
			continue;
		}
        	if(n.substr(x, 2) == "es"){
			--sygn;
			x+=2;
			continue;
		}
	}
}

string Note::getName(){
	string answer;
	answer += name;
	int s = sygn;
	while(s != 0){
        if(s > 0){
            --s;
            answer += "is";
        }
        if(s < 0){
            ++s;
            answer += "es";
        }
	}
	if((name == 'a' || name == 'e') && answer[1] == 'e'){
	    answer = answer[0] + answer.substr(2);
	}
	return answer;
}

int Note::resolution(string keyName, bool direction){
	Key key;
	key.change(keyName);
	Scale s = key.getScale(1);
	int firstHeight = getHeight();//для проверки перехода в другую октаву
	int noteIndex = 0;

	for(int x=0; x<7; ++x){
		if(name == s.noteScale[x].name) break;
		++noteIndex;
	}

	if(noteIndex == 0 || noteIndex == 2 || noteIndex == 4){
		sygn = s.noteScale[noteIndex].sygn;
	}

	if(noteIndex == 5){
		if(direction){
			name = s.noteScale[0].name;
			sygn = s.noteScale[0].sygn;
			octave += 1;
		} else {
			name = s.noteScale[4].name;
			sygn = s.noteScale[4].sygn;
		}
	}

	if(noteIndex == 6){
		if(direction){
			name = s.noteScale[0].name;
			sygn = s.noteScale[0].sygn;
			octave += 1;
		} else {
			name = s.noteScale[4].name;
			sygn = s.noteScale[4].sygn;
		}
	}

	if(noteIndex == 1 || noteIndex == 3){
		if(direction){
			name = s.noteScale[noteIndex + 1].name;
			sygn = s.noteScale[noteIndex + 1].sygn;
		} else {
			name = s.noteScale[noteIndex - 1].name;
			sygn = s.noteScale[noteIndex - 1].sygn;
		}
	}

    if(firstHeight - getHeight() < -4){
        --octave;
    }
    if(firstHeight - getHeight() > 4){
        ++octave;
    }
    
    return s.whereIs(*this) + 1;
}
