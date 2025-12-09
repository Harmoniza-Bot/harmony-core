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
    for (int x = 0; x < s.get_note_list_size(); ++x) {
        note_list.resize(note_list.size() + 1);
        note_list[x].first = s.get_note(x).first;
        note_list[x].second = s.get_note(x).second;
    }
    for (int x = 0; x < s.tie_size(); ++x) {
        tie_list.resize(tie_list.size() + 1);
        tie_list[x] = s.get_tie(x);
    }
    for (int x = 0; x < s.bar_size(); ++x) {
        bar_list.resize(bar_list.size() + 1);
        bar_list[x] = s.get_bar(x);
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
    return note_list[i];
}

size_t Staff::get_note_list_size() const noexcept {
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

void Staff::add_tie(uint16_t index) noexcept {
    if (index > note_list.size()) {
        std::cerr << "From add_tie: Слишком большой индекс ноты..." << std::endl;
        return;
    }
    if (tie_list.size() == 0) {
        tie_list.push_back(index);
        return;
    }
    for (int x = 0; x < tie_list.size(); ++x) {
        if (index <= tie_list[x]) {
            tie_list.insert(tie_list.begin() + x, index);
        }
    }
    tie_list.push_back(index);
}

void Staff::rm_tie(uint16_t index) noexcept {
    for (int x = 0; x < tie_list.size(); ++x) {
        if (tie_list[x] == index) {
            tie_list.erase(tie_list.begin() + x);
            return;
        }
    }
    std::cerr << "From rm_tie: Нота " << index << " и так не залигована..." << std::endl;
}

bool Staff::is_tie(uint16_t index) const noexcept {
    for (int x = 0; x < tie_list.size(); ++x) {
        if (tie_list[x] == index) {
            return 1;
        }
    }
    return 0;
}

size_t Staff::tie_size() const noexcept {
    return tie_list.size();
}

uint16_t Staff::get_tie(uint16_t index) const noexcept {
    if (index > tie_list.size()) {
        std::cerr << "From get_tie: Слишком большой индекс..." << std::endl;
        return 0;
    }
    return tie_list[index];
}

void Staff::add_bar(uint16_t index) noexcept {
    if (index > note_list.size()) {
        std::cerr << "From add_bar: Слишком большой индекс ноты..." << std::endl;
        return;
    }
    if (bar_list.size() == 0) {
        bar_list.push_back(index);
        return;
    }
    for (int x = 0; x < bar_list.size(); ++x) {
        if (index <= bar_list[x]) {
            bar_list.insert(bar_list.begin() + x, index);
        }
    }
    bar_list.push_back(index);
}

void Staff::rm_bar(uint16_t index) noexcept {
    for (int x = 0; x < bar_list.size(); ++x) {
        if (bar_list[x] == index) {
            bar_list.erase(bar_list.begin() + x);
            return;
        }
    }
    std::cerr << "From rm_bar: После ноты " << index << " нет тактовой черты..." << std::endl;
}

uint16_t Staff::get_bar(uint16_t index) const noexcept {
    return bar_list[index];
}

bool Staff::is_bar(uint16_t index) const noexcept {
    return std::count(bar_list.begin(), bar_list.end(), index) != 0;
}


void Staff::fix_bar() noexcept {
}

size_t Staff::bar_size() const noexcept {
    return bar_list.size();
}

void Staff::add(std::pair<harmony_core::Note, uint16_t> n) noexcept {
    // Происходит умная вставка: ноты сортируются по индексу (2 элемент пары)
    auto &notes = note_list;

    // Определяем размер списка
    int size = notes.size();

    if (size != 0) { // Если список не пустой
        for (int i = 0; i < size; ++i) {
            // Теперь проверяем, что текущий элемент больше нового
            if (notes[i].second >= n.second) {
                // Вставляем новую пару в позицию перед текущим элементом
                notes.insert(notes.begin() + i, n);
                return;
            }
        }

        // Если не нашли подходящего места, значит добавляем в конец
        notes.push_back(n);
        return;
    } else {
        // Если список пуст, просто добавляем новую пару
        notes.push_back(n);
        return;
    }
}


void Staff::rm(uint16_t index) noexcept {
    if (index + 1 > note_list.size()) {
        return;
    }
    note_list.erase(note_list.begin() + index);
}

// size_t Staff::get_size() const noexcept {
//     float full_note_size = 0;
//     for (int x = 0; x < note_list.size(); ++x) {
//         static uint8_t note_size;
//         note_size = static_cast<int>(note_list[x].get_duration());
//         if (note_size == 0) {
//             full_note_size += 2;
//         } else {
//             --note_size;
//             full_note_size += 1 / pow(2, note_size);
//         }
//     }
//     full_note_size /= (static_cast<float>(time_sig.get_numerator()) /
//     static_cast<float>(time_sig.get_denominator())); return static_cast<size_t>(full_note_size);
// }

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
