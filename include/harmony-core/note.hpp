#ifndef HARMONY_CORE_NOTE_HPP
#define HARMONY_CORE_NOTE_HPP

#include <cstdint>
#include <harmony-core/enums.hpp>
#include <string>

namespace harmony_core {
    /*! \brief Представляет собой ноту.
     *
     * Данный класс позволяет как получить информацию о ноте, так и изменить её:
     * - Основание ноты.
     * - Октава ноты.
     * - Ключевой знак альтерации ноты.
     * - Случайный знак альтерации ноты.
     * - Длительность ноты.
     *
     * Также данный класс позволяет получить
     * используемый знак альтерации ноты и её полное название.
     */
    class Note final {
    public:
        // constructors & destructor

        /*!
         * \brief Создаёт ноту \code Ля₂ \endcode с длительностью целой ноты.
         */
        Note() noexcept;

        /*!
         * \brief Создаёт ноту на основе \code base \endcode, \code octave \endcode, \code key_accidental \endcode,
         * \code random_accidental \endcode и \code duration \endcode.
         * \param [in] base основание ноты.
         * \param [in] octave октава ноты.
         * \param [in] key_accidental ключевой знак альтерации ноты.
         * \param [in] random_accidental случайный знак альтерации ноты.
         * \param [in] duration длительность ноты.
         */
        explicit Note(Base base, Octave octave, Accidental key_accidental, Accidental random_accidental,
                      Duration duration) noexcept;

        /*!
         * \brief Создаёт ноту на основе \code data \endcode.
         * \param [in] data информация об основании, октаве, а также о ключевом и случайном знаке альтерации ноты.
         */
        explicit Note(uint_fast16_t data) noexcept;

        /*!
         * \brief Создаёт ноту на основе \code note \endcode.
         * \param [in] note другая нота.
         */
        Note(const Note &note) noexcept;

        /*!
         * \brief Удаляет ноту.
         */
        ~Note() noexcept = default;

        // data getter & setter

        /*!
         * \brief Задаёт информацию об основании, октаве, ключевом и случайном знаке альтерации, а также о длительности
         * этой ноты равной \code data \endcode.
         * \param [in] data новая информация об основании, октаве, ключевом и случайном знаке альтерации, а также о
         * длительности этой ноты.
         */
        void set_data(uint_fast16_t data) noexcept;

        /*!
         * \brief Возвращает информацию об основании, октаве, ключевом и случайном знаке альтерации, а также о
         * длительности этой ноты.
         * \return Информация об основании, октаве, ключевом и случайном знаке альтерации, а также о длительности этой
         * ноты.
         */
        [[nodiscard]] uint_fast16_t get_data() const noexcept;

        // base getter & setter

        /*!
         * \brief Задаёт основание этой ноты равным \code base \endcode.
         * \param [in] base новое основание этой ноты.
         */
        void set_base(Base base) noexcept;

        /*!
         * \brief Возвращает основание этой ноты.
         * \return Основание этой ноты.
         */
        [[nodiscard]] Base get_base() const noexcept;

        // octave getter & setter

        /*!
         * \brief Задаёт октаву этой ноты равной \code octave \endcode.
         * \param [in] octave новая октава этой ноты.
         */
        void set_octave(Octave octave) noexcept;

        /*!
         * \brief Возвращает октаву этой ноты.
         * \return Октаву этой ноты.
         */
        [[nodiscard]] Octave get_octave() const noexcept;

        // key accidental getter & setter

        /*!
         * \brief Задаёт ключевой знак альтерации этой ноты равным \code accidental \endcode.
         * \param [in] accidental новый ключевой знак альтерации этой ноты.
         */
        void set_key_accidental(Accidental accidental) noexcept;

        /*!
         * \brief Возвращает ключевой знак альтерации этой ноты.
         * \return Ключевой знак альтерации этой ноты.
         */
        [[nodiscard]] Accidental get_key_accidental() const noexcept;

        // random accidental getter & setter

        /*!
         * \brief Задаёт случайный знак альтерации этой ноты равным \code accidental \endcode.
         * \param [in] accidental новый случайный знак альтерации этой ноты.
         */
        void set_random_accidental(Accidental accidental) noexcept;

        /*!
         * \brief Возвращает случайный знак альтерации этой ноты.
         * \return Случайный знак альтерации этой ноты.
         */
        [[nodiscard]] Accidental get_random_accidental() const noexcept;

        /*!
         * \brief Возвращает общий знак альтерации этой ноты.
         * \return Знак тональности, если случайный знак не определен и случайный знак, если определен.
         * Возвращает реально используемый знак альтерации этой ноты.
         */
        [[nodiscard]] Accidental get_accidental() const noexcept;

        // duration getter & setter

        /*!
         * \brief Задаёт длительность этой ноты равной \code duration \endcode.
         * \param [in] duration новая длительность этой ноты.
         */
        void set_duration(Duration duration) noexcept;

        /*!
         * \brief Возвращает длительность этой ноты.
         * \return Длительность этой ноты.
         */
        [[nodiscard]] Duration get_duration() const noexcept;

        // height getter & setter

        /*!
         * \brief Задаёт высоту этой ноты в полутонах от ноты \code Ля1 \endcode равной \code height \endcode.
         * \param [in] height новая высота этой ноты в полутонах от ноты \code Ля1 \endcode.
         * \throw invalid_exception \code height \endcode должна быть меньше \code 126 \endcode.
         */
        void set_height(uint_fast8_t height);

        /*!
         * \brief Возвращает высоту этой ноты в полутонах от ноты \code Ля₂ \endcode.
         * \return Высота этой ноты в полутонах от ноты \code Ля1 \endcode.
         */
        [[nodiscard]] uint_fast8_t get_height() const noexcept;

        // name getter

        /*!
         * \brief Возвращает полное название этой ноты по общепринятому стандарту.
         * \return Полное название этой ноты.
         */
        std::string get_name() const noexcept;

        //---------------

        /*!
         * \brief Делает энгармоническую замену в указанном направлении.
         * \param [in] dir Направление замены.
         * 0 - энгармонизм вниз, 1 - энгармонизм наверх
         */
        void enharmony_сhange(bool dir) noexcept;

        // equality operators

        /*!
         * \brief Проверяет на равенство левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая и правая ноты равны, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator==(const Note &lhs, const Note &rhs) {
            return lhs.data == rhs.data;
        }

        /*!
         * \brief Проверяет на неравенство левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая и правая ноты неравны, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator!=(const Note &lhs, const Note &rhs) {
            return lhs.data != rhs.data;
        }

        // relational operators

        /*!
         * \brief Сравнивает левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая нота ниже правой, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator<(const Note &lhs, const Note &rhs) {
            return lhs.get_height() < rhs.get_height();
        }

        /*!
         * \brief Сравнивает левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая нота ниже или равна правой, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator<=(const Note &lhs, const Note &rhs) {
            return lhs.get_height() <= rhs.get_height();
        }

        /*!
         * \brief Сравнивает левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая нота выше правой, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator>(const Note &lhs, const Note &rhs) {
            return lhs.get_height() > rhs.get_height();
        }

        /*!
         * \brief Сравнивает левую и правую ноты.
         * \param lhs левая нота.
         * \param rhs правая нота.
         * \return Если левая нота выше или равна правой, то \code true \endcode, иначе \code false \endcode.
         */
        friend bool operator>=(const Note &lhs, const Note &rhs) {
            return lhs.get_height() >= rhs.get_height();
        }

        // copy operator

        /*!
         * \brief Задаёт эту ноту равной \code note \endcode.
         * \param note другая нота.
         * \return Эту ноту.
         */
        Note &operator=(const Note &note) {
            if (this == &note)
                return *this;
            data = note.data;
            return *this;
        }

        //---- increment and decrement -----

        /*!
         * \brief Повышает ноту на полтона.
         */
        Note &operator++();

        /*!
         * \brief Повышает ноту на полтона.
         */
        Note operator++(int);

        /*!
         * \brief Понижает ноту на полтона.
         */
        Note &operator--();

        /*!
         * \brief Понижает ноту на полтона.
         */
        Note operator--(int);

    private:
        /*!
         * \brief Представляет собой информацию об основании, октаве, ключевом и случайном знаке альтерации, а также о
         * длительности этой ноты.
         *
         * Далее указано, какой информации об этой ноте соответствуют биты значения этого поля:
         * - Биты \code 0-2 \endcode задают основание этой ноты.
         * - Биты \code 3-6 \endcode задают октаву этой ноты.
         * - Биты \code 7-9 \endcode задают ключевой знак альтерации этой ноты.
         * - Биты \code 10-12 \endcode задают случайный знак альтерации этой ноты.
         * - Биты \code 13-15 \endcode задают длительность этой ноты.
         */
        uint_fast16_t data;
    };
} // namespace harmony_core

#endif // HARMONY_CORE_NOTE_HPP
