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
#include "Timer.hpp"
#include "Entity.hpp"
#include "Rectangle.hpp"
#include "Animal.hpp"

namespace Entities {
    class Sheep: public Animal {
    private:
        float speed;
        Graphics::Timer t = Graphics::Timer(2.0f);
    public:
        Sheep(std::string imageName, Position::Rectangle pen, Position::Vector2D velocity = {0.0, 1.0});
        
        ~Sheep();
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Sheep_hpp */
