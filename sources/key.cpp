#include <harmony-core/key.hpp>

using namespace harmony_core;

// Устанавливает до мажор натуральный
Key::Key() noexcept : data(0b0000000000001001)
{
}

explicit Key(Note note) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
}

explicit Key(Note note, Mode mode) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
}


explicit Key(Note note, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
    set_specie(specie);
}

explicit Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    this->set_base(base);
    this->set_accidental(accidental);
    this->set_mode(mode);
    this->set_specie(specie);
}

explicit Key(uint_fast16_t data) noexcept
{
    this->data = data;
}

Key(const Key &key) noexcept
{
    this->data = key.get_data();
}

//--------------------------------

void set_data(uint_fast16_t data) noexcept
{
    this->data = data;
}

uint_fast16_t get_data() const noexcept
{
    return this->data;
}

void set_base(Base base) noexcept
{
}

Base get_base() noexcept
{
    int circle_index = this->data & 0b1111;
    Base b;
    // преобразование с помошью круга
    return static_cast<Base>(b);
}

void set_accidental(Accidental accidental) noexcept
{
}

Accidental get_accidental() noexcept
{
}

void set_mode(Mode mode) noexcept
{
}

void set_specie(Specie specie) noexcept
{
}

Mode get_mode() noexcept
{
}

Specie get_specie() noexcept
{
}

//--------------------------------

Note get_main_tone() noexcept
{
}

Note get_tone(uint8_t index) noexcept
{
}

int8_t get_tone_index(Note note) noexcept
{
}

Note resolution(Note note) noexcept
{
}

get_accidentals() noexcept
{
}

//--------------------------------
