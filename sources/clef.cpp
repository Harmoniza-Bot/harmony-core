#include <stdexcept>
#include <string>

#include <harmony-core/clef.hpp>
#include <harmony-core/note.hpp>

using namespace harmony_core;

Clef::Clef() : data(0b00110011) noexcept {}

Clef::Clef(Clef_name n, Clef_type t) noexcept {
    this->data &= ~0b00111111;
    this->data |= (static_cast<uint8_t>(t) << 4);
    this->data |= (static_cast<uint8_t>(n));
}

Clef::Clef(uint8_t data) : data(data) noexcept {}

void Clef::set_data(uint_fast8_t d) : data(d) noexcept {}

uint8_t Clef::get_data() noexcept {
    return this->data;
}

void Clef::set_type(Clef_type t) noexcept {
    this->data &= ~0b00110000;
    this->data |= (static_cast<uint8_t>(t) << 4);
}

Clef_type Clef::get_type() noexcept {
    return static_cast<Clef_type>((this->data & 0b00110000) >> 4);
}

void Clef::set_name(Clef_name n) noexcept {
    this->data &= ~0b00001111;
    this->data |= static_cast<uint8_t>(n);
}

Clef_name Clef::get_clef_name() noexcept {
    return static_cast<Clef_name>(this->data & 0b00001111);
}

float Clef::get_place(const Note &note) const noexcept {
}

Note Clef::get_note(float line) const noexcept {
}

void Clef::clef_alteration(Note &note, Clef clef) noexcept {
}

std::string Clef::get_name() noexcept {
}
