#include <hc2img/hc2img.hpp>

using namespace hc2img;

void Staff::add(Bar *bar) noexcept {
    staff_list.push_back(bar);
}

void Staff::remove(uint8_t index) noexcept {
    if (staff_list.size() < index) {
        return;
    }
    std::erase(staff_list, staff_list[index]);
}

size_t Staff::get_size() const noexcept {
    return staff_list.size();
}
