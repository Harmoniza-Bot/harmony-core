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

void Note::enharmonyChange(bool dir) const noexcept
{
  int first_height = get_height();
    if(dir){
      if((base==Base::C || base==Base::E) && 
      get_accidental() == Accidental::SHARP){
        return;
      }
      if(get_accidental() == Accidental::DOUBLE_SHARP){
        return;
      }
      base = 
      [](){
        if(base == Base::B){
          return Base::C;
        }
        return static_cast<Base>(
          static_cast<int>(base) + 1
          );
        }
        set_octave(
          static_cast<Octave>(
            static_cast<int> + 1
          )
        );
      };
      while(get_height() != first_height){
        accidental = static_cast<Accidental>(static_cast<int>(accidental) - 1);
      }
    } else {
    }
}

inline int Note::get_height() const
{
    return (int)data;
}

void Note::resolution(Note key, bool dir) noexcept
{
}
