#ifndef IMAGES_NOTE_1_HPP
#define IMAGES_NOTE_1_HPP

#include <cstddef>
#include <cstdint>

namespace images {
    /*!
     * Данная структура хранит опорные точки для рисования закрашенной ноты (без штиля).
     */
    struct Note_1 final {

    public:
        /*!
         * Возвращает количество опорных точек ноты
         */
        size_t size() const noexcept {
            return 8;
        };

        /*!
         * Возвращает y координату опорной точки по индексу или 1 и предупреждение, если индекс больше количества точек.
         */
        uint8_t y(uint8_t i) const noexcept {
            switch (i) {
                case 0: {
                    return 1;
                }
                case 1: {
                    return 2;
                }
                case 2: {
                    return 1;
                }
                case 3: {
                    return 0;
                }
                case 4: {
                    return 1;
                }
                case 5: {
                    return 1;
                }
                case 6: {
                    return 0;
                }
                case 7: {
                    return 2;
                }
                default: {
                    std::cerr << "from note::y(): too big argument" << std::endl;
                }
            }
            return 1;
        };

        /*!
         * Возвращает x координату опорной точки по индексу или 1 и предупреждение, если индекс больше количества точек.
         */
        uint8_t x(uint8_t i) const noexcept {
            switch (i) {
                case 0: {
                    return 0;
                }
                case 1: {
                    return 1;
                }
                case 2: {
                    return 2;
                }
                case 3: {
                    return 1;
                }
                case 4: {
                    return 0;
                }
                case 5: {
                    return 2;
                }
                case 6: {
                    return 1;
                }
                case 7: {
                    return 1;
                }
                default:
                    std::cerr << "from note::y(): too big argument" << std::endl;
            }
            return 1;
        };

        /*!
         * Возвращает x координату точки для крепления штиля по направлению (0 - вниз, 1 - вверх).
         */
        uint8_t x_stem(bool dir) {
            if (dir) {
                return 0;
            }
            return 2;
        }

        /*!
         * Возвращает у координату точки для крепления штиля по направлению (0 - вниз, 1 - вверх).
         */
        uint8_t y_stem(bool dir) {
            return 1;
        }
    } note_1;
} // namespace images
#endif // IMAGES_NOTE_1_HPP
