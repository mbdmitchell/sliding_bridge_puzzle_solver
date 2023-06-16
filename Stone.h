#pragma once

class Stone {

public:
    enum Colour {WHITE, YELLOW, BROWN};
    Stone(Colour c, int size) : colour(c), size(size){}
    char getSprite();
private:
    Colour colour;
    int size;
};

