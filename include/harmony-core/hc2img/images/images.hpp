#pragma once
#ifndef IMAGES_HPP_INCLUDE
#define IMAGES_HPP_INCLUDE

/*! 
 * Данное пространство имен хранит координатные структуры, 
 * возвращающие точки для отрисовки музыкальгых элементов.
 * Каждая структура имеет методы x(int), y(int) и size(), возвращающие точки для отрисовки и количество точек соответственно.
 * Также у нот есть отдельная функция, возвращающая координату для крепления штиля.
 */
 namespace images{
}

#include "accidentals/accidentals.hpp"
#include "clefs/clefs.hpp"
#include "notes/notes.hpp"

#endif // IMAGES_HPP_INCLUDE
