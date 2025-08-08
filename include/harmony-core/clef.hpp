#ifndef HARMONY_CORE_CLEF
#define HARMONY_CORE_CLEF

#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
#include <stdexcept>

namespace harmony_core{
    /*! \brief Данный класс представляет музыкальный ключ.
    * Ключ необходим для определения линейки в нотном стане от ноты и определения ноты от линейки.
    * Также с помощью ключа можно изменить ноту, указав начальный и конечный ключ (ключевая альтерация).  
    */
    class Clef final
    {
        public:
        
        /*!
        * \brief Создает скрипичный ключ
        */
        Clef() noexcept
        {
            this->data = 0b00110011;
        }
        
        /*!
        * \brief Создает ключ по типу и имени ключа
        */
        Clef(Clef_name n, Clef_type t) noexcept
        {
            this->data &= ~0b00111111;
            this->data |=(static_cast<uint8_t>(t) << 4);
            this->data |=(static_cast<uint8_t>(n));
        }
        
        /*!
        * \brief Создает ключ по информации о ключе
        */
        Clef(uint8_t data) noexcept
        {
            this->data = data;
        }
        
        // getters & setters
        
        /*!
        * \brief Задает всю информацию
        */
        void set_data(uint_fast8_t d) noexcept
        {
            this->data = d;
        }
        
        /*!
        * \brief Возвращает информацию о ключе
        */
        [[nodiscard]] uint8_t get_data() noexcept
        {
            return this->data;
        }
        
        /*!
        * \brief Задает тип ключа
        */
        void set_type(Clef_type t) noexcept
        {
            this->data &= ~0b00110000;
            this->data |= (static_cast<uint8_t>(t) << 4);
        }
        
        /*!
        * \brief Возвращает тип ключа
        */
        [[nodiscard]] Clef_type get_type() noexcept
        {
            return static_cast<Clef_type>((this->data & 0b00110000) >> 4);
        }
        
        /*!
        * \brief Задает имя ключа
        */
        void set_name(Clef_name n) noexcept
        {
            this->data &= ~0b00001111;
            this->data |= static_cast<uint8_t>(n);
        }
        
        /*!
        * \brief Возвращает имя ключа
        */
        [[nodiscard]] Clef_name get_name() noexcept
        {
            return static_cast<Clef_name>(this->data & 0b00001111);
        }
        
        //functions
        
        /*!
        * \brief Данная функция возвращает расположение ноты на нотном стане от 0-й линии снизу.
        *
        * Целые числа - нота на нотной линейке.
        * Дробные числа - нота между линейками.
        * 
        * Отрицательное число - 
        * колличество добавочных линеек вниз.
        *
        * положительное число больше пяти - колличество основных линеек (5-ти) + добавочные линейки вверх 
        */
        [[nodiscard]] float get_place(Note&) const noexcept;

        /*!
        * \brief Данная функция возвращает ноту, насположенную на указанной линейке текущего ключа.
        * Линейки считаются от 0-й линейки снизу.
        * Например, get_place(0) от скрипичного ключа вернет \code Ми 1 октавы \endcode
        * \param [in] float Линейка для определения ноты (целое число - на линейке, дробное - между линейками)
        * \return \code Note \endcode 
        */
        [[nodiscard]] Note get_note(float) const noexcept;

        /*!
        * \brief Данная функция делает ключевую альтерацию, используя новый ключ.
        * Вначале определяется линейка ноты в текущем ключе. 
        * Потом нота изменяется на ноту, насположенную на той же линейке в целевом ключе.
        * \param [in] Note Нота для альтерации.
        * \param [in] Clef Целевой ключ.
        */
        void clef_alteration(Note&, Clef) noexcept; 
        
        private:
        /*!
        * Биты 0-3 обозначают имя ключа
        * Биты 4-5 обозначают тип ключа
        * Бит 6 обозначает перенос ключа на октаву вверх
        * Бит 7 обозначает перенос ключа на октаву вниз 
        */
        uint8_t data;
    };
}
#endif //HARMONY_CORE_CLEF