#ifndef HARMONY_CORE_KEY_HPP
#define HARMONY_CORE_KEY_HPP

#include <harmony-core/note.hpp>
#include <harmony-core/accidental.hpp>
#include <harmony-core/octave.hpp>
#include <cstdint>
#include <vector>

namespace harmony_core
{
    /*!
     * \brief Представляет собой соглашение об именовании лада тональности.
     * Каждый лад является своеобразным ключом, точкой отсчета нот для тональности.
     * Каждый лад имеет свое соотношение тонов и полутонов, не меняющееся по мере продвижения тональности по квинтовому кругу.
     */
    enum class Mode
    {
        /*!
         * \brief Представляет эолийский (минорный) лад.
         * Лад ноты ля.
         * Соотношения тонов и полутонов: whole-half-whole-whole-half-whole
         */
        AEOLIAN = 0b110,
        
        /*!
         * \brief Представляет локрийский лад.
         * Лад ноты си.
         * Соотношения тонов и полутонов: half-whole-whole-half-whole-whole
         */
        LOCRIAN = 0b111,
        
        /*!
         * \brief Представляет ионийский (мажорный) лад.
         * Лад ноты ля.
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
        MIXOLYDIAN = 0b101
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

        // main getter & setter

        /*!
         * \brief Задает тонику тон-ти.
         * \param [in] note новая тоника тональности
         */
        void set_main(Note note) noexcept;

        /*!
         * \brief Возвращает тонику тон-ти.
         * \return текущую тонику тональности.
         */
        [[nodiscard]] Note get_main() noexcept;

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

        //---- equality operator --------

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

        //----- Знаковые и нотные функции ------

        // tone getters

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


        /*!
         * \brief Делает шаг по кварто-квинтовому кругу в сторону диезных тональностей.
         */
        void sharp_step() noexcept;

        /*!
         * \brief Делает шаг по кварто-квинтовому кругу в сторону бемольных тон-тей.
         */
        void flat_step() noexcept;


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
    };
} // namespace harmony_core

#endif // HARMONY_CORE_KEY_HPP
