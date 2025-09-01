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
         * \brief Добавляет такт в нотный стан
         */
        void add(Bar *) noexcept;

        /*!
         * \brief Удаляет из такта ноту по указанному индексу
         */
        void remove(uint8_t) noexcept;

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
