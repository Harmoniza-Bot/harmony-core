#include <harmony-core/interval.hpp>
#include <stdexcept>

using namespace harmony_core;

Interval::Interval() noexcept
{
    this->data = 0b10000000;
}

Interval::Interval(uint8_t di, Quality q, bool d) noexcept
{
    if (d)
        this->data | 0b10000000;
    else
        this->data & 01111111;

    this->data = data | (static_cast<uint8_t>(q) << 4);

    if (di > 15)
        di = 15;
    data | di;
}

Interval::Interval(Interval in)
{
    this->data = in->get_data();
}

Interval::Interval(uint_fast8_t data)
{
    this->data = data;
}
// WRITING THIS!!!
Interval::Interval(Note n1, Note n2)
{
    if (n1.get_height() >= n2.get_height())
    {
        this->set_ditection(1);
    }
    else
    {
        this->set_direction(0);
        Note n3 = n1;
        n1 = n2;
        n2 = n3;
    }
    this->set_distance(0);
    while (1)
    {
        static uint8_t note_base = static_cast<uint8_t>(n1.get_base()) - 1;
        ++note_base;
        if (note_base > 7)
        {
            note_base = 1;
        }
        if (static_cast<Base>(note_base) == n2.get_base())
        {
            this->set_distance(++this->get_distance());
            break;
        }
        this->set_distance(++this->get_distance());
    }
    switch (n2.get_height() - n1.get_height())
    {
    }
}