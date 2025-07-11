#include <harmony-core/interval.hpp>
#include <stdexcept>

using namespace harmony_core;

Interval::Interval() noexcept 
{
    this->data = 0b10000000;
}

Interval::Interval(uint8_t di, Quality q, bool d) noexcept
{
    if(d) this->data | 0b10000000;
    else this -> data & 01111111;
    
    this->data = data | (static_cast<uint8_t>(q) << 4);
    
    if(di > 15) di = 15;
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
//WRITE!!!
Interval::Interval(Note n1, Note n2)
{
    if(n1.get_height() >= n2.get_height()){
        this->set_ditection(1);
        while(1)
        {  
            if(static_cast<int>(n1.get_base()) == static_cast<int>(n2.get_base()))
            {
                break;
            }
            static uint8_t distance = 0;
        } 
    }
    else
    {
        this->set_direction(0);
    }
}