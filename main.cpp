#include <iostream>
#include "Puzzle.h"

int main() {

    Stone b = Stone(Stone::Colour::BROWN, 1);
    Stone w = Stone(Stone::Colour::WHITE, 1);
    Stone y = Stone(Stone::Colour::YELLOW, 1);
    Stone B = Stone(Stone::Colour::BROWN, 2);
    Stone W = Stone(Stone::Colour::WHITE, 2);
    Stone Y = Stone(Stone::Colour::YELLOW, 2);

    Puzzle target = Puzzle::init();
    Puzzle current = Puzzle(Loop(Loop::ID::UPPER, Y,w,Y,b,W,y,B,w,Y),
                      Loop(Loop::ID::LOWER, B,w,B,w,B,y,W,b,W),
                      Bridge(w,Y,w));

    current.display(); // check right board while program is running

    std::vector<char> solution;

    if (current.solve(0, target, solution)) {
        std::cout << "Success: Board Solved\n";
        current.printSolution(solution);
    }
    else {
        std::cout << "Board not solvable at this depth\n";
    }

    return 0;
}

