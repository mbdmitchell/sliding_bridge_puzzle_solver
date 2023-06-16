//
// Created by maxmi on 20/05/2023.
//

#include <cctype>
#include "Stone.h"

char Stone::getSprite() {
    char sprite;

    switch (colour) {
        case Colour::WHITE : sprite = 'W'; break;
        case Colour::BROWN : sprite = 'B'; break;
        case Colour::YELLOW : sprite = 'Y'; break;
    }

    if (size == 2) return sprite;
    return std::tolower(sprite);
}

