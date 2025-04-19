#include "headers.h"
#include <iostream>

using namespace std;



Key::Key(){
    	Note n;
    	mainTone = n;
	lad = "dur";
	mod = 'n';
}

void Key::change(string n){
	if(n[0] <= 'G' && n[0] >= 'A'){
		lad = "dur";
		n[0] += 32;
	} else if (n[0] <= 'g' && n[0] >= 'a'){
		lad = "mol";
	} else return;

    mainTone.name = n[0];
    if(n[0] == 'a' || n[0] == 'e'){
	    if(n.length() > 2){
		    n.erase(1);
	    }
	    --mainTone.sygn;
    }
    if(n.length() == 1){
        mainTone.sygn = 0;
        return;
    }
    for(int x=1; x< n.length(); x+=2){
        if(n.substr(x, 2) == "is") ++mainTone.sygn;
        if(n.substr(x, 2) == "es") --mainTone.sygn;
    }
}

Scale Key::getScale(bool direction){
	Scale answer;
	Note n;
	vector<int> l;
//----------------------------------------------------	
	if(lad == "dur"){
		for(int x=0; x<7; ++x){
			l.push_back(dTones[x]);
		}
	}
	if(lad == "mol"){
		for(int x=0; x<7; ++x){
			l.push_back(mTones[x]);
		}
	}
	if(lad == "dor"){
		for(int x=0; x<7; ++x){
			l.push_back(oTones[x]);
		}
	}
	if(lad == "frg"){
		for(int x=0; x<7; ++x){
			l.push_back(fTones[x]);
		}
	}
	if(lad == "lid"){
		for(int x=0; x<7; ++x){
			l.push_back(lTones[x]);
		}
	}
	if(lad == "mks"){
		for(int x=0; x<7; ++x){
			l.push_back(mTones[x]);
		}
	}
	if(lad == "lks"){
		for(int x=0; x<7; ++x){
			l.push_back(kTones[x]);
		}
	}

	if(mod == 'g'){
		l[4] = 1;
		l[5] = 3;
	}
	if(mod == 'm'){
		l[4] = 2;
		l[5] = 2;
	}

//-----------------------------------------------------
	answer.noteScale.push_back(mainTone);
	for(int x=1; x<l.size(); ++x){
		n = mainTone;
		n.name += x;
		if(n.name > 'g'){
			n.name -= 7;
			++n.octave;
		}
		n.sygn = 0;
		n.sygn = l[x-1] - (n.getHeight() - answer.noteScale[x-1].getHeight());
		answer.noteScale.push_back(n);
	}//строим натуральную гамму

	Scale natAnswer = answer;//сохраняем исходрую гамму на случай обработки хром. исключений

	if(mod == 'h'){
		int t = answer.noteScale.size();
		n = answer.noteScale[0];
		++n.octave;
		answer.noteScale.push_back(n);//Прибавляем ноту след. гаммы чтобы найти большую секунду между 7 и 1 
		for(int x=0; x<t; ++x){
			if(answer.noteScale[x+1].getHeight() - answer.noteScale[x].getHeight() == 2){
				n = answer.noteScale[x];
				++n.sygn;
				if(!direction) n.enharmonyChange(1);
				auto iter = answer.noteScale.cbegin();
				answer.noteScale.emplace(iter + (x+1), n);
				++t;
				++x;
			}
		}
		answer.noteScale.pop_back();//Убираем последнюю ноту, дублирующую первую через октаву
	}
	
	if(!direction){
		if(mod == 'n' || mod == 'g' || mod == 'm'){
			for(int x=0; x<3; ++x){
				n = answer.noteScale[x];
				if(x==0) ++n.octave;
				answer.noteScale[x] = answer.noteScale[6-x];
				answer.noteScale[6-x] = n;
			}
			answer.noteScale.insert(answer.noteScale.begin(), answer.noteScale[6]);
			answer.noteScale.pop_back();

			if(mod == 'm'){
				--answer.noteScale[1].sygn;
				--answer.noteScale[2].sygn;
			}
		}
		if(mod == 'h'){
			++answer.noteScale[0].octave;
			for(int x=1; x<=5; ++x){
				n = answer.noteScale[x];
				answer.noteScale[x] = answer.noteScale[12-x];
				answer.noteScale[12-x] = n;
			}
		}//Алгоритмы разворачивания гамм
	}
//------------------ обработка хроматической гаммы ----------
	if(mod=='h'){
		int t = natAnswer.noteScale.size();
		if(direction){
			for(int x=0; x<t; ++x){
				natAnswer.noteScale.push_back(natAnswer.noteScale[x]);
				++natAnswer.noteScale[x+7].octave;
			}//Прибавляем вторую октаву к нат. гамме
			int t = natAnswer.noteScale.size();
			for(int x=0; x<t; ++x){
				if((natAnswer.noteScale[x+4].getHeight() - natAnswer.noteScale[x].getHeight()) == 6){
					natAnswer.noteScale.insert(natAnswer.noteScale.begin(), natAnswer.noteScale[t-1]);
					natAnswer.noteScale[0].octave -= 2;//на случай, если гамма начинается с малой секунды

					int enn = answer.whereIs(natAnswer.noteScale[x]);
					if(natAnswer.noteScale[x].getHeight() - natAnswer.noteScale[x-1].getHeight() == 2){
						answer.noteScale[enn-1].enharmonyChange(1);
					}
				}
			}//собственно, поиск уменьшенной квинты
		} else {
			for(int x=0; x<3; ++x){
				n = natAnswer.noteScale[x];
				natAnswer.noteScale[x] = natAnswer.noteScale[6-x];
				natAnswer.noteScale[6-x] = n;
			}//Прибавляем
			for(int x=0; x<t; ++x){
				natAnswer.noteScale.push_back(natAnswer.noteScale[x]);
				--natAnswer.noteScale[x+7].octave;
			}//разворачиваем

			natAnswer.noteScale.insert(natAnswer.noteScale.begin(), natAnswer.noteScale[natAnswer.noteScale.size() - 1]);
			natAnswer.noteScale.pop_back();
			natAnswer.noteScale[0].octave += 2;//переносим последнюю ноту в начало и урезаем ее октаву
			
			int t = natAnswer.noteScale.size();
			for(int x=0; x<t; ++x){
				if((natAnswer.noteScale[x].getHeight() - natAnswer.noteScale[x+4].getHeight()) == 6){
					natAnswer.noteScale.insert(natAnswer.noteScale.begin(), natAnswer.noteScale[t-1]);
					natAnswer.noteScale[0].octave += 2;//на тот хе случай, что в первом разе
					
					int enn = answer.whereIs(natAnswer.noteScale[x]);
					if(natAnswer.noteScale[x-1].getHeight() - natAnswer.noteScale[x].getHeight() == 2){
						answer.noteScale[enn+1] = answer.noteScale[enn+2];
						++answer.noteScale[enn+1].sygn;//это костыль, но вроде работает
					}
				}
			}//такой же поиск, как раньше, но ноты поиска инвертированы
		}
	}
	return answer;
}

int Key::whereIs(Note n, bool direction){
	int answer;
	Scale s = getScale(direction);
	int t = s.noteScale.size();
	for(int x=0; x<t; ++x){
		if(s.noteScale[x].name == n.name){
		    if(s.noteScale[x].sygn == n.sygn){
			    if(s.noteScale[x].octave == n.octave){
					return x + 1;
			    }
		    }
		}
	}
	return -1;
}

int Key::whereIs(Interval i, bool direction){
    Scale s = this->getScale(direction);
    int firstSize = s.noteScale.size();
    for(int x=0; x<firstSize; ++x){
        s.noteScale.push_back(s.noteScale[x]);
        ++s.noteScale[x+firstSize].octave;
    }
    if(direction){
        for(int x=0; x<s.noteScale.size(); ++x){
            if(i.low.name == s.noteScale[x].name && i.low.sygn == s.noteScale[x].sygn){
                if(i.high.name == s.noteScale[x + i.getDistance()].name && i.high.sygn == s.noteScale[x + i.getDistance()].sygn){
                    return x + 1;
                }
            }
        }
    } else {
        for(int x=0; x<s.noteScale.size(); ++x){
            if(i.high.name == s.noteScale[x].name && i.high.sygn == s.noteScale[x].sygn){
                if(i.low.name == s.noteScale[x + i.getDistance()].name && i.low.sygn == s.noteScale[x + i.getDistance()].sygn){
                    return (x + 1) - i.getDistance();
                }
            }
        }
    }
	return -1;
}//потестить. Сейчас я в бк, бухать колу

int Key::whereIs(Accord a, bool direction){
	int answer;

	return answer;
}
