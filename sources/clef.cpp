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
    float line = 0;
    Note clef_base;

    switch (this->get_type()) {
        case Clef_type::G_CLEF: {
            switch (this->get_clef_name()) {
                case Clef_name::FRENCH_VIOLIN: {
                    clef_base.set_base(Base::G);
                    clef_base.set_octave(Octave::_1_LINE);
                    goto exit_from_switch;
                }
                case Clef_name::TREBLE: {
                    clef_base.set_base(Base::E);
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
    int t = note.get_height() - clef_base.get_height();
    Base b = note.get_base();
    while (t != 0) {
        if (t > 0) {
            --note;
            --t;
            if (b != note.get_base()) {
                b = note.get_base();
                line += 0.5;
            }
        } else {
            ++note;
            ++t;
            if (b != note.get_base()) {
                b = note.get_base();
                line -= 0.5;
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
    switch (static_cast<int>(get_clef_name())) {
        case 1: {
            return "NEUTRAL";
        }
        case 2: {
            return "FRENCH_VIOLIN";
        }
        case 3: {
            return "TREBLE";
        }
        case 4: {
            return "SOPRANO";
        }
        case 5: {
            return "MEZZO_SOPRANO";
        }
        case 6: {
            return "ALTO";
        }
        case 7: {
            return "TENOR";
        }
        case 8: {
            return "BARITONE";
        }
        case 9: {
            return "BASS";
        }
        case 10: {
            return "SUBBASS";
        }
        case 11: {
            return "TABULATURE";
        }
        case 0: {
            return "NONE";
        }
    }
    return "no_name";
}

bool Clef::check_clef() {
    switch (static_cast<int>(get_type())) {
        case 0: {
            return 1;
        }
        case 1: {
            if (get_clef_name() != Clef_name::BARITONE && get_clef_name() != Clef_name::BASS &&
                get_clef_name() != Clef_name::SUBBASS) {
                return 1;
            }
            return 0;
        }
        case 2: {
            if (get_clef_name() != Clef_name::SOPRANO && get_clef_name() != Clef_name::MEZZO_SOPRANO &&
                get_clef_name() != Clef_name::ALTO && get_clef_name() != Clef_name::TENOR &&
                get_clef_name() != Clef_name::BARITONE) {
                return 1;
            }
            return 0;
        }
        case 3: {
            if (get_clef_name() != Clef_name::TREBLE && get_clef_name() != Clef_name::FRENCH_VIOLIN) {
                return 1;
            }
            return 0;
        }
    }
    return 0;
}
