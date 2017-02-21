//
//  EventFramework.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "EventFramework.hpp"

// Control Schemes
namespace Graphics {
    const ControlScheme EventFramework::ControlSchemes::WASD = {
        {Graphics::Vector2D::Direction::up, SDL_SCANCODE_W},
        {Graphics::Vector2D::Direction::down, SDL_SCANCODE_S},
        {Graphics::Vector2D::Direction::left, SDL_SCANCODE_A},
        {Graphics::Vector2D::Direction::right, SDL_SCANCODE_D}
    };
    const ControlScheme EventFramework::ControlSchemes::WASD_UPDOWN = {
        {Graphics::Vector2D::Direction::up, SDL_SCANCODE_W},
        {Graphics::Vector2D::Direction::down, SDL_SCANCODE_S}
    };
    const ControlScheme EventFramework::ControlSchemes::WASD_LEFTRIGHT = {
        {Graphics::Vector2D::Direction::left, SDL_SCANCODE_A},
        {Graphics::Vector2D::Direction::right, SDL_SCANCODE_D}
    };
    
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys = {
        {Graphics::Vector2D::Direction::up, SDL_SCANCODE_UP},
        {Graphics::Vector2D::Direction::down, SDL_SCANCODE_DOWN},
        {Graphics::Vector2D::Direction::left, SDL_SCANCODE_LEFT},
        {Graphics::Vector2D::Direction::right, SDL_SCANCODE_RIGHT}
    };
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys_UPDOWN = {
        {Graphics::Vector2D::Direction::up, SDL_SCANCODE_UP},
        {Graphics::Vector2D::Direction::down, SDL_SCANCODE_DOWN}
    };
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys_LEFTRIGHT = {
        {Graphics::Vector2D::Direction::left, SDL_SCANCODE_LEFT},
        {Graphics::Vector2D::Direction::right, SDL_SCANCODE_RIGHT}
    };
}

// Event framework
namespace Graphics {
    void EventFramework::registerKeyHandler(SDL_Scancode code, std::function<void()> handler, bool keyUp) {
        if (keyUp) keyUpHandlers[code] = handler;
        else keyDownHandlers[code] = handler;
    }
}
