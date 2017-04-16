//
//  Texturey2.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/14/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Texturey_cpp
#define Texturey_cpp

#include "Game.hpp"
#include "functionlibraries.h"

namespace Games { namespace Texturey {
    inline let directionChangeProbability = 0.4;
    inline let animalSpeed = 1.5f;
    
    inline void generateAnimal(Game* g, State state) {
        var animal = new Entity();
        var movementTimer = new Timer(3.0);
        animal->willSetup = [animal, g, movementTimer]() {
            animal->texture = new Texture("picture.png");
            animal->velocity = {animalSpeed, 0.0f};
            animal->bounds = {
                {
                    arc4random_uniform(g->window.uv.width()) + g->window.uv.left,
                    arc4random_uniform(g->window.uv.height()) + g->window.uv.bottom
                }, 1, 1
            };
            movementTimer->action = Movements::randomDirection(animal, g, directionChangeProbability);
        };
        animal->onCollide = Collisions::penCheck(animal, g);
        
        g->timers[state].insert(movementTimer);
        g->frames[state].insert(animal);
    }
    
    inline void generateWalls(Game* g, State state) {
        let wallWidth = 0.01f;
        for (var i = 0; i < 4; ++i) {
            var wall = new Entity();
            switch (static_cast<Vec2::Direction>(i + 1)) {
                case Vec2::left:
                    wall->bounds = {
                        g->window.uv.bottomLeft(),
                        wallWidth, g->window.uv.height()
                    };
                    break;
                case Vec2::right:
                    wall->bounds = {
                        g->window.uv.bottomRight(),
                        -wallWidth, g->window.uv.height()
                    };
                    break;
                case Vec2::down:
                    wall->bounds = {
                        g->window.uv.bottomLeft(),
                        g->window.uv.width(), wallWidth
                    };
                    break;
                case Vec2::up:
                    wall->bounds = {
                        g->window.uv.topLeft(),
                        g->window.uv.width(), -wallWidth
                    };
                    break;
                default: SDL_assert(false);
            }
            wall->texture = new Texture("blueLine.png");
            //wall->hidden = true;
            g->frames[state].insert(wall);
        }
    }
    
    inline void setupGame(Game* game) {
        game->createState(RUNNING);
        for (var i = 0; i < 10; ++i) {
            generateAnimal(game, RUNNING);
        }
        generateWalls(game, RUNNING);
        game->changeState(RUNNING);
    }
    
    inline void play() {
        var game = new Game("Texturey");
        setupGame(game);
        game->start();
    }
} }

#endif
