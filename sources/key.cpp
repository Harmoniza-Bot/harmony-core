#include <harmony-core/key.hpp>
#include <stdextept>

using namespace harmony_core;

// Устанавливает до мажор натуральный
Key::Key() noexcept : data(0b0000000000001001)
{
}

Key::Key(Note note) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
}

Key::Key(Note note, Mode mode) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
}


Key::Key(Note note, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    set_base(note.get_base());
    set_accidental(note.get_accidental());
    set_mode(mode);
    set_specie(specie);
}

Key::Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    this->set_base(base);
    this->set_accidental(accidental);
    this->set_mode(mode);
    this->set_specie(specie);
}

Key::Key(uint_fast16_t data) noexcept
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

void Key::set_main(Note note) noexcept
{
    Note note1;
    uint8_t flats = 0;
    uint8_t sharps = 0;
    while(1){
        // первую ноту увеличиваем на кварту вторую на квинту
        for(int x=0; x<7; ++x)
        {
            --note;
            if(note.get_octave() != 5)
            {
                note.set_octave(Octave::_1_LINE);
            }
            if(x<5){
                --note1;
                if(note.get_octave() != 5)
                {
                    note.set_octave(Octave::_1_LINE);
                }
                if (x == 4)
                {
                    ++flat;
                }
            }
            if(x == 6)
            {
                ++sharp;
            }
        }
        // если одна из нот достигает до натурального - записываем расположение в квинтовом круге
        if((note.get_accidental() == Accidental::NATURAL && note.get_base() == Base::C)) || (note1.get_accidental() == Accidental::NATURAL && note1.get_base() == Base::C))
        {
            if (flats >= sharps)
            {
                data = data & 0b1111 | flat;
                data = data & 0b10000 | 1;
                return;
            }
            else
            {
                data = data & 0b1111 | sharps;
                data = data & 0b10000 | 0;
                return;
            }
        }
        
        if(sharps > 14 || flats > 14){
            return;
        }
    }
}

Note Key::get_main() noexcept
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
        note.set_base(Base::B);
    }
    else if(this->get_mode() == Mode::MIXOLYDIAN)
    {
        note.set_base(Base::G);
    }
    else if(this->get_mode() == Mode::LYDIAN)
    {
        note.set_base(Base::F);
    }
    else if(this->get_mode() == Mode::PHRYGIAN)
    {
        note.set_base(Base::E);
    }
    else if(this->get_mode() == Mode::DORIAN)
    {
        note.set_base(Base::D);
    }
    
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
    data = data & 0b11100000 | (static_cast<uint16_t>(mode) << 3);
}

Mode Key::get_mode() noexcept
{
    return static_cast<Mode>(data & 0b11100000);
}

void Key::set_specie(Specie specie) noexcept
{
    data = data & 0b11100000000 | (static_cast<uint16_t>(specie) << 3);
}

Specie Key::get_specie() noexcept
{
    return static_cast<Specie>(data & 0b11100000000);
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

void sharp_step() noexcept
{
        const bool is_negative = data & 0b10000; // Извлекаем знаковый бит
        uint8_t value = data & 0b1111; // Берём первые 4 бита как unsigned число
        
        if(is_negative)
        {
            if(value == 1) // Если достигнуто минимальное значение
            {
                data &= ~0b10000;
                value = 0;       // Устанавливаем 0
            }
            else
            {
                value -= 1;      // Просто уменьшаем значение на 1
            }
        }
        else
        {
            if(value == 14) // Если достигнут максимум
            {
                return;     // Ничего не делаем
            }
            else
            {
                value += 1; // Просто увеличиваем значение на 1
            }
        }
        
        data = (data & ~0b1111) | value; // Записываем обновленное значение назад
}

void Key::flat_step() noexcept
{
    const bool is_negative = data & 0b10000;
    uint8_t value = data & 0b1111;
    
    if(!is_negative)
    {
        if(value == 0) // Если достигнуто минимальное значение
        {
            data |= 0b10000;
            value = 1;
        }
        else
        {
            value -= 1;      // Просто уменьшаем значение на 1
        }
    }
    else
    {
        if(value == 14) // Если достигнут максимум
        {
            return;     // Ничего не делаем
        }
        else
        {
            value += 1; // Просто увеличиваем значение на 1
        }
    }
        
    data = (data & ~0b1111) | value;
}
