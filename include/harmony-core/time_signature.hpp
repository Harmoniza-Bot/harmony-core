#ifndef HARMONY_CORE_TIME_SIGNATURE
#define HARMONY_CORE_TIME_SIGNATURE

#include <cstdint>
#include <iostream>
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
         * \param [in] uint8_t числитель
         * \param [in] uint8_t знаменатель
         */
        Time_signature(uint8_t, uint8_t);

        /*!
         * \brief Создает размер на основе другого размера.
         * \param [in] Time_signature другой размер
         */
        Time_signature(const Time_signature &);

        // getters & setters

        /*!
         * \brief Задает числитель и знаменатель.
         * \param [in] uint8_t числитель
         * \param [in] uint8_t знаменатель
         */
        void set_signature(uint8_t, uint8_t) noexcept;

        /*!
         * \brief Возвращает числитель размера.
         * \return Числитель.
         */
        uint8_t get_numerator() const noexcept;

        /*!
         * \brief Возвращает знаменатель размера.
         * \return Знаменатель.
         */
        uint8_t get_denominator() const noexcept;

        /*!
         * \brief Возвращает остаточный размер такта после добавления ноты или 0 если нота больше или равна размеру
         * такта.
         * \param note нота для добавления.
         * \param num - числитель размера такта.
         * \param den - знаменатель размера такта.
         * \return Пару числитель - знаменатель остатка размера.
         */
        std::pair<int, int> get_remainder(harmony_core::Note note, int num, int den) const noexcept;

        /*!
         * \brief Возвращает остаточный размер такта после добавления ноты.
         * Используется размер объекта.
         */
        std::pair<int, int> get_remainder(harmony_core::Note note) const noexcept;

        /*!
         * \brief Возвращает остаточный размер такта после добавления нескольких нот.
         * Используется размер объекта.
         */
        std::pair<int, int> get_remainder(std::vector<harmony_core::Note> note) const noexcept;

    private:
        /*!
         * Представляет информацию о числителе размера.
         */
        uint8_t numerator = 0;

        /*!
         * Представляет информацию о знаменателе размера.
         */
        uint8_t denominator = 0;
    };
} // namespace harmony_core

#endif // HARMONY_CORE_TIME_SIGNATURE
