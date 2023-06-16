//
// Created by maxmi on 20/05/2023.
//

#include <iostream>
#include <algorithm>
#include <cassert>
#include <utility>
#include "Puzzle.h"
Puzzle::Puzzle(Loop upper, Loop lower, Bridge bridge) : upper(std::move(upper)), lower(std::move(lower)), bridge(std::move(bridge)) {}

void Puzzle::display() {

    std::vector<Stone> uc = upper.getChain();
    std::vector<Stone> lc = lower.getChain();
    std::vector<Stone> bc = bridge.getChain();

    std::cout << "      " << uc[7].getSprite() << "           " << lc[7].getSprite() << "     \n"
                 "  " << uc[6].getSprite() << "       " << uc[8].getSprite() << "   " << lc[8].getSprite() << "       " << lc[6].getSprite() << "  \n"
                 "" << uc[5].getSprite() << "          |" << bc[0].getSprite() << "|          " << lc[5].getSprite() << "\n"
                 "" << uc[4].getSprite() << "   upper  |" << bc[1].getSprite() << "|  lower   " << lc[4].getSprite() << "\n"
                 "" << uc[3].getSprite() << "          |" << bc[2].getSprite() << "|          " << lc[3].getSprite() << "\n"
                 "  " << uc[2].getSprite() << "       " << uc[0].getSprite() << "   " << lc[0].getSprite() << "       " << lc[2].getSprite() << "  \n"
                 "      " << uc[1].getSprite() << "           " << lc[1].getSprite() << "     \n\n\n";
}

void Puzzle::lrotate(Loop::ID id, int amount) {

    assert(amount % 2 == 0); // "rotation amount must be an even number"

    const size_t CHAIN_LENGTH = 9;

    Loop &rotating = (id == Loop::UPPER) ? upper : lower;

    std::vector<Stone> rotatingChain = rotating.getChain();
    std::vector<Stone> bridgeChain = bridge.getChain();

    std::vector<Stone> temp;
    temp.insert( temp.end(), rotatingChain.begin(), rotatingChain.end() );
    temp.insert( temp.end(), bridgeChain.begin(), bridgeChain.end() );

    std::rotate(temp.begin(), temp.begin() + amount, temp.end());

    rotatingChain.clear();
    bridgeChain.clear();

    for (size_t i = 0; i < CHAIN_LENGTH; i++) {
        rotatingChain.push_back(temp[i]);
    }

    for (size_t i = 9; i < temp.size(); i++) {
        bridgeChain.push_back(temp[i]);
    }

    // set rotating and bridge
    rotating.setChain(rotatingChain);
    bridge.setChain(bridgeChain);

}
void Puzzle::rotate(Loop::ID id, int amount) { //atm stone same size, change to rotateToNextLarge

    assert(amount % 2 == 0); // "rotation amount must be an even number"

    const size_t CHAIN_LENGTH = 9;

    Loop &rotating = (id == Loop::UPPER) ? upper : lower;

    std::vector<Stone> rotatingChain = rotating.getChain();
    std::vector<Stone> bridgeChain = bridge.getChain();

    std::vector<Stone> temp;
    temp.insert( temp.end(), rotatingChain.begin(), rotatingChain.end() );
    temp.insert( temp.end(), bridgeChain.begin(), bridgeChain.end() );

    std::rotate(temp.rbegin(), temp.rbegin() + amount, temp.rend());

    rotatingChain.clear();
    bridgeChain.clear();

    for (size_t i = 0; i < CHAIN_LENGTH; i++) {
        rotatingChain.push_back(temp[i]);
    }

    for (size_t i = 9; i < temp.size(); i++) {
        bridgeChain.push_back(temp[i]);
    }

    // set rotating and bridge
    rotating.setChain(rotatingChain);
    bridge.setChain(bridgeChain);

}

Puzzle Puzzle::init() {
    Stone b = Stone(Stone::Colour::BROWN, 1);
    Stone w = Stone(Stone::Colour::WHITE, 1);
    Stone y = Stone(Stone::Colour::YELLOW, 1);
    Stone B = Stone(Stone::Colour::BROWN, 2);
    Stone W = Stone(Stone::Colour::WHITE, 2);
    Stone Y = Stone(Stone::Colour::YELLOW, 2);

    Loop upper = Loop(Loop::ID::UPPER, B, b, B, w, W, w, Y, y, Y);
    Loop lower = Loop(Loop::ID::LOWER, B, b, B, w, W, w, Y, y, Y);
    Bridge bridge = Bridge(w,W,w);
    return {upper, lower, bridge};
}

bool Puzzle::operator==(const Puzzle &other) {

    const size_t LOOP_SIZE = upper.getChain().size();
    const size_t BRIDGE_SIZE = bridge.getChain().size();

    for (size_t i = 0; i < LOOP_SIZE; i++){
        if (this->upper.getChain()[i].getSprite() != other.upper.getChain()[i].getSprite()) return false;
        if (this->lower.getChain()[i].getSprite() != other.lower.getChain()[i].getSprite()) return false;
    }
    for (size_t i = 0; i < BRIDGE_SIZE; i++){
        if (this->bridge.getChain()[i].getSprite() != other.bridge.getChain()[i].getSprite()) return false;
    }

    return true;
}


bool Puzzle::solve(int currentDepth, const Puzzle& target, std::vector<char>& solution) {
    /// `solution` is order of rotations (U,L,U == rotate upper, lower, upper)
    const int MAX_DEPTH = 28;
    Puzzle current = *this; // create copy so not modifying *this

    auto lastSixElementsSame = [solution]() -> bool {
        char comp = solution.back();
        auto checkBackTo = solution.end() - 6;
        for (auto it = solution.end()-1; it != checkBackTo; it--) {
            if (*it != comp) return false;
        }
        return true;
    };

    // Base
    if (current == target) return true;
    if (currentDepth == MAX_DEPTH || (solution.size() >= 6 && lastSixElementsSame())) return false;

    // Add new rotation
    for (auto i : {Loop::ID::UPPER, Loop::ID::LOWER}) {
        solution.push_back((i == Loop::LOWER) ? 'L' : 'U');

        current.rotate(i,2);
        if (solve(currentDepth+1, target, solution)) return true;

        // Remove as it was wrong
        solution.pop_back();
        current.lrotate(i,2);
    }
    return false;
}

void Puzzle::printSolution(const std::vector<char>& solution){
    Loop::ID id = (solution[0] == 'U') ? Loop::ID::UPPER : Loop::ID::LOWER;

    auto asVector = [&solution, &id]() -> std::vector<int> {
        /// solution UULLLUULULUUUULL -> vector {2,3,2,1,1,1,4,2}

        auto atEndOfSolution = [&solution](size_t i) -> bool {
            return (i == solution.size() - 1);
        };

        std::vector<int> v;
        char currentChar = solution[0];
        int currentCharSum = 0;

        for (size_t i = 0; i <= solution.size() - 1; ++i) {
            if (currentChar == solution[i]){
                ++currentCharSum;
            }
            else {
                v.push_back(currentCharSum);
                id = ((id == Loop::ID::UPPER) ? Loop::ID::LOWER : Loop::ID::UPPER);
                currentChar = solution[i];
                currentCharSum = 1;
            }
            if (atEndOfSolution(i)) {
                v.push_back(currentCharSum);
            }
        }

        return v;

    };

    std::vector<int> rotationVec = asVector();
    id = (solution[0] == 'U') ? Loop::ID::UPPER : Loop::ID::LOWER; // been possibly changed by asVector()

    std::cout << "INITIAL BOARD\n";
    display();
    for (auto rotations : rotationVec) {
        rotate(id, rotations * 2);
        std::cout << "Move " << ((id == Loop::ID::UPPER) ? "UPPER " : "LOWER ") << rotations << " (x2)\n";
        display();
        id = ((id == Loop::ID::UPPER) ? Loop::ID::LOWER : Loop::ID::UPPER);
    }
}
