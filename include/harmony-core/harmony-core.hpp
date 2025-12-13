#ifndef HARMONY_CORE_INCLUDES
#define HARMONY_CORE_INCLUDES

/*!
 * Данное пространство имен хранит основные структуры библиотеки -
 * ноты, интервалы, аккорды, нотные станы. Последний служит контейнером самого высокого уровня. Его можно добавить в
 * hc2img::List для дальнейшей отрисовки его и всех объектов в нем.
 */
namespace harmony_core {}

#include "clef.hpp"
#include "enums.hpp"
#include "interval.hpp"
#include "key.hpp"
#include "note.hpp"
#include "staff.hpp"
#include "time_signature.hpp"

#endif // HARMONY_CORE_INCLUDES
