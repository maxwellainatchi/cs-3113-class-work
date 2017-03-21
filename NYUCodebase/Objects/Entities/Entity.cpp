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
    
    void Entity::translate(Graphics::Vector2D offset) {
        setCoordinates(position + offset);
    }
    
    void Entity::rotate(float angle) {
        //TODO: Fix rotation
        //TODO: Update positional coordinates
        modelMatrix.Rotate(angle);
    }
    
    void Entity::setCoordinates(Graphics::Coordinates newCoordinates) {
        position = newCoordinates;
        modelMatrix.setPosition(0, 0, 0);
    }
    
    void Entity::setOrigin(Graphics::Coordinates::XY newOrigin) {
        position = {
            newOrigin,
            position.width(),
            position.height()
        };
    }
    
    void Entity::move(Graphics::Vector2D velocity, float elapsed) {
        Graphics::Vector2D offset = {
            velocity.x * elapsed,
            velocity.y * elapsed
        };
        translate(offset);
    }
    
    void Entity::scale(Graphics::Coordinates::XY by) {
        position = position * by;
    }
    
    void Entity::scale(float by) {
        scale({by, by});
    }
    
    Graphics::Vector2D Entity::withoutness(Graphics::Coordinates pen, bool inclusive) {
        Graphics::Vector2D result = {0,0};
        auto positionBounds = position.bounds();
        auto penBounds = pen.bounds();
        
        if (inclusive) {
            if (positionBounds.top > penBounds.top)
                result.y = positionBounds.top - penBounds.top;
            else if (positionBounds.bottom < penBounds.bottom)
                result.y = positionBounds.bottom - penBounds.bottom;
            if (positionBounds.left > penBounds.right)
                result.x = positionBounds.left - penBounds.right;
            else if (positionBounds.right < penBounds.left)
                result.x = positionBounds.right - penBounds.left;
        } else {
            if (positionBounds.bottom > penBounds.top)
                result.y = positionBounds.bottom - penBounds.top;
            else if (positionBounds.top < penBounds.bottom)
                result.y = positionBounds.top - penBounds.bottom;
            if (positionBounds.right < penBounds.right)
                result.x = positionBounds.right - penBounds.right;
            else if (positionBounds.left > penBounds.left)
                result.x = positionBounds.left - penBounds.left;
        }
        
        return result;
    }
    
    void Entity::draw(ShaderProgram* shader) {
        if (hidden) { return; }
        shader->setModelMatrix(modelMatrix);
        texture.draw(shader, position);
    }
    
    void Entity::update(float elapsed) {}
    
    bool Entity::isCollidingWith(Entity* entity) {
        if (entity == this || intangible || entity->intangible) { return false; }
        auto without = withoutness(entity->position, false);
        return without.x == 0 && without.y == 0;
    }
}
