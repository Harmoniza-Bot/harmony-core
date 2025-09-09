#include "harmony-core/time_signature.hpp"

Time_signature::Time_signature() {
}

Time_signature::Time_signature(uint8_t, uint8_t) {
}

Time_signature::Time_signature(Time_signature &) {
}

void Time_signature::set_signature(uint8_t, uint8_t) noexcept {
}

uint8_t Time_signature::get_numerator() const noexcept {
}

uint8_t Time_signature::get_denominator() const noexcept {
}

std::pair<uint8_t, uint8_t> Time_signature::get_remainder(std::vector<harmony_core::Note>) {
}
