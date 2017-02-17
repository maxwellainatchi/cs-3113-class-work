//
//  Texturey.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Texturey_hpp
#define Texturey_hpp

#include "libraries.h"
#include "Game.hpp"
#include "Magician.hpp"
#include "objects.h"

namespace Games {
    class Texturey: public Graphics::Game {
    public:
        // Inherited
        virtual void setup();
        virtual void update(float elapsed);
    };
}

#endif /* Texturey_hpp */
