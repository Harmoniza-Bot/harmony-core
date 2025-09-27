#include <hc2img/list.hpp>
#include <images/images.hpp>
#include <iostream>

namespace hc2img {

    List::List() {
    }

    void List::add(Staff &s) {
        staff_list.push_back(s);
    }

    void List::rm(uint8_t index) {
        if (index < staff_list.size()) {
            return;
        }
        // staff_list.erase(index);
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
                cord_y = cords[x]._1 = staff_edge_gap + y * staff_line_gap + (x * (staff_line_gap * 5 + staff_gap));

                switch (y) {
                    case 0:
                        cords[x]._1 = cord_y;
                    case 1:
                        cords[x]._2 = cord_y;
                    case 2:
                        cords[x]._3 = cord_y;
                    case 3:
                        cords[x]._4 = cord_y;
                    case 4:
                        cords[x]._5 = cord_y;
                }
                cords[x].clef_cord = {staff_edge_gap, cords[y]._1};
                cords[x].accidental_cord = {staff_edge_gap + clef_acc_gap, cords[y]._1};
                cords[x].time_signature_cord = {staff_edge_gap + clef_acc_gap + acc_ts_gap, cords[y]._1};
            }
        }
        return cords;
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);
        // cimg_library::CImg<unsigned char> image1("/home/tim/Загрузки/ключ_до.bmp");

        // image.save_bmp("img/list.bmp");
        // image1.display("1");
        std::vector<hc2img::Staff_cord> s = draw_staff(image);
        draw_parts(image, images::treble_clef, 50, 22);
        image.display("winnn");
    }

    size_t List::size() const noexcept {
        return staff_list.size();
    }
} // namespace hc2img
