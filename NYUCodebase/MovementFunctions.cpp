//
//  MovementFunctions.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef movementfunctions_hpp
#define movementfunctions_hpp

#include "Game.hpp"

namespace Movements {
    inline InstantAction randomDirection(Entity* entity, Game* g, float probability) {
        return [entity, g, probability]() {
            guard (arc4random() > UINT32_MAX * probability) else {
                let newDirection = static_cast<Vec2::Direction>(arc4random_uniform(4)+1);
                entity->velocity = Vec2::directionVector(newDirection) * entity->velocity.magnitude();
            }
        };
    }
}

#endif
