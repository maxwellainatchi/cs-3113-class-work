//
//  Animal.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Animal_hpp
#define Animal_hpp

#include "libraries.h"
#include "Entity.hpp"
#include "Coordinates.hpp"

namespace Entities {
    class Animal: public Entity {
    public:
        Graphics::Coordinates pen;
        Graphics::Vector2D velocity;
        
        Animal(std::string imageName, Graphics::Coordinates pen, Graphics::Vector2D velocity = {0.0, 1.0});
        
        virtual void checkBounds(float elapsed);
        
        virtual void move(float elapsed);
        
        //void overstepBounds(Vector2D by) = 0;
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Animal_hpp */
