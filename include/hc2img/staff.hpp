#ifndef HC2IMG_STUFF
#define HC2IMG_STUFF

#include "hc2img.hpp"

namespace hc2img{
    /*!
     * \brief Представляет нотный стан и является контейнером для тактов.
     * (Для функционирования интерфейса необходимо подключить библиотеку CImg.h)
     */
    struct Staff final{

    private:
        /*!
         * Хранит ссылки на такты
         */
        std::vector<bar*> staff_list;
    };
}

#endif //HC2IMG_STUFF
