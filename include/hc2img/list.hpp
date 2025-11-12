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
     * В него можно добавить нотный стан (harmony_core::Staff).
     * Если добавить больше одного стана они объединятся в систему нотных станов.
     * Также можно сохранить лист как изображение.
     * (Для работы с графикой исаользуется библиотека CImg.h)
     */
    class List final {
    public:
        /*!
         * \brief Создает пустой нотный лист
         */
        List();

        /*!
         * \brief Добавляет нотный стан в лист.
         * \param[in] Staff Ссылка на стан для добавления
         */
        void add(harmony_core::Staff &s);

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

        harmony_core::Staff &operator[](int index) {
            return staff_list[index];
        }

    private:
        /*!
         * Рисует нотный стан.
         * Возвращает объекты hc2img::staff_cord c координатами нотных станов.
         * В hc2img::staff_cord хранятся координаты только одного стана без учета систем.
         * Поэтому нужно учитывать количество станов в листе staff_list.size().
         * \param &image общект cimg_library (лист) для рисования.
         */
        std::vector<hc2img::Staff_cord> draw_staffs(cimg_library::CImg<unsigned char> &image) noexcept;

        /*!
         * Рисует примитив, используя сам примитив и координаты для смещения.
         * \param &image общект cimg_library (лист) для рисования.
         * \param part объект с координатами опорных точек для рисования.
         * \param x х-координата
         * \param y y-координата
         */
        template<typename T>
        void draw_parts(cimg_library::CImg<unsigned char> &image, T part, int x, int y);

        /*!
         * Рисует лигу между двумя координатами.
         * \param image лист для рисования.
         * \param start координаты стартовой точки лиги.
         * \param finish координаты конечной точки лиги.
         * \param direction ориентация лиги (1 - вверх, 0 - вниз).
         */
        void draw_tie(cimg_library::CImg<unsigned char> &image, std::pair<uint16_t, uint16_t> start,
                      std::pair<uint16_t, uint16_t> finish, bool direction);

        /*!
         * Рисует ключ по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_clefs(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) noexcept;

        /*!
         * Рисует знаки по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_accidentals(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> &cord) noexcept;

        /*!
         * Рисует нотный размер по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_time_signature(cimg_library::CImg<unsigned char> &image,
                                 std::vector<hc2img::Staff_cord> &cord) noexcept;

        /*!
         * Рисует ноты по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_notes(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord);

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
        std::vector<harmony_core::Staff> staff_list;
    };
} // namespace hc2img

#endif // HC2IMG_LIST
