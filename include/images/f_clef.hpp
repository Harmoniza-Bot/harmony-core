#ifndef IMAGES_F_CLEF
#define IMAGES_F_CLEF

namespace images {
    struct F_clef final {
    private:

        /*!
         * Данная константа хранит опорные точки скрипичного ключа.
         * Нулевые координаты расположены в левом верхнем углу.
         * Первые 4 бита хранят координату x остальные - координату y
         */
        const std::vector<uint8_t> f_clef_cord = {0b0010'0100, 0b011'0100,  0b0011'0101, 0b0010'0101, 0b0001'0101,
                                                  0b0000'0100, 0b0000'0001, 0b0001'0000, 0b0100'0000, 0b0101'0010,
                                                  0b0101'0110, 0b0100'1001, 0b0001'1100};

    public:
        /*!
         * Возвращает количество опорных точек ключа
         */
        size_t size() const noexcept {
            return 13;
        };

        /*!
         * Возвращает y координату опорной точки по индексу или 255, если индекс больше количества точек.
         */
        uint8_t y(uint8_t i) const noexcept {
            if (i >= clef_size) {
                return 255;
            }
            return f_clef_cord[i] & 0xF;
        };

        /*!
         * Возвращает x координату опорной точки по индексу
         */
        uint8_t x(uint8_t i) const noexcept {
            return (f_clef_cord[i] >> 4) & 0xF;
        };

    } f_clef;
} // namespace images

#endif // IMAGES_F_CLEF
