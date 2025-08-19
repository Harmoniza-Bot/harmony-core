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

    private:
        /*!
         * \brief Хранит ссылки на такты
         */
        std::vector<Bar *> staff_list;
    };
} // namespace hc2img

#endif // HC2IMG_STUFF
