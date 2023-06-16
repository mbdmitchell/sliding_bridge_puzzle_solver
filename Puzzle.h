#pragma once

#include "Loop.h"
#include "Bridge.h"

class Puzzle {
    Loop upper;
    Loop lower;
    Bridge bridge;
public:
    void lrotate(Loop::ID id, int amount);
    void rotate(Loop::ID id, int amount);
    void display();
    static Puzzle init();
    Puzzle(Loop upper, Loop lower, Bridge bridge);
    void printSolution(const std::vector<char>& solution);
    bool solve(int depth, const Puzzle& target, std::vector<char>& solution);
private:
    bool operator==(const Puzzle& other);
};