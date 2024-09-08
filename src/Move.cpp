#include "Move.h"

Move::Move(const std::string& m, int s) : move(m), score(s) {}

bool Move::operator<(const Move& other) const {
    return score < other.score;
}
bool Move::operator>(const Move& other) const {
    return score > other.score;
}

std::ostream& operator<<(std::ostream& os, const Move& m) {
    os <<m.move;
    return os;
}
