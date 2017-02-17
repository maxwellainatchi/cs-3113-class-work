//
//  Player.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "libraries.h"
#include "Coordinates.hpp"
#include "Entity.hpp"
#include "EventFramework.hpp"

namespace Entities {
    class Player: public Entity {
    public:
        Graphics::Vector2D::Direction moveDirection;
        
        Player(std::string imageName);
        
        void registerMovementHandlers(Graphics::EventFramework* g);
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Player_hpp */
