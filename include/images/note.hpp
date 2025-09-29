#ifndef IMAGES_NOTE_HPP
#define IMAGES_NOTE_HPP

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
        const uint8_t note_size = 4;

        /*!
         * Данная константа хранит опорные точки ноты.
         */
        const uint16_t note_cord = 0b00'01'01'10'10'01'10'00;

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
            return ((note_cord >> (i * 2 + 1)) & 0b11);
        };

        /*!
         * Возвращает x координату опорной точки по индексу
         */
        uint8_t x(uint8_t i) const noexcept {
            return ((note_cord >> (i * 2)) & 0b11);
        };

    } note;
} // namespace images
#endif // IMAGES_NOTE_HPP
