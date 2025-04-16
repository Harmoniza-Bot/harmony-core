#ifndef HARMONY_CORE_OCTAVE_HPP
#define HARMONY_CORE_OCTAVE_HPP

namespace harmony_core
{
    /*!
     * \brief Представляет собой октаву.
     */
    enum class Octave
    {
        /*!
         * \brief Представляет собой субконтроктаву.
         */
        SUB_CONTRA = 0b0000,
        /*!
         * \brief Представляет собой контроктаву.
         */
        CONTRA = 0b0001,
        /*!
         * \brief Представляет собой большую октаву.
         */
        GREAT = 0b0010,
        /*!
         * \brief Представляет собой малую октаву.
         */
        SMALL = 0b0011,
        /*!
         * \brief Представляет собой первую октаву.
         */
        _1_LINE = 0b0100,
        /*!
         * \brief Представляет собой вторую октаву.
         */
        _2_LINE = 0b0101,
        /*!
         * \brief Представляет собой третью октаву.
         */
        _3_LINE = 0b0110,
        /*!
         * \brief Представляет собой четвёртую октаву.
         */
        _4_LINE = 0b0111,
        /*!
         * \brief Представляет собой пятую октаву.
         */
        _5_LINE = 0b1000,
    };
} // namespace harmony_core

#endif // HARMONY_CORE_OCTAVE_HPP
