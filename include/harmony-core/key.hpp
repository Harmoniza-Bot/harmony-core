#ifndef HARMONY_CORE_KEY_HPP
#define HARMONY_CORE_KEY_HPP

#include <cstdint>
#include <harmony_core/note.hpp>
#include <vector>

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
        IONIAN = 0b001,

        /*!
         * \brief Представляет дорийский лад.
         * Соотношения тонов и полутонов: whole-half-whole-whole-whole-half
         */
        DORIAN = 0b010,

        /*!
         * \brief Представляет фригийский лад.
         * Соотношения тонов и полутонов: half-whole-whole-whole-half-whole
         */
        PHRYGIAN = 0b011,

        /*!
         * \brief Представляет лидийский лад.
         * Соотношения тонов и полутонов: whole-whole-whole-half-whole-whole
         */
        LYDIAN = 0b100,

        /*!
         * \brief Представляет миксолидийский лад.
         * Соотношения тонов и полутонов: whole-whole-half-whole-whole-half
         */
        MIXOLYDIAN = 0b101,

        /*!
         * \brief Представляет эолийский (минорный) лад.
         * Соотношения тонов и полутонов: whole-half-whole-whole-half-whole
         */
        AEOLIAN = 0b110,

        /*!
         * \brief Представляет локрийский лад.
         * Соотношения тонов и полутонов: half-whole-whole-half-whole-whole
         */
        LOCRIAN = 0b111
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
        NATURAL = 0b001,

        /*!
         * \brief Представляет гармонический вид.
         * Соотношения тонов и полутонов: n-n-n-n-n-one&half
         */
        HARMONIC = 0b010,

        /*!
         * \brief Представляет мелодический вид.
         * Соотношения тонов и полутонов: n-n-n-n-one-one
         */
        MELODIC = 0b011,

        /*!
         * \brief Представляет дважды гармонический вид.
         * Соотношения тонов и полутонов: n-n-one&half-n-n-one&half
         */
        DOUBLE_HARMONIC = 0b100,
    }

    class Key final
    {
    public:
        /*!
         * \brief Создаёт тональность \code C IONIAN NAIURAL \endcode.
         */
        Key() noexcept;

        /*!
         * \brief Создает \code IONIAN NATURAL \endcode тональность на основе \code Note \endcode.
         * \param [in] note тоника тон-ти.
         */
        explicit Key(Note note) noexcept;

        /*!
         * \brief Создает тональность \code NATURAL \endcode на основе \code Note \endcode и \code Mode \endcode.
         * \param [in] note тоника тон-ти.
         * \param [in] mode лад тон-ти.
         */
        explicit Key(Note note, Mode mode) noexcept;

        /*!
         * \brief Создает тональность на основе \code Note \endcode, \code Mode \endcode и \code Specie \endcode.
         * \param [in] note тоника тон-ти.
         * \param [in] mode лад тон-ти.
         * \param [in] specie вид тон-ти.
         */
        explicit Key(Note note, Mode mode, Specie specie) noexcept;

        /*!
         * \brief Создает тональность на основе \code Base \endcode, \code Accidental \endcode, \code Mode \endcode и
         * \code Specie \endcode. \param [in] base основание тон-ти. \param [in] accidental знак тон-ти. \param [in]
         * mode лад тон-ти. \param [in] specie вид тон-ти.
         */
        explicit Key(Base base, Accidental accidental, Mode mode, Specie specie) noexcept;

        /*!
         * \brief Создаёт тональность на основе \code data \endcode.
         * \param [in] data информация об основании, знаке, ладе и виде тон-ти.
         */
        explicit Key(uint_fast16_t data) noexcept;

        /*!
         * \brief Создаёт тональность на основе \code key \endcode.
         * \param [in] key другая тон-тъ.
         */
        Key(const Key &key) noexcept;

        /*!
         * \brief Удаляет тональность.
         */
        ~Key() noexcept = default;

        // data setter & getter

        /*!
         * \brief Задает информацию об основании, знаке, ладе и виде тон-ти.
         */
        void set_data(uint_fast16_t data) noexcept;

        /*!
         * \brief Возвращает информацию об основании, знаке, ладе и виде тон-ти.
         * \return Информация об основании, знаке, ладе и виде этой тон-ти.
         */
        [[nodiscard]] uint_fast16_t get_data() const noexcept;

        // base getter & setter

        /*!
         * \brief Задает основание тон-ти.
         * \param [in] base новое основане тональности
         */
        void set_base(Base base) noexcept;

        /*!
         * \brief Возвращает основание тон-ти.
         * * \return Основание тональности.
         */
        [[nodiscard]] Base get_dase() noexcept;

        // accidental getter & setter

        /*!
         * \brief Задает знак тон-ти.
         * \param [in] accidental знак тон-ти.
         */
        void set_accidental(Accidental accidental) noexcept;

        /*!
         * \brief Возвращает знак тон-ти.
         * \return знак тональности.
         */
        [[nodiscard]] Accidental get_accidental() noexcept;

        // mode getter & setter

        /*!
         * \brief Задает лад тон-ти.
         * \param [in] mode новый лад тон-ти.
         */
        void set_mode(Mode mode) noexcept;

        /*!
         * \brief Возвращает лад тон-ти.
         * \return текущий лад тональности.
         */
        [[nodiscard]] Mode get_mode() noexcept;

        // specie getter & setter

        /*!
         * \brief Задает вид тон-ти.
         * \param [in] specie новый вид тональности.
         */
        void set_specie(Specie specie) noexcept;

        /*!
         * \brief Возвращает вид тон-ти.
         * \return текущий лад тональности.
         */
        [[nodiscard]] Specie get_specie() noexcept;

        // equality operator

        /*!
         * \brief Проверяет на равенство левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-то.
         * \return Если левая и правая тон-ти равны, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator==(const Key &lhs, const Key &rhs)
        {
            return lhs.data == rhs.data;
        }

        /*!
         * \brief Проверяет на неравенство левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-то.
         * \return Если левая и правая тон-ти равны, то \code false \endcode, иначе \code true \endcode.
         */
        friend bool operator!=(const Key &lhs, const Key &rhs)
        {
            return lhs.data != rhs.data;
        }

        // relational operator

        /*!
         * \brief Сравнивает левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-ть.
         * \return Если индекс квинтового круга правой тон-ти больше, то \code true\endcode, иначе \code false \endcode.
         */
        friend bool operator<(const Key &lhs, const Key &rhs)
        {
        }

        /*!
         * \brief Сравнивает левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-ть.
         * \return Если индекс квинтового круга правой тон-ти больше или равен, то \code true\endcode, иначе \code false
         * \endcode.
         */
        friend bool operator<=(const Key &lhs, const Key &rhs)
        {
        }

        /*!
         * \brief Сравнивает левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-ть.
         * \return Если индекс квинтового круга левой тон-ти больше, то \code true\endcode, иначе \code false\endcode.
         */
        friend bool operator>(const Key &lhs, const Key &rhs)
        {
        }

        /*!
         * \brief Сравнивает левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-ть.
         * \return Если индекс квинтового круга левой тон-ти больше или равен, то \code true\endcode, иначе \code
         * false\endcode.
         */
        friend bool operator>=(const Key &lhs, const Key &rhs)
        {
        }

        // copy operator

        /*!
         * \brief Задаёт эту тональность равной \code key \endcode.
         * \param key другая тон-ть.
         * \return Эту тональность.
         */
        Key &operator=(const key &key)
        {
            if (this == &key)
                return *this;
            data = key.data;
            return *this;
        }

        /*!
         * \brief Увеличивают и уменьшают тон-ть изменением индекса кватро-квинтового круга.
         * Дальнейшие вычисления производятся по индексу и спецификаторам тон-ти.
         *
         * При увеличении основание тон-ти смещается в сторону диезных тон-тей от беззнаковой тональности \code индекс
         * \endcode раз. При этом следующая тон-ть выше на квинту (или на 7 полутонов).
         *
         * При уменьшении основание тон-ти смещается в сторону бемольных тон-тей от беззнаковой тональности \code индекс
         * \endcode раз. При этом следующая тон-ть ниже на кварту (или на 5 полутонов).
         *
         * К-во знаков равно модулю индекса. При этом знак индекса показывает вид знаков тон-ти (минус = бемоли, плюс =
         * диезы). После седьмого знака последующие знаки становятся своей дублированной версией.
         */
        Key &operator++()
        {
            uint8_t current_value = data & 0b0001'1111;
            if (current_value >= 14)
            {
                return *this;
            }
            current_value++;
            data = ((data & ~0b0001'1111) | current_value);
            return *this;
        }

        //        Key operator++(int);
        //        {
        //            Key temp = *this;
        //            ++*this;
        //            return temp;
        //        }

        Key &operator--()
        {
            uint8_t current_value = data & 0b0001'1111;
            if (current_value == 0)
            {
                return *this;
            }
            current_value--;
            data = ((data & ~0b0001'1111) | current_value);
            return *this;
        }


        //        Key operator--(int);
        //        {
        //            Key temp = *this;
        //            --*this;
        //            return temp;
        //        }

        //----- specific functions ------

        // tone getters

        /*!
         * \brief Возвращает главную ступень тон-ти.
         * \return главная ступень тональности.
         */
        [[nodiscard]] Note get_main_tone() noexcept;

        /*!
         * \brief Возвращает ступень тон-ти по индексу.
         * \return Нота, расположенная на указанном индексе
         */
        [[nodiscard]] Note get_tone(uint8_t index) noexcept;

        /*!
         * \brief Ищет указанную ноту в текущей тон-ти.
         * \param [in] note нота для поиска
         * \return Индекс ноты в звукоряде тон-ти или -1 если нота не найдена.
         */
        [[nodiscard]] int8_t get_tone_index(Note note) noexcept;

        // resolution

        /*!
         * \brief Разрешает ноту в текущей тональности в ближайшую устойчивую ступень.
         * \param [in] note разрешаемая нота.
         * \return Нота, в которую возможно разрешение указанной ноты.
         */
        Note resolution(Note note) noexcept;

        // accidental getter

        /*!
         * \brief Вычисляет знаки тональности.
         * \return Вектор знаков тон-ти или пустой вектор если знаков нет.
         */
        vector<accidental> get_accidentals() noexcept;


    private:
        /**
         * \brief Представляет информацию об основании, знаке и ладе тональности.
         *
         * Далее указано, какой информации об этой тон-ти соответствуют биты значения этого поля:
         * - Биты \code 0-4 \endcode задают расположение в кварто-квинтовом круге (один бит под знак).
         * - Биты \code 5-7 \endcode задает лад тональности (Mode).
         * - Биты \code 8-10 \endcode задают вид тональности (Specie).
         */
        uint_fast16_t data;
    }
} // namespace harmony_core

#endif // HARMONY_CORE_KEY_HPP
