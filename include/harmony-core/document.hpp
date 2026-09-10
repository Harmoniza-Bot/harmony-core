#ifndef DOCUMENT_HPP
#define DOCUMENT_HPP

#include "clef.hpp"
#include "enums.hpp"
#include "interval.hpp"
#include "key.hpp"
#include "note.hpp"
#include "staff.hpp"
#include "time_signature.hpp"
#include "document.hpp"

#include <string>

namespace harmony_core{

/*!
 * Данный класс представляет документ, в который помещаются нотные станы, ключи, ноты и тд.
 * Предназначен для конвертации нот в другие форматы (в первую очередь musicXML и abc).
 */
    class Document final {


    public:
        // Здесь должны храниться функции конвертирования в musicxml и abc
    private:
        /*!
        * Хранит название произведения.
        */
        std::string name;

        /*!
        * Хранит нотные станы.
        */
        std::vector<harmony_core::Staff> staff_list;
    }
}

#endif // DOCUMENT_HPP
