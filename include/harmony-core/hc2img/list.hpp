#ifndef HC2IMG_LIST
#define HC2IMG_LIST

#include <cstdint>
#include "CImg/CImg.h"

#include <harmony-core/harmony-core.hpp>

#include "images/images.hpp"
#include "list_param.hpp"
#include "staff_cord.hpp"

namespace hc2img {
    /*!
     * \brief Представляет нотный лист.
     * В него можно добавить нотный стан (harmony_core::Staff).
     * Также можно сохранить лист как изображение.
     * (Для работы с графикой используется библиотека CImg.h).
     */
    class List final {
    public:
        /*!
         * \brief Создает пустой нотный лист.
         */
        List();

        /*!
         * \brief Создает стан на основе другого стана.
         */
        List(const hc2img::List &);

        /*!
         * \brief Добавляет нотный стан в лист.
         * \param[in] Staff Ссылка на стан для добавления.
         */
        void add(harmony_core::Staff &s);

        /*!
         * \brief Удаляет нотный стан из листа.
         */
        void rm(uint8_t index);

        /*!
         * \brief Сохраняет лист как изображение.
         */
        void save() noexcept;

        /*!
         * \brief Возвращает количество нотных станов в листе.
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
         * Принимает специальную структуру, обязательно имеющую функции x(), y() и size(),
         * возвращающие координаты для отрисовки примитива и количество точек соответственно.
         * (Данные структуры хранятся в папке harmony-core/hc2img/images).
         * \param &image общект cimg_library (лист) для рисования.
         * \param part объект с координатами опорных точек для рисования.
         * \param x х-координата для смещения.
         * \param y y-координата для смещения.
         */
        template<typename T>
        void draw_parts(cimg_library::CImg<unsigned char> &image, T part, int x, int y);

        /*!
         * Рисует лигу между нотами, чьи индексы были добавлены методом add_tie.
         * \param image лист для рисования.
         * \param cord вектор из координат нотных станов (возвращается функцией рисования станов).
         */
        void draw_tie(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord);

        /*!
         * Рисует ключ по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_clefs(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) noexcept;

        /*!
         * \brief Рисует знаки по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_accidentals(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> &cord) noexcept;

        /*!
         * \brief Рисует нотный размер по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_time_signature(cimg_library::CImg<unsigned char> &image,
                                 std::vector<hc2img::Staff_cord> &cord) noexcept;

        /*!
         * \brief Рисует ноты по координатам нотного стана.
         * \param &image общект cimg_library (лист) для рисования.
         * \param cord объект класса с координатами нотного стана (возвращается функцией рисования стана).
         */
        void draw_notes(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord);

        /*!
         * \brief Рисует тактовые черты после нот, указанных нотных станах.
         * \param &image объект cimg_library (лист) для рисования.
         * \param cord вектор из координат нотных станов.
         * Важный момено - ноты начинаются с первой ноты (не с нулевой!).
         */
        void draw_bar(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord);

        /*!
         * \brief Рисует штили, если нужно.
         * \param &image объект cimg_library (лист) для рисования.
         * \param cord вектор из координат нотных станов.
         */
        void draw_stem(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord);

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
         */
        std::vector<harmony_core::Staff> staff_list;
    };
} // namespace hc2img

#endif // HC2IMG_LIST
