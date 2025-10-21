#include <cstdint>
#include <hc2img/list.hpp>
#include <images/images.hpp>
#include <iostream>

namespace hc2img {

    List::List() {
    }

    void List::add(Staff &s) {
        if (staff_list.size() == 0) {
            staff_list.push_back(s);
            return;
        }
        for (int x = 0; x < staff_list.size(); ++x) {
            if (static_cast<int>(staff_list[x].get_clef().get_type()) <= static_cast<int>(s.get_clef().get_type())) {
                staff_list.insert(staff_list.begin() + x, s);
                return;
            }
        }
        staff_list.push_back(s);
    }

    void List::rm(uint8_t index) {
        if (index < staff_list.size()) {
            return;
        }
        this->staff_list.erase(staff_list.begin() + index);
    }

    void List::save() noexcept {
        cimg_library::CImg<unsigned char> image(list_param::list_size_x, list_param::list_size_y, 1, 3, 255);

        std::vector<hc2img::Staff_cord> s = draw_staffs(image);
        draw_clefs(image, s);
        draw_accidentals(image, s); // нуждается в доработке
        // draw_time_signature(image, s); // нуждается в доработке
        draw_notes(image, s);
        image.display("winnn");

        // image.save_bmp("img/list.bmp");
        // Для сохранения фотки

        // for(int x=0; x<staff_list.size(); ++x){
        //     for(int y=0; y<staff_list[x].get_note_list_size(); ++y){
        //         std::cout << "note index " << y << " in " << x << " staff: " << staff_list[x].get_note(y).second <<
        //         std::endl;
        //     }
        // }
        // Для проверки сортировки нот
    }

    size_t List::size() const noexcept {
        return staff_list.size();
    }

    //================== Приватные функции ==================

    std::vector<hc2img::Staff_cord> List::draw_staffs(cimg_library::CImg<unsigned char> &image) noexcept {
        std::vector<Staff_cord> cords;

        for (int x = 0; x < staff_list.size(); ++x) {
            static Staff_cord cord;
            cords.push_back(cord);
            for (int y = 0; y < 5; ++y) {
                image.draw_line(
                    /*первая координата*/ list_param::staff_edge_gap,
                    list_param::staff_edge_gap + y * list_param::staff_line_gap +
                        (x * (list_param::staff_line_gap * 5 + list_param::staff_gap)),
                    /*вторая координата*/ list_param::list_size_x - list_param::staff_edge_gap,
                    list_param::staff_edge_gap + y * list_param::staff_line_gap +
                        (x * (list_param::staff_line_gap * 5 + list_param::staff_gap)),
                    /*цвет*/ list_param::black);

                static uint16_t cord_y;
                cord_y = list_param::staff_edge_gap + y * list_param::staff_line_gap +
                         (x * (list_param::staff_line_gap * 5 + list_param::staff_gap));
                cords[x]._1_LINE = cord_y;

                cords[x].clef_cord = {list_param::staff_edge_gap, cords[x]._1_LINE};
                cords[x].accidental_cord = {list_param::staff_edge_gap + list_param::clef_acc_gap, cords[x]._1_LINE};
                cords[x].time_signature_cord = {
                    list_param::staff_edge_gap + list_param::clef_acc_gap + list_param::acc_ts_gap, cords[x]._1_LINE};
            }
        }
        return cords;
    }

    template<typename T>
    void List::draw_parts(cimg_library::CImg<unsigned char> &image, T part, int x, int y) {
        for (int a = 0; a < part.size() - 1; ++a) {
            image.draw_line((part.x(a) * list_param::pixel_index) + x, (part.y(a) * list_param::pixel_index) + y,
                            (part.x(a + 1) * list_param::pixel_index) + x,
                            (part.y(a + 1) * list_param::pixel_index) + y, list_param::black);
            image.draw_line((part.x(a) * list_param::pixel_index) + x + 1, (part.y(a) * list_param::pixel_index) + y,
                            (part.x(a + 1) * list_param::pixel_index) + x + 1,
                            (part.y(a + 1) * list_param::pixel_index) + y, list_param::black);
            image.draw_line((part.x(a) * list_param::pixel_index) + x, (part.y(a) * list_param::pixel_index) + y + 1,
                            (part.x(a + 1) * list_param::pixel_index) + x,
                            (part.y(a + 1) * list_param::pixel_index) + y + 1, list_param::black);
            image.draw_line((part.x(a) * list_param::pixel_index) + x + 1,
                            (part.y(a) * list_param::pixel_index) + y + 1,
                            (part.x(a + 1) * list_param::pixel_index) + x + 1,
                            (part.y(a + 1) * list_param::pixel_index) + y + 1, list_param::black);
        }
    }

    void List::draw_clefs(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) noexcept {
        if (staff_list.size() == 0) {
            return;
        }

        for (int x = 0; x < staff_list.size(); ++x) {
            switch (static_cast<int>(staff_list[x].get_clef().get_type())) {
                case 0: {
                    std::cerr << "From List::draw_clef: clef type is NONE!" << std::endl;
                    continue;
                }
                case 1: {
                    switch (static_cast<int>(staff_list[x].get_clef().get_clef_name())) {
                        case 8: {
                            draw_parts(image, images::f_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 6);
                            continue;
                        }
                        case 9: {
                            draw_parts(image, images::f_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 5);
                            continue;
                        }
                        case 10: {
                            draw_parts(image, images::f_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 4);
                            continue;
                        }
                        default: {
                            std::cerr << "From List::draw_clef(F fork): clef type and name dont fit together"
                                      << std::endl;
                            continue;
                        }
                    }
                }
                case 2: {
                    switch (static_cast<int>(staff_list[x].get_clef().get_clef_name())) {
                        case 4: {
                            draw_parts(image, images::c_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 3);
                            continue;
                        }
                        case 5: {
                            draw_parts(image, images::c_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 4);
                            continue;
                        }
                        case 6: {
                            draw_parts(image, images::c_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 5);
                            continue;
                        }
                        case 7: {
                            draw_parts(image, images::c_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 6);
                            continue;
                        }
                        case 8: {
                            draw_parts(image, images::c_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 7);
                            continue;
                        }
                        default: {
                            std::cerr << "From List::draw_clef(C fork): clef type and name dont fit together"
                                      << std::endl;
                            continue;
                        }
                    }
                }
                case 3: {
                    switch (static_cast<int>(staff_list[x].get_clef().get_clef_name())) {
                        case 2: {
                            draw_parts(image, images::treble_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 4);
                            continue;
                        }
                        case 3: {
                            draw_parts(image, images::treble_clef, cord[x].clef_cord.first,
                                       cord[x].clef_cord.second - list_param::staff_line_gap * 5);
                            continue;
                        }
                        default: {
                            std::cerr << "From List::draw_clef(G fork): clef type and name dont fit together"
                                      << std::endl;
                            continue;
                        }
                    }
                }
                default: {
                    std::cerr << "From List::draw_clef: something broken..." << std::endl;
                }
            }
        }
    }

    void List::draw_accidentals(cimg_library::CImg<unsigned char> &image,
                                std::vector<hc2img::Staff_cord> &cord) noexcept {
        if (staff_list.size() == 0) {
            return;
        }
        for (int x = 0; x < staff_list.size(); ++x) {
            if (staff_list[x].get_clef().check_clef()) {
                std::cerr << "from List::draw_accidentals: clef is none or type & name dont fit" << std::endl;
            }
            int acc_index = staff_list[x].get_key();
            int acc_num = 0;
            harmony_core::Key k;
            k.set_step(acc_index);
            std::vector<harmony_core::Note> acc_vector = k.get_accidentals();
            for (int s = 0; s < acc_vector.size(); ++s) {
                if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::C_CLEF) {
                    acc_vector[s].set_octave(harmony_core::Octave::_1_LINE);
                }
                if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::G_CLEF) {
                    acc_vector[s].set_octave(harmony_core::Octave::_2_LINE);
                }
                if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::F_CLEF) {
                    acc_vector[s].set_octave(harmony_core::Octave::SMALL);
                }
            }
            while (acc_index != 0) {
                std::cout << "acc_vector notes: " << acc_vector[acc_num].get_name() << std::endl;
                if (acc_index > 0) {
                    --acc_index;
                    draw_parts(
                        image, images::sharp, cord[x].accidental_cord.first + acc_num * list_param::staff_line_gap,
                        cord[x].accidental_cord.second -
                            staff_list[x].get_clef().get_place(acc_vector[acc_index]) * list_param::staff_line_gap);
                }
                if (acc_index < 0) {
                    ++acc_index;
                    draw_parts(
                        image, images::flat, cord[x].accidental_cord.first + acc_num * list_param::staff_line_gap,
                        cord[x].accidental_cord.second -
                            staff_list[x].get_clef().get_place(acc_vector[acc_index]) * list_param::staff_line_gap);
                }
                ++acc_num;
            }
            std::cout << std::endl;
        }
    }

    void List::draw_time_signature(cimg_library::CImg<unsigned char> &image,
                                   std::vector<hc2img::Staff_cord> &cord) noexcept {
        if (staff_list.size() == 0)
            return;

        if (staff_list[0].get_clef().check_clef()) {
            std::cerr << "from List::draw_time_signature: clef is none or type & name dont fit" << std::endl;
        }
        for (int x = 0; x < cord.size(); ++x) {
            image.draw_text(cord[x].time_signature_cord.first, cord[x].time_signature_cord.second, "4",
                            list_param::black, list_param::white, 0.5f, 40);
        }
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
                // В этих переменных хранятся переменные прошлых нот
                static int past_note_height;
                static uint16_t past_note_index;
                static uint8_t add_gap = 0;

                // Получаем место ноты на нотном стане
                int note_place =
                    static_cast<int>(staff_list[x].get_clef().get_place(staff_list[x].get_note(y).first) * 2 + 1);

                // Проверяем, нужен ли доп. зазор между соседних нот
                if (y != 0) {
                    if (past_note_index == staff_list[x].get_note(y).second) {
                        if (past_note_height == note_place || past_note_height - note_place == -1 ||
                            past_note_height - note_place == 1) {
                            add_gap = 10;
                        }
                    } else {
                        add_gap = 0;
                    }
                }

                past_note_height = note_place;
                past_note_index = staff_list[x].get_note(y).second;

                uint16_t x_gap = list_param::staff_edge_gap + list_param::start_note_gap +
                                 (staff_list[x].get_note(y).second * list_param::note_gap) + add_gap;

                uint16_t y_gap = 0;

                // находим у-координату ноты
                y_gap = cord[x]._1_LINE;
                while (note_place != 0) {
                    if (note_place > 0) {
                        --note_place;
                        y_gap -= list_param::staff_line_gap / 2;
                    }
                    if (note_place < 0) {
                        ++note_place;
                        y_gap += list_param::staff_line_gap / 2;
                    }
                    if (y_gap < list_param::staff_line_gap / 2) {
                        note_place = 0;
                        std::cerr << "from List::draw_notes: note outs from list!" << std::endl;
                    }
                }

                // рисуем ноту
                draw_parts(image, images::note, x_gap, y_gap);

                // Рисуем добавочные линейки

                uint16_t start_cord = cord[x]._1_LINE; // координаты первой линии стана
                if (y_gap > start_cord) {
                    while (y_gap > start_cord) {
                        start_cord += list_param::staff_line_gap;
                        image.draw_line(
                            /*первая координата*/ x_gap - 5, start_cord,
                            /*вторая координата*/ x_gap + 15, start_cord,
                            /*цвет*/ list_param::black);
                    }
                } else if (y_gap < start_cord) {
                    while (y_gap < start_cord) {
                        image.draw_line(
                            /*первая координата*/ x_gap - 5, start_cord,
                            /*вторая координата*/ x_gap + 15, start_cord,
                            /*цвет*/ list_param::black);
                        start_cord -= list_param::staff_line_gap;
                    }
                }
            }
        }
    }
} // namespace hc2img
