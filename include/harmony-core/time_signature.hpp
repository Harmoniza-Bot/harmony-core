#ifndef HARMONY_CORE_TIME_SIGNATURE
#define HARMONY_CORE_TIME_SIGNATURE

#include <cstdint>
#include <vector>
#include "harmony-core/note.hpp"

namespace harmony_core {
    /*!
     * \brief Данный класс представляет музыкальный размер.
     * Это натуральная дробь, обозначающая, сколько целых нот может быть в такте.
     * Значение числителя и знаменателя находится в диапазоне 1 - 16.
     */
    class Time_signature final {
    public:
        /*!
         * \brief Создает размер 4/4.
         */
        Time_signature();

        /*!
         * \brief Создает размер по числителю и знаменателю.
         */
        Time_signature(uint8_t, uint8_t);

        /*!
         * \brief Создает размер на основе другого размера.
         */
        Time_signature(const Time_signature &);

        // getters & setters

        /*!
         * \brief Задает числитель и знаменатель.
         */
        void set_signature(uint8_t, uint8_t) noexcept;

        /*!
         * \brief Возвращает числитель размера.
         */
        uint8_t get_numerator() const noexcept;

        /*!
         * \brief Возвращает знаменатель размера.
         */
        uint8_t get_denominator() const noexcept;

        /*!
         * \brief Возвращает остаточный размер такта после добавления списка нот или -1, если ноты не помещаются.
         * \param [in] список нот для добавления
         * \return Пару числитель - знаменатель остатка размера.
         */
        std::pair<uint8_t, uint8_t> get_remainder(std::vector<harmony_core::Note>);

    private:
        /*!
         * Представляет информацию о размере
         * numerator - числитель размера
         * denominator - знаменатель размера
         */
        uint8_t numerator = 0;
        uint8_t denominator = 0;
    };
} // namespace harmony_core

#endif // HARMONY_CORE_TIME_SIGNATURE
