//
//  Entity.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "libraries.h"
#include "Coordinates.hpp"
#include "Texture.hpp"
#include "Matrix.h"

namespace Entities {
    class Entity {
    public:
        Graphics::Coordinates position;
        Graphics::Texture texture;
        Matrix modelMatrix;
        
        Entity();
        
        Entity(std::string imageName);
        
        void translate(Graphics::Vector2D offset);
        
        void rotate(float angle);
        
        void setCoordinates(Graphics::Coordinates newPosition);
        
        void move(Graphics::Vector2D velocity, float elapsed);
        
        void draw(ShaderProgram* shader);
        
        virtual void update(float elapsed);
        
        bool isCollidingWith(Entity entity);
    };
}

#endif /* Entity_hpp */
