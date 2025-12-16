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
    bar_list.clear();
    float note_stack = 0; // сюда добавляется размер нот.
    // Если он переваливает за размер такта нотного стана - нота,
    // на которой произошло переполнение разбивается.

    float staff_size = static_cast<float>(time_sig.get_numerator()) / static_cast<float>(time_sig.get_denominator());

    int note_size = 0; // Количество полей с нотами.

    const float epsilon = 1.0f / 254.0f; // эпсилон для сравнения чисел с плавающей точкой
    const float min_gap = 1.0f / 64.0f; // Минимальный зазор между нот

    // Ищем к-во полей с нотами
    for (int x = 0; x < note_list.size(); ++x) {
        std::vector<uint16_t> note_finder;
        if (std::find(note_finder.begin(), note_finder.end(), note_list[x].second) == note_finder.end()) {
            note_finder.push_back(note_list[x].second);
            ++note_size;
        }
    }

    // Основной цикл, проверяющий длительности нот
    for (int x = 0; x < note_size; ++x) {
        if (note_list[x].first.get_duration() == Duration::DOUBLE) {
            note_stack += 2.0;
        } else {
            // Лямбда вычисляет степень двойки
            int s = [](int n) {
                if (n < 0)
                    return 1;
                return 1 << n;
            }(static_cast<int>(note_list[x].first.get_duration()) - 1);
            note_stack += 1.0f / s;
        }

        if (std::abs(note_stack - staff_size) < epsilon) {
            // Если общий размер нот равен размеру такта с точностью до epsilon
            note_stack = 0.0f;
            bar_list.push_back(x + 1);
        }
        if ((note_stack > staff_size + epsilon) && (std::abs(note_stack - staff_size) > min_gap + epsilon)) {
            std::cerr << "Fron Staff::fix_bar: Слишком большая длительность ноты " << x + 1 << std::endl;
            return;
        }
    }
}

size_t Staff::bar_size() const noexcept {
    return bar_list.size();
}

void Staff::add(std::pair<harmony_core::Note, uint16_t> n) noexcept {

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

void Staff::fix_err() noexcept {
    bar_list.clear();
    float note_stack = 0; // сюда добавляется размер нот.
    // Если он переваливает за размер такта нотного стана - нота,
    // на которой произошло переполнение разбивается.

    float staff_size = static_cast<float>(time_sig.get_numerator()) / static_cast<float>(time_sig.get_denominator());

    int note_size = 0; // Количество полей с нотами.

    const float epsilon = 1.0f / 254.0f; // эпсилон для сравнения чисел с плавающей точкой
    const float min_gap = 1.0f / 64.0f; // минимальное изменение нотной длительности

    // Ищем к-во полей с нотами
    for (int x = 0; x < note_list.size(); ++x) {
        std::vector<uint16_t> note_finder;
        if (std::find(note_finder.begin(), note_finder.end(), note_list[x].second) == note_finder.end()) {
            note_finder.push_back(note_list[x].second);
            ++note_size;
        }
    }

    // Основной цикл, проверяющий ноты на правильность группировки
    for (int x = 0; x < note_size; ++x) {
        if (note_list[x].first.get_duration() == Duration::DOUBLE) {
            note_stack += 2.0;
        } else {
            // Лямбда вычисляет степень двойки
            int s = [](int n) {
                if (n < 0)
                    return 1;
                return 1 << n;
            }(static_cast<int>(note_list[x].first.get_duration()) - 1);
            note_stack += 1.0f / s;
        }

        if (std::abs(note_stack - staff_size) < epsilon) {
            // Если общий размер нот равен размеру такта с точностью до epsilon
            note_stack = 0.0f;
            bar_list.push_back(x + 1);
        } else if ((note_stack > staff_size + epsilon) && (std::abs(note_stack - staff_size) > min_gap + epsilon)) {
            std::cerr << "Fron Staff::fix_err: Исправление группировок пока не работает..." << std::endl;
        }
    }
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
