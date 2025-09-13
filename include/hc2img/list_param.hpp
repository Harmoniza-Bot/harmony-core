#ifndef HC2IMG_LIST_PARAM
#define HC2IMG_LIST_PARAM

constexpr uint8_t staff_line_gap = 10; // расстояние между линиями стана
constexpr uint8_t staff_gap = 30; // расстояние между нотными станами
constexpr uint8_t staff_edge_gap = 33; // расстояние от края до стана

constexpr uint8_t note_gap = 25; // зазор между нотами
constexpr uint8_t note_length = 12; // длина ноты
constexpr uint8_t note_stem_length = 30; // длина шниля ноты

constexpr unsigned char black[] = {0, 0, 0}; // цвет нот и станов (черный)

constexpr uint16_t list_size_x = 1000; // размер листа (х)
constexpr uint16_t list_size_y = 500; // размер листа (у)

constexpr float treble_clef_index = 0.18; // коэфициент сжатия скрипичного ключа

#endif // HC2IMG_LIST_PARAM
