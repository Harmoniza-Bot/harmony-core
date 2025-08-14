#ifndef HARMONY_CORE_INTERVAL_HPP
#define HARMONY_CORE_INTERVAL_HPP

#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
#include <string>

namespace harmony_core {
    /*
    \brief Данный класс представляет интервал.
    * Доступны функции изменения звуков интервала, получения названия, расстояния между звуками, извлечения и поиска
    интервала из звукоряда тональности и тд.
    */
    class Interval final {
    public:
        /*!
         * \brief Создаёт интервал, равный чистой приме
         */
        Interval() noexcept;

        /*!
         * \brief Создаёт интервал на основе расстояния, вида и направления
         * \param [in] uint8_t расстояние между нотами.
         * \param [in] Quality вид интервала.
         * \param [in] bool направление интервала.
         */
        explicit Interval(uint8_t, Quality, bool) noexcept;

        /*!
         * \brief Создаёт интервал на основе данных другого интервала
         * \param [in] uint8_t данные другого интервала.
         */
        explicit Interval(uint_fast8_t) noexcept;

        /*!
         * \brief Создаёт интервал на основе двух нот.
         * \param [in] Note первая нота.
         * \param [in] Note вторая нота.
         */
        explicit Interval(const Note n1 &, const Note &n2) noexcept;

        ~Interval() noexcept = default;

        //----- data getters & setters ------

        /*!
         * \brief Задает информацию об объекте на основе \code data \endcode.
         \param [in] uint_fast8_t информация об интервале согласно соглашению о коодировке.
         */
        void set_data(uint_fast8_t data) noexcept;

        /*!
         * \brief Возвращает информацию о расстоянии, виде и направлении интервала.
         * \return uint_fast8_t Информация об объекте.
         */
        [[nodiscard]] uint_fast8_t get_data() const noexcept;

        /*!
         * \brief Задает расстояние интервала (по натуральному звукоряду).
         \param [in] uint8_t расстояние между нот интервала.
         */
        void set_distance(uint8_t) noexcept;

        /*!
         * \brief Возвращает расстояние интервала.
         * \return Расстояние интервала.
         */
        [[nodiscard]] uint8_t get_distance() const noexcept;

        /*!
         * \brief Задает вид интервала.
         param [in] Quality вид интервала
         */
        void set_quality(Quality) noexcept;

        /*!
         * \brief Возвращает вид интервала.
         * \return Quality Вид интервала.
         */
        [[nodiscard]] Quality get_quality() const noexcept;

        /*!
         * \brief Задает направление интервала.
         \param [in] bool направление интервала (1 - вверх, 0 - вниз)
         */
        void set_direction(bool) noexcept;

        /*!
         * \brief Возвращает направление интервала.
         * \return bool Направление интервала.
         */
        [[nodiscard]] bool get_direction() const noexcept;

        /*!
         * \brief Возвращает имя интервала на английском.
         * \return std::string Полное имя интервала.
         */
        [[nodiscard]] std::string get_name() const noexcept;

        friend bool operator==(const Interval &lhs, const Interval &rhs) {
            return lhs.data == rhs.data;
        }

    private:
        /**
         * \brief Представляет информацию об интервале.
         * - Биты \code 0-3 \endcode задают расстояние интервала
         * - Биты \code 4-6 \endcode задают вид интервала
         * - Бит \code 7 \endcode задаёт направление интервала
         */
        uint_fast8_t data;
    };
} // namespace harmony_core
#endif // HARMONY_CORE_INTERVAL_HPP
