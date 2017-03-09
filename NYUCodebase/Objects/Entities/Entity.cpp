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
    
    void Entity::setCoordinates(Graphics::Coordinates newPosition) {
        position = newPosition;
        modelMatrix.setPosition(0, 0, 0);
    }
    
    void Entity::move(Graphics::Vector2D velocity, float elapsed) {
        Graphics::Vector2D offset = {
            velocity.x * elapsed,
            velocity.y * elapsed
        };
        translate(offset);
    }
    
    void Entity::draw(ShaderProgram* shader) {
        shader->setModelMatrix(modelMatrix);
        texture.draw(shader, position);
    }
    
    void Entity::update(float elapsed) {}
    
    bool Entity::isCollidingWith(Entity entity) {
        auto bounds = position.bounds();
        auto otherBounds = entity.position.bounds();
        return !(bounds.bottom > otherBounds.top ||
                bounds.top < otherBounds.bottom ||
                bounds.left > otherBounds.right ||
                bounds.right < otherBounds.left
                );
    }
}
