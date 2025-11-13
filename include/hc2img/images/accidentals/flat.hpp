#ifndef HC2IMG_ACCIDENTALS_FLAT
#define HC2IMG_ACCIDENTALS_FLAT
#include <cstdint>
#include <iostream>
#include <vector>

namespace images {
    extern const struct Flat final {
    public:
        size_t size() {
            return 5;
        }
        uint8_t x(uint8_t i) {
            switch (i) {
                case 0:
                    return 0;
                case 1:
                    return 0;
                case 2:
                    return 1;
                case 3:
                    return 1;
                case 4:
                    return 0;
                default: {
                    std::cerr << "From images::Flat: incorrect x cord" << std::endl;
                }
            }
            return 1;
        }
        uint8_t y(uint8_t i) {
            switch (i) {
                case 0:
                    return 0;
                case 1:
                    return 4;
                case 2:
                    return 3;
                case 3:
                    return 2;
                case 4:
                    return 2;
                default: {
                    std::cerr << "From images::Flat: incorrect y cord" << std::endl;
                }
            }
            return 1;
        }
    } flat;
} // namespace images

#endif // HC2IMG_ACCIDENTALS_FLAT
