#include <stdexcept>

#include <harmony-core/clef.hpp>
#include <harmony-core/note.hpp>

#include <string>
#include <stdexcept>

using namespace harmony_core;

float Clef::get_place(const Note note&) const noexcept
{
    // расстояние до нулевой линейки ключа от ля суб контр октавы 
    int8_t clef_zero_point = 0; 

    switch(this->get_name())
    {
        case Clef_name::FRENCH_VIOLIN : 
        {
            clef_zero_point = 13;
            break;
        }
        case Clef_name::TREBLE : 
        {
            clef_zero_point = 12;
            break;
        }
        case Clef_name::SOPRANO : 
        {
            clef_zero_point = 11;
            break;
        }
        case Clef_name::MEZZO_SOPRANO : 
        {
            clef_zero_point = 10;
            break;
        }
        case Clef_name::ALTO : 
        {
            clef_zero_point = 9;
            break;
        }
        case Clef_name::TENOR : 
        {
            clef_zero_point = 8;
            break;
        }
        case Clef_name::BARITONE : 
        {
            clef_zero_point = 7;
            break;
        }
        case Clef_name::BASS : 
        {
            clef_zero_point = 6;
            break;
        }
        case Clef_name::SUBBASS : 
        {
            clef_zero_point = 6;
            break;
        }
    }

    int8_t number_note_line = static_cast<int>(note.get_octave()) * 4;
    number_note_line += static_cast<int>(note.get_base()) - static_cast<int>(Base::A);

    return (static_cast<float>(note.get_height()) / 2) - static_cast<float>(clef_zero_point);
}

Note Clef::get_note(float line) const noexcept
{

}

void Clef::clef_alteration(Note& note, Clef clef) noexcept
{

}

std::string Clef::get_name()
{

}
