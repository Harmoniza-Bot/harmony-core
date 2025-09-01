#ifndef HARMONY_CORE_TIME_SIGNATURE
#define HARMONY_CORE_TIME_SIGNATURE

#include <cstdint>

namespace harmony_core {
    /*!
     * \brief Данный класс представляет музыкальный размер.
     * Это натуральная дробь, обозначающая, сколько целых нот может быть в такте.
     * Значение числителя и знаменателя находится в диапазоне 1 - 16.
     */
    class Time_signature final {
    public:
        // vrite getters & setters
    private:
        /*!
         * Представляет информацию о размере
         * Биты \code 0-3 \endcode хранят числитель дроби
         * Биты \code 4-7 \endcode хранят знаменатель дроби
         */
        uint8_t data;
    };
} // namespace harmony_core

#endif // HARMONY_CORE_TIME_SIGNATURE
