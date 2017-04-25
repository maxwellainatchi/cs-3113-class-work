//
//  Pong.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 4/16/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Game.hpp"
#include "functionlibraries.h"

#define LOSE "lose"

namespace Games { namespace Pong {
    inline Vec2 PLAYER_SIZE = {0.1f, 1.0f};
    inline Vec2 PLAYER_PADDING = {0.2f, 0.1f};
    inline float PLAYER_SPEED = 3.f;
    inline Vec2 BALL_SIZE = {0.1f};
    inline float BALL_SPEED = 4.f;
    inline var BALL_IDENTIFIER = "ball";

    inline std::string alphabet =
    std::string(16, (char) 26) +
    std::string(16, (char) 26) +
    " !\"#$%&'()*+,-./"
    "0123456789:;<=>?"
    "@ABCDEFGHIJKLMNO"
    "PQRSTUVWXYZ[\\]^_"
    "`abcdefghijklmno"
    "pqrstuvwxyz{|}~␀";
    
    inline Entity* generatePongBall(Game* g, State state) {
        Entity* ball = new Entity();
        ball->willSetup = [=]() {
            ball->texture = new Texture("whiteLine.png");
            ball->identifier = BALL_IDENTIFIER;
            ball->bounds = {
                g->window.uv.center() - BALL_SIZE * 0.5f,
                BALL_SIZE.x,
                BALL_SIZE.y
            };
            ball->velocity = {BALL_SPEED};
            ball->onCollide = [=](Entity* entity, float elapsed){
                guard (!(entity->identifier == WALL_INFO.identifier &&
                         entity->bounds.height() == g->window.uv.height())) else { g->changeState(LOSE); return; }
                Collisions::penCheck(ball, g, Collisions::uncollide, Collisions::bounce)(entity, elapsed);
            };
        };
        g->frames[state].insert(ball);
        return ball;
    }
    
    inline void setupGame(Game* g) {
        var font = Generation::loadFont(/* Filename: */             "font1.png",
                                        /* Number of Rows: */       16,
                                        /* Number of Cols: */       16,
                                        /* Horizontal Spacing: */   0.2f,
                                        /* Using String: */         alphabet);
        var playerCollisionDetection = [](Entity* entity, Game* g) -> CollisionAction {
            return [entity, g](Entity* other, float elapsed) {
                guard (other->identifier == WALL_INFO.identifier) else { return; }
                Collisions::penCheck(entity, g, Collisions::uncollide, Collisions::nonresponsive)(other, elapsed);
            };
        };
        
        // MARK: Running
        g->createState(RUNNING);
        var walls = Generation::generateWalls(/* With Game: */  g,
                                              /* For State: */  RUNNING,
                                              /* Visibility: */ false);
        
        var player1 = Generation::generatePlayer(/* With Game: */       g,
                                                 /* For State: */       RUNNING,
                                                 /* In Area: */         {g->window.uv.topLeft() + Vec2(PLAYER_PADDING.x, -PLAYER_PADDING.y),
                                                                        PLAYER_SIZE.x,
                                                                        -PLAYER_SIZE.y},
                                                 /* With Speed: */      PLAYER_SPEED,
                                                 /* Controlled with: */ EventFramework::ControlSchemes::WASD_UPDOWN,
                                                 /* On Collision: */    playerCollisionDetection);
        
        var player2 = Generation::generatePlayer(/* With Game: */       g,
                                                 /* For State: */       RUNNING,
                                                 /* In Area: */         {g->window.uv.bottomRight() + Vec2(-PLAYER_PADDING.x, PLAYER_PADDING.y),
                                                                        -PLAYER_SIZE.x,
                                                                        PLAYER_SIZE.y},
                                                 /* With Speed: */      PLAYER_SPEED,
                                                 /* Controlled with: */ EventFramework::ControlSchemes::ArrowKeys_UPDOWN,
                                                 /* On Collision: */    playerCollisionDetection);
        var ball = generatePongBall(g, RUNNING);
        
        // MARK: Paused
        g->createState(PAUSED);
        var pausedText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      PAUSED,
                                                  /* Showing Text: */   "The\ngame\nis\ncurrently\npaused.",
                                                  /* Given Height: */   6.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        // MARK: Game Over
        g->createState(LOSE);
        var losingText = Generation::generateText(/* With Game: */      g,
                                                  /* For State: */      LOSE,
                                                  /* Showing Text: */   "Game Over!",
                                                  /* Given Height: */   10.f,
                                                  /* Using Font: */     font,
                                                  /* Within Bounds: */  g->window.uv);
        
        // MARK: Misc
        g->registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING, PAUSED}, [g]() {
            g->changeState(g->state == PAUSED ? RUNNING : PAUSED);
        });
        g->changeState(PAUSED);
    }
    
    inline void play() {
        Game* game = new Game("Pong");
        setupGame(game);
        game->start();
    }
}}
