#ifndef HARMONY_CORE_ENUMS
#define HARMONY_CORE_ENUMS

namespace harmony_core
{
    // Здесь хранятся вспомогательные конструкции для класса Note, Key и Clef.

    //--------- Части ноты -----------

    // /*!
    //  * \brief Представляет собой соглашение об именовании нот.
    //  */
    // enum class NamingConvention
    // {
    //     /*!
    //      * \brief Представляет собой английское соглашение об именовании нот.
    //      */
    //     ENGLISH,
    //     /*!
    //      * \brief Представляет собой немецкое соглашение об именовании нот.
    //      */
    //     GERMAN,
    //     /*!
    //      * \brief Представляет собой голландское соглашение об именовании нот.
    //      */
    //     DUTCH,
    //     /*!
    //      * \brief Представляет собой византийское соглашение об именовании нот.
    //      */
    //     BYZANTINE,
    //     /*!
    //      * \brief Представляет собой японское соглашение об именовании нот.
    //      */
    //     JAPANESE
    // };

    /*!
     * \brief Представляет собой основание ноты.
     */
    enum class Base
    {
        /*!
         * \brief Представляет собой ноту \code До\endcode.
         */
        A = 0b001,
        /*!
         * \brief Представляет собой ноту \code Ре\endcode.
         */
        B = 0b010,
        /*!
         * \brief Представляет собой ноту \code Ми\endcode.
         */
        C = 0b011,
        /*!
         * \brief Представляет собой ноту \code Фа\endcode.
         */
        D = 0b100,
        /*!
         * \brief Представляет собой ноту \code Соль\endcode.
         */
        E = 0b101,
        /*!
         * \brief Представляет собой ноту \code Ля\endcode.
         */
        F = 0b110,
        /*!
         * \brief Представляет собой ноту \code Си\endcode.
         */
        G = 0b111
    };

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

    /*!
     * \brief Представляет собой длительность ноты.
     */
    enum class Duration
    {
        /*!
         * \brief Представляет собой двойную длительность целой ноты.
         */
        DOUBLE = 0b000,
        /*!
         * \brief Представляет собой длительность целой ноты.
         */
        WHOLE = 0b001,
        /*!
         * \brief Представляет собой половину длительности целой ноты.
         */
        HALF = 0b010,
        /*!
         * \brief Представляет собой четверть длительности целой ноты.
         */
        QUARTER = 0b011,
        /*!
         * \brief Представляет собой восьмую часть длительности целой ноты.
         */
        EIGHTH = 0b100,
        /*!
         * \brief Представляет собой тридцать вторую часть длительности целой ноты.
         */
        THIRTY_SECOND = 0b101,
        /*!
         * \brief Представляет собой шестьдесят четвёртую часть длительности целой ноты.
         */
        SIXTY_FOURTH = 0b110,
        /*!
         * \brief Представляет собой сто двадцать восьмую часть длительности целой ноты.
         */
        HUNDRED_TWENTY_EIGHTH = 0b111
    };

    // Части тональности

    /*!
     * \brief Представляет собой соглашение об именовании лада тональности.
     * Каждый лад является своеобразным ключом, точкой отсчета нот для тональности.
     * Каждый лад имеет свое соотношение тонов и полутонов,
     * не меняющееся по мере продвижения тональности по квинтовому кругу.
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

    /*!
     * \brief Представляет собой соглашение об именовании спецификации (вида) тональности.
     */
    enum class Specie
    {
        /*!
         * Представляет натуральный вид.
         */
        NATURAL = 0b00,

        /*!
         * Представляет гармонический вид.
         */
        HARMONYC = 0b01,

        /*!
         * Представляет мелодический вид.
         */
        MELODYC = 0b10,

        /*!
         * Представляет дважды гармонический вид.
         */
        DOUBLE_HARMONYC = 0b11
    };

    // Части интервала

    /*!
     * \brief Представляет собой соглашение об именовании видов интервала.
     */
    enum class Quality
    {
        /*!
         * Представляет чистый вид.
         */
        PERFECT = 0b000,

        /*!
         * Представляет малый вид.
         */
        MINOR = 0b001,

        /*!
         * Представляет большой вид.
         */
        MAJOR = 0b010,

        /*!
         * Представляет увеличенный вид (Augumented).
         */
        AUG = 0b011,

        /*!
         * Представляет уменьшенный вид (Diminished).
         */
        DIM = 0b100,

        /*!
         * Представляет дважды увеличенный вид.
         */
        DOUBLY_AUG = 0b101,

        /*!
         * Представляет дважды уменьшенный вид.
         */
        DOUBLY_DIM = 0b110
    };
    
     /*!
     * \brief Представляет собой соглашение об именовании видов ключей.
     */
    enum class Clef_name
    {
       /*!
        * \brief Представляет Отсутствие ключа.
        */
        NONE = 0b0000,
        
        /*!
        * \brief Представляет нейтральный 
        * (ударный) ключ.
        */
        NEUTRAL = 0b0001,
        
        /*!
        * Представляет французский скрипичный ключ
        */
        FRENCH_VIOLIN = 0b0010,
        
        /*!
        * Представляет скрипичный ключ
        */
        TREBLE = 0b0011,
        
        /*!
        * Представляет Сопрановый ключ
        */
        SOPRANO = 0b0100,
        
        /*!
        * Представляет Меццо сопрановый ключ
        */
        MEZZO_SOPRANO = 0b0101,
        
        /*!
        * Представляет Альтовый ключ
        */
        ALTO = 0b0110,
        
        /*!
        * Представляет Теноровый ключ
        */
        TENOR = 0b0111,
        
        /*!
        * Представляет Баритоновый ключ
        */
        BARITONE = 0b1000,
        
        /*!
        * Представляет Басовый ключ
        */
        BASS = 0b1001,
        
        /*!
        * Представляет суб басовый ключ
        */
        SUBBASS = 0b1010,
        
        /*!
        * Представляет ключ для табулатуры
        */
        TABULATURE = 0b1011
    };
    
    /*!
    * представляет соглашение имен
    * для типов ключей
    */
    enum class Clef_type
    {
        /*!
        * Тип ключа не определен
        */
        NONE = 0b00,
        /*!
        * Представляет ключ фа
        */
        F_CLEF = 0b01,
        
        /*!
        * Представляет ключ до
        */
        C_CLEF = 0b10,
        
        /*!
        * Представляет ключ соль
        */
        G_CLEF = 0b11
    };
} // namespace harmony_core

#endif // HARMONY_CORE_ENUMS
