#ifndef HC2IMG_ACCIDENTALS_DOUBLE_FLAT
#define HC2IMG_ACCIDENTALS_DOUBLE_FLAT
#include <cstdint>
#include <iostream>
#include <vector>

namespace images {
    /*! Хранит опорные точки дубль бемоля */
    extern const struct Double_flat final {
    public:
        size_t size() {
            return 8;
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
                    return 1;
                case 5:
                    return 2;
                case 6:
                    return 2;
                case 7:
                    return 0;
                default: {
                    std::cerr << "From images::Double_flat: incorrect x cord" << std::endl;
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
                    return 0;
                case 4:
                    return 4;
                case 5:
                    return 3;
                case 6:
                    return 2;
                case 7:
                    return 2;
                default: {
                    std::cerr << "From images::Double_flat: incorrect y cord" << std::endl;
                }
            }
            return 1;
        }
    } double_flat;
} // namespace images

#endif // HC2IMG_ACCIDENTALS_DOUBLE_FLAT
