#ifndef HARMONY_CORE_CLEF
#define HARMONY_CORE_CLEF
#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
#include <stdexcept>

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
        
        /*!
        * Создает ключ по информации о ключе
        */
        explicit clef(uint8_t data)
        {
            this->data = data;
        }
        
        // getters & setters
        
        /*!
        * Задает всю информацию
        */
        void set_data(uint_fast8_t d)
        {
            this->data = d;
        }
        
        /*!
        * Возвращает информацию о ключе
        */
        [[nodiscard]] uint8_t get_data()
        {
            return this->data;
        }
        
        /*!
        * Задает тип ключа
        */
        void set_type(Clef_type t)
        {
            this->data &= ~0b00110000;
            this->data |= (static_cast<uint8_t>(t) << 4);
        }
        
        /*!
        * Возвращает тип ключа
        */
        [[nodiscard]] Clef_type get_type()
        {
            return static_cast<Clef_type>((this->data & 0b00110000) >> 4);
        }
        
        /*!
        * Задает имя ключа
        */
        void set_name(Clef_name n)
        {
            this->data &= ~0b00001111;
            this->data |= static_cast<uint8_t>(n);
        }
        
        /*!
        * Возвращает имя ключа
        */
        [[nodiscard]] Clef_name get_name()
        {
            return static_cast<Clef_type>(this->data & 0b00001111);
        }
        
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
        float get_place(Note);
        
        private:
        /*!
        * Биты 0-3 обозначают имя ключа
        * Биты 4-5 обозначают тип ключа
        */
        uint8_t data;
    }
}
#endif //HARMONY_CORE_CLEF