#include <stdexcept>
#include <string>

#include <harmony-core/clef.hpp>
#include <harmony-core/note.hpp>

using namespace harmony_core;

float Clef::get_place(const Note &note) const noexcept {
}

Note Clef::get_note(float line) const noexcept {
}

void Clef::clef_alteration(Note &note, Clef clef) noexcept {
}

std::string Clef::get_name() noexcept {
}
