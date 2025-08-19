#ifndef HARMONY_CORE_CLEF
#define HARMONY_CORE_CLEF

#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
#include <stdexcept>
#include <string>

namespace harmony_core {
    /*! \brief Данный класс представляет музыкальный ключ.
     * Ключ необходим для определения линейки в нотном стане от ноты и определения ноты от линейки.
     * Также с помощью ключа можно изменить ноту, указав начальный и конечный ключ (ключевая альтерация).
     */
    class Clef final {
    public:
        /*!
         * \brief Создает скрипичный ключ
         */
        Clef() noexcept;

        /*!
         * \brief Создает ключ по типу и имени ключа
         */
        Clef(Clef_name n, Clef_type t) noexcept;

        /*!
         * \brief Создает ключ по информации о ключе
         */
        Clef(uint8_t data) noexcept;

        // getters & setters

        /*!
         * \brief Задает всю информацию
         */
        void set_data(uint_fast8_t d) noexcept;

        /*!
         * \brief Возвращает информацию о ключе
         */
        [[nodiscard]] uint8_t get_data() const noexcept;

        /*!
         * \brief Задает тип ключа
         */
        void set_type(Clef_type t) noexcept;

        /*!
         * \brief Возвращает тип ключа
         */
        [[nodiscard]] Clef_type get_type() const noexcept;

        /*!
         * \brief Задает имя ключа
         */
        void set_name(Clef_name n) noexcept;

        /*!
         * \brief Возвращает имя ключа в формате Clef_name.
         */
        [[nodiscard]] Clef_name get_clef_name() const noexcept;

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
        [[nodiscard]] float get_place(Note note) const noexcept;

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
        void clef_alteration(Note &, Clef) noexcept;

        /*!
         * \brief Возвращает имя ключа в строковом формате.
         */
        [[nodiscard]] std::string get_name() const noexcept;


    private:
        /*!
         * Биты \code 0-3 \endcode обозначают имя ключа
         * Биты \code 4-5 \endcode обозначают тип ключа
         * Бит \code 6 \endcode обозначает перенос ключа на октаву вверх
         * Бит \code 7 \endcode обозначает перенос ключа на октаву вниз
         */
        uint8_t data;
    };
} // namespace harmony_core
#endif // HARMONY_CORE_CLEF
