#ifndef HC2IMG_ACCIDENTALS_DOUBLE_SHARP
#define HC2IMG_ACCIDENTALS_DOUBLE_SHARP
#include <cstdint>
#include <iostream>
#include <vector>

namespace images {
    extern const struct Double_sharp final {
    public:
        size_t size() {
            return 5;
        }
        uint8_t x(uint8_t i) {
            switch (i) {
                case 0:
                    return 0;
                case 1:
                    return 2;
                case 2:
                    return 1;
                case 3:
                    return 2;
                case 4:
                    return 0;
                default: {
                    std::cerr << "From images::Double_sharp: incorrect x cord" << std::endl;
                }
            }
            return 1;
        }
        uint8_t y(uint8_t i) {
            switch (i) {
                case 0:
                    return 1;
                case 1:
                    return 3;
                case 2:
                    return 2;
                case 3:
                    return 1;
                case 4:
                    return 3;
                default: {
                    std::cerr << "From images::Double_sharp: incorrect y cord" << std::endl;
                }
            }
            return 1;
        }
    } double_sharp;
} // namespace images

#endif // HC2IMG_ACCIDENTALS_DOUBLE_SHARP
