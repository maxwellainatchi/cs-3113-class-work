//
//  Bullet.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/10/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "Animal.hpp"

namespace Entities {
    class Bullet: public Animal {
    public:
        Bullet(std::string imageName, Position::Rectangle pen, Position::Vector2D velocity = {0.0, 3.0});
        
        void kill();
        
        // Inherited
        virtual void checkBounds(float elapsed);
    };
}

#endif /* Bullet_hpp */
