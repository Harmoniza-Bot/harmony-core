#include <hc2img/list.hpp>
#include <iostream>

namespace hc2img {

    std::vector<uint16_t> cord_staff_line; // Вектор для записи коордират линий нотных станов

    List::List() {
    }

    void draw_clef(cimg_library::CImg<unsigned char> &image, uint16_t mutch) {
        //cimg_library::CImg<unsigned char> overlay_image("/home/tim/Документы/test_harm/tmp/images/clef_1.bmp");
        cimg_library::CImg<unsigned char> overlay_image_1("/home/tim/Документы/test_harm/tmp/images/clef.bmp");

        //image.draw_image(30, 10, 0, 0, overlay_image, 0.5f); // накладывает любое изображение (просто серым квадратом)
        image+= overlay_image_1; // накладывает изображение равное по размеру (правильно)

    }

    void draw_staff(cimg_library::CImg<unsigned char> &image, uint16_t mutch) noexcept{
        int current_y = staff_edge_gap; // Начальная координата Y

        for (int x = 0; x < mutch; ++x) {
            for (int y = 0; y < 5; ++y) {
                // Вычисляем координаты начала и конца линии
                int start_y = current_y + y * staff_line_gap;
                int end_y = start_y;

                // Рисуем линию
                image.draw_line(staff_edge_gap, start_y,
                                list_size_x - staff_edge_gap, end_y,
                                black, 1.0f);

                // Записываем координату (y) линейки в вектор
                cord_staff_line.push_back(start_y);
            }

            // Обновляем текущую координату Y для следующего набора линий
            current_y += staff_gap + 5 * staff_line_gap;
        }
    }


    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);

        draw_staff(image, 3);
        draw_clef(image, 1);

        for(int x=0; x<cord_staff_line.size(); ++x){
            std::cout << cord_staff_line[x] << std::endl;
        }

        // image.save_bmp("img/list.bmp");
        image.display("winnn");
    }
} // namespace hc2img
