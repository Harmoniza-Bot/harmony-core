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
        this->staff_list.erase(staff_list.begin() + index);
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_size_x, list_size_y, 1, 3, 255);
        // image.save_bmp("img/list.bmp");
        // image1.display("1");
        std::vector<hc2img::Staff_cord> s = draw_staff(image);
        for (int x = 0; x < s.size(); ++x) {
            draw_clef(image, s[x]);
        }
        draw_notes(image, s);
        image.display("winnn");
    }

    size_t List::size() const noexcept {
        return staff_list.size();
    }

    //================== Приватные функции ==================

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

                cords[x].clef_cord = {staff_edge_gap, cords[x]._1_LINE};
                cords[x].accidental_cord = {staff_edge_gap + clef_acc_gap, cords[x]._1_LINE};
                cords[x].time_signature_cord = {staff_edge_gap + clef_acc_gap + acc_ts_gap, cords[x]._1_LINE};
            }
        }
        return cords;
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

    void List::draw_clef(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord cord) noexcept {
        if (staff_list.size() == 0) {
            return;
        }

        switch (static_cast<int>(staff_list[0].get_clef().get_type())) {
            case 0: {
                std::cerr << "From List::draw_clef: clef type is NONE!" << std::endl;
                return;
            }
            case 1: {
                switch (static_cast<int>(staff_list[0].get_clef().get_clef_name())) {
                    case 8: {
                        draw_parts(image, images::f_clef, 50, 12);
                        return;
                    }
                    case 9: {
                        draw_parts(image, images::f_clef, 50, 22);
                        return;
                    }
                    case 10: {
                        draw_parts(image, images::f_clef, 50, 32);
                        return;
                    }
                    default: {
                        std::cerr << "From List::draw_clef(F fork): clef type and name dont fit together" << std::endl;
                        return;
                    }
                }
            }
            case 2: {
                switch (static_cast<int>(staff_list[0].get_clef().get_clef_name())) {
                    case 4: {
                        draw_parts(image, images::c_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 3);
                        return;
                    }
                    case 5: {
                        draw_parts(image, images::c_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 4);
                        return;
                    }
                    case 6: {
                        draw_parts(image, images::c_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 5);
                        return;
                    }
                    case 7: {
                        draw_parts(image, images::c_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 6);
                        return;
                    }
                    case 8: {
                        draw_parts(image, images::c_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 7);
                        return;
                    }
                    default: {
                        std::cerr << "From List::draw_clef(C fork): clef type and name dont fit together" << std::endl;
                        return;
                    }
                }
            }
            case 3: {
                switch (static_cast<int>(staff_list[0].get_clef().get_clef_name())) {
                    case 2: {
                        draw_parts(image, images::treble_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 4);
                        return;
                    }
                    case 3: {
                        draw_parts(image, images::treble_clef, cord.clef_cord.first,
                                   cord.clef_cord.second - staff_line_gap * 5);
                        return;
                    }
                    default: {
                        std::cerr << "From List::draw_clef(G fork): clef type and name dont fit together" << std::endl;
                        return;
                    }
                }
            }
            default: {
                std::cerr << "From List::draw_clef: something broken..." << std::endl;
            }
        }
    }

    void List::draw_accidentals(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord &cord) noexcept {
        if (staff_list.size() == 0)
            return;
        if (staff_list[0].get_clef().check_clef()) {
            std::cerr << "from List::draw_accidentals: clef is none or type & name dont fit" << std::endl;
        }
        // Дописать
    }

    void List::draw_time_signature(cimg_library::CImg<unsigned char> &image, hc2img::Staff_cord &cord) noexcept {
        if (staff_list.size() == 0)
            return;

        if (staff_list[0].get_clef().check_clef()) {
            std::cerr << "from List::draw_time_signature: clef is none or type & name dont fit" << std::endl;
        }
        // Дописать
    }

    void List::draw_notes(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) {
        if (staff_list.size() == 0) {
            return;
        }

        for (int x = 0; x < staff_list.size(); ++x) {
            if (staff_list[x].get_clef().check_clef()) {
                std::cerr << "from List::draw_notes(iteration " << x << "): clef is none or type & name dont fit"
                          << std::endl;
                return;
            }
            for (int y = 0; y < staff_list[x].get_note_list_size(); ++y) {
                uint16_t x_gap = staff_edge_gap + 50 + (note_gap * (y + 1));
                uint16_t y_gap = 0;
                int note_place =
                    static_cast<int>(staff_list[x].get_clef().get_place(staff_list[x].get_note(y)) * 2 + 1);
                // std::cout << "note_place: " << note_place << std::endl;
                // std::cout << "y_gap: " << y_gap << std::endl;
                // находим у-координату ноты
                y_gap = cord[x]._1_LINE;
                while (note_place != 0) {
                    // std::cout << "y_gap(in while): " << y_gap << std::endl;
                    if (note_place > 0) {
                        --note_place;
                        y_gap -= staff_line_gap / 2;
                    }
                    if (note_place < 0) {
                        ++note_place;
                        y_gap += staff_line_gap / 2;
                    }
                    if (y_gap < staff_line_gap / 2) {
                        note_place = 0;
                        std::cerr << "from List::draw_notes: note outs from list!" << std::endl;
                    }
                }
                // std::cout << "y_gap(finish): " << y_gap << std::endl;

                // рисуем ноту
                draw_parts(image, images::note, x_gap, y_gap);

                // Рисуем добавочные линейки

                uint16_t start_cord = cord[x]._1_LINE; // координаты первой линии стана
                if (y_gap > start_cord) {
                    while (y_gap > start_cord) {
                        start_cord += staff_line_gap;
                        image.draw_line(
                            /*первая координата*/ x_gap - 5, start_cord,
                            /*вторая координата*/ x_gap + 15, start_cord,
                            /*цвет*/ black);
                    }
                } else if (y_gap < start_cord) {
                    while (y_gap < start_cord) {
                        image.draw_line(
                            /*первая координата*/ x_gap - 5, start_cord,
                            /*вторая координата*/ x_gap + 15, start_cord,
                            /*цвет*/ black);
                        start_cord -= staff_line_gap;
                    }
                }
            }
        }
    }
} // namespace hc2img
