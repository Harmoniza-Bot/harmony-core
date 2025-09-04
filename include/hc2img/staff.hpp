#ifndef HC2IMG_STUFF
#define HC2IMG_STUFF

#include <cstdint>

#include <harmony-core/harmony-core.hpp>

namespace hc2img {
    /*!
     * \brief Представляет нотный стан и является контейнером для тактов.
     * (Для функционирования интерфейса необходимо подключить библиотеку CImg.h)
     */
    struct Staff final {
     
        /*!
         * \brief создает нотный стан без нот со скрипичным ключем в размере 4/4.
         */
        explicit Staff();
        
        /*!
         * \brief создает нотный стан на основе днугого нотного стана.
         */
         explicit Staff(hc2img::Staff);
         
        /*!
         * \brief устанавливает ключ.
         * \param [in] harmony_core::Clef
         */
         void set_clef(harmony_core::Clef) noexcept;
         
         /*!
          * \brief возвращает ключ.
          * \return ключ стана.
          */ 
          harmony_core::Clef get_clef() noexcept;
          
         /*!
         * \brief устанавливает размер нотного стана.
         * \param [in] harmony_core::Time_signature
         */
         void set_time_signature(harmony_core::Time_signature) noexcept;
         
         /*!
          * \brief возвращает музыкальный размер стана.
          * \return размер стана (один на весь стан).
          */
          harmony_core::time_signature get_time_signature() noexcept;
          
         /*!
          * \brief возвращает ноту по индексу.
          */
         std::pair<Note::Note n, bool i> get_note(uint16_t i);
         
        /*!
         * \brief возвращает количество нот и пауз в нотном стане.
         */
         size_t get_note_list_size();
        
        /*!
         * \brief Добавляет ноту в такт.
         * \param [in] n Нота для добпвления
         * \param [in] is_pause Флаг, обозначающий добавление паузы. В этом случае считывается только размер ноты.
         * Такты и связки штилей расставляются автоматически.
         */
        void add(Note *n, bool is_pause) noexcept;

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

    private:
        /*!
         * \brief Хранит Ключ нотного стана.
         */
         harmony_core::Clef * clef = nullptr;

        /*!
         * \brief Хранит размер нотного стана.
         */
         harmony_core::Time_signature * time_sig = nullptr;

        /*!
         * \brief Хранит список пар "нота - флаг паузы".
         */
        std::vector<std::pair<harmony_core::Note, bool>> note_list;
        
        /*! 
         * \brief Представляет индекс нотного указателя, на месте которого происходит вставка и удаление нот.
         */
        uint16_t ptr_index = 0;
    };
} // namespace hc2img

#endif // HC2IMG_STUFF
