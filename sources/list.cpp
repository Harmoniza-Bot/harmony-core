#include <hc2img/list.hpp>
#include <images/images.hpp>
#include <iostream>

namespace hc2img {

    List::List() {
    }

    void List::add(Staff &s) {
        staff_list.resize(staff_list.size() + 1);
        staff_list[staff_list.size() - 1] = s;
    }

    void List::rm(uint8_t index) {
        if (index < staff_list.size()) {
            return;
        }
        this->staff_list.erase(staff_list.begin() + index);
    }

    template<typename T>
    void List::draw_parts(cimg_library::CImg<unsigned char> &image, T part, int x, int y) {
        for (int a = 0; a < part.size() - 1; ++a) {
            image.draw_line((part.x(a) * pixel_index) + x, (part.y(a) * pixel_index) + y,
                            (part.x(a + 1) * pixel_index) + x, (part.y(a + 1) * pixel_index) + y, black);
            image.draw_line((part.x(a) * pixel_index) + x + 1, (part.y(a) * pixel_index) + y,
                            (part.x(a + 1) * pixel_index) + x + 1, (part.y(a + 1) * pixel_index) + y, black);
            image.draw_line((part.x(a) * pixel_index) + x, (part.y(a) * pixel_index) + y + 1,
                            (part.x(a + 1) * pixel_index) + x, (part.y(a + 1) * pixel_index) + y + 1, black);
            image.draw_line((part.x(a) * pixel_index) + x + 1, (part.y(a) * pixel_index) + y + 1,
                            (part.x(a + 1) * pixel_index) + x + 1, (part.y(a + 1) * pixel_index) + y + 1, black);
        }
    }

    std::vector<hc2img::Staff_cord> List::draw_staff(cimg_library::CImg<unsigned char> &image) noexcept {
        std::vector<Staff_cord> cords;

        for (int x = 0; x < staff_list.size(); ++x) {
            static Staff_cord cord;
            cords.push_back(cord);
            for (int y = 0; y < 5; ++y) {
                image.draw_line(
                    /*первая координата*/ staff_edge_gap,
                    staff_edge_gap + y * staff_line_gap + (x * (staff_line_gap * 5 + staff_gap)),
                    /*вторая координата*/ list_size_x - staff_edge_gap,
                    staff_edge_gap + y * staff_line_gap + (x * (staff_line_gap * 5 + staff_gap)),
                    /*цвет*/ black);

                static uint16_t cord_y;
                cord_y = staff_edge_gap + y * staff_line_gap + (x * (staff_line_gap * 5 + staff_gap));
                cords[x]._1_LINE = cord_y;

                // cords[x].clef_cord = {staff_edge_gap, cords[y]._1_LINE};
                // cords[x].accidental_cord = {staff_edge_gap + clef_acc_gap, cords[y]._1};
                // cords[x].time_signature_cord = {staff_edge_gap + clef_acc_gap + acc_ts_gap, cords[y]._1};
            }
        }
        return cords;
    }

    void List::draw_notes(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord cord) {
        if (staff_list.size() == 0)
            return;

        for (int y = 0; y < staff_list[0].get_note_list_size(); ++y) {
            uint16_t x_gap = staff_edge_gap + 50 + (note_gap * (y + 1));
            uint16_t y_gap = 0;
            int note_place = static_cast<int>(staff_list[0].get_clef().get_place(staff_list[0].get_note(y)) * 2 + 1);
            int note_place_2 = note_place;
            std::cout << "note height: " << note_place << std::endl;

            // находим у-координату ноты
            y_gap = cord._1_LINE;
            while (note_place != 0) {
                if (note_place > 0) {
                    --note_place;
                    y_gap -= staff_line_gap / 2;
                }
                if (note_place < 0) {
                    ++note_place;
                    y_gap += staff_line_gap / 2;
                }
            }

            // рисуем ноту
            draw_parts(image, images::note, x_gap, y_gap);

            // округляем у-координату до линеечной
            if (y_gap % staff_line_gap != 0) {
                if (note_place >= 0) {
                    y_gap -= staff_line_gap / 2;
                } else {
                    y_gap += staff_line_gap / 2;
                }
            }

            // Рисуем добавочные линейки
            // Необходимо дописать
        }
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);
        // cimg_library::CImg<unsigned char> image1("/home/tim/Загрузки/ключ_до.bmp");

        // image.save_bmp("img/list.bmp");
        // image1.display("1");
        std::vector<hc2img::Staff_cord> s = draw_staff(image);
        draw_parts(image, images::treble_clef, 50, 22);
        draw_notes(image, s[0]);
        image.display("winnn");
    }

    size_t List::size() const noexcept {
        return staff_list.size();
    }
} // namespace hc2img
