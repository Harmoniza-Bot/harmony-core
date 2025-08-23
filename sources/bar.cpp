#include <cmath>
#include <hc2img/hc2img.hpp>

using namespace hc2img;
using namespace harmony_core;

unsigned int greatest_common_divisor(unsigned int a, unsigned int b) {
    if (a % b == 0)
        return b;
    if (b % a == 0)
        return a;

    if (a > b)
        return greatest_common_divisor(a % b, b);
    return greatest_common_divisor(a, b % a);
}

std::pair<uint8_t, uint8_t> get_abbr(std::pair<uint8_t, uint8_t> P) {
    P.first = P.first / greatest_common_divisor(P.first, P.second);
    P.second = P.second / greatest_common_divisor(P.first, P.second);
    return P;
}

std::pair<uint8_t, uint8_t> get_note_dur_sum(std::vector<Note> v) {
    std::pair<uint8_t, uint8_t> ans;
    ans.first = 0;
    ans.second = 1;

    for (int x = 0; x < v.size(); ++x) {
        static uint8_t degree_2 = 0;
        degree_2 = std::exp2(static_cast<uint8_t>(v[x].get_duration()) - 1);

        if (v[x].get_duration() != Duration::DOUBLE) {
            if (ans.second < degree_2)
                ans.second = degree_2;
        }
    }

    for (int x = 0; x < v.size(); ++x) {
        if (std::exp2(static_cast<int>(v[x].get_duration()) - 1) != ans.second) {
            ans.first += 1 * (ans.first / std::exp2(static_cast<int>(v[x].get_duration()) - 1));
        } else {
            ans.first += 1;
        }
    }
    return ans;
}

void Bar::add(Note &note, uint8_t num) noexcept {
    //Определяем размер ноты
    std::pair<uint8_t, uint8_t> note_frac;
    if (note.get_duration() == Duration::DOUBLE) {
        note_frac.first = 2;
        note_frac.second = 1;
    } else {
        note_frac.first = 1;
        note_frac.second = std::exp2(static_cast<uint8_t>(note.get_duration()) - 1);
    }

    //определяем размер такта и приводим его к размеру ноты
    std::pair<uint8_t, uint8_t> t_s = get_abbr(this->get_time_signature());
    t_s.first *= note_frac.second;
    t_s.second *= note_frac.second;

    double t_s_dec = t_s.first / t_s.second;
    double note_frac_dec = note_frac.first / note_frac.second;

    //добавляем ноту вслепую
    std::pair<uint8_t, Note *> add_n;
    add_n.first = num;
    add_n.second = &note;
    this->bar_notes.push_back(add_n);

    //Получаем сумму всех нот
    std::vector<Note> v_n;
    int b_s = this->bar_notes.size();
    for (int x = 0; x < b_s; ++x) {
        v_n.push_back(*(this->bar_notes[x].second));
    }

    //Если сумма больше 1 - убираем добавленную ноту
    if (get_note_dur_sum(v_n).first > get_note_dur_sum(v_n).second) {
        this->bar_notes.pop_back();
    }
}

void Bar::remove(uint8_t index) noexcept {
    std::erase(this->bar_notes, this->bar_notes[index]);
}
