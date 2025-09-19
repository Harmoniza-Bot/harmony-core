#ifndef IMAGES_C_CLEF
#define IMAGES_C_CLEF

namespace images {
    struct C_clef {
    private:
        /*!
         * Данная константа хранит количество опорных точек в ключе до
         */
        const uint8_t clef_size = 16;

        /*!
         * Данная константа хранит опорные точки скрипичного ключа.
         * Нулевые координаты расположены в левом верхнем углу.
         * Первые 4 бита хранят координату x остальные - координату y
         */
        const std::vector<uint8_t> c_clef_cord = {
            0b0000'1100, 0b000'0000,  0b0001'0000, 0b0001'1100, 0b0010'1100, 0b0010'0000, 0b0100'0000, 0b0101'0001,
            0b0101'0101, 0b0100'0110, 0b0010'0110, 0b0100'0110, 0b0101'0111, 0b0101'1011, 0b0100'1100, 0b0010'1100};

    public:
        /*!
         * Возвращает количество опорных точек ключа
         */
        size_t size() const noexcept {
            return static_cast<size_t>(clef_size);
        };

        /*!
         * Возвращает y координату опорной точки по индексу или 255, если индекс больше количества точек.
         */
        uint8_t y(uint8_t i) const noexcept {
            if (i >= clef_size) {
                return 255;
            }
            return c_clef_cord[i] & 0xF;
        };

        /*!
         * Возвращает x координату опорной точки по индексу
         */
        uint8_t x(uint8_t i) const noexcept {
            return (c_clef_cord[i] >> 4) & 0xF;
        };

    } c_clef;
} // namespace images

#endif // IMAGES_C_CLEF
