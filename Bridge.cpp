//
// Created by maxmi on 20/05/2023.
//

#include "Bridge.h"

Bridge::Bridge(Stone s0, Stone s1, Stone s2) {
    chain.push_back(s0);
    chain.push_back(s1);
    chain.push_back(s2);
}

std::vector<Stone> Bridge::getChain() const {
    return chain;
}

void Bridge::setChain(std::vector<Stone> c) {
    chain = c;
}
