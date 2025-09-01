#include <hc2img/list.hpp>

using namespace hc2img;

List::List() {
}

void List::save() noexcept {

    cimg_library::CImg<unsigned char> image(1000, 480, 1, 3, 255);

    // Define the color red
    const unsigned char black[] = {0, 0, 0};

    // Draw a line from (100, 100) to (500, 300) with red color and full opacity
    image.draw_line(33, 33, 970, 33, black, 1.0f);
    image.draw_line(33, 43, 970, 43, black, 1.0f);
    image.draw_line(33, 53, 970, 53, black, 1.0f);
    image.draw_line(33, 63, 970, 63, black, 1.0f);
    image.draw_line(33, 73, 970, 73, black, 1.0f);

    image.save_bmp("img/img.bmp");
    // image.display("winnn");
}
