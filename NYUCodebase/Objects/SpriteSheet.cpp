//
//  SpriteSheet.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "SpriteSheet.hpp"

namespace Graphics {
    SpriteSheet::SpriteSheet(std::string imageName, Position::Point spriteSize, std::vector<std::string> names) {
        sheet = new Graphics::Texture(imageName);
        Position::Point origin = {0,1};
        size_t index = 0;
        while (origin.y > 0) {
            while (origin.x < 1) {
                atlas.push_back(Position::Rectangle(origin, spriteSize.x, -spriteSize.y));
                if (names.size() > index && names[index] != "") {
                    // Pass over the index if it's a substitute char
                    if (names[index] != std::string(1, char(13))) {
                        sprites[names[index]] = index;
                    }
                    ++index;
                }
                origin.x += spriteSize.x;
            }
            origin.y -= spriteSize.y;
            origin.x = 0;
        }
    }
    
    Position::Rectangle SpriteSheet::getNamedSpriteCoords(std::string name) {
        auto spriteIndex = sprites.find(name);
        if (spriteIndex != sprites.end()) {
            return atlas[spriteIndex->second];
        } else {
            return {{0,0},0,0};
        }
    }
}
