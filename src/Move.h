#ifndef MOVE_H
#define MOVE_H

#include <string>
#include <iostream>

class Move {
private:
    std::string move;
    int score;
public:
    Move(const std::string& m, int s);
    bool operator<(const Move& other) const;
    bool operator>(const Move& other) const;

    friend std::ostream& operator<<(std::ostream& os, const Move& m);
};

#endif // MOVE_H
