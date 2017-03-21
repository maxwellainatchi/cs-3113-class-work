//
//  Sprite.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/10/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Sprite.hpp"

namespace Entities {
    Sprite::Sprite(Graphics::SpriteSheet* spriteSheet, std::string name) {
        texture = *spriteSheet->sheet;
        auto coords = spriteSheet->getNamedSpriteCoords(name);
        if (coords.width() == 0 && coords.height() == 0) {
            texture.loaded = false;
            return;
        }
        texture.coords = coords;
        float ratio = (texture.w*coords.width())/(texture.h*coords.height());
        Graphics::Vector2D size;
        if (ratio < 1) {
            size = {ratio, 1};
        } else {
            size = {1, ratio};
        }
        Graphics::Coordinates::XY center = {0,0};
        position = {
            center - size,
            size.x,
            size.y
        };
    }
}
