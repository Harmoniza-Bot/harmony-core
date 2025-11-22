#ifndef HC2IMG_ACCIDENTALS_NATURAL
#define HC2IMG_ACCIDENTALS_NATURAL
#include <cstdint>
#include <iostream>
#include <vector>

namespace images {
    extern const struct Natural final {
    public:
        size_t size() {
            return 6;
        }
        uint8_t x(uint8_t i) {
            switch (i) {
                case 0:
                    return 0;
                case 1:
                    return 1;
                case 2:
                    return 1;
                case 3:
                    return 1;
                case 4:
                    return 0;
                case 5:
                    return 0;
                default: {
                    std::cerr << "From images::Natural: incorrect x cord" << std::endl;
                }
            }
            return 1;
        }
        uint8_t y(uint8_t i) {
            switch (i) {
                case 0:
                    return 2;
                case 1:
                    return 1;
                case 2:
                    return 4;
                case 3:
                    return 2;
                case 4:
                    return 3;
                case 5:
                    return 0;
                default: {
                    std::cerr << "From images::Natural: incorrect y cord" << std::endl;
                }
            }
            return 1;
        }
    } natural;
} // namespace images

#endif // HC2IMG_ACCIDENTALS_NATURAL
