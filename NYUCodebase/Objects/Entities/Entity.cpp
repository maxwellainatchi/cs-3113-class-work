//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Entity.hpp"

namespace Entities {
    Entity::Entity() {}
    
    Entity::Entity(std::string imageName): Entity() {
        texture = Graphics::Texture(imageName);
    }
    
    void Entity::translate(Position::Vector2D offset) {
        setCoordinates(bounds + offset);
    }
    
    void Entity::rotate(float angle) {
        //TODO: Fix rotation
        //TODO: Update positional coordinates
        modelMatrix.Rotate(angle);
    }
    
    void Entity::setCoordinates(Position::Rectangle newBounds) {
        bounds = newBounds;
        modelMatrix.setPosition(0, 0, 0);
    }
    
    void Entity::setOrigin(Position::Point newOrigin) {
        bounds = {
            newOrigin,
            bounds.width(),
            bounds.height()
        };
    }
    
    void Entity::move(Position::Vector2D velocity, float elapsed) {
        translate(velocity * elapsed);
    }
    
    void Entity::scale(Position::Point by) {
        bounds = bounds * by;
    }
    
    void Entity::scale(float by) {
        scale({by, by});
    }
    
    void Entity::draw(ShaderProgram* shader) {
        if (hidden) { return; }
        shader->setModelMatrix(modelMatrix);
        texture.draw(shader, bounds);
    }
    
    void Entity::update(float elapsed) {}
    
    bool Entity::isCollidingWith(Entity* entity) {
        guard (entity != this && !intangible && !entity->intangible) else { return false; }
        return bounds.isWithin(entity->bounds, false);
    }
}
