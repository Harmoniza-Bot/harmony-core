#include <harmony-core/key.hpp>
#include <stdexcept>

using namespace harmony_core;

// Устанавливает до мажор натуральный
Key::Key() noexcept : data(0b0000000000001001)
{
}

Key::Key(Note note) noexcept : data(0b0000000000001001)
{
    this->set_main(note);
}

Key::Key(Note note, Mode mode) noexcept : data(0b0000000000001001)
{
    this->set_main(note);
    set_mode(mode);
}


Key::Key(Note note, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    this->set_main(note);
    this->set_mode(mode);
    this->set_specie(specie);
}

Key::Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept : data(0b0000000000001001)
{
    Note note;
    note.set_base(base);
    note.set_key_accidental(accidental);
    this->set_main(note);
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
    while (1)
    {
        // первую ноту увеличиваем на кварту вторую на квинту
        for (int x = 0; x < 7; ++x)
        {
            --note;
            if (static_cast<int>(note.get_octave()) != 5)
            {
                note.set_octave(Octave::_1_LINE);
            }
            if (x < 5)
            {
                --note1;
                if (static_cast<int>(note.get_octave()) != 5)
                {
                    note.set_octave(Octave::_1_LINE);
                }
                if (x == 4)
                {
                    ++flats;
                }
            }
            if (x == 6)
            {
                ++sharps;
            }
        }
        // если одна из нот достигает до натурального - записываем расположение в квинтовом круге
        if ((note.get_accidental() == Accidental::NATURAL && note.get_base() == Base::C) ||
            (note1.get_accidental() == Accidental::NATURAL && note1.get_base() == Base::C))
        {
            if (flats >= sharps)
            {
                data = data & 0b1111 | flats;
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

        if (sharps > 14 || flats > 14)
        {
            return;
        }
    }
}

Note Key::get_main() noexcept
{
    Note note(Base::C, Octave::_1_LINE, Accidental::NATURAL, Accidental::NATURAL, Duration::WHOLE);
    if (this->get_mode() == Mode::IONIAN)
    {
        note.set_base(Base::C);
    }
    else if (this->get_mode() == Mode::AEOLIAN)
    {
        note.set_base(Base::A);
    }
    else if (this->get_mode() == Mode::LOCRIAN)
    {
        note.set_base(Base::B);
    }
    else if (this->get_mode() == Mode::MIXOLYDIAN)
    {
        note.set_base(Base::G);
    }
    else if (this->get_mode() == Mode::LYDIAN)
    {
        note.set_base(Base::F);
    }
    else if (this->get_mode() == Mode::PHRYGIAN)
    {
        note.set_base(Base::E);
    }
    else if (this->get_mode() == Mode::DORIAN)
    {
        note.set_base(Base::D);
    }

    // извлекаем положение в квинтовом круге
    int8_t circle_rotate = static_cast<int8_t>((this->data & 0b111) ^ (-((this->data & 0b1000) != 0)));
    Octave first_octave = Octave::_1_LINE;

    while (circle_rotate != 0)
    {
        for (int x = 0; x < 7; ++x)
        {
            if (circle_rotate)
            {
                ++note;
                if (note.get_octave() != first_octave)
                {
                    note.set_octave(Octave::_1_LINE);
                }
            }
            else
            {
                --note;
                if (note.get_octave() != first_octave)
                {
                    note.set_octave(harmony_core::Octave::_1_LINE);
                }
            }
        }
        if (circle_rotate)
            --circle_rotate;
        else
            ++circle_rotate;
    }
    return note;
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
    Note note;
    // ищем первый тон натуральной модификации тон-ти.
    for (int x = 0; x != static_cast<uint8_t>(get_mode()); ++x)
    {
        ++note;
        if (note.get_accidental() != Accidental::NATURAL)
        {
            ++note;
        }
        if (note.get_octave() != Octave::_1_LINE)
        {
            note.set_octave(Octave::_1_LINE);
        }
    }

    // повышаем ноту до необходимого индекса
    while (index)
    {
        ++note;
        if (note.get_accidental() != Accidental::NATURAL)
        {
            ++note;
        }
        if (note.get_octave() != Octave::_1_LINE)
        {
            note.set_octave(Octave::_1_LINE);
        }
        --index;
    }

    // перекидываем ноту на нужную тональность по кварто-квинтовому кругу
    for (int x = 0; x < (data & 0b1111); ++x)
    {
        for (int y = 0; y < 7; ++y)
        {
            if (data & 0b10000)
            {
                --note;
            }
            else
            {
                ++note;
            }
        }
        if (note.get_octave() != Octave::_1_LINE)
        {
            note.set_octave(Octave::_1_LINE);
        }
    }
    note.set_octave(Octave::_1_LINE);
    return note;
}

int8_t Key::search_tone(Note note) noexcept
{
    note.set_octave(Octave::_1_LINE);
    for (int x = 0; x < 7; ++x)
    {
        Note answer = this->get_tone(x);
        if (answer == note)
        {
            return x;
        }
    }
    return -1;
}

Note get_interval(uint8_t index) noexcept
{
    
}

uint8_t search_interval(Note first, Note second) noexcept
{
    
}



std::vector<Note> Key::get_accidentals() noexcept
{
    std::vector<Note> answer;
    uint8_t index = 0;
    if ((static_cast<uint8_t> (data & 0b1111 - index)) == 0)
    {
        return answer;
    }
    Note note; // знаки одинаковы для всех ладов
    if (data & 0b10000)
    {
        note.set_base(Base::B);
        note.set_key_accidental(Accidental::FLAT);
    }
    else
    {
        note.set_base(Base::F);
        note.set_key_accidental(Accidental::SHARP);
    }

    for (int x = 0; x <= 14; ++x)
    {
        if ((static_cast<uint8_t> (data & 0b1111 - index)) == 0)
        {
            return answer;
        }

        for (int y = 0; y < 7; ++y)
        {
            if (data & 0b10000)
            {
                --note;
            }
            else
            {
                ++note;
            }

            if (note.get_octave() != Octave::_1_LINE)
            {
                note.set_octave(Octave::_1_LINE);
            }

            if (y == 6)
            {
                ++index;
            }
        }
        answer.push_back(note);
    }
    return answer;
}

Note Key::get_resolution(const Note& note) const noexcept
{
    
}

//--------------------------------

void Key::sharp_step() noexcept
{
    const bool is_negative = data & 0b10000; // Извлекаем знаковый бит
    uint8_t value = data & 0b1111; // Берём первые 4 бита как unsigned число

    if (is_negative)
    {
        if (value == 1) // Если достигнуто минимальное значение
        {
            data &= ~0b10000;
            value = 0; // Устанавливаем 0
        }
        else
        {
            value -= 1; // Просто уменьшаем значение на 1
        }
    }
    else
    {
        if (value == 14) // Если достигнут максимум
        {
            return; // Ничего не делаем
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

    if (!is_negative)
    {
        if (value == 0) // Если достигнуто минимальное значение
        {
            data |= 0b10000;
            value = 1;
        }
        else
        {
            value -= 1; // Просто уменьшаем значение на 1
        }
    }
    else
    {
        if (value == 14) // Если достигнут максимум
        {
            return; // Ничего не делаем
        }
        else
        {
            value += 1; // Просто увеличиваем значение на 1
        }
    }

    data = (data & ~0b1111) | value;
}

void Key::set_step(int8_t step) noexcept
{
    if (step > 0)
    {
        data &= ~0b10000;
    }
    else
    {
        data |= 0b10000;
    }

    if (data < 0)
    {
        data = -data;
    }

    if (step > 14 || step < -14)
        return;
    data = data & 0b1111 | (static_cast<uint16_t>(step));
}

int8_t Key::get_step() const noexcept
{
    int8_t answer;
    answer = data & 0b1111;

    if (data & 0b10000)
    {
        return -answer;
    }
    else
    {
        return answer;
    }
}

Note Key::Note get_resolution (const Note note, bool dir) const noexcept
{
    //гамма тональности
    std::vector<Note> scale;

    //необходимо для проверки перехода через октаву
    bool octave_trig = 0;

    //получаем гамму
    for(int x=0; x<7; ++x)
    {
        scale.push_back(this->get_tone(x));
        scale[x].set_octave(Octave::_1_LINE);

        //если итераций больше одной и наткнулись на ля - переход между октав
        if(x>0 && scale[x].get_base() == Base::A)
        {
            octave_trig = 1;
        }

        //если произошел переход через октаву - + октава
        if(octave_trig)
        {
            scale[x].set_octave(Octave::_2_LINE);
        }

        //если наткнулись на ноту из параметра - устанавливаем ей нужную октаву
        if(scale[x].get_base() == note.get_base())
        {
            note.set_octave(scale[x].get_octave());
        }

    }
    //имеем гамму и привеленную к одной с гаммой октаве ноту. Необходимо найти ближайшую к ней ноту

}
