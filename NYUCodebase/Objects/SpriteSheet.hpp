//
//  SpriteSheet.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/9/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef SpriteSheet_hpp
#define SpriteSheet_hpp

#include "libraries.h"
#include "Coordinates.hpp"
#include "Texture.hpp"

namespace Graphics {
    class SpriteSheet {
    public:
        std::vector<Coordinates> atlas;
        std::map<std::string, size_t> sprites;
        Graphics::Texture* sheet;
        
        SpriteSheet(std::string imageName, Coordinates::XY spriteSize, std::vector<std::string> names);
        
        Graphics::Coordinates getNamedSpriteCoords(std::string name);
    };
}

#endif /* SpriteSheet_hpp */
