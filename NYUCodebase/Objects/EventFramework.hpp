//
//  EventFramework.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef EventFramework_hpp
#define EventFramework_hpp

#include "libraries.h"
#include "Rectangle.hpp"

namespace Graphics {
    typedef std::map<Position::Vector2D::Direction, SDL_Scancode> ControlScheme;
    
    class EventFramework {
    public:
        class ControlSchemes {
        public:
            static const ControlScheme WASD;
            static const ControlScheme WASD_UPDOWN;
            static const ControlScheme WASD_LEFTRIGHT;
            
            static const ControlScheme ArrowKeys;
            static const ControlScheme ArrowKeys_UPDOWN;
            static const ControlScheme ArrowKeys_LEFTRIGHT;
        };
        
        std::map<std::string, std::map<SDL_Scancode, std::function<void()>>> keyDownHandlers;
        std::map<std::string, std::map<SDL_Scancode, std::function<void()>>> keyUpHandlers;
        
        void registerKeyHandler(SDL_Scancode code, std::vector<std::string> states, std::function<void()> handler, bool keyUp = false);
    };
}

#endif /* EventFramework_hpp */
