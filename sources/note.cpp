#include <harmony-core/note.hpp>

using namespace harmony_core;

Note::Note() noexcept : Note(105)
{
}

Note::Note(Base base, Accidental accidental, Octave octave) noexcept : Note(
    static_cast<uint_fast8_t>(octave) * 21 + static_cast<uint_fast8_t>(accidental) * 7 + static_cast<uint_fast8_t>(base))
{
}

Note::Note(const uint_fast8_t data) noexcept : data(data)
{
}

Note::Note(const Note &note) noexcept : Note(note.data)
{
}

void Note::set_base(Base base) noexcept
{
    data = data - data % 21 % 7 + static_cast<uint_fast8_t>(base);
}

inline Note::Base Note::get_base() const noexcept
{
    return static_cast<Base>(data % 21 % 7);
}

void Note::set_accidental(Accidental accidental) noexcept
{
    data = data - data % 21 / 7 + static_cast<uint_fast8_t>(accidental) * 7;
}

inline Accidental Note::get_accidental() const noexcept
{
    return static_cast<Accidental>(data % 21 / 7);
}

void Note::set_octave(Octave octave) noexcept
{
    data = data - data / 21 + static_cast<uint_fast8_t>(octave) * 21;
}

inline Octave Note::get_octave() const noexcept
{
    return static_cast<Octave>(data / 21);
}
