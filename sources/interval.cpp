#include <harmony-core/interval.hpp>
#include <stdexcept>

using namespace harmony_core;

Interval::Interval() noexcept {
    this->data = 0b10000000;
}

Interval::Interval(uint8_t di, Quality q, bool d) noexcept {
    if (d) {
        this->data |= 0b10000000;
    } else {
        this->data &= ~0b10000000;
    }

    this->data &= ~0b1110000;
    this->data |= (static_cast<uint8_t>(q) << 4);

    if (di > 15) {
        di = 15;
    }
    data &= ~0xF;
    data |= di;
}

Interval::Interval(uint_fast8_t data) noexcept {
    this->data = data;
}

Interval::Interval(const Note &n1, const Note n2) noexcept {
    if (n1.get_height() <= n2.get_height()) {
        this->set_direction(1);
    } else {
        this->set_direction(0);
        Note n3 = n1;
        n1 = n2;
        n2 = n3;
    }

    if (n1.get_height() - n2.get_height() > 24) {
        Interval i;
        this->data = i.get_data();
        return;
    }

    this->set_distance(0);
    while (1) {
        static uint8_t note_base = static_cast<uint8_t>(n1.get_base()) - 1;
        ++note_base;
        if (note_base > 7) {
            note_base = 1;
        }

        uint8_t d = this->get_distance();

        if (static_cast<Base>(note_base) == n2.get_base()) {
            this->set_distance(++d);
            break;
        }
        this->set_distance(++d);
    }

    // определяем тип интервала
    uint8_t oct_step = 0;
    bool rev_q = 0;
    while (this->get_distance() >= 8) {
        this->set_distance(this->get_distance() - 8);
        ++oct_step;
    }
    // this->set_distance(this->get_distance() + 8  * oct_step());

    if (this->get_distance() >= 4) {
        if (static_cast<int>(n2.get_octave()) == 0) {
            n1.set_octave(static_cast<Octave>(static_cast<int>(n1.get_octave()) + 1));
            n2.set_octave(static_cast<Octave>(static_cast<int>(n2.get_octave()) + 1));
        }
        if (static_cast<int>(n2.get_octave()) == 8) {
            n1.set_octave(static_cast<Octave>(static_cast<int>(n1.get_octave()) - 1));
            n2.set_octave(static_cast<Octave>(static_cast<int>(n2.get_octave()) - 1));
        }
        n2.set_octave(static_cast<Octave>(static_cast<int>(n2.get_octave()) + 1));
        Note n3 = n1;
        n1 = n2;
        n2 = n3;

        rev_q = 1;
    }

    int8_t base_dist = this->get_distance();
    while (base_dist >= 8) {
        base_dist -= 8;
    }
    if (base_dist >= 4)
        base_dist = 7 - base_dist;

    switch (base_dist) {
        case 0: {
            switch (n1.get_height() - n2.get_height()) {
                case 0:
                    this->set_quality(Quality::PERFECT);
                case 1:
                    this->set_quality(Quality::AUG);
                case 2:
                    this->set_quality(Quality::DOUBLY_AUG);
            }
        }
        case 1: {
            switch (n1.get_height() - n2.get_height()) {
                case 0:
                    this->set_quality(Quality::DIM);
                case 1:
                    this->set_quality(Quality::MINOR);
                case 2:
                    this->set_quality(Quality::MAJOR);
                case 3:
                    this->set_quality(Quality::AUG);
                case 4:
                    this->set_quality(Quality::DOUBLY_AUG);
            }
        }
        case 2: {
            switch (n1.get_height() - n2.get_height()) {
                case 1:
                    this->set_quality(Quality::DOUBLY_DIM);
                case 2:
                    this->set_quality(Quality::DIM);
                case 3:
                    this->set_quality(Quality::MINOR);
                case 4:
                    this->set_quality(Quality::MAJOR);
                case 5:
                    this->set_quality(Quality::AUG);
                case 6:
                    this->set_quality(Quality::DOUBLY_AUG);
            }
        }
        case 3: {
            switch (n1.get_height() - n2.get_height()) {
                case 3:
                    this->set_quality(Quality::DOUBLY_DIM);
                case 4:
                    this->set_quality(Quality::DIM);
                case 5:
                    this->set_quality(Quality::PERFECT);
                case 6:
                    this->set_quality(Quality::AUG);
                case 7:
                    this->set_quality(Quality::DOUBLY_AUG);
            }
        }
    }

    if (rev_q) {
        switch (this->get_quality()) {
            case (Quality::MAJOR):
                this->set_quality(Quality::MINOR);
            case (Quality::MINOR):
                this->set_quality(Quality::MAJOR);
            case (Quality::AUG):
                this->set_quality(Quality::DIM);
            case (Quality::DIM):
                this->set_quality(Quality::AUG);
            case (Quality::DOUBLY_AUG):
                this->set_quality(Quality::DOUBLY_DIM);
            case (Quality::DOUBLY_DIM):
                this->set_quality(Quality::DOUBLY_AUG);
        }
    }
}

void Interval::set_data(uint_fast8_t data) noexcept {
    this->data = data;
}

uint_fast8_t Interval::get_data() const noexcept {
    return this->data;
}

void Interval::set_distance(uint8_t d) noexcept {
    if (d > 15) {
        d = 15;
    }
    this->data &= ~0b1111;
    this->data | d;
}

uint8_t Interval::get_distance() const noexcept {
    return this->data >> 4;
}

void Interval::set_quality(Quality q) noexcept {
    this->data &= ~0b0111000;
    this->data |= (static_cast<uint8_t>(q) << 4);
}

Quality Interval::get_quality() const noexcept {
    return static_cast<Quality>((this->data & 0b01110000) >> 4);
}

void Interval::set_direction(bool d) noexcept {
    if (d) {
        this->data |= 0b10000000;
    } else {
        this->data &= ~0b10000000;
    }
}

bool Interval::get_direction() const noexcept {
    return this->data >> 7;
}

std::string Interval::get_name() const noexcept {
    std::string name;
    switch (this->get_quality()) {
        case Quality::PERFECT:
            name += "per";
        case Quality::MINOR:
            name += "min";
        case Quality::MAJOR:
            name += "maj";
        case Quality::AUG:
            name += "aug";
        case Quality::DIM:
            name += "dim";
        case Quality::DOUBLY_AUG:
            name += "2xdim";
        case Quality::DOUBLY_DIM:
            name += "2xdim";
    }

    name += std::to_string(this->get_distance());

    return name;
}
