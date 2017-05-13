//
//  CollisionFunctions.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/15/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef collisionfunctions_hpp
#define collisionfunctions_hpp

#include "Game.hpp"

namespace Collisions {
    typedef std::function<void(Entity*, bool)> Response;
    typedef std::function<void(Entity*, Rectangle, Rectangle, bool)> Prevention;
    
    // MARK: Preventions
    
    inline void uncollide(Entity* entity, Rectangle bounds, Rectangle otherBounds, bool y) {
        var penetration = bounds.penetration(otherBounds);
        var movement = Vector();
        float direction;
        if (y) {
            direction = -2 * (bounds.bottom < otherBounds.bottom) + 1;
            movement.y = penetration.y + SMALL_AMOUNT;
        } else {
            direction = -2 * (bounds.left < otherBounds.left) + 1;
            movement.x = penetration.x + SMALL_AMOUNT;
        }
        
        // Move the entity just outside the other entity
        entity->bounds += movement * direction;
    }
    
    inline void moveWithout(Entity* entity, Rectangle bounds, Rectangle otherBounds, bool y) {
        var without = bounds.withoutness(otherBounds, true);
        var movement = Vector();
        float direction;
        if (y) {
            direction = bounds.bottom > otherBounds.bottom ? 1 : -1;
            movement.x = without.x + SMALL_AMOUNT * direction;
        } else {
            direction = bounds.left > otherBounds.left ? 1 : -1;
            movement.y = without.y + SMALL_AMOUNT * direction;
        }
        entity->bounds += movement;
    }
    
    // MARK: Responses
    
    inline void nonresponsive(Entity* entity, bool y) {}
    
    inline void stopDead(Entity* entity, bool y) {
        Vector neg = Vector((float)(!y), (float) (y)) * -1;
        entity->oneOffVelocity = entity->velocity * neg;
        entity->oneOffAcceleration = entity->acceleration * neg;
        entity->oneOffFriction = entity->friction * neg;
        entity->oneOffGravity = entity->gravity * neg;
    }
    
    inline void bounce(Entity* entity, bool y) {
        entity->velocity *= {!y ? -1.f : 1.f, y ? -1.f : 1.f};
    };
    
    // MARK: Detection
    
    inline CollisionAction penCheck(Entity* entity, Game* g, Prevention prevention, Response response) {
        return [entity, g, prevention, response](Entity* otherEntity, float elapsed) {
            SDL_assert_paranoid(g); // The game better exist
            guard (entity && otherEntity) else { return; };
            
            // Only project the y-movement for now
            var position = entity->projectedPosition(elapsed, true);
            
            // Check if y-movement causes a collision
            if (position.isWithin(otherEntity->bounds, false)) {
                prevention(entity, position, otherEntity->bounds, true);
                response(entity, true);
            }
            
            // Set the projected position to full movement
            position = entity->projectedPosition(elapsed, false);
            
            // Check if x-movement causes a collision
            if (position.isWithin(otherEntity->bounds, false)) {
                prevention(entity, position, otherEntity->bounds, false);
                response(entity, false);
            }
        };
    }
}

#endif
