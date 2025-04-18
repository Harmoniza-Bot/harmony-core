#include <harmony-core/key.hpp>

using namespace harmony_core;

// Устанавливает до мажор натуральный
Key::Key() noexcept
{
    data = 0b0000000000001001;
}

explicit Key(Note note) noexcept
{
}

explicit Key(Note note, Mode mode) noexcept
{
}

explicit Key(Note note, Mode mode, Specie specie) noexcept
{
}

explicit Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept
{
}

explicit Key(uint_fast16_t data) noexcept
{
    this->data = data;
}

Key(const Key &key) noexcept
{
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
