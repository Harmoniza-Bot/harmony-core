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