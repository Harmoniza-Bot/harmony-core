#ifndef HC2IMG_ACCIDENTALS_SHARP
#define HC2IMG_ACCIDENTALS_SHARP
#include <cstdint>
#include <iostream>
#include <vector>

namespace images {
    extern const struct Sharp final {
    public:
        size_t size() {
            return 11;
        }
        uint8_t x(uint8_t i) {
            switch (i) {
                case 0:
                    return 0;
                case 1:
                    return 3;
                case 2:
                    return 2;
                case 3:
                    return 2;
                case 4:
                    return 2;
                case 5:
                    return 2;
                case 6:
                    return 3;
                case 7:
                    return 0;
                case 8:
                    return 1;
                case 9:
                    return 1;
                case 10:
                    return 1;
                default: {
                    std::cerr << "From images::Sharp: incorrect x cord" << std::endl;
                }
            }
            return 1;
        }
        uint8_t y(uint8_t i) {
            switch (i) {
                case 0:
                    return 3;
                case 1:
                    return 0;
                case 2:
                    return 1;
                case 3:
                    return 0;
                case 4:
                    return 4;
                case 5:
                    return 2;
                case 6:
                    return 1;
                case 7:
                    return 4;
                case 8:
                    return 3;
                case 9:
                    return 4;
                case 10:
                    return 0;
                default: {
                    std::cerr << "From images::Sharp: incorrect y cord" << std::endl;
                }
            }
            return 1;
        }
    } sharp;
} // namespace images

#endif // HC2IMG_ACCIDENTALS_SHARP
