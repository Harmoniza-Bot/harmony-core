#include <hc2img/list.hpp>
#include <images/images.hpp>
#include <iostream>

namespace hc2img {

    std::vector<uint16_t> cord_staff_line; // Вектор для записи коордират линий нотных станов

    List::List() {
    }

    void add(Staff &s) {
    }
    void rm(uint8_t index) {
    }

    hc2img::Staff_cord List::draw_staff(cimg_library::CImg<unsigned char> &image, uint16_t mutch) noexcept {
        Staff_cord cord; // Сюда необходимо добавить координаты нотного стана

        int current_y = staff_edge_gap; // Начальная координата Y

        for (int x = 0; x < mutch; ++x) {
            for (int y = 0; y < 5; ++y) {
                // Вычисляем координаты начала и конца линии
                int start_y = current_y + y * staff_line_gap;
                int end_y = start_y;

                // Рисуем линию
                image.draw_line(staff_edge_gap, start_y, list_size_x - staff_edge_gap, end_y, black, 1.0f);

                // Записываем координату (y) линейки в вектор
                cord_staff_line.push_back(start_y);
            }

            // Обновляем текущую координату Y для следующего набора линий
            current_y += staff_gap + 5 * staff_line_gap;
        }
        return cord;
    }

    void List::draw_clef(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord &cord) noexcept {
        for (int x = 0; x < images::treble_clef_size - 1; ++x) {
            image.draw_line(images::treble_clef[x].first * treble_clef_index,
                            images::treble_clef[x].second * treble_clef_index,
                            images::treble_clef[x + 1].first * treble_clef_index,
                            images::treble_clef[x + 1].second * treble_clef_index, black, 1.0f);
        }
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);

        // image.save_bmp("img/list.bmp");
        image.display("winnn");
    }
} // namespace hc2img
