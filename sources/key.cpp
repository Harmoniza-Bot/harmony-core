#include <harmony-core/key.hpp>

using namespace harmony_core;

// Устанавливает до мажор натуральный
Key::Key() noexcept : data(0b0000000000001001)
{
}

explicit Key::Key(Note note) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
}

explicit Key::Key(Note note, Mode mode) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
}


explicit Key::Key(Note note, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
    set_specie(specie);
}

explicit Key::Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    this->set_base(base);
    this->set_accidental(accidental);
    this->set_mode(mode);
    this->set_specie(specie);
}

explicit Key::Key(uint_fast16_t data) noexcept
{
    this->data = data;
}

Key::Key(const Key &key) noexcept
{
    this->data = key.get_data();
}

//--------------------------------

void Key::set_data(uint_fast16_t data) noexcept
{
    this->data = data;
}

uint_fast16_t Key::get_data() const noexcept
{
    return this->data;
}

void Key::set_main(Note note)
{
}

Note Key::get_main()
{
    Note note(Base::C, Octave::_1_LINE, Accidental::NATURAL, Accidental::NATURAL, Duration::WHOLE);
    if(this->get_mode() == Mode::IONIAN)
    {
        note.set_base(Base::C);
    }
    else if(this->get_mode() == Mode::AEOLIAN)
    {
        note.set_base(Base::A);
    }
    else if(this->get_mode() == Mode::LOCRIAN)
    {
        note.set_base(Base::LOCRIAN
    }
    //дописать для дркгих ладов такие же базовые тон-ти
    
    
    // извлекаем положение в квинтовом круге
    int8_t circle_rotate = static_cast<int8_t>((this->data & 0b111) ^ (-((this->data & 0b1000) != 0))); 
    Octave first_octave = Octave::_1_LINE;
    
    while(circle_rotate != 0){
        for (int x = 0; x < 7; ++x)
        {
        if (circle_rotate)
        {
            ++Note;
            if (note.get_octave() != first_octave)
            {
                note.set_octave(Octave::_1_LINE);
            }
        }
        else
        {
            --Note
            if (note.get_octave() != first_octave)
            {
                note.set_octave(_1_LINE);
            }
        }
        }
        if(circle_rotate) --circle_rotate;
        else ++circle_rotate;
    }
}

void Key::set_mode(Mode mode) noexcept
{
}

Mode Key::get_mode() noexcept
{
}

void Key::set_specie(Specie specie) noexcept
{
}

Specie Key::get_specie() noexcept
{
}

//--------------------------------

Note Key::get_tone(uint8_t index) noexcept
{
}

int8_t Key::get_tone_index(Note note) noexcept
{
}

Note Key::resolution(Note note) noexcept
{
}

vector<Accidental> Key::get_accidentals() noexcept
{
}

//--------------------------------

Key::sharp_step()
{
}

Key::flat_step()
{
}
