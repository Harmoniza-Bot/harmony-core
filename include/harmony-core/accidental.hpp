#ifndef HARMONY_CORE_ACCIDENTAL_HPP
#define HARMONY_CORE_ACCIDENTAL_HPP

namespace harmony_core
{
    /*!
     * \brief Знак альтерации.
     */
    enum class Accidental
    {
        /*!
         * \brief Бекар.
         */
        NATURAL,
        /*!
         * \brief Бемоль.
         */
        FLAT,
        /*!
         * \brief Диез.
         */
        SHARP,
        /*!
         * \brief Дубль-бемоль.
         */
        DOUBLE_FLAT,
        /*!
         * \brief Дубль-диез.
         */
        DOUBLE_SHARP
    };
}

#endif // HARMONY_CORE_ACCIDENTAL_HPP
