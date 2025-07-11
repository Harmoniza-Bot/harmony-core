#ifndef HARMONY_CORE_INTERVAL_HPP
#define HARMONY_CORE_INTERVAL_HPP
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
         * \brief Создаёт интервал, равный 
         */
        Interval(int8_t) noexcept;

        private: 
        /**
         * \brief Представляет информацию об интервале.
         * - Биты \code 0-3 \endcode задают расстояние интервала
         * - Биты \code 4-6 \endcode задают вид интервала
         * - Бит \code 7 \endcode задаёт направление интервала 
         */
        uint8_t data;
    }
}
#endif //HARMONY_CORE_INTERVAL_HPP