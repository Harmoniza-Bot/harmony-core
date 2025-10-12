#include "harmony-core/time_signature.hpp"

using namespace harmony_core;

Time_signature::Time_signature() {
}

Time_signature::Time_signature(uint8_t, uint8_t) {
}

Time_signature::Time_signature(const Time_signature &) {
}

void Time_signature::set_data(uint8_t i) {
    data = i;
}

uint8_t Time_signature::get_data() {
    return data;
}

void Time_signature::set_signature(uint8_t, uint8_t) noexcept {
}

uint8_t Time_signature::get_numerator() const noexcept {
    uint8_t ans;

    return ans;
}

uint8_t Time_signature::get_denominator() const noexcept {
    uint8_t ans;

    return ans;
}

std::pair<uint8_t, uint8_t> Time_signature::get_remainder(std::vector<harmony_core::Note>) {
    std::pair<uint8_t, uint8_t> ans;

    return ans;
}
