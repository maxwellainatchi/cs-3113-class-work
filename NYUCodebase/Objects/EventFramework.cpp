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
        {Position::Vector2D::Direction::up, SDL_SCANCODE_W},
        {Position::Vector2D::Direction::down, SDL_SCANCODE_S},
        {Position::Vector2D::Direction::left, SDL_SCANCODE_A},
        {Position::Vector2D::Direction::right, SDL_SCANCODE_D}
    };
    const ControlScheme EventFramework::ControlSchemes::WASD_UPDOWN = {
        {Position::Vector2D::Direction::up, SDL_SCANCODE_W},
        {Position::Vector2D::Direction::down, SDL_SCANCODE_S}
    };
    const ControlScheme EventFramework::ControlSchemes::WASD_LEFTRIGHT = {
        {Position::Vector2D::Direction::left, SDL_SCANCODE_A},
        {Position::Vector2D::Direction::right, SDL_SCANCODE_D}
    };
    
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys = {
        {Position::Vector2D::Direction::up, SDL_SCANCODE_UP},
        {Position::Vector2D::Direction::down, SDL_SCANCODE_DOWN},
        {Position::Vector2D::Direction::left, SDL_SCANCODE_LEFT},
        {Position::Vector2D::Direction::right, SDL_SCANCODE_RIGHT}
    };
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys_UPDOWN = {
        {Position::Vector2D::Direction::up, SDL_SCANCODE_UP},
        {Position::Vector2D::Direction::down, SDL_SCANCODE_DOWN}
    };
    const ControlScheme EventFramework::ControlSchemes::ArrowKeys_LEFTRIGHT = {
        {Position::Vector2D::Direction::left, SDL_SCANCODE_LEFT},
        {Position::Vector2D::Direction::right, SDL_SCANCODE_RIGHT}
    };
}

// Event framework
namespace Graphics {
    void EventFramework::registerKeyHandler(SDL_Scancode code, std::vector<std::string> states, std::function<void()> handler, bool keyUp) {
        for (auto state : states) {
            if (keyUp) keyUpHandlers[state][code] = handler;
            else keyDownHandlers[state][code] = handler;
        }
    }
}
