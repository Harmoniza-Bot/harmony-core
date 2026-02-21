#include <harmony-core/note.hpp>
#include <iostream>
#include <stdexcept>
#include <string>
#include <cctype>

using namespace harmony_core;

Note::Note() noexcept : Note(Base::C, Octave::_1_LINE, Accidental::NATURAL, Accidental::UNDEFINED, Duration::WHOLE) {
}

Note::Note(const Base base, const Octave octave, const Accidental key_accidental, Accidental const random_accidental,
           const Duration duration) noexcept : data(0) {
    set_base(base);
    set_octave(octave);
    set_key_accidental(key_accidental);
    set_random_accidental(random_accidental);
    set_duration(duration);
}

Note::Note(const uint_fast16_t data) noexcept : data(data) {
}

Note::Note(const Note &note) noexcept : Note(note.data) {
}

void Note::set_data(const uint_fast16_t data) noexcept {
    this->data = data;
}

uint_fast16_t Note::get_data() const noexcept {
    return data;
}

void Note::set_base(Base base) noexcept {
    data = data & 0xFFF8 | static_cast<uint_fast16_t>(base);
}

Base Note::get_base() const noexcept {
    return static_cast<Base>(data & 0x7);
}

void Note::set_octave(Octave octave) noexcept {
    data = data & 0xFF87 | (static_cast<uint_fast16_t>(octave) << 3);
}

Octave Note::get_octave() const noexcept {
    return static_cast<Octave>((data & 0x78) >> 3);
}

void Note::set_key_accidental(Accidental accidental) noexcept {
    data = data & 0xFC7F | (static_cast<uint_fast16_t>(accidental) << 7);
}

Accidental Note::get_key_accidental() const noexcept {
    return static_cast<Accidental>((data & 0x380) >> 7);
}

void Note::set_random_accidental(Accidental accidental) noexcept {
    data = data & 0xE3FF | (static_cast<uint_fast16_t>(accidental) << 10);
}

Accidental Note::get_random_accidental() const noexcept {
    return static_cast<Accidental>((data & 0x1C00) >> 10);
}

Accidental Note::get_accidental() const noexcept {
    if (this->get_random_accidental() == Accidental::UNDEFINED) {
        return this->get_key_accidental();
    }
    return this->get_random_accidental();
}


void Note::set_duration(Duration duration) noexcept {
    data = data & 0x1FFF | (static_cast<uint_fast16_t>(duration) << 13);
}

Duration Note::get_duration() const noexcept {
    return static_cast<Duration>((data & 0xE000) >> 13);
}

void Note::set_height(const uint_fast8_t height) {
    if (height >= 9 * 7 * 2) {
        std::cerr << "height must be less than 126" << std::endl;
        return;
    }
    set_octave(static_cast<Octave>(height / (7 * 2)));
    set_base(static_cast<Base>(height % 7 / 2));
    if (height % (9 * 7 * 2) > 0) {
        set_random_accidental(Accidental::SHARP);
        return;
    }
    set_key_accidental(Accidental::UNDEFINED);
    set_random_accidental(Accidental::UNDEFINED);
}

uint_fast8_t Note::get_height() const noexcept {
    uint_fast8_t result = static_cast<uint_fast8_t>(get_octave()) * 12;
    for (int x = 1; x < 7; ++x) {
        if (this->get_base() == static_cast<Base>(x)) {
            break;
        }
        if (x == 2 || x == 5) {
            result += 1;
        } else {
            result += 2;
        }
    }

    switch (get_accidental()) {
        case Accidental::DOUBLE_FLAT:
            result -= 2;
            break;
        case Accidental::FLAT:
            --result;
            break;
        case Accidental::SHARP:
            ++result;
            break;
        case Accidental::DOUBLE_SHARP:
            result += 2;
            break;
        default:
            break;
    }
    return result;
}

std::string Note::get_name() const noexcept {
    std::string name{static_cast<char>(66 + static_cast<int>(get_base()))};
    if(static_cast<int>(get_base()) > 5){
        name[0] -= 7;
    }

    // if (name == "B") {
    //     name = "H";
    // }
    // Во всех форматах эта фигня не используется

    switch (static_cast<uint8_t>(get_accidental())) {
        case 1: {
            if (name == "A" || name == "E") {
                name += "ses";
            } else {
                name += "eses";
            }
            break;
        }
        case 2: {
            if (name == "A" || name == "E") {
                name += "s";
            } else {
                name += "es";
            }
            break;
        }
        case 4: {
            name += "is";
            break;
        }
        case 5: {
            if (name == "A" || name == "E") {
                name += "sis";
            } else {
                name += "isis";
            }
            break;
        }
    };

    // if (name == "Hes") {
    //     name = "B";
    // }

    return name;
}

std::string Note::get_name_abc(){
    std::string ans;
    ans += get_name();

    if(static_cast<int>(get_octave()) > 4){
        ans[0] = std::tolower(ans[0]);
        for(int x=static_cast<int>(get_octave()); x>5; --x){
            ans.insert(1, "'");
        }
    }

    if(static_cast<int>(get_octave()) == 5){
        ans[0] = std::tolower(ans[0]);
    }

    if(static_cast<int>(get_octave()) < 4){
        ans[0] = std::toupper(ans[0]);
        for(int x=4; x>static_cast<int>(get_octave()); --x){
            ans.insert(1, ",");
        }
    }

    if(ans.ends_with("is")){
        ans.erase(ans.length() - 2);
        if(ans.ends_with("is")){
            ans.erase(ans.length() - 2);
            ans.insert(0, "^^");
            return ans;
        }
        if(ans.ends_with("s")){
            ans.erase(ans.length() - 1);
            ans.insert(0, "^^");
            return ans;
        }
        ans.insert(0, "^");
        return ans;
    }

    if(ans.ends_with("es")){

        // Персональная обработка ноты es.
        if(ans == "es"){
            ans.pop_back();
            goto not_touch_es;
        }

        ans.erase(ans.length() - 2);
        if(ans.ends_with("es")){
            ans.erase(ans.length() - 2);
            ans.insert(0, "__");
            return ans;
        }
        if(ans.ends_with("s")){
            ans.erase(ans.length() - 1);
            ans.insert(0, "__");
            return ans;
        }

        not_touch_es:

        ans.insert(0, "_");
        return ans;
    }

    if(ans.ends_with("s")){
        ans.pop_back();
        ans.insert(0, "_");
    }

    return ans;
}


void Note::set_pause(bool i) {
    is_pause_data = i;
}

bool Note::is_pause() {
    return is_pause_data;
}

void Note::enharmony_сhange(bool dir) noexcept {
    Accidental first_a = this->get_random_accidental();
    Base first_b = this->get_base();
    Octave first_o = this->get_octave();
    uint8_t height = static_cast<uint8_t>(this->get_height());
    if (dir) {
        uint8_t base = static_cast<uint8_t>(this->get_base());
        ++base;
        if (base > 7) {
            base = 1;
            if (this->get_octave() == Octave::_5_LINE) {
                std::cerr << "(en_ch) Эта нота слишком высокая" << std::endl;
                this->set_random_accidental(first_a);
                this->set_base(first_b);
                this->set_octave(first_o);
                return;
            }
            this->set_octave(static_cast<Octave>(static_cast<int>(this->get_octave()) + 1));
        }
        this->set_base(static_cast<Base>(base));

        this->set_random_accidental(Accidental::SHARP);
        if (height != static_cast<uint8_t>(this->get_height())) {
            this->set_random_accidental(Accidental::NATURAL);
        }
        if (height != static_cast<uint8_t>(this->get_height())) {
            this->set_random_accidental(Accidental::FLAT);
        }
        if (height != static_cast<uint8_t>(this->get_height())) {
            this->set_random_accidental(Accidental::DOUBLE_FLAT);
        }
        if (height != static_cast<uint8_t>(this->get_height())) {
            this->set_random_accidental(first_a);
            this->set_base(first_b);
            this->set_octave(first_o);
            std::cerr << "(en_ch, 1 iteration) целевая нота слишком далеко от исходной" << std::endl;
            return;
        }
    } else {
        uint8_t base = static_cast<uint8_t>(this->get_base());
        --base;
        if (base < 1) {
            base = 7;
            if (this->get_octave() == Octave::SUB_CONTRA) {
                std::cerr << "(en_ch) Эта нота слишком низкая" << std::endl;
                this->set_random_accidental(first_a);
                return;
            }
            this->set_octave(static_cast<Octave>(static_cast<int>(this->get_octave()) - 1));
        }
        this->set_base(static_cast<Base>(base));

        this->set_random_accidental(Accidental::FLAT);
        if (height != static_cast<int>(this->get_height())) {
            this->set_random_accidental(Accidental::NATURAL);
        }
        if (height != static_cast<int>(this->get_height())) {
            this->set_random_accidental(Accidental::SHARP);
        }
        if (height != static_cast<int>(this->get_height())) {
            this->set_random_accidental(Accidental::DOUBLE_SHARP);
        }
        if (height != static_cast<int>(this->get_height())) {
            this->set_random_accidental(first_a);
            this->set_base(first_b);
            this->set_octave(first_o);
            std::cerr << "(en_ch, 2 iteration)целевая нота слишком далеко от исходной" << std::endl;
            return;
        }
    }
}

// ------ operators --------

Note &Note::operator++() {
    if (this->get_accidental() == Accidental::UNDEFINED) {
        this->set_random_accidental(Accidental::NATURAL);
    }

    int first_base = static_cast<int>(get_base());

    if(get_base() == Base::E || get_base() == Base::B){
        if(get_base() != static_cast<Base>(7)){
            set_base(static_cast<Base>(static_cast<int>(get_base()) + 1));
        } else {
            set_base(static_cast<Base>(1));
        }
    } else {
        if(get_accidental() == Accidental::DOUBLE_SHARP){
            set_random_accidental(Accidental::NATURAL);
            if(get_base() != static_cast<Base>(7)){
                set_base(static_cast<Base>(static_cast<int>(get_base()) + 1));
            } else {
                set_base(static_cast<Base>(1));
            }
        }
        set_random_accidental(static_cast<Accidental>(static_cast<int>(get_accidental()) + 1));
    }

    if(get_accidental() == Accidental::DOUBLE_SHARP){
        set_random_accidental(Accidental::NATURAL);
        if(get_base() != static_cast<Base>(7)){
            set_base(static_cast<Base>(static_cast<int>(get_base()) + 1));
        } else {
            set_base(static_cast<Base>(1));
        }
    }

    if(first_base == 7 && first_base != static_cast<int>(get_base())){
        if(get_octave() != Octave::_5_LINE){
            set_octave(static_cast<Octave>(static_cast<int>(get_octave()) + 1));
        } else {
            std::cout << "From Note::operator++: Нота слишком высокая..." << std::endl;
        }
    }

    return *this;
}

Note Note::operator++(int i) {
    Note first_note(this->get_data());
    ++*this;
    return first_note;
}

Note &Note::operator--() {
    if (this->get_accidental() == Accidental::UNDEFINED) {
        this->set_random_accidental(Accidental::NATURAL);
    }

    int first_base = static_cast<int>(get_base());

    if(get_base() == Base::F || get_base() == Base::C){
        if(get_base() != static_cast<Base>(1)){
            set_base(static_cast<Base>(static_cast<int>(get_base()) - 1));
        } else {
            set_base(static_cast<Base>(7));
        }
    } else {
        if(get_accidental() == Accidental::DOUBLE_FLAT){
            set_random_accidental(Accidental::NATURAL);
            if(get_base() != static_cast<Base>(1)){
                set_base(static_cast<Base>(static_cast<int>(get_base()) - 1));
            } else {
                set_base(static_cast<Base>(7));
            }
        }
        set_random_accidental(static_cast<Accidental>(static_cast<int>(get_accidental()) - 1));
    }

    if(get_accidental() == Accidental::DOUBLE_FLAT){
        set_random_accidental(Accidental::NATURAL);
        if(get_base() != static_cast<Base>(1)){
            set_base(static_cast<Base>(static_cast<int>(get_base()) - 1));
        } else {
            set_base(static_cast<Base>(7));
        }
    }

    if(first_base == 1 && first_base != static_cast<int>(get_base())){
        if(get_octave() != Octave::SUB_CONTRA){
            set_octave(static_cast<Octave>(static_cast<int>(get_octave()) - 1));
        } else {
            std::cout << "From Note::operator++: Нота слишком низкая..." << std::endl;
        }
    }

    return *this;
}

Note Note::operator--(int i) {
    Note first_note(this->get_data());
    --*this;
    return first_note;
}
