#include <hc2img/hc2img.hpp>

using namespace hc2img;

List::List(hc2img::Bar *b) {
    // Пока не работает
}

List::List(hc2img::Staff *s) {
    staff = s;
}

void List::save_list() noexcept {
    uint8_t str_index = 0;
    if (staff != nullptr) {
        str_index = staff->get_size() / 8 + 1;
    } else if (staff_system != nullptr) {
        // Не работает
    } else {
        return;
    }

    for (int x = 0; x < str_index; ++x) {
    }
    cimg_library::CImg<unsigned char> output(256, 256, 1, 3, 255);

    output.save("output.jpg");
}
