namespace harmony_core
{
    /*!
     * \brief Представляет собой соглашение об именовании лада тональности.
     * Каждый лад является своеобразным ключом, точкой отсчета нот для тональности.
     * Каждый лад имеет свое соотношение тонов и полутонов, не меняющееся по мере продвижения тональности по квинтовому
     * кругу.
     */
    enum class Mode
    {
        /*!
         * \brief Представляет эолийский (минорный) лад.
         * Лад ноты ля.
         * Соотношения тонов и полутонов: whole-half-whole-whole-half-whole
         */
        AEOLIAN = 0b110,

        /*!
         * \brief Представляет локрийский лад.
         * Лад ноты си.
         * Соотношения тонов и полутонов: half-whole-whole-half-whole-whole
         */
        LOCRIAN = 0b111,

        /*!
         * \brief Представляет ионийский (мажорный) лад.
         * Лад ноты ля.
         * Соотношение тонов и полутонов: whole-whole-half-whole-whole-whole
         */
        IONIAN = 0b001,

        /*!
         * \brief Представляет дорийский лад.
         * Соотношения тонов и полутонов: whole-half-whole-whole-whole-half
         */
        DORIAN = 0b010,

        /*!
         * \brief Представляет фригийский лад.
         * Соотношения тонов и полутонов: half-whole-whole-whole-half-whole
         */
        PHRYGIAN = 0b011,

        /*!
         * \brief Представляет лидийский лад.
         * Соотношения тонов и полутонов: whole-whole-whole-half-whole-whole
         */
        LYDIAN = 0b100,

        /*!
         * \brief Представляет миксолидийский лад.
         * Соотношения тонов и полутонов: whole-whole-half-whole-whole-half
         */
        MIXOLYDIAN = 0b101
    };
} // namespace harmony_core
