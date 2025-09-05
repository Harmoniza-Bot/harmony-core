#include <hc2img/list.hpp>

namespace hc2img{
    // размеры, кооидинаты и константы
    constexpr uint8_t staff_line_gap = 10;
    constexpr uint8_t staff_gap = 30;
    constexpr uint8_t staff_edge_gap = 33;
    
    constexpr unsigned char black[] = {0, 0, 0};
    
    constexpr uint16_t list_size_x = 1000;
    constexpr uint16_t list_size_y = 500;

    List::List() {
    }
    
    void draw_staff(
        cimg_library::CImg<unsigned char> &image,
        uint16_t mutch
    ) {
        for(int x=0; x<mutch; ++x){
            for(int y=0; y<5; ++y){
                image->draw_line(
                staff_edge_gap,
                staff_edge_gap + y * staff_line_gap + x * staff_gap,
                list_size_x - staff_edge_gap,
                staff_edge_gap + y * staff_line_gap + x * staff_gap,
                black, 1.0f);
            }
        }
    }

    void List::draw() noexcept {

        cimg_library::CImg<unsigned char> image(1000, 500, 1, 3, 255);

      image.save_bmp("img/img.bmp");
        // image.display("winnn");
    }
}