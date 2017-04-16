//
//  CollisionFunctions.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/15/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"

namespace Collisions {
    inline CollisionAction bounce(Entity* entity, Game* g) {
        return [entity, g](Entity* otherEntity, float elapsed) {
            weak_assert(entity && otherEntity);
            SDL_assert(g);
            
            var position = entity->projectedPosition(elapsed);
            // Only project the y-movement for now
            position = {{entity->bounds.left, position.bottom}, position.width(), position.height()};
            
            // Check if y-movement causes a collision
            if (position.isWithin(otherEntity->bounds, false)) {
                var penetration = position.penetration(entity->bounds);
                var direction = entity->bounds.bottom > otherEntity->bounds.bottom ? 1 : -1;
                let movement = (penetration.y + 0.001f) * direction;
                
                // Move the entity just outside the other entity
                entity->bounds += {0, movement};
                
                // Reverse the x-velocity
                entity->velocity *= {1, -1};
            }
            
            // Set the projected position to full movement
            position = entity->projectedPosition(elapsed);
            
            // Check if x-movement causes a collision
            if (position.isWithin(entity->bounds, false)) {
                var penetration = position.penetration(otherEntity->bounds);
                var direction = entity->bounds.left > otherEntity->bounds.left ? 1 : -1;
                let movement = (penetration.x + 0.001f) * direction;
                entity->bounds += {movement, 0};
                entity->velocity *= {-1, 1};
            }
        };
    }
}
