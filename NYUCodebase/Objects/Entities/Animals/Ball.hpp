//
//  Ball.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Ball_hpp
#define Ball_hpp

#include "libraries.h"
#include "Animal.hpp"
#include "Coordinates.hpp"
#include "Player.hpp"

namespace Entities {
    class Ball: public Animal {
    public:
        Ball(std::string imageName, Graphics::Coordinates pen);
        bool paused;
        
        void reset(Graphics::Coordinates& window);
        
        //Inherited
        void update(float elapsed);
        void checkBounds(float elapsed);
    };
}

#endif /* Ball_hpp */
