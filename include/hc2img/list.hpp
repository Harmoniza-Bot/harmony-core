#ifndef HC2IMG_LIST
#define HC2IMG_LIST

#include <cstdint>

#include <harmony-core/harmony-core.hpp>
#include <hc2img/staff_cord.hpp>

#include "CImg.h"
#include "list_param.hpp"
#include "staff.hpp"

namespace hc2img {
    /*!
     * \brief Представляет нотный лист.
     * В него можно добавить нотный стан (hc2img::Staff). Если добпвить больше одного стана они объединятся в систему
     * нотных станов. Также можно сохранить лист как изображение. (Для работы с графикой исаользуется библиотека CImg.h)
     */
    class List final {
      public:
        /*!
         * \brief Создает пустой нотный лист
         */
        List();

        /*!
         * \brief Добавляет нотный стан в лист.
         * \param[in] Staff& Ссылка на стан для добавления
         */
        void add(Staff &s);

        /*!
         * \brief Удаляет нотный стан из листа
         */
        void rm(uint8_t index);

        /*!
         * \brief Сохраняет лист как изображение.
         */
        void save() noexcept;

        /*!
         * \brief Возвращает количество нотных станов в листе
         */
        size_t size() const noexcept;

        Staff &operator[](int index) {
            return staff_list[index];
        }

      private:
        /*!
         * Рисует нотный стан. Возвращает объекты hc2img::staff_cord c координатами нотных станов.
         */
        std::vector<hc2img::Staff_cord> draw_staff(cimg_library::CImg<unsigned char> &image) noexcept;

        /*!
         * Рисует ключ по координатам нотного стана
         */
        void draw_clef(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord &cord) noexcept;


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
