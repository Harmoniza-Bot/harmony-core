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

// НОД
long long gcd(long long a, long long b) {
    while (b) {
        a %= b;
        std::swap(a, b);
    }
    return a;
}

// НОК
long long lcm(long long a, long long b) {
    if (a == 0 || b == 0) {
        return 0;
    }
    return std::abs(a * b) / gcd(a, b);
}

std::pair<uint16_t, uint16_t> Time_signature::get_remainder(std::vector<harmony_core::Note> n) {
    std::pair<uint16_t, uint16_t> ans;
    int max_note_sig = 0;
    for (int x = 0; x < n.size(); ++x) {
        if (max_note_sig < static_cast<int>(n[x].get_duration())) {
            max_note_sig = static_cast<int>(n[x].get_duration());
        }
    }

    ans.second = lcm(max_note_sig, denominator);
    ans.first = ans.second;

    for (int x = 0; x < n.size(); ++x) {
        static std::pair<uint16_t, uint16_t> note_sig;
        note_sig.first = max_note_sig / static_cast<int>(n[x].get_duration());
        note_sig.second = lcm(max_note_sig, denominator);
        note_sig.first *= note_sig.second / max_note_sig;

        if (note_sig.first > ans.first) {
            ans.first = 0;
            return ans;
        }
        ans.first -= note_sig.first;
    }
    return ans;
}
