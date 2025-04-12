#ifndef HARMONY_CORE_KEY_HPP
#define HARMONY_CORE_KEY_HPP

#include <cstdint>

namespace harmony_core
{
    /*!
     * \brief Представляет собой соглашение об именовании лада тональности.
     * Каждый лад представляет собой соотношение тонов и полутонов в натуральной гамме тональности.
     * Здесь указаны шесть расстояний между нотами, чего достаточно для определения лада.
     * Ведь расстояние между седьмой и первой нотой след. октавы всегда вычисляется по формуле:
     * \code расстояние между 1 ст. соседних октав - расстояние от 1 до 7 ст.\endcode
     */
    enum class Mode
    {
        /*!
         * \brief Представляет ионийский (мажорный) лад.
         * Соотношение тонов и полутонов: whole-whole-half-whole-whole-whole
         */
        IONIAN,

        /*!
         * \brief Представляет дорийский лад.
         * Соотношения тонов и полутонов: whole-half-whole-whole-whole-half
         */
        DORIAN,

        /*!
         * \brief Представляет фригийский лад.
         * Соотношения тонов и полутонов: half-whole-whole-whole-half-whole
         */
        PHRYGIAN,

        /*!
         * \brief Представляет лидийский лад.
         * Соотношения тонов и полутонов: whole-whole-whole-half-whole-whole
         */
        LYDIAN,

        /*!
         * \brief Представляет миксолидийский лад.
         * Соотношения тонов и полутонов: whole-whole-half-whole-whole-half
         */
        MIXOLYDIAN,

        /*!
         * \brief Представляет эолийский (минорный) лад.
         * Соотношения тонов и полутонов: whole-half-whole-whole-half-whole
         */
        AEOLIAN,

        /*!
         * \brief Представляет локрийский лад.
         * Соотношения тонов и полутонов: half-whole-whole-half-whole-whole
         */
        LOCRIAN
    }

    /*!
     * \brief Представляет собой соглашение об именовании вида тональности.
     * Вид, отличный от натурального модифицирует натуральное соотношение тонов и полутонов в тон-ти.
     * В пояснении \code n \endcode обозначает отсутствие изменений.
     */
    enum class Specie
    {
        /*!
         * \brief Представляет натуральный вид.
         * Соотношения тонов и полутонов не изменяется.
         */
        NATURAL,

        /*!
         * \brief Представляет гармонический вид.
         * Соотношения тонов и полутонов: n-n-n-n-n-one&half
         */
        HARMONIC,

        /*!
         * \brief Представляет мелодический вид.
         * Соотношения тонов и полутонов: n-n-n-n-one-one
         */
        MELODIC,

        /*!
         * \brief Представляет дважды гармонический вид.
         * Соотношения тонов и полутонов: n-n-one&half-n-n-one&half
         */
        DOUBLE_HARMONIC,
    }

    class Key final
    {
    public:

        Key() noexcept;

        ~Key() noexcept = default;

        /*!
         * \brief Задает информацию об основании, знаке, ладе и виде тон-ти.
         */
        void set_data(uint_fast16_t data) noexcept;

        /*!
         * \brief Возвращает информацию об основании, знаке, ладе и виде тон-ти.
         * \return Информация об основании, знаке, ладе и виде этой тон-ти.
         */
        [[nodiscard]] uint_fast16_t get_data() const noexcept;

        /*!
         * \brief Задает основание тон-ти.
         */
        void set_base(Base base) noexcept;

        /*!
         * \brief Возвращает основание тон-ти.
         */
        [[nodiscard]] Base get_dase() noexcept;

        /*!
         * \brief Задает знак тон-ти.
         */
        void set_accidental(Accidental accidental) noexcept;

        /*!
         * \brief Возвращает знак тон-ти.
         */
        [[nodiscard]] Accidental get_accidental() noexcept;

        /*!
         * \brief Задает лад тон-ти.
         */
        void set_mode(Mode mode) noexcept;

        /*!
         * \brief Возвращает лад тон-ти.
         */
        [[nodiscard]] Accidental get_mode() noexcept;

        /*!
         * \brief Задает вид тон-ти.
         */
        void set_mode(Specie specie) noexcept;

        /*!
         * \brief Возвращает вид тон-ти.
         */
        [[nodiscard]] Specie get_mode() noexcept;

    private:
        /**
         * \brief Представляет информацию об основании, знаке и ладе тональности.
         *
         * Далее указано, какой информации об этой ноте соответствуют биты значения этого поля:
         * - Биты \code 0-2\endcode задают основание тон-ти.
         * - Биты \code 3-6\endcode задают знак тон-ти.
         * - Биты \code 7-9\endcode задают лад тон-ти (Mode).
         * - Биты \code 10-11\endcode задают вид тон-ти (Specie).
         */
        uint_fast16_t data;
    }
}

#endif // HARMONY_CORE_KEY_HPP
