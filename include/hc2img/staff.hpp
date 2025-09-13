#ifndef HC2IMG_STUFF
#define HC2IMG_STUFF

#include <cstdint>

#include <harmony-core/harmony-core.hpp>

namespace hc2img {
    /*!
     * \brief Представляет нотный стан и является контейнером для тактов.
     * (Для функционирования интерфейса необходимо подключить библиотеку CImg.h)
     */
    class Staff final {

        /*!
         * \brief создает нотный стан без нот со скрипичным ключем в размере 4/4.
         */
        explicit Staff();

        /*!
         * \brief создает нотный стан на основе днугого нотного стана.
         */
        Staff(const hc2img::Staff &);
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
        harmony_core::Note get_note(uint16_t i) const noexcept;

        /*!
         * \brief возвращает количество нот и пауз в нотном стане.
         */
        size_t get_note_list_size() const noexcept;

        /*!
         * \brief Добавляет ноту в такт.
         * \param [in] n Нота для добпвления
         * \param [in] is_pause Флаг, обозначающий добавление паузы. В этом случае считывается только размер ноты.
         * Такты и связки штилей расставляются автоматически.
         */
        void add(harmony_core::Note &n) noexcept;

        /*!
         * \brief Удаляет из нотного стана ноту по индексу.
         * \param [in] index Индекс удаляемой ноты
         */
        void rm(uint16_t index) noexcept;

        /*!
         * \brief Возвращает количество тактов в  нотном стане.
         */
        size_t get_size() const noexcept;

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
         * \brief Хранит список нот.
         */
        std::vector<harmony_core::Note> note_list;

        /*!
         * \brief Представляет индекс нотного указателя, на месте которого происходит вставка и удаление нот.
         */
        uint16_t ptr_index = 0;
    };
} // namespace hc2img

#endif // HC2IMG_STUFF
