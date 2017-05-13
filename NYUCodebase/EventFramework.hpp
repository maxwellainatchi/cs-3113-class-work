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


typedef std::map<Direction, SDL_Scancode> ControlScheme;

class EventFramework {
private:
    typedef std::map<State, std::map<SDL_Scancode, InstantAction>> _keyHandlerRegistry;
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
    
    _keyHandlerRegistry keyDownHandlers;
    _keyHandlerRegistry keyUpHandlers;
    _keyHandlerRegistry continuousKeyPressHandlers;
    _keyHandlerRegistry continuousKeyUnpressHandlers;
    
    void registerKeyHandler(SDL_Scancode code, std::vector<State> states, InstantAction handler, bool keyUp = false);
    
    void registerContinuousKeyHandler(SDL_Scancode code, std::vector<State> states, InstantAction handler, bool unpress = false);
};

#endif /* EventFramework_hpp */
