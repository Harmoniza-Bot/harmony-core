#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "clef.hpp"
#include "enums.hpp"
#include "interval.hpp"
#include "key.hpp"
#include "note.hpp"
#include "staff.hpp"
#include "time_signature.hpp"

#include <string>

namespace harmony_core{

/*!
 * Данная структура представляет документ, в который группируются нотные станы.
 * Предназначен для конвертации нот в другие форматы (в первую очередь musicXML).
 */
    struct Document final {

    public:

        /*!
         * Создает нотный лист
         */
        Document() = default;

        /*! \brief Возвращает содержимое структуры в формате musicxml
         */
        std::string get_musicxml() const noexcept;

        /*!
        * Хранит название произведения.
        */
        std::string name = "harmony_core document";

        /*!
         * \brief Хранит подпись перед нотными станами.
         */
        std::string staffs_name = "Music";

        /*!
        * Хранит нотные станы.
        */
        std::vector<harmony_core::Staff> staffs;
    };
}

#endif // DOCUMENT_HPP
