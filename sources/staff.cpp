#include <hc2img/staff.hpp>
#include <cmath>
using namespace hc2img;

explicit Staff::Staff(){
    harmony_core::Clef c;
    clef = c;
    harmony_core::Time_signature t_s;
    time_sig = t_s;
}

explicit Staff::Staff(hc2img::Staff s){
    clef = s.get_clef();
    time_sig = s.get_time_signature();
    ptr_index = 0;
    for(int x=0; x<s.get_note_list_size(); ++x){
        note_list[x] = s.get_note(x);
    }
}

void set_clef(harmony_core::Clef c){
    clef = *c.get_clef();
}

harmony_core::Clef get_clef(){
    return *clef;
}

void set_time_signature(harmony_core::Time_signature t){
    time_sig = *t.get_time_signature();
}
        
harmony_core::time_signature get_time_signature(){
    return *time_sig;
}

std::pair<Note::Note n, bool i> get_note(uint16_t i){
    return note_list[i];
}

size_t get_note_list_size(){
    return note_list.size();
}

void Staff::add(harmony_core::Note *n, bool is_pause) noexcept {
    std::pair<harmony_core::Note *, bool> p(n, is_pause);
    if(ptr_index==note_list.size() || !ptr_index){
        note_list.push_back(p);
    } else {
        note_list[note_list] = p;
    }
}

void Staff::rm(uint16_t index) noexcept {
    if(index + 1 > note_list.size()){
        return;
    }
    note_list.erase(note_list.begin() + index);
}

size_t Staff::get_size() const noexcept {
    float full_note_size = 0;
    for(int x=0; x<note_list.size(); ++x){
        static uint8_t note_size;
        note_size = static_cast<int>(note_list.first.get_duration());
        if (note_size == 0){
            full_note_size += 2;
        } else {
            --note_size;
            full_note_size += 1/pow(2, note_size);
        }
    }
    full_note_size /= (
        time_sig.get_numerator() /
        time_sig.get_denominator()
    );
    return static_cast<size_t>(full_note_size);
}

Staff &Staff::operator++(){
    if(index == 65'536){
        return *this;
    }
    ++ptr_index;
    return *this;
}

Staff Staff::operator++(int){
    Staff s(*this);
    ++*this;
    return s;
}

Staff &Staff::operator--(){
    if(index == 0){
        return *this;
    }
    --ptr_index;
    return *this;
}

Staff Staff::operator--(int){
    Staff s(*this);
    --*this;
    return s;
}