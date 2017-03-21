//
//  Sprite.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/10/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Sprite_hpp
#define Sprite_hpp

#include "libraries.h"
#include "Entity.hpp"
#include "SpriteSheet.hpp"

namespace Entities {
    class Sprite: public Entity {
    public:
        Sprite(Graphics::SpriteSheet* spriteSheet, std::string name);
    };
}

#endif /* Sprite_hpp */
