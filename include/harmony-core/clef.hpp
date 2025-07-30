#ifndef HARMONY_CORE_CLEF
#define HARMONY_CORE_CLEF
#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
namespace harmony_core{
    /*! 
    * Класс представляет ключ.
    * Главная функция - определить,
    * На какой линейке расположена нота.
    */
    class Clef
    {
        public:
        
        /*!
        * Создает скрипичный ключ
        */
        explicit clef()
        {
            this->data = 0b00110011;
        }
        
        /*!
        * Создает ключ по типу и имени ключа
        */
        explicit clef(Clef_name n, Clef_type t)
        {
            this->data &= ~0b00111111;
            this->data |=(static_cast<uint8_t>(t) << 4);
            this->data |=(static_cast<uint8_t>(n));
        }
        
        // getters & setters
        
        /*!
        * 
        */
        
        //functions
        
        /*!
        * Данная функция возвращает расположение
        * ноты на нотном стане от линии снизу.
        *
        * Целые числа - нота на нотной палке.
        * Дробные числа - нота между палками.
        * 
        * Отрицательное число - 
        * колличество добавочных линеек вниз.
        *
        * положительное число больше пяти - 
        * колличество основных линеек + 
        * добавочные ввкрх 
        * (если ключ не табулатурный).
        */
        float get_place(Note)
        {
            
        }
        
        private:
        /*!
        * Биты 0-3 обозначают имя ключа
        * Биты 4-5 обозначают тип ключа
        */
        uint8_t data;
    }
}
#endif //HARMONY_CORE_CLEF