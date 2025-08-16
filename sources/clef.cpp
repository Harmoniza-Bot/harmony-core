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

    switch(this->get_type()){
        case Clef_type::G_CLEF : {
            clef_base.set_base(Base::G);
            clef_base.set_octave(Octave::_1_LINE);

            switch(this->get_clef_name()){
                case Clef_name::FRENCH_VIOLIN : {
                    //////дописать......
                }
                case Clef_name::TREBLE : {
                    //////
                }
            }
        }
        case Clef_type::C_CLEF : {
            clef_base.set_base(Base::C);
            clef_base.set_octave(Octave::_1_LINE);

            switch (this->get_clef_name()){
                case Clef_name::SOPRANO : {

                }
                case Clef_name::MEZZO_SOPRANO : {

                }
                case Clef_name::ALTO : {

                }
                case Clef_name::TENOR : {

                }
                case Clef_name::BARITONE : {

                }
            }
        }
        case Clef_type::F_CLEF : {
            clef_base.set_base(Base::F);
            clef_base.set_octave(Octave::SMALL);

            switch (this->get_clef_name()){
                case Clef_name::BARITONE : {

                }
                case Clef_name::BASS : {

                }
                case Clef_name::SUBBASS : {

                }
            }
        }
    }
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
