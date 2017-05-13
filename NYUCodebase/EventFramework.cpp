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
    {Direction::up, SDL_SCANCODE_W},
    {Direction::down, SDL_SCANCODE_S},
    {Direction::left, SDL_SCANCODE_A},
    {Direction::right, SDL_SCANCODE_D}
};
const ControlScheme EventFramework::ControlSchemes::WASD_UPDOWN = {
    {Direction::up, SDL_SCANCODE_W},
    {Direction::down, SDL_SCANCODE_S}
};
const ControlScheme EventFramework::ControlSchemes::WASD_LEFTRIGHT = {
    {Direction::left, SDL_SCANCODE_A},
    {Direction::right, SDL_SCANCODE_D}
};

const ControlScheme EventFramework::ControlSchemes::ArrowKeys = {
    {Direction::up, SDL_SCANCODE_UP},
    {Direction::down, SDL_SCANCODE_DOWN},
    {Direction::left, SDL_SCANCODE_LEFT},
    {Direction::right, SDL_SCANCODE_RIGHT}
};
const ControlScheme EventFramework::ControlSchemes::ArrowKeys_UPDOWN = {
    {Direction::up, SDL_SCANCODE_UP},
    {Direction::down, SDL_SCANCODE_DOWN}
};
const ControlScheme EventFramework::ControlSchemes::ArrowKeys_LEFTRIGHT = {
    {Direction::left, SDL_SCANCODE_LEFT},
    {Direction::right, SDL_SCANCODE_RIGHT}
};


// Event framework
void EventFramework::registerKeyHandler(SDL_Scancode code, std::vector<std::string> states, std::function<void()> handler, bool keyUp) {
    for (var state : states) {
        if (keyUp) keyUpHandlers[state][code] = handler;
        else keyDownHandlers[state][code] = handler;
    }
}

void EventFramework::registerContinuousKeyHandler(SDL_Scancode code, std::vector<State> states, InstantAction handler, bool unpress) {
    for (var state : states) {
        if (unpress) continuousKeyUnpressHandlers[state][code] = handler;
        else continuousKeyPressHandlers[state][code] = handler;
    }
}

