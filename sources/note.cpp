#include <harmony-core/note.hpp>
#include <stdexcept>

using namespace harmony_core;

static const char8_t *NOTE_NAMES[sizeof(NamingConvention)][9 * 7 * 3] = {
    // TODO: use correct size instead of 9 * 7 * 3
    {
        u8"" // TODO: make it completely
    }};

Note::Note() noexcept : Note(Base::A, Octave::SUB_CONTRA, Accidental::UNDEFINED, Accidental::UNDEFINED, Duration::WHOLE)
{
}

Note::Note(const Base base, const Octave octave, const Accidental key_accidental, Accidental const random_accidental,
           const Duration duration) noexcept :
    data(0)
{
    set_base(base);
    set_octave(octave);
    set_key_accidental(key_accidental);
    set_random_accidental(random_accidental);
    set_duration(duration);
}

Note::Note(const uint_fast16_t data) noexcept : data(data)
{
}

Note::Note(const Note &note) noexcept : Note(note.data)
{
}

void Note::set_data(const uint_fast16_t data) noexcept
{
    this->data = data;
}

uint_fast16_t Note::get_data() const noexcept
{
    return data;
}

void Note::set_base(Base base) noexcept
{
    data = data & 0xFFF8 | static_cast<uint_fast16_t>(base);
}

Base Note::get_base() const noexcept
{
    return static_cast<Base>(data & 0x7);
}

void Note::set_octave(Octave octave) noexcept
{
    data = data & 0xFF87 | (static_cast<uint_fast16_t>(octave) << 3);
}

Octave Note::get_octave() const noexcept
{
    return static_cast<Octave>((data & 0x78) >> 3);
}

void Note::set_key_accidental(Accidental accidental) noexcept
{
    data = data & 0xFC7F | (static_cast<uint_fast16_t>(accidental) << 7);
}

Accidental Note::get_key_accidental() const noexcept
{
    return static_cast<Accidental>((data & 0x380) >> 7);
}

void Note::set_random_accidental(Accidental accidental) noexcept
{
    data = data & 0xE3FF | (static_cast<uint_fast16_t>(accidental) << 10);
}

Accidental Note::get_random_accidental() const noexcept
{
    return static_cast<Accidental>((data & 0x1C00) >> 10);
}

void Note::set_duration(Duration duration) noexcept
{
    data = data & 0x1FFF | (static_cast<uint_fast16_t>(duration) << 13);
}

Duration Note::get_duration() const noexcept
{
    return static_cast<Duration>((data & 0xE000) >> 13);
}

void Note::set_height(const uint_fast8_t height)
{
    if (height >= 9 * 7 * 2)
        throw std::invalid_argument("height must be less than 126");
    set_octave(static_cast<Octave>(height / (7 * 2)));
    set_base(static_cast<Base>(height % 9 / 2));
    if (height % (9 * 7 * 2) > 0)
    {
        set_random_accidental(Accidental::SHARP);
        return;
    }
    set_key_accidental(Accidental::UNDEFINED);
    set_random_accidental(Accidental::UNDEFINED);
}

uint_fast8_t Note::get_height() const noexcept
{
    uint_fast8_t result = static_cast<uint_fast8_t>(get_octave()) * 7 + static_cast<uint_fast8_t>(get_base());
    switch (get_accidental())
    {
        case Accidental::DOUBLE_FLAT:
            result -= 2;
            break;
        case Accidental::FLAT:
            --result;
            break;
        case Accidental::SHARP:
            ++result;
            break;
        case Accidental::DOUBLE_SHARP:
            result += 2;
            break;
        default:
            break;
    }
    return result;
}

Accidental Note::get_accidental() const noexcept
{
    const Accidental random_accidental = get_random_accidental();
    return random_accidental != Accidental::UNDEFINED ? random_accidental : get_key_accidental();
}

std::u8string_view Note::get_name(const NamingConvention convention) const noexcept
{
    return NOTE_NAMES[static_cast<size_t>(convention)][static_cast<size_t>(this->data)];
}
