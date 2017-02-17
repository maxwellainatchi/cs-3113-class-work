//
//  Sheep.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Sheep_hpp
#define Sheep_hpp

#include "libraries.h"
#include "Entity.hpp"
#include "Coordinates.hpp"
#include "Animal.hpp"

namespace Graphics {
    class Sheep: public Animal {
    public:
        Sheep(std::string imageName, Coordinates pen, Vector2D velocity = {0.0, 1.0});
        
        float timeSinceLastMove;

        void millAbout(float elapsed);
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Sheep_hpp */
