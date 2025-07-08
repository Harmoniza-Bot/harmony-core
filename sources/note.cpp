#include <harmony-core/note.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
using namespace harmony_core;

// static const char8_t *NOTE_NAMES[sizeof(NamingConvention)][9 * 7 * 3] = {
//     // TODO: use correct size instead of 9 * 7 * 3
//     {
//         u8"" // TODO: make it completely
//     }};

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

Accidental Note::get_accidental() const noexcept
{
    const Accidental random_accidental = get_random_accidental();
    return random_accidental != Accidental::UNDEFINED ? random_accidental : get_key_accidental();
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


// std::u8string_view Note::get_name(const NamingConvention convention) const noexcept
// {
//     return NOTE_NAMES[static_cast<size_t>(convention)][static_cast<size_t>(this->data)];
// }

// std::u8string_view Note::get_name(NamingConvention convention = NamingConvention::ENGLISH) const noexcept;

std::string Note::get_name() const noexcept
{
    std::string name{(char) 64 + static_cast<char>(get_base())};
    switch (static_cast<uint8_t>(get_accidental()))
    {
        case 1:
        {
            if (name == "A" || name == "E")
            {
                name += "ses";
            }
            else
            {
                name += "eses";
            }
            break;
        }
        case 2:
        {
            if (name == "A" || name == "E")
            {
                name += "s";
            }
            else
            {
                name += "es";
            }
            break;
        }
        case 4:
        {
            name += "is";
            break;
        }
        case 5:
        {
            if (name == "A" || name == "E")
            {
                name += "sis";
            }
            else
            {
                name += "isis";
            }
            break;
        }
    };
    return name;
}

void Note::enharmony_сhange(bool dir) noexcept
{
    uint8_t height = this->get_height();
    if (dir)
    {
        uint8_t base = static_cast<uint8_t>(this->get_base());
        this->set_base(static_cast<Base>(++base));
        while (height != this->get_height())
        {
            uint8_t acc = static_cast<uint8_t>(this->get_accidental());
            this->set_key_accidental(static_cast<Accidental>(--acc));
        }
    }
    else
    {
        uint8_t base = static_cast<uint8_t>(this->get_base());
        this->set_base(static_cast<Base>(--base));
        while (height != this->get_height())
        {
            uint8_t acc = static_cast<uint8_t>(this->get_accidental());
            this->set_key_accidental(static_cast<Accidental>(++acc));
        }
    }
}

// ------ operators --------

Note &Note::operator++()
{
    //если знак не равен дубль диезу любую ноту можно повысить, сместив знак в диезную сторону
    if (this->get_accidental() != Accidental::DOUBLE_SHARP)
    {
        uint8_t acc = static_cast<uint8_t>(this->get_accidental());
        this->set_key_accidental(static_cast<Accidental>(++acc));
    }
    // если нота не ми и си можно повысить ее установкой диеза и повышением основания. В противном случае просто
    // повысить основание
    else
    {
        if (this->get_base() != Base::B || this->get_base() != Base::E)
        {
            this->set_key_accidental(Accidental::SHARP);
            uint8_t base = static_cast<uint8_t>(this->get_base());
            this->set_base(static_cast<Base>(++base));
        }
        else
        {
            uint8_t base = static_cast<uint8_t>(this->get_base());
            this->set_base(static_cast<Base>(++base));
        }
    }

    if ((this->get_base() == Base::B || this->get_base() == Base::E) && this->get_accidental() == Accidental::SHARP)
    {
        this->enharmony_сhange(1);
        return *this;
    }
    if (this->get_accidental() == Accidental::DOUBLE_SHARP)
    {
        this->enharmony_сhange(1);
        return *this;
    }
    return *this;
}

Note Note::operator++(int i)
{
    Note first_note(this->get_data());
    ++*this;
    return first_note;
}

Note &Note::operator--()
{
    //если знак не равен дубль бемолю любую ноту можно понизить, сместив знак в бемоьнуб сторону
    if (this->get_accidental() != Accidental::DOUBLE_FLAT)
    {
        uint8_t acc = static_cast<uint8_t>(this->get_accidental());
        this->set_key_accidental(static_cast<Accidental>(--acc));
    }
    // если нота не фа и до можно понизить ее установкой бемоля и понижением основания. В противном случае просто
    // понизить основание
    else
    {
        if (this->get_base() != Base::B || this->get_base() != Base::E)
        {
            this->set_key_accidental(Accidental::FLAT);
            uint8_t base = static_cast<uint8_t>(this->get_base());
            this->set_base(static_cast<Base>(--base));
        }
        else
        {
            uint8_t base = static_cast<uint8_t>(this->get_base());
            this->set_base(static_cast<Base>(--base));
        }
    }
    if ((this->get_base() == Base::C || this->get_base() == Base::F) && this->get_accidental() == Accidental::FLAT)
    {
        this->enharmony_сhange(0);
        return *this;
    }
    if (this->get_accidental() == Accidental::DOUBLE_FLAT)
        this->enharmony_сhange(0);

    return *this;
}

Note Note::operator--(int i)
{
    Note first_note(this->get_data());
    --*this;
    return first_note;
}
