#ifndef HARMONY_CORE_OCTAVE_HPP
#define HARMONY_CORE_OCTAVE_HPP

namespace harmony_core
{
    /*!
     * \brief Октава.
     */
    enum class Octave
    {
        /*!
         * \brief Субконтроктава.
         */
        SUB_CONTRA,
        /*!
         * \brief Контроктава.
         */
        CONTRA,
        /*!
         * \brief Большая октава.
         */
        GREAT,
        /*!
         * \brief Малая октава.
         */
        SMALL,
        /*!
         * \brief Первая октава.
         */
        _1_LINE,
        /*!
         * \brief Вторая октава.
         */
        _2_LINE,
        /*!
         * \brief Третья октава.
         */
        _3_LINE,
        /*!
         * \brief Четвёртая октава.
         */
        _4_LINE,
        /*!
         * \brief Пятая октава.
         */
        _5_LINE,
    };
}

#endif // HARMONY_CORE_OCTAVE_HPP
