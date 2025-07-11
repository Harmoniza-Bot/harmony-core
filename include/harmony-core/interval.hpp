#ifndef HARMONY_CORE_INTERVAL_HPP
#define HARMONY_CORE_INTERVAL_HPP
#include <string>
#include <harmony-core/enums.hpp>
#include <harmony-core/note.hpp>
namespace harmony_core
{
    class Interval final
    {
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
         * \brief Создаёт интервал на основе другого интервала
         * \param [in] Interval другой интервал.
         */
        explicit Interval(Interval) noexcept;

        /*!
         * \brief Создаёт интервал на основе данных другого интервала
         * \param [in] uint8_t данные другого интервала.
         */
        explicit Interval(uint_fast8_t) noexcept;
        
        /*!
         * \brief Создаёт интервал на основе двух нот и направления.
         * \param [in] Note первая нота.
         * \param [in] Note вторая нота.
         * \param [in] bool расчтояние. 
         */
        explicit Interval(Note, Note, bool) noexcept;

        ~Interval() noexcept = default;

        //----- data getters & setters ------

        /*!
         * \brief Задает информацию об объекте на основе \code data \endcode.
         */
        void set_data(uint_fast8_t data) noexcept;

        /*!
         * \brief Возвращает информацию об расстоянии, виде и направлении интервала.
         * \return Информация об объекте.
         */
        [[nodiscard]] uint_fast8_t get_data() const noexcept;

        /*!
         * \brief Задает расстояние интервала.
         */
        void set_distance(uint8_t) noexcept;

        /*!
         * \brief Возвращает расстояние интервала.
         * \return Расстояние интервала.
         */
        [[nodiscard]] uint8_t get_distance() const noexcept;

        /*!
         * \brief Задает вид интервала.
         */
        void set_quality(Quality) noexcept;

        /*!
         * \brief Возвращает вид интервала.
         * \return Вид интервала.
         */
        [[nodiscard]] Quality get_quality() const noexcept;

        /*!
         * \brief Задает направление интервала.
         */
        void set_direction(bool) noexcept;

        /*!
         * \brief Возвращает направление интервала.
         * \return Направление интервала.
         */
        [[nodiscard]] bool get_direction() const noexcept;

        /*!
         * \brief Возвращает имя интервала на английском.
         * \return Полное имя интервала.
         */
        [[nodiscard]] string get_name() const noexcept;

        private: 
        /**
         * \brief Представляет информацию об интервале.
         * - Биты \code 0-3 \endcode задают расстояние интервала
         * - Биты \code 4-6 \endcode задают вид интервала
         * - Бит \code 7 \endcode задаёт направление интервала 
         */
        uint_fast8_t data;
    }
}
#endif //HARMONY_CORE_INTERVAL_HPP
