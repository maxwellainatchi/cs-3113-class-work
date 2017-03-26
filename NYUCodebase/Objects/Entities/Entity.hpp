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
#include "Rectangle.hpp"
#include "Texture.hpp"
#include "Matrix.h"

namespace Entities {
    class Entity {
    public:
        typedef std::function<void(Entity*)> Collision;
        Position::Rectangle bounds;
        Graphics::Texture texture;
        Matrix modelMatrix;
        bool hidden = false;
        bool intangible = false;
        Collision onCollide;
        
        Entity();
        
        Entity(std::string imageName);
        
        void translate(Position::Vector2D offset);
        
        void rotate(float angle);
        
        void setCoordinates(Position::Rectangle newBounds);
        
        void setOrigin(Position::Point newOrigin);
        
        void move(Position::Vector2D velocity, float elapsed);
        
        void scale(Position::Point by);
        
        void scale(float by);
        
        bool isInBounds();
        
        // TODO: Implement withinness
        //Position::Vector2D withinness(Position::Rectangle pen);
    
        virtual void draw(ShaderProgram* shader);
        
        virtual void update(float elapsed);
        
        bool isCollidingWith(Entity* entity);
    };
}

#endif /* Entity_hpp */
