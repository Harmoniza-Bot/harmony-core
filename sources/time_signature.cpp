#include "harmony-core/time_signature.hpp"

using namespace harmony_core;

Time_signature::Time_signature() : numerator(2), denominator(4) {
}

Time_signature::Time_signature(uint8_t n, uint8_t d) {
    numerator = n;
    denominator = d;
}

Time_signature::Time_signature(const Time_signature &t) {
    denominator = t.get_denominator();
    numerator = t.get_numerator();
}

void Time_signature::set_signature(uint8_t n, uint8_t d) noexcept {
    numerator = n;
    denominator = d;
}

uint8_t Time_signature::get_numerator() const noexcept {
    return numerator;
}

uint8_t Time_signature::get_denominator() const noexcept {
    return denominator;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

unsigned long long powerOfTwo(int exponent) {
    return 1ULL << exponent;
}

std::pair<int, int> Time_signature::get_remainder(harmony_core::Note note, int num, int den) const noexcept {
    int num2, den2;
    if (note.get_duration() == Duration::DOUBLE) {
        num2 = 2;
        den2 = 1;
    } else {
        num2 = 1;
        den2 = powerOfTwo(static_cast<int>(note.get_duration()) - 1);
    }
    if (den == 0 || den2 == 0) {
        std::cerr << "from get_remainder: гле-то ноль...." << std::endl;
        return {1, 1};
    }

    // Приведение дробей к общему знаменателю
    int common_denominator = den * den2 / gcd(den, den2);
    int numerator1 = num * (common_denominator / den); // Числитель первой дроби
    int numerator2 = num2 * (common_denominator / den2); // Числитель второй дроби

    // Вычитаем дроби
    int result_numerator = numerator1 - numerator2;
    if (result_numerator < 0) {
        result_numerator = 0;
        std::cerr << "from get_remainder: слишком большая нота..." << std::endl;
    }
    // Сокращение результата
    /*
    int divisor = gcd(result_numerator, common_denominator);
    result_numerator /= divisor;
    common_denominator /= divisor;
    */

    return {result_numerator, common_denominator};
}

std::pair<int, int> Time_signature::get_remainder(harmony_core::Note note) const noexcept {
    return get_remainder(note, numerator, denominator);
}

std::pair<int, int> Time_signature::get_remainder(std::vector<harmony_core::Note> note) const noexcept {
    int s = note.size();
    std::pair<int, int> flag_t_s = {numerator, denominator};
    for (int x = 0; x < s; ++x) {
        flag_t_s = get_remainder(note[x], flag_t_s.first, flag_t_s.second);
        if (flag_t_s.first <= 0) {
            flag_t_s.first = 0;
            std::cerr << "From get_remainder(vector): Размер нот слишком большой..." << std::endl;
            break;
        }
    }
    return flag_t_s;
}
