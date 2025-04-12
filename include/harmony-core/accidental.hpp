#ifndef HARMONY_CORE_ACCIDENTAL_HPP
#define HARMONY_CORE_ACCIDENTAL_HPP

namespace harmony_core
{
    /*!
     * \brief Представляет собой знак альтерации.
     */
    enum class Accidental
    {
        /*!
         * \brief Представляет собой неопределённый знак альтерации.
         */
        UNDEFINED = 0b000,
        /*!
         * \brief Представляет собой дубль-бемоль.
         */
        DOUBLE_FLAT = 0b001,
        /*!
         * \brief Представляет собой бемоль.
         */
        FLAT = 0b010,
        /*!
         * \brief Представляет собой бекар.
         */
        NATURAL = 0b011,
        /*!
         * \brief Представляет собой диез.
         */
        SHARP = 0b100,
        /*!
         * \brief Представляет собой дубль-диез.
         */
        DOUBLE_SHARP = 0b101
    };
} // harmony_core

#endif // HARMONY_CORE_ACCIDENTAL_HPP
