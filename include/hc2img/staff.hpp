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
         * \brief Хранит ссылки на такты
         */
        std::vector<Bar *> staff_list;
    };
} // namespace hc2img

#endif // HC2IMG_STUFF
