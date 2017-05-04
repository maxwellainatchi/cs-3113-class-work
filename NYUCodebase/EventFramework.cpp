//
//  EventFramework.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "EventFramework.hpp"

// Control Schemes

const ControlScheme EventFramework::ControlSchemes::WASD = {
    {Vec2::Direction::up, SDL_SCANCODE_W},
    {Vec2::Direction::down, SDL_SCANCODE_S},
    {Vec2::Direction::left, SDL_SCANCODE_A},
    {Vec2::Direction::right, SDL_SCANCODE_D}
};
const ControlScheme EventFramework::ControlSchemes::WASD_UPDOWN = {
    {Vec2::Direction::up, SDL_SCANCODE_W},
    {Vec2::Direction::down, SDL_SCANCODE_S}
};
const ControlScheme EventFramework::ControlSchemes::WASD_LEFTRIGHT = {
    {Vec2::Direction::left, SDL_SCANCODE_A},
    {Vec2::Direction::right, SDL_SCANCODE_D}
};

const ControlScheme EventFramework::ControlSchemes::ArrowKeys = {
    {Vec2::Direction::up, SDL_SCANCODE_UP},
    {Vec2::Direction::down, SDL_SCANCODE_DOWN},
    {Vec2::Direction::left, SDL_SCANCODE_LEFT},
    {Vec2::Direction::right, SDL_SCANCODE_RIGHT}
};
const ControlScheme EventFramework::ControlSchemes::ArrowKeys_UPDOWN = {
    {Vec2::Direction::up, SDL_SCANCODE_UP},
    {Vec2::Direction::down, SDL_SCANCODE_DOWN}
};
const ControlScheme EventFramework::ControlSchemes::ArrowKeys_LEFTRIGHT = {
    {Vec2::Direction::left, SDL_SCANCODE_LEFT},
    {Vec2::Direction::right, SDL_SCANCODE_RIGHT}
};


// Event framework
void EventFramework::registerKeyHandler(SDL_Scancode code, std::vector<std::string> states, std::function<void()> handler, bool keyUp) {
    for (auto state : states) {
        if (keyUp) keyUpHandlers[state][code] = handler;
        else keyDownHandlers[state][code] = handler;
    }
}

