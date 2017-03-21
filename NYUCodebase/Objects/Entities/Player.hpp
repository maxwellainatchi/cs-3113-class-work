//
//  Player.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "libraries.h"
#include "Coordinates.hpp"
#include "SpriteSheet.hpp"
#include "Sprite.hpp"
#include "EventFramework.hpp"

namespace Entities {
    class Player: public Sprite {
    public:
        Graphics::ControlScheme controlScheme;
        Graphics::Coordinates pen;
        
        Graphics::Vector2D::Direction moveDirection;
        float speed;
        
        Player(Graphics::SpriteSheet* spriteSheet, std::string name, Graphics::Coordinates pen);
        
        void registerMovementHandlers(Graphics::EventFramework* g, std::vector<std::string> states, std::set<Graphics::Vector2D::Direction> directions = {
            Graphics::Vector2D::Direction::up,
            Graphics::Vector2D::Direction::down,
            Graphics::Vector2D::Direction::left,
            Graphics::Vector2D::Direction::right
        });
        
        // Inherited
        virtual void update(float elapsed);
    };
}

#endif /* Player_hpp */
