#ifndef HC2IMG_LIST_PARAM
#define HC2IMG_LIST_PARAM
namespace list_param {
    constexpr uint8_t staff_line_gap = 10; // расстояние между линиями стана
    constexpr uint8_t staff_gap = 45; // расстояние между нотными станами
    constexpr uint8_t staff_edge_gap = 60; // расстояние от края до стана

    constexpr uint8_t start_note_gap = 160; // доп. зазор между ключем и первой нотой в стане
    constexpr uint8_t note_gap = 35; // зазор между нотами
    constexpr uint8_t note_stem_length = 30; // длина штиля ноты

    constexpr uint8_t tie_height = 15; // выстоа лиги

    constexpr uint8_t clef_acc_gap = 30; // зазор между ключем и ключевыми знаками
    constexpr uint8_t acc_ts_gap = 80; // зазор между ключевыми знаками и размером

    constexpr unsigned char black[] = {0, 0, 0}; // цвет нот и станов (черный)
    constexpr unsigned char white[] = {255, 255, 255}; // белый цвет

    constexpr uint16_t list_size_x = 1000; // размер листа (х)
    constexpr uint16_t list_size_y = 500; // размер листа (у)

    constexpr float pixel_index = 5; // множитель увеличения пиксельных частей
} // namespace list_param

#endif // HC2IMG_LIST_PARAM
