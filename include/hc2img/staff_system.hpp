#ifndef HC2IMG_STAFF_SYSTEM
#define HC2IMG_STAFF_SYSTEM

#include <cstdint>

#include <harmony-core/harmony-core.hpp>
#include "staff.hpp"

namespace hc2img {
    /*!
     * \brief Может объединить несколько нотных станов в одну систему.
     * Возможно изменить окколаду.
     * (Для функционирования интерфейса необходимо подключить библиотеку CImg.h)
     */
    struct Staff_system final {

    private:
        std::vector<Staff *> staffs;
    };
} // namespace hc2img

#endif // HC2IMG_STAFF_SYSTEM
