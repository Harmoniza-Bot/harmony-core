#ifndef HARMONY_CORE_KEY_HPP
#define HARMONY_CORE_KEY_HPP

#include <cstdint>
#include <vector>
#include <harmony-core/note.hpp>
#include <harmony-core/enums.hpp>

namespace harmony_core
{
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
         * \brief Задает информацию об основании, знаке, ладе и виде тон-ти на основе \code data \endcode.
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

        // resolurions

        /*!
         * \brief Разрешает структуры в текущей тоальности.
         */

        // или поместить разрешения внуть самих структур (?)

        // accidental getter

        /*!
         * \brief Вычисляет знаки тональности.
         * \return Вектор знаков тон-ти или пустой вектор если знаков нет.
         */
        std::vector<Note> get_accidentals() noexcept;


        /*!
         * \brief Делает шаг по кварто-квинтовому кругу в сторону диезных тональностей.
         */
        void sharp_step() noexcept;

        /*!
         * \brief Делает шаг по кварто-квинтовому кругу в сторону бемольных тон-тей.
         */
        void flat_step() noexcept;

        /*!
         * \brief Задает количество шагов в кварто-квинтовом круге
         */
        void set_step(int8_t) noexcept;

        /*!
         * \brief Возвращает количество шагов по кварто-квинтовому кругу
         */
        int8_t get_step() const noexcept;

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
            return lhs.get_step() < rhs.get_step();
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
            return lhs.get_step() <= rhs.get_step();
        }

        /*!
         * \brief Сравнивает левую и правую тональности.
         * \param lhs левая тон-ть.
         * \param rhs правая тон-ть.
         * \return Если индекс квинтового круга левой тон-ти больше, то \code true\endcode, иначе \code false\endcode.
         */
        friend bool operator>(const Key &lhs, const Key &rhs)
        {
            return lhs.get_step() > rhs.get_step();
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
            return lhs.get_step() >= rhs.get_step();
        }

        // copy operator

        /*!
         * \brief Задаёт эту тональность равной \code key \endcode.
         * \param key другая тон-ть.
         * \return Эту тональность.
         */
        Key &operator=(const Key &key)
        {
            if (this == &key)
                return *this;
            data = key.data;
            return *this;
        }

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
