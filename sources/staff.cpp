#include <cmath>
#include <harmony-core/harmony-core.hpp>
#include <hc2img/staff.hpp>
using namespace hc2img;

Staff::Staff() {
    harmony_core::Clef c;
    clef = c;
    harmony_core::Time_signature t_s;
    time_sig = t_s;
    key = 0;
}

Staff::Staff(const hc2img::Staff &s) {
    clef = s.get_clef();
    time_sig = s.get_time_signature();
    ptr_index = 0;
    for (int x = 0; x < s.get_note_list_size(); ++x) {
        note_list.resize(note_list.size() + 1);
        note_list[x].first = s.get_note(x).first;
        note_list[x].second = s.get_note(x).second;
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

void Staff::set_key(int8_t k) noexcept {
    key = k;
}

int8_t Staff::get_key() const noexcept {
    return key;
}

void Staff::add(std::pair<harmony_core::Note, uint16_t> &n) noexcept {
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
