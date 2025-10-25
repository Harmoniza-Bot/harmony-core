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

std::pair<uint8_t, uint8_t> Time_signature::get_remainder(std::vector<harmony_core::Note>) {
    std::pair<uint8_t, uint8_t> ans;

    return ans;
}
