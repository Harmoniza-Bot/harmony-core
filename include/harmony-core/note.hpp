#ifndef HARMONY_CORE_NOTE_HPP
#define HARMONY_CORE_NOTE_HPP

#include <cstdint>
#include <harmony-core/accidental.hpp>
#include <harmony-core/octave.hpp>

namespace harmony_core
{
    /*!
     * \brief Нота со знаком альтерации и информацией об октаве.
     */
    class Note
    {
    public:
        /*!
         * \brief Основа ноты.
         */
        enum class Base
        {
            /*!
             * \brief Нота \code До\endcode.
             */
            C,
            /*!
             * \brief Нота \code Ре\endcode.
             */
            D,
            /*!
             * \brief Нота \code Ми\endcode.
             */
            E,
            /*!
             * \brief Нота \code Фа\endcode.
             */
            F,
            /*!
             * \brief Нота \code Соль\endcode.
             */
            G,
            /*!
             * \brief Нота \code Ля\endcode.
             */
            A,
            /*!
             * \brief Нота \code Си\endcode.
             */
            B
        };

        /*!
         * \brief Создаёт ноту \code До¹\endcode (Бекар) со значением \code 105\endcode.
         */
        Note() noexcept;
        /*!
         * \brief Создаёт ноту на основе \code base\endcode, \code accidental\endcode и \code octave\endcode.
         * \param [in] base основа ноты.
         * \param [in] accidental знак альтерации ноты.
         * \param [in] octave октава ноты.
         */
        explicit Note(Base base, Accidental accidental, Octave octave) noexcept;
        /*!
         * \brief Создаёт ноту на основе \code data\endcode.
         * \param [in] data информация об основе, знаке альтерации и октаве ноты.
         */
        explicit Note(uint_fast8_t data) noexcept;
        /*!
         * \brief Создаёт ноту на основе \code note\endcode.
         * \param [in] note другая нота.
         */
        explicit Note(const Note &note) noexcept;
        /*!
         * \brief Удаляет ноту.
         */
        ~Note() noexcept = default;

        /*!
         * \brief Задаёт основу этой ноты равной \code base\endcode.
         * \param [in] base основа ноты.
         */
        void set_base(Base base) noexcept;

        /*!
         * \brief Возвращает основу этой ноты.
         * @return Основа этой ноты.
         */
        Base get_base() const noexcept;

        /*!
         * \brief Задаёт знак альтерации этой ноты равным \code accidental\endcode.
         * \param [in] accidental знак альтерации ноты.
         */
        void set_accidental(Accidental accidental) noexcept;

        /*!
         * \brief Возвращает знак альтерации этой ноты.
         * @return Знак альтерации этой ноты.
         */
        Accidental get_accidental() const noexcept;

        /*!
         * \brief Задаёт октаву этой ноты равной \code octave\endcode.
         * \param [in] octave октава ноты.
         */
        void set_octave(Octave octave) noexcept;

        /*!
         * \brief Возвращает октаву этой ноты.
         * @return Октаву этой ноты.
         */
        Octave get_octave() const noexcept;

    private:
        /**
         * \brief Содержит информацию об основе, знаке альтерации и октаве ноты.
         *
         * Значение должно находится в пределе от \code 0\endcode до \code 188\endcode, то есть, к примеру:
         * 1. Ноте \code До₂\endcode (Бекар) соответствует значение \code 0\endcode.
         * 2. Ноте \code Си₂\endcode (Бекар) соответствует значение \code 6\endcode.
         * 3. Ноте \code До-бемоль₂\endcode соответствует значение \code 7\endcode.
         * 4. Ноте \code Си-бемоль₂\endcode соответствует значение \code 13\endcode.
         * 5. Ноте \code До-диез₂\endcode соответствует значение \code 14\endcode.
         * 6. Ноте \code Си-диез₂\endcode соответствует значение \code 20\endcode.
         * 7. Ноте \code До₁\endcode (Бекар) соответствует значение \code 21\endcode.
         * 8. Ноте \code Си-диез₁\endcode соответствует значение \code 41\endcode.
         * 9. Ноте \code До\endcode (Бекар) соответствует значение \code 42\endcode.
         * 10. Ноте \code Си-диез\endcode соответствует значение \code 62\endcode.
         * 11. Ноте \code До⁵\endcode (Бекар) соответствует значение \code 167\endcode.
         * 12. Ноте \code Си-диез⁵\endcode соответствует значение \code 188\endcode.
         */
        uint_fast8_t data;
    };
}

#endif // HARMONY_CORE_NOTE_HPP
