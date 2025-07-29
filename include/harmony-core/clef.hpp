#ifndef HARMONY_CORE_CLEF
#define HARMONY_CORE_CLEF
#include <harmony-core/enums.hpp>
namespace harmony_core{
    /*! 
    * Класс представляет ключ.
    * Главная функция - определить,
    * На какой 
    */
    class Clef
    {
        public:
        
        private:
        /*!
        * Биты 0-3 обозначают имя ключа
        * Биты 4-5 обозначают тип ключа
        */
        uint8_t data;
    }
}
#endif //HARMONY_CORE_CLEF