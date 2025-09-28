#include <iostream>
#include <stdexcept>
#include <string>

#include <harmony-core/clef.hpp>
#include <harmony-core/note.hpp>

using namespace harmony_core;

Clef::Clef() noexcept : data(0b00110011) {
}

Clef::Clef(Clef_name n, Clef_type t) noexcept {
    this->data &= ~0b00111111;
    this->data |= (static_cast<uint8_t>(t) << 4);
    this->data |= (static_cast<uint8_t>(n));
}

Clef::Clef(uint8_t data) noexcept : data(data) {
}

void Clef::set_data(uint_fast8_t d) noexcept {
    this->data = d;
}

uint8_t Clef::get_data() const noexcept {
    return this->data;
}

void Clef::set_type(Clef_type t) noexcept {
    this->data &= ~0b00110000;
    this->data |= (static_cast<uint8_t>(t) << 4);
}

Clef_type Clef::get_type() const noexcept {
    return static_cast<Clef_type>((this->data & 0b00110000) >> 4);
}

void Clef::set_name(Clef_name n) noexcept {
    this->data &= ~0b00001111;
    this->data |= static_cast<uint8_t>(n);
}

Clef_name Clef::get_clef_name() const noexcept {
    return static_cast<Clef_name>(this->data & 0b00001111);
}

float Clef::get_place(Note note) const noexcept {
    float line;
    Note clef_base;

    switch (this->get_type()) {
        case Clef_type::G_CLEF: {
            switch (this->get_clef_name()) {
                case Clef_name::FRENCH_VIOLIN: {
                    clef_base.set_base(Base::E);
                    clef_base.set_octave(Octave::_1_LINE);
                    goto exit_from_switch;
                }
                case Clef_name::TREBLE: {
                    clef_base.set_base(Base::G);
                    clef_base.set_octave(Octave::_1_LINE);
                    goto exit_from_switch;
                }
            }
        }
        case Clef_type::C_CLEF: {
            switch (this->get_clef_name()) {
                case Clef_name::SOPRANO: {
                    clef_base.set_base(Base::C);
                    clef_base.set_octave(Octave::_1_LINE);
                    goto exit_from_switch;
                }
                case Clef_name::MEZZO_SOPRANO: {
                    clef_base.set_base(Base::A);
                    clef_base.set_octave(Octave::SMALL);
                    goto exit_from_switch;
                }
                case Clef_name::ALTO: {
                    clef_base.set_base(Base::F);
                    clef_base.set_octave(Octave::SMALL);
                    goto exit_from_switch;
                }
                case Clef_name::TENOR: {
                    clef_base.set_base(Base::D);
                    clef_base.set_octave(Octave::SMALL);
                    goto exit_from_switch;
                }
                case Clef_name::BARITONE: {
                    clef_base.set_base(Base::B);
                    clef_base.set_octave(Octave::SMALL);
                    goto exit_from_switch;
                }
            }
        }
        case Clef_type::F_CLEF: {
            switch (this->get_clef_name()) {
                case Clef_name::BARITONE: {
                    clef_base.set_base(Base::B);
                    clef_base.set_octave(Octave::SMALL);
                    goto exit_from_switch;
                }
                case Clef_name::BASS: {
                    clef_base.set_base(Base::G);
                    clef_base.set_octave(Octave::GREAT);
                    goto exit_from_switch;
                }
                case Clef_name::SUBBASS: {
                    clef_base.set_base(Base::E);
                    clef_base.set_octave(Octave::GREAT);
                    goto exit_from_switch;
                }
            }
        }
    }

exit_from_switch:
    line = (static_cast<float>(note.get_octave()) * 3.5f) - (static_cast<float>(clef_base.get_octave()) * 3.5f);

    line += (static_cast<float>(note.get_base())) - (static_cast<float>(clef_base.get_base()));
    return line;
}

Note Clef::get_note(float line) const noexcept {
    Note answer;

    return answer;
}

void Clef::clef_alteration(Note &note, Clef clef) noexcept {
}

std::string Clef::get_name() const noexcept {
    std::string name;

    return name;
}
