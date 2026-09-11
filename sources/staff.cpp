#include <algorithm>
#include <cmath>
#include <harmony-core/harmony-core.hpp>
using namespace harmony_core;

Staff::Staff() {
    harmony_core::Clef c;
    clef = c;
    harmony_core::Time_signature t_s;
    time_sig = t_s;
}

Staff::Staff(const harmony_core::Staff &s) {
    clef = s.get_clef();
    time_sig = s.get_time_signature();
    ptr_index = 0;
    key = s.get_key();
    for (int x = 0; x < s.get_size(); ++x) {
        note_list.resize(note_list.size() + 1);
        note_list[x].first = s.get_note(x).first;
        note_list[x].second = s.get_note(x).second;
    }
    for (int x = 0; x < s.tie_size(); ++x) {
        tie_list.resize(tie_list.size() + 1);
        tie_list[x] = s.get_tie(x);
    }
}

void Staff::set_clef(harmony_core::Clef c) noexcept {
    clef = c;
}

harmony_core::Clef Staff::get_clef() const noexcept {
    return clef;
}

void Staff::set_time_signature(harmony_core::Time_signature t) noexcept {
    time_sig = t;
}

harmony_core::Time_signature Staff::get_time_signature() const noexcept {
    return time_sig;
}

std::pair<harmony_core::Note, uint16_t> Staff::get_note(uint16_t i) const noexcept {
    if(i > note_list.size()){
        std::cerr << "From get_note: номер получаемой ноты слишком большой, UB!\n";
    }
    return note_list[i];
}

std::vector<harmony_core::Note> Staff::get_note_to_index(uint16_t i) const noexcept{
    if(i > get_index_size()){
        std::cout << "From get_note_to_index: Индекс слишком большой, UB!\n";
    }
    std::vector<harmony_core::Note> ans;
    for(int x=0; x<get_size(); ++x){
        if(note_list[x].second == i){
            ans.push_back(note_list[x].first);
        }
    }
    return ans;
}


size_t Staff::get_size() const noexcept {
    return note_list.size();
}

size_t Staff::get_index_size() const noexcept {
    size_t s = 0;
    for (int x = 1; x < note_list.size(); ++x) {
        if (note_list[x].second != note_list[x - 1].second) {
            ++s;
        }
    }
    return s;
}


void Staff::set_key(int8_t k) noexcept {
    key = k;
}

int Staff::get_key() const noexcept {
    return static_cast<int>(key);
}

void Staff::add_tie(std::pair<uint16_t, uint16_t> index) noexcept {
    if (index.first > note_list.size() || index.second > note_list.size()) {
        std::cerr << "From add_tie: Слишком большой индекс ноты..." << std::endl;
        return;
    }
    if (tie_list.size() == 0) {
        tie_list.push_back(index);
        return;
    }
    tie_list.push_back(index);
}

void Staff::rm_tie(uint16_t index) noexcept {
    for (int x = 0; x < tie_list.size(); ++x) {
        if (tie_list[x].first == index || tie_list[x].second == index) {
            tie_list.erase(tie_list.begin() + x);
            return;
        }
    }
    std::cerr << "From rm_tie: Нота " << index << " и так не залигована..." << std::endl;
}

int Staff::is_tie(uint16_t index) const noexcept {
    if (index > note_list.size()) {
        std::cerr << "From is_tie: Слишком большой индекс для поиска..." << std::endl;
        return -1;
    }
    for (int x = 0; x < tie_list.size(); ++x) {
        if (tie_list[x].first == index) {
            return static_cast<int>(tie_list[x].second);
        }
        if (tie_list[x].second == index) {
            return static_cast<int>(tie_list[x].first);
        }
    }
    return -1;
}

size_t Staff::tie_size() const noexcept {
    return tie_list.size();
}

std::pair<uint16_t, uint16_t> Staff::get_tie(uint16_t index) const noexcept {
    if (index > tie_list.size()) {
        std::cerr << "From get_tie: Слишком большой индекс..." << std::endl;
        return {0, 0};
    }
    return tie_list[index];
}

bool Staff::is_bar(uint16_t index) const noexcept {
    // Написать на основе суммы длительностей нот
}

void Staff::add_note(std::pair<harmony_core::Note, uint16_t> n) noexcept {

    // Проверка начального индекса
    if (n.second == 0) {
        std::cerr << "from Staff::add: Индексация нот начинается с 1" << std::endl;
        return;
    }

    // Проверка на то, что индекс добавляемой ноты следующий после самого большoго индекса
    int max_i = 0;
    for (int x = 0; x < note_list.size(); ++x) {
        if (max_i < note_list[x].second) {
            max_i = note_list[x].second;
        }
    }
    if (n.second > (max_i + 1)) {
        std::cerr << "from Staff::add: Индекс ноты должен быть не больше (max индекса + 1)" << std::endl;
        return;
    }

    // Проверка парных нот на одинаковость длительностей.
    for (int x = 0; x < note_list.size(); ++x) {
        if (n.second == note_list[x].second) {
            if (n.first.get_duration() != note_list[x].first.get_duration()) {
                std::cerr << "From Staff::add: Слияние нот с разной длительностью не доступно..." << std::endl;
                return;
            }
        }
    }

    note_list.push_back(n);
}


void Staff::rm(uint16_t index) noexcept {
    if (index + 1 > note_list.size()) {
        std::cerr << "From Staff::rm: Ноты с таким индексом нет" << std::endl;
        return;
    }
    note_list.erase(note_list.begin() + index);
}

Staff &Staff::operator++() {
    if (ptr_index == 65'536) {
        return *this;
    }
    ++ptr_index;
    return *this;
}

Staff Staff::operator++(int) {
    Staff s(*this);
    ++*this;
    return s;
}

Staff &Staff::operator--() {
    if (ptr_index == 0) {
        return *this;
    }
    --ptr_index;
    return *this;
}

Staff Staff::operator--(int) {
    Staff s(*this);
    --*this;
    return s;
}
