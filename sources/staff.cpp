#include <hc2img/staff.hpp>
#include <cmath>
using namespace hc2img;

Staff::Staff(){
    harmony_core::Clef c;
    clef = c;
    harmony_core::Time_signature t_s;
    time_sig = t_s;
}

void Staff::add(harmony_core::Note *n, bool is_pause) noexcept {
    std::pair<harmony_core::Note *, bool> p(n, is_pause);
    if(ptr_index==note_list.size() || !ptr_index){
        note_list.push_back(p);
    } else {
        note_list[note_list] = p;
    }
}

void Staff::rm(uint16_t) noexcept {
    
}

size_t Staff::get_whole() const noexcept {
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

Staff &Staff::operator--(){
    if(index == 0){
        return *this;
    }
    --ptr_index;
    return *this;
}