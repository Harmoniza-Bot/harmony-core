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

    void List::draw_clef(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord &cord) noexcept {
        for (int x = 0; x < images::treble_clef_size - 1; ++x) {
            image.draw_line(images::treble_clef[x].first * treble_clef_index,
                            images::treble_clef[x].second * treble_clef_index,
                            images::treble_clef[x + 1].first * treble_clef_index,
                            images::treble_clef[x + 1].second * treble_clef_index, black);
        }

        for (int x = 0; x < images::c_clef_size - 1; ++x) {
            image.draw_line(images::c_clef[x].first * c_clef_index, images::c_clef[x].second * c_clef_index,
                            images::c_clef[x + 1].first * c_clef_index, images::c_clef[x + 1].second * c_clef_index,
                            black);
        }
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);
        // cimg_library::CImg<unsigned char> image1("/home/tim/Загрузки/ключ_до.bmp");

        // image.save_bmp("img/list.bmp");
        // image1.display("1");
        std::vector<hc2img::Staff_cord> s = draw_staff(image);
        image.display("winnn");
    }

    size_t List::size() const noexcept {
        return staff_list.size();
    }
} // namespace hc2img
