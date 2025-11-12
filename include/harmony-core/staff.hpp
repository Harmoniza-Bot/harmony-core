#ifndef HC2IMG_STUFF
#define HC2IMG_STUFF

#include <cstdint>

namespace harmony_core {
    /*!
     * \brief Представляет нотный стан и является контейнером для нот и нотных обозначений.
     */
    class Staff final {
    public:
        /*!
         * \brief создает нотный стан без нот со скрипичным ключем в размере 4/4.
         */
        explicit Staff();

        /*!
         * \brief создает нотный стан на основе днугого нотного стана.
         */
        Staff(const harmony_core::Staff &);
        /*!
         * \brief устанавливает ключ.
         * \param [in] harmony_core::Clef
         */
        void set_clef(harmony_core::Clef) noexcept;

        /*!
         * \brief возвращает ключ.
         * \return ключ стана.
         */
        harmony_core::Clef get_clef() const noexcept;

        /*!
         * \brief устанавливает размер нотного стана.
         * \param [in] harmony_core::Time_signature
         */
        void set_time_signature(harmony_core::Time_signature) noexcept;

        /*!
         * \brief возвращает музыкальный размер стана.
         * \return размер стана (один на весь стан).
         */
        harmony_core::Time_signature get_time_signature() const noexcept;

        /*!
         * \brief возвращает ноту по индексу.
         */
        std::pair<harmony_core::Note, uint16_t> get_note(uint16_t i) const noexcept;

        /*!
         * \brief возвращает количество нот и пауз в нотном стане.
         */
        size_t get_note_list_size() const noexcept;

        /*!
         * \brief Задает знаки нотного стана.
         * Отрицательное число - бемоли, положительное - диезы.
         */
        void set_key(int8_t) noexcept;


        /*!
         * \brief Возвращает количество знаков нотного стана
         */
        int get_key() const noexcept;

        /*!
         *\brief Добавляет номера нот, которые нужно залиговать.
         * Используются номера от общего к-ва нот в стане.
         */
        void add_tie(uint16_t index) noexcept;

        /*!
         * \brief Убирает номера нот, которые нужно залиговать
         * Используются номера от общего к-ва нот в стане.
         */
        void rm_tie(uint16_t index) noexcept;

        /*!
         * \brief Проверяет, является ли нота по указанному индексу залигованой
         * Используются номера от общего к-ва нот в стане.
         */
        bool is_tie(uint16_t index) const noexcept;

        /*!
         * \brief Возвращает элемент из списка лиг по индексу.
         */
        uint16_t get_tie(uint16_t index) const noexcept;

        /*!
         * \brief Возвращает количество залигованных нот
         */
        size_t tie_size() const noexcept;

        /*!
         * \brief Добавляет ноту в такт.
         * \param [in] n Нота для добпвления
         * \param [in] is_pause Флаг, обозначающий добавление паузы. В этом случае считывается только размер ноты.
         * Такты и связки штилей расставляются автоматически.
         */
        void add(std::pair<harmony_core::Note, uint16_t> &n) noexcept;

        /*!
         * \brief Удаляет из нотного стана ноту по индексу.
         * \param [in] index Индекс удаляемой ноты
         */
        void rm(uint16_t index) noexcept;

        /*!
         * \brief Возвращает количество тактов в нотном стане.
         */
        size_t get_size() const noexcept;

        /*!
         * \brief Исправляет группировку нот в нотном стане на основе размера
         */
        void fix_groups() noexcept;

        /*!
         * \brief инкрементирует указатель на ноту стана.
         */
        Staff &operator++();

        /*!
         * \brief декрементирует указатель на ноту стана.
         */
        Staff &operator--();

        /*!
         * \brief инкрементирует указатель на ноту стана (постфиксный).
         */
        Staff operator++(int);

        /*!
         * \brief декрементирует указатель на ноту стана (постфиксный).
         */
        Staff operator--(int);

        // /*!
        //  * Копирует один стан в другой
        //  */
        // Staff &operator=(const Staff &staff) {
        //     clef.set_data(staff.get_clef().get_data());
        //     time_sig.set_data(staff.get_time_signature().get_data());
        //     note_list.resize(staff.get_note_list_size());
        //     for (int x = 0; x < note_list.size(); ++x) {
        //         note_list[x].first = staff.get_note(x).first;
        //         note_list[x].second = staff.get_note(x).second;
        //     }
        //     return *this;
        // }

    private:
        /*!
         * \brief Хранит Ключ нотного стана.
         */
        harmony_core::Clef clef;

        /*!
         * \brief Хранит музыкальный размер нотного стана.
         */
        harmony_core::Time_signature time_sig;

        /*!
         * \brief Хранит знаки нотного стана.
         * Отрицательное число - бемоли, положительное - диезы.
         */
        int8_t key = 0;

        /*!
         * \brief Хранит список нот.
         */
        std::vector<std::pair<harmony_core::Note, uint16_t>> note_list;

        /*!
         * \brief Хранит список залигованных нот
         */
        std::vector<uint16_t> tie_list;

        /*!
         * \brief Представляет индекс нотного указателя, на месте которого происходит вставка и удаление нот.
         */
        uint16_t ptr_index = 0;
    };
} // namespace harmony_core

#endif // HC2IMG_STUFF
