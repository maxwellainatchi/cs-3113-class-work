//
//  Entity.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Entity.hpp"

namespace Graphics {
    Entity::Entity() {}
    
    Entity::Entity(std::string imageName): Entity() {
        texture = Texture(imageName);
    }
    
    void Entity::translate(Graphics::Vector2D offset) {
        position = position + offset;
        modelMatrix.Translate(offset.x, offset.y, 0);
    }
    
    void Entity::rotate(float angle) {
        //TODO: Update positional coordinates
        modelMatrix.Rotate(angle);
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
        texture.draw(shader);
    }
    
    void Entity::update(float elapsed) {
        
    }
}
