#include <harmony-core/document.hpp>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
using namespace harmony_core;

// Сайт для теста https://inf-schule.de/tools/music-xml-viewer

// ============================================================================
// ВСПУМОГАТЕЛЬНЫЕ СТРУКТУРЫ ДАННЫХ
// ============================================================================

/**
 * @brief Структура для внутренней сортировки и сборки полифонии внутри такта.
 * Хранит копию ноты, её временной маркер и исходную позицию в плоском векторе.
 */
struct TrackNote {
    harmony_core::Note note;     ///< Музыкальная нота со всеми флагами альтерации и длительности
    uint16_t time_index;         ///< Временной индекс (номер тактовой доли/позиции на стане)
    size_t original_index;       ///< Исходный порядковый индекс ноты в векторе Staff::note_list
};


// ============================================================================
// ВСПУМОГАТЕЛЬНЫЕ ФУНКЦИИ-МАППЕРЫ (МЕТОДЫ ОПРЕДЕЛЕНИЯ ФОРМАТА XML)
// ============================================================================

/**
 * @brief Конвертирует основание ноты из внутреннего битового перечисления в формат буквы MusicXML.
 * @param base Перечисление Base (C, D, E, F, G, A, B)
 * @return std::string Строковое представление базовой ноты (например, "C", "D")
 */
static std::string base_to_xml(harmony_core::Base base) {
    switch (base) {
        case harmony_core::Base::C: return "C";
        case harmony_core::Base::D: return "D";
        case harmony_core::Base::E: return "E";
        case harmony_core::Base::F: return "F";
        case harmony_core::Base::G: return "G";
        case harmony_core::Base::A: return "A";
        case harmony_core::Base::B: return "B";
    }
    return "C";
}

/**
 * @brief Возвращает числовой сдвиг полутонов для тега <alter>.
 * @param acc Знак альтерации ноты Accidental
 * @return std::string Строка с числовым значением от "-2" до "2"
 */
static std::string accidental_to_alter_value(harmony_core::Accidental acc) {
    switch (acc) {
        case harmony_core::Accidental::DOUBLE_FLAT:  return "-2";
        case harmony_core::Accidental::FLAT:         return "-1";
        case harmony_core::Accidental::SHARP:        return "1";
        case harmony_core::Accidental::DOUBLE_SHARP: return "2";
        default:                                     return "0"; // Бемоли и бекары не сдвигают полутон относительно знаков
    }
}

/**
 * @brief Возвращает текстовое имя длительности ноты в соответствии со спецификацией MusicXML.
 * @param dur Длительность ноты Duration
 * @return std::string Название типа ноты (например, "whole", "half", "quarter", "16th")
 */
static std::string duration_to_xml_type(harmony_core::Duration dur) {
    switch (dur) {
        case harmony_core::Duration::DOUBLE:        return "breve";
        case harmony_core::Duration::WHOLE:         return "whole";
        case harmony_core::Duration::HALF:          return "half";
        case harmony_core::Duration::QUARTER:       return "quarter";
        case harmony_core::Duration::EIGHTH:        return "eighth";
        case harmony_core::Duration::SIXTEENTH:     return "16th";
        case harmony_core::Duration::THIRTY_SECOND: return "32nd";
        case harmony_core::Duration::SIXTY_FOURTH:  return "64th";
    }
    return "quarter";
}

/**
 * @brief Вычисляет абсолютную длительность ноты в системных делениях (divisions).
 * Для обеспечения поддержки мелких длительностей без дробей базовая единица (divisions) зафиксирована как 16.
 * @param dur Длительность ноты Duration
 * @return int Количество системных квантов времени для тега <duration>
 */
static int duration_to_xml_value(harmony_core::Duration dur) {
    switch (dur) {
        case harmony_core::Duration::DOUBLE:        return 128; // Двойная целая нота
        case harmony_core::Duration::WHOLE:         return 64;  // Целая нота
        case harmony_core::Duration::HALF:          return 32;  // Половинная нота
        case harmony_core::Duration::QUARTER:       return 16;  // Четвертная нота
        case harmony_core::Duration::EIGHTH:        return 8;   // Восьмая нота
        case harmony_core::Duration::SIXTEENTH:     return 4;   // Шестнадцатая нота
        case harmony_core::Duration::THIRTY_SECOND: return 2;   // Тридцать вторая нота
        case harmony_core::Duration::SIXTY_FOURTH:  return 1;   // Шестьдесят четвертая нота
    }
    return 16;
}

/**
 * @brief Переводит внутренний музыкальный ключ во фронтальные теги знака и линии для MusicXML.
 * @param clef Объект музыкального ключа Clef
 * @return std::pair<std::string, std::string> Пара {"Знак_Ключа", "Номер_Линии_Стана"}
 */
static std::pair<std::string, std::string> clef_to_xml(harmony_core::Clef clef) {
    switch (clef.get_clef_name()) {
        case harmony_core::Clef_name::BASS:
        case harmony_core::Clef_name::SUBBASS:
            return {"F", "4"}; // Басовый ключ на 4-й линии
        case harmony_core::Clef_name::ALTO:
            return {"C", "3"}; // Альтовый ключ на 3-й линии
        case harmony_core::Clef_name::TENOR:
            return {"C", "4"}; // Теноровый ключ на 4-й линии
        case harmony_core::Clef_name::NEUTRAL:
            return {"percussion", "3"}; // Ударный ключ
        case harmony_core::Clef_name::TABULATURE:
            return {"TAB", "5"}; // Гитарная табулатура
        default:
            return {"G", "2"}; // Скрипичный ключ на 2-й линии (по умолчанию)
    }
}

std::string Document::get_musicxml() const noexcept{
    std::string ans = R"(<?xml version="1.0" encoding="UTF-8" standalone="no"?>
<!DOCTYPE score-partwise PUBLIC "-//Recordare//DTD MusicXML 4.0 Partwise//EN" "http://musicxml.org">
<score-partwise version="4.0">)";

    ans += "\n  <work>\n    <work-title>" + name + "</work-title>\n  </work>\n";
    ans += "  <part-list>\n    <score-part id=\"P1\">\n      <part-name>" + staffs_name + "</part-name>\n    </score-part>\n  </part-list>\n  <part id=\"P1\">\n";

    uint16_t max_time_index = 0;
    for (const auto& staff : staffs) {
        for (size_t i = 0; i < staff.get_size(); ++i) {
            max_time_index = std::max(max_time_index, staff.get_note(static_cast<uint16_t>(i)).second);
        }
    }

    int total_measures = max_time_index;
    if (total_measures == 0) total_measures = 1;

    for (int bar_num = 1; bar_num <= total_measures; ++bar_num) {
        ans += "    <measure number=\"" + std::to_string(bar_num) + "\">\n";

        if (bar_num == 1 && !staffs.empty()) {
            ans += "      <attributes>\n";
            ans += "        <divisions>16</divisions>\n";
            ans += "        <key>\n          <fifths>" + std::to_string(staffs[0].get_key()) + "</fifths>\n        </key>\n";

            harmony_core::Time_signature ts = staffs[0].get_time_signature();
            ans += "        <time>\n";
            ans += "          <beats>" + std::to_string(ts.get_numerator()) + "</beats>\n";
            ans += "          <beat-type>" + std::to_string(ts.get_denominator()) + "</beat-type>\n";
            ans += "        </time>\n";

            ans += "        <staves>2</staves>\n";

            auto clef1 = clef_to_xml(staffs[0].get_clef());
            ans += "        <clef number=\"1\">\n";
            ans += "          <sign>" + clef1.first + "</sign>\n";
            ans += "          <line>" + clef1.second + "</line>\n";
            ans += "        </clef>\n";

            auto clef2 = (staffs.size() > 1) ? clef_to_xml(staffs[1].get_clef()) : std::pair<std::string,std::string>{"F", "4"};
            ans += "        <clef number=\"2\">\n";
            ans += "          <sign>" + clef2.first + "</sign>\n";
            ans += "          <line>" + clef2.second + "</line>\n";
            ans += "        </clef>\n";

            ans += "      </attributes>\n";
        }

        for (size_t x = 0; x < staffs.size(); ++x) {
            const auto& current_staff = staffs[x];
            int staff_id = static_cast<int>(x) + 1;

            std::vector<TrackNote> measure_notes;
            for (size_t i = 0; i < current_staff.get_size(); ++i) {
                auto p = current_staff.get_note(static_cast<uint16_t>(i));
                if (p.second == bar_num) {
                    measure_notes.push_back({p.first, p.second, i});
                }
            }

            if (measure_notes.empty()) continue;

            std::map<int, std::vector<TrackNote>> voices;

            for (const auto& tn : measure_notes) {
                int target_voice = 1;
                while (true) {
                    bool slot_busy = false;
                    for (const auto& existing_note : voices[target_voice]) {
                        if (existing_note.time_index == tn.time_index) {
                            slot_busy = true;
                            break;
                        }
                    }
                    if (!slot_busy) {
                        voices[target_voice].push_back(tn);
                        break;
                    }
                    target_voice++;
                }
            }

            size_t voice_count = 0;
            for (const auto& [voice_id, notes] : voices) {
                if (voice_count > 0) {
                    int total_duration_to_backup = 0;
                    for (const auto& prev_note : voices.at(1)) {
                        total_duration_to_backup += duration_to_xml_value(prev_note.note.get_duration());
                    }
                    if (total_duration_to_backup > 0) {
                        ans += "      <backup>\n";
                        ans += "        <duration>" + std::to_string(total_duration_to_backup) + "</duration>\n";
                        ans += "      </backup>\n";
                    }
                }
                voice_count++;

                for (const auto& item : notes) {
                    ans += "      <note>\n";

                    if (item.note.is_pause()) {
                        ans += "        <rest/>\n";
                    } else {
                        ans += "        <pitch>\n";
                        ans += "          <step>" + base_to_xml(item.note.get_base()) + "</step>\n";
                        ans += "          <octave>" + std::to_string(static_cast<int>(item.note.get_octave())) + "</octave>\n";
                        if (item.note.get_accidental() != harmony_core::Accidental::UNDEFINED &&
                            item.note.get_accidental() != harmony_core::Accidental::NATURAL) {
                            ans += "          <alter>" + accidental_to_alter_value(item.note.get_accidental()) + "</alter>\n";
                        }
                        ans += "        </pitch>\n";
                    }

                    ans += "        <duration>" + std::to_string(duration_to_xml_value(item.note.get_duration())) + "</duration>\n";
                    ans += "        <voice>" + std::to_string(voice_id + (staff_id - 1) * 2) + "</voice>\n";
                    ans += "        <type>" + duration_to_xml_type(item.note.get_duration()) + "</type>\n";
                    ans += "        <staff>" + std::to_string(staff_id) + "</staff>\n";

                    int tied_with = current_staff.is_tie(static_cast<uint16_t>(item.original_index));
                    if (tied_with != -1) {
                        if (static_cast<int>(item.original_index) < tied_with) {
                            ans += "        <tie type=\"start\"/>\n";
                            ans += "        <notations><tied type=\"start\"/></notations>\n";
                        } else {
                            ans += "        <tie type=\"stop\"/>\n";
                            ans += "        <notations><tied type=\"stop\"/></notations>\n";
                        }
                    }

                    ans += "      </note>\n";
                }
            }

            if (x == 0 && staffs.size() > 1) {
                int measure_total_duration = 0;
                if (voices.count(1)) {
                    for (const auto& v_note : voices.at(1)) {
                        measure_total_duration += duration_to_xml_value(v_note.note.get_duration());
                    }
                }
                if (measure_total_duration > 0) {
                    ans += "      <backup>\n";
                    ans += "        <duration>" + std::to_string(measure_total_duration) + "</duration>\n";
                    ans += "      </backup>\n";
                }
            }
        }

        ans += "    </measure>\n";
    }

    ans += "  </part>\n";
    ans += "</score-partwise>\n";
    return ans;
}

