#ifndef IMAGES_TREBLE_CLEF
#define IMAGES_TREBLE_CLEF

#include <cstdint>
#include <vector>

namespace images {
    /*!
     * Данная структура хранит опорные точки для рисования скрипичного ключа
     */
    const struct Treble_clef final {
    private:
        /*!
         * Данная константа хранит опорные точки скрипичного ключа.
         * Нулевые координаты расположены в левом верхнем углу.
         * Первые 4 бита хранят координату x остальные - координату y
         */
        const std::vector<uint8_t> treble_clef_cord = {
            0b0001'1000, 0b0001'0111, 0b0010'0110, 0b0011'0110, 0b0100'0111, 0b0100'1001, 0b0011'1010, 0b0001'1010,
            0b0000'1001, 0b0000'0111, 0b0011'0010, 0b0011'0000, 0b0010'0000, 0b0010'1100, 0b0001'1100, 0b0001'1011};

    public:
        /*!
         * Возвращает количество опорных точек ключа
         */
        size_t size() const noexcept {
            return 16;
        };

        /*!
         * Возвращает y координату опорной точки по индексу или 255, если индекс больше количества точек.
         */
        uint8_t y(uint8_t i) const noexcept {
            if (i >= 16) {
                return 255;
            }
            return treble_clef_cord[i] & 0xF;
        };

        /*!
         * Возвращает x координату опорной точки по индексу
         */
        uint8_t x(uint8_t i) const noexcept {
            return (treble_clef_cord[i] >> 4) & 0xF;
        };

    } treble_clef;
} // namespace images

#endif // IMAGES_TREBLE_CLEF
