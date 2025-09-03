#ifndef HC2IMG_STUFF
#define HC2IMG_STUFF

#include <cstdint>

#include <harmony-core/harmony-core.hpp>
#include "bar.hpp"

namespace hc2img {
    /*!
     * \brief Представляет нотный стан и является контейнером для тактов.
     * (Для функционирования интерфейса необходимо подключить библиотеку CImg.h)
     */
    struct Staff final {
     
        /*!
         * \brief создает нотный стан без нот со скрипичным ключем в размере 4/4.
         */
        Staff();
        
        /*!
         * \brief Добавляет ноту в такт.
         * \param [in] n Нота для добпвления
         * \param [in] is_pause Флаг, обозначающий добавление паузы. В этом случае считывается только размер ноты.
         * Такты и связки штилей расставляются автоматически.
         */
        void add(Note *n, bool is_pause) noexcept;

        /*!
         * \brief Удаляет из такта ноту по указанному индексу
         */
        void rm(uint16_t) noexcept;

        /*!
         * \brief Возвращает количество тактов
         */
        size_t get_size() const noexcept;

    private:
        /*!
         * \brief Хранит список изменений ключей
         */
        std::vector<std::pair<harmony_core::Clef, uint8_t>> clef_list;

        /*!
         * \brief Хранит список изменений размеров
         */
        std::vector<std::pair<harmony_core::Time_signature, uint8_t>> t_s_list;

        /*!
         * \brief Хранит список нот
         */
        std::vector<harmony_core::Note> note_list;
    };
} // namespace hc2img

#endif // HC2IMG_STUFF
