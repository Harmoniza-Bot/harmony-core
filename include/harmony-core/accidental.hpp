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
         * \brief дубль бемоль.
         */
        DOUBLE_FLAT,
        /*!
         * \brief Бемоль.
         */
        FLAT,
        /*!
         * \brief бекар.
         */
        NATURAL,
        /*!
         * \brief диез.
         */
        SHARP,
        /*!
         * \brief Дубль-диез.
         */
        DOUBLE_SHARP
    };
}

#endif // HARMONY_CORE_ACCIDENTAL_HPP
