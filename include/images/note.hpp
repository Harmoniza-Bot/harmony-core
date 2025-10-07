#ifndef IMAGES_NOTE_HPP
#define IMAGES_NOTE_HPP

#include <cstddef>
#include <cstdint>

namespace images {
    /*!
     * Данная структура хранит опорные точки для рисования ноты (без штиля).
     */
    struct Note final {
    private:
        /*!
         * Данная константа хранит количество опорных точек ноты
         */
        const uint8_t note_size = 5;

    public:
        /*!
         * Возвращает количество опорных точек ноты
         */
        size_t size() const noexcept {
            return static_cast<size_t>(note_size);
        };

        /*!
         * Возвращает y координату опорной точки по индексу или 255, если индекс больше количества точек.
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
                default:
                    if (i > 3) {
                        std::cerr << "from note::y(): too big argument" << std::endl;
                    }
            }
            return 1;
        };

        /*!
         * Возвращает x координату опорной точки по индексу
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
                default:
                    if (i > 3) {
                        std::cerr << "from note::y(): too big argument" << std::endl;
                    }
            }
            return 1;
        };
    } note;
} // namespace images
#endif // IMAGES_NOTE_HPP
