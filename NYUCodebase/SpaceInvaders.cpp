//
//  SpaceInvaders.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/17/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"
#include "functionlibraries.h"

namespace Games { namespace SpaceInvaders {
    inline Vec2 PLAYER_SIZE = {1.f, 1.f};
    inline Vec2 PLAYER_PADDING = {0.2f, 0.1f};
    inline float PLAYER_SPEED = 3.f;
    
    inline void setupGame(Game* g) {
        var spriteSheet = Rectangle::generateGrid(1, 3);
        
        var playerCollisionDetection = [](Entity* entity, Game* g) -> CollisionAction {
            return [entity, g](Entity* other, float elapsed) {
                guard (other->category == WALL_INFO.category) else { return; }
                Collisions::penCheck(entity, g, Collisions::nah, Collisions::nonresponsive)(other, elapsed);
            };
        };
        
        g->createState(RUNNING);
        var walls = Generation::generateWalls(/* With Game: */  g,
                                              /* For State: */  RUNNING,
                                              /* Visibility: */ false);
        
        var player1 = Generation::generatePlayer(/* With Game: */       g,
                                                 /* For State: */       RUNNING,
                                                 /* In Area: */         {g->window.uv.bottomLeft() + PLAYER_PADDING,
                                                                        PLAYER_SIZE.x,
                                                                        PLAYER_SIZE.y},
                                                 /* With Speed: */      PLAYER_SPEED,
                                                 /* Controlled with: */ EventFramework::ControlSchemes::ArrowKeys_LEFTRIGHT,
                                                 /* On Collision: */    playerCollisionDetection);
        player1->texture = new Texture("invaderssheetnew.png", spriteSheet[2]);
        g->registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING}, [=]() {
            var bullet = new Entity();
            Generation::configureAndInsertBullet(g, RUNNING, bullet, player1, category, Vec2::Direction::up, 10.f, [](Entity* bullet, Game* g) {
                return Collisions::penCheck(bullet, g, Collisions::uncollide, Collisions::bounce);
            });
        });
        g->changeState(RUNNING);
    }
    
    inline void play() {
        Game* game = new Game("Space Invaders");
        setupGame(game);
        game->start();
    }
}}
