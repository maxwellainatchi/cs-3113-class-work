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
        typedef std::function<void(Entity*)> Collision;
        Graphics::Coordinates position;
        Graphics::Texture texture;
        Matrix modelMatrix;
        bool hidden = false;
        bool intangible = false;
        Collision onCollide;
        
        Entity();
        
        Entity(std::string imageName);
        
        void translate(Graphics::Vector2D offset);
        
        void rotate(float angle);
        
        void setCoordinates(Graphics::Coordinates newCoordinates);
        
        void setOrigin(Graphics::Coordinates::XY newOrigin);
        
        void move(Graphics::Vector2D velocity, float elapsed);
        
        void scale(Graphics::Coordinates::XY by);
        
        void scale(float by);
        
        Graphics::Vector2D withoutness(Graphics::Coordinates pen, bool inclusive = true);
        
        // TODO: Implement withinness
        //Graphics::Vector2D withinness(Graphics::Coordinates pen);
    
        virtual void draw(ShaderProgram* shader);
        
        virtual void update(float elapsed);
        
        bool isCollidingWith(Entity* entity);
    };
}

#endif /* Entity_hpp */
