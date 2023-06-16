#include "Loop.h"

Loop::Loop(Loop::ID id, Stone s0, Stone s1, Stone s2, Stone s3, Stone s4, Stone s5, Stone s6, Stone s7, Stone s8) {
    this->id = id;
    chain.push_back(s0);
    chain.push_back(s1);
    chain.push_back(s2);
    chain.push_back(s3);
    chain.push_back(s4);
    chain.push_back(s5);
    chain.push_back(s6);
    chain.push_back(s7);
    chain.push_back(s8);
}

std::vector<Stone> Loop::getChain() const {
    return chain;
}
void Loop::setChain(const std::vector<Stone>& c){
    chain = c;
}

