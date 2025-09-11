#ifndef HC2IMG_LIST
#define HC2IMG_LIST

#include <cstdint>

#include <harmony-core/harmony-core.hpp>

#include "CImg.h"
#include "staff.hpp"
#include "list_param.hpp"

namespace hc2img {
    /*!
     * \brief Представляет нотный лист.
     * В него можно добавить нотный стан (hc2img::Staff). Если добпвить больше одного стана они объединятся в систему
     * нотных станов. Также можно сохранить лист как изображение. (Для работы с графикой исаользуется библиотека CImg.h)
     */
    struct List final {
    public:
        /*!
         * \brief Создает пустой нотный лист
         */
        List();

        /*!
         * \brief Сохраняет лист как изображение.
         */
        void save() noexcept;

    private:
        /*!
         * \brief Хранит информацию о патаметрах листа.
         * Бит \code 0 \endcode хранит информацию об ориентации нотоносца: 0 - линейный, 1 - переносной.
         * Биты \code 1-3 \endcode хранят множитель размера такта от 1 до 8.
         * При множителе, равном 1, размер такта равен 20х40 пикселей.
         * \TODO Параметры листа не функционируют.
         */
        // uint8_t list_param;

        /*!
         * \brief Хранит вектор из нотных станов.
         * Если станов больше одного, то они объединяются в систему.
         */
        std::vector<Staff> staff_list;
    };
} // namespace hc2img

#endif // HC2IMG_LIST
