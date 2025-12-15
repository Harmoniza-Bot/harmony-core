#ifndef HC2IMG_STAFF_CORD
#define HC2IMG_STAFF_CORD

#include <cstdint>
#include <utility>

namespace hc2img {

    /*!
     * \brief Данная структура хранит координаты линеек нотного стана. Отсчет идет снизу вверх.
     * Кроме того, данный класс хранит местоположение ключа, музыкального размера и знаков.
     * Координаты ключа, размера и знаков начинаются с левого верхнего угла.
     */
    struct Staff_cord final {

        /*!
         * \brief первая линейка нотного стана.
         */
        uint16_t _1_LINE = 0;

        /*!
         * \brief Координаты ключа.
         */
        std::pair<uint16_t, uint16_t> clef_cord;

        /*!
         * \brief Координаты размера.
         */
        std::pair<uint16_t, uint16_t> time_signature_cord;

        /*!
         * \brief Координаты ключевых знаков.
         */
        std::pair<uint16_t, uint16_t> accidental_cord;
    };
} // namespace hc2img

#endif // HC2IMG_STAFF_CORD
