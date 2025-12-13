#include <hc2img/images/images.hpp>
#include <hc2img/list.hpp>
#include <hc2img/list_param.hpp>
namespace hc2img {

    List::List() {
    }

    void List::add(harmony_core::Staff &s) {
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
        draw_accidentals(image, s);
        draw_time_signature(image, s);
        s = draw_staffs(image);
        draw_notes(image, s);
        draw_bar(image, s);
        draw_tie(image, s);
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
                cords[x].time_signature_cord = {list_param::staff_edge_gap + list_param::clef_acc_gap +
                                                    list_param::acc_ts_gap,
                                                cords[x]._1_LINE - list_param::staff_line_gap * 2};
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

    // Данная реализация функции рисует квадратную лигу. Новая реализация использует сплайн
    // void List::draw_tie(cimg_library::CImg<unsigned char> &image, std::pair<uint16_t, uint16_t> start,
    //               std::pair<uint16_t, uint16_t> finish, bool direction) {
    //     if (direction) {
    //         image.draw_line(
    //             /*первая координата*/ start.first, start.second,
    //             /*вторая координата*/ start.first - list_param::tie_height, start.second - list_param::tie_height,
    //             /*цвет*/ list_param::black);
    //         image.draw_line(
    //             /*первая координата*/ start.first - list_param::tie_height, start.second - list_param::tie_height,
    //             /*вторая координата*/ finish.first - list_param::tie_height, finish.second - list_param::tie_height,
    //             /*цвет*/ list_param::black);
    //         image.draw_line(
    //             /*первая координата*/ finish.first + list_param::tie_height, finish.second + list_param::tie_height,
    //             /*вторая координата*/ finish.first, finish.second,
    //             /*цвет*/ list_param::black);
    //     } else {
    //         image.draw_line(
    //             /*первая координата*/ start.first, start.second,
    //             /*вторая координата*/ start.first + list_param::tie_height, start.second + list_param::tie_height,
    //             /*цвет*/ list_param::black);
    //         image.draw_line(
    //             /*первая координата*/ start.first + list_param::tie_height, start.second + list_param::tie_height,
    //             /*вторая координата*/ finish.first + list_param::tie_height, finish.second + list_param::tie_height,
    //             /*цвет*/ list_param::black);
    //         image.draw_line(
    //             /*первая координата*/ finish.first + list_param::tie_height, finish.second + list_param::tie_height,
    //             /*вторая координата*/ finish.first, finish.second,
    //             /*цвет*/ list_param::black);
    //     }
    // }


    void List::draw_tie(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) {
        for (int x = 0; x < staff_list.size(); ++x) {

            std::vector<std::pair<uint16_t, uint16_t>> tie_list;

            for (int y = 0; y < staff_list[x].tie_size(); ++y) {
                tie_list.push_back(staff_list[x].get_tie(y));
            }

            // вектора, ответственные за изгиб лиги.
            // один из векторов изгибает стартовую точку в одну сторону,
            // другой вектор - конечную инвертированно
            // (чтобы оба изгибали в одну сторону нужно сделать векторы равными +- число для изгиба)
            int start_vector = -50;
            int finish_vector = 50;

            // Получаем количество знаков
            int acc_size = staff_list[x].get_key();
            if (acc_size < 0) {
                acc_size = -acc_size;
            }

            int x_cord_last_acc = list_param::staff_edge_gap + // расстояние до стана
                                  (list_param::pixel_index * 5) + // примерный размер ключа
                                  (acc_size * list_param::staff_line_gap) + // примерный общий размер знаков
                                  20; // зазор между ключевыми знаками и размером.
            // Почему-то из list_param берется неправильно

            for (int y = 0; y < tie_list.size(); ++y) {

                int first_x_cord =
                    x_cord_last_acc + (staff_list[x].get_note(tie_list[y].first).second * list_param::note_gap);

                int second_x_cord =
                    x_cord_last_acc + (staff_list[x].get_note(tie_list[y].second).second * list_param::note_gap);

                int first_y_cord = cord[x]._1_LINE;
                int second_y_cord = cord[x]._1_LINE;

                // Получаем место ноты на нотном стане
                int note_place = static_cast<int>(
                    staff_list[x].get_clef().get_place(staff_list[x].get_note(tie_list[y].first).first) * 2 + 1);

                if (note_place < 1) {
                    start_vector = 50;
                    finish_vector = -50;
                    first_y_cord += 10;
                    second_y_cord += 10;
                } else {
                    start_vector = -50;
                    finish_vector = 50;
                }

                while (note_place != 0) {
                    if (note_place > 0) {
                        --note_place;
                        first_y_cord -= list_param::staff_line_gap / 2;
                    }
                    if (note_place < 0) {
                        ++note_place;
                        first_y_cord += list_param::staff_line_gap / 2;
                    }
                    if (first_y_cord < list_param::staff_line_gap / 2) {
                        note_place = 0;
                        std::cerr << "from List::draw_tie: note outs from list!" << std::endl;
                    }
                }
                note_place = static_cast<int>(
                    staff_list[x].get_clef().get_place(staff_list[x].get_note(tie_list[y].second).first) * 2 + 1);

                while (note_place != 0) {
                    if (note_place > 0) {
                        --note_place;
                        second_y_cord -= list_param::staff_line_gap / 2;
                    }
                    if (note_place < 0) {
                        ++note_place;
                        second_y_cord += list_param::staff_line_gap / 2;
                    }
                    if (second_y_cord < list_param::staff_line_gap / 2) {
                        note_place = 0;
                        std::cerr << "from List::draw_tie: note outs from list!" << std::endl;
                    }
                }
                // Теперь мы имеем пару координат,
                // в которые нужно нарисовать лигу.

                image.draw_spline(first_x_cord, first_y_cord,
                                  0, // хз, что это
                                  start_vector, second_x_cord, second_y_cord,
                                  0, // хз, что это
                                  finish_vector, list_param::black);
            }
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
            static harmony_core::Key k;
            k.set_step(acc_index);
            std::vector<harmony_core::Note> acc_vector = k.get_accidentals();

            // Данный фрагмент принудительно меняет октаву знака.
            // Не требуется, тк алгоритм меняет октавы в зависимости от позиции знака на нотном стане.
            // for (int s = 0; s < acc_vector.size(); ++s) {
            //     if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::C_CLEF) {
            //         acc_vector[s].set_octave(harmony_core::Octave::SMALL);
            //     }
            //     if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::G_CLEF) {
            //         acc_vector[s].set_octave(harmony_core::Octave::_2_LINE);
            //     }
            //     if (staff_list[x].get_clef().get_type() == harmony_core::Clef_type::F_CLEF) {
            //         acc_vector[s].set_octave(harmony_core::Octave::SMALL);
            //     }
            // }

            while (acc_index != 0) {
                // std::cout << "acc_vector notes: " << acc_vector[acc_num].get_name() << std::endl;
                if (acc_index > 0) {
                    --acc_index;
                    int y_cord = cord[x].accidental_cord.second - list_param::staff_line_gap -
                                 staff_list[x].get_clef().get_place(acc_vector[acc_num]) * list_param::staff_line_gap;
                    if (y_cord > cord[x]._1_LINE - list_param::staff_line_gap * 1.5) {
                        y_cord -= list_param::staff_line_gap * 3 + list_param::staff_line_gap / 2;
                    }
                    if (y_cord < cord[x]._1_LINE - list_param::staff_line_gap * 5) {
                        y_cord += list_param::staff_line_gap * 3 + list_param::staff_line_gap / 2;
                    }
                    draw_parts(image, images::sharp,
                               cord[x].accidental_cord.first + acc_num * list_param::staff_line_gap, y_cord);
                }
                if (acc_index < 0) {
                    ++acc_index;
                    int y_cord = cord[x].accidental_cord.second - list_param::staff_line_gap * 1.5 -
                                 staff_list[x].get_clef().get_place(acc_vector[acc_num]) * list_param::staff_line_gap;
                    if (y_cord > cord[x]._1_LINE - list_param::staff_line_gap * 2.5) {
                        y_cord -= list_param::staff_line_gap * 3 + list_param::staff_line_gap / 2;
                    }
                    if (y_cord < cord[x]._1_LINE - list_param::staff_line_gap * 5) {
                        y_cord += list_param::staff_line_gap * 3 + list_param::staff_line_gap / 2;
                    }
                    draw_parts(image, images::flat,
                               cord[x].accidental_cord.first + acc_num * list_param::staff_line_gap, y_cord);
                }
                ++acc_num;
            }
            // std::cout << std::endl;
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

            // Получаем количество знаков
            int acc_size = staff_list[x].get_key();
            if (acc_size < 0) {
                acc_size = -acc_size;
            }

            int x_cord_last_acc = list_param::staff_edge_gap + // расстояние до стана
                                  (list_param::pixel_index * 5) + // примерный размер ключа
                                  (acc_size * list_param::staff_line_gap) + // примерный общий размер знаков
                                  20; // зазор между ключевыми знаками и размером.
                                      // Почему-то из list_param берется неправильно

            // Получаем числитель в виде строки
            std::string num = std::to_string(staff_list[x].get_time_signature().get_numerator());
            // Получаем знаменатель в виде строки
            std::string den = std::to_string(staff_list[x].get_time_signature().get_denominator());

            // Рисуем))
            image.draw_text(x_cord_last_acc, cord[x].time_signature_cord.second, den.c_str(), list_param::black,
                            list_param::white, 1.0f, 30);

            // Числитель рисуется выше знаменателья на 3 линейки
            image.draw_text(x_cord_last_acc, cord[x].time_signature_cord.second - list_param::staff_line_gap * 3,
                            num.c_str(), list_param::black, list_param::white, 1.0f, 30);
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

            // Хранир информацию, является ли залигованная нот началом лиги или концом
            bool tie_flag = 0;

            // Стартовые координаты лиги
            std::pair<int, int> start_tie;

            for (int y = 0; y < staff_list[x].get_note_list_size(); ++y) {
                // В этих переменных хранятся переменные прошлых нот
                static int past_note_height;
                static uint16_t past_note_index;
                uint8_t add_gap = 0;

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

                // Получаем количество знаков
                int acc_size = staff_list[x].get_key();
                if (acc_size < 0) {
                    acc_size = -acc_size;
                }

                int x_cord_last_acc = list_param::staff_edge_gap + // расстояние до стана
                                      (list_param::pixel_index * 5) + // примерный размер ключа
                                      (acc_size * list_param::staff_line_gap) + // примерный общий размер знаков
                                      20; // зазор между ключевыми знаками и размером.
                // Почему-то значение из list_param берется неправильно, поэтому mag-val 20.

                uint16_t x_gap = x_cord_last_acc + (staff_list[x].get_note(y).second * list_param::note_gap) + add_gap;

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

                // рисуем ноту (закрашенную или не закрашенную)
                if (static_cast<int>(staff_list[x].get_note(y).first.get_duration()) > 2) {
                    draw_parts(image, images::note_1, x_gap, y_gap);
                } else {
                    draw_parts(image, images::note, x_gap, y_gap);
                }

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

    void List::draw_bar(cimg_library::CImg<unsigned char> &image, std::vector<hc2img::Staff_cord> cord) {
        if (staff_list.size() == 0) {
            return;
        }

        for (int x = 0; x < staff_list.size(); ++x) {
            if (staff_list[x].get_clef().check_clef()) {
                std::cerr << "from List::draw_bar(iteration " << x << "): clef is none or type & name dont fit"
                          << std::endl;
                return;
            }
            for (int y = 0; y < staff_list[x].get_note_list_size(); ++y) {
                if (staff_list[x].is_bar(staff_list[x].get_note(y).second)) {
                    uint16_t x_bar = list_param::staff_edge_gap + list_param::start_note_gap +
                                     (staff_list[x].get_note(y).second * list_param::note_gap) +
                                     (list_param::note_gap / 1.2);


                    image.draw_line(
                        /*первая координата*/ x_bar, cord[x]._1_LINE,
                        /*вторая координата*/ x_bar, cord[x]._1_LINE - list_param::staff_line_gap * 4,
                        /*цвет*/ list_param::black);
                }
            }
        }
    }
} // namespace hc2img
