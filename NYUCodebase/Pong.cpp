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
    inline var PLAYER_IDENTIFIER = "player";
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
    
    inline SpriteSheet* loadFont(std::string fontName, int rows, int cols, float xSpacing, std::string alphabet) {
        var font = new SpriteSheet();
        font->sheetName = fontName;
        font->xSpacing = xSpacing;
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                let index = row * cols + col;
                guard (index < alphabet.length()) else { return font; }
                font->atlas.insert({
                    std::string(1, alphabet[index]),
                    {{1.f/16 * col, 1.f/16 * row}, 1.f/cols, 1.f/rows}
                });
            }
        }
        return font;
    }
    
    inline Entity* generatePlayer(Game* g, State state, Vec2 origin, ControlScheme scheme) {
        Entity* player = new Entity();
        player->willSetup = [=](){
            player->identifier = PLAYER_IDENTIFIER;
            player->texture = new Texture("whiteLine.png");
            Vec2 size = {
                origin.x + PLAYER_SIZE.x > g->window.uv.right ? -PLAYER_SIZE.x : PLAYER_SIZE.x,
                origin.y + PLAYER_SIZE.y > g->window.uv.top ? -PLAYER_SIZE.y : PLAYER_SIZE.y,
            };
            Vec2 padding = {
                size.x < 0 ? -PLAYER_PADDING.x : PLAYER_PADDING.x,
                size.y < 0 ? -PLAYER_PADDING.y : PLAYER_PADDING.y
            };
            player->bounds = {
                padding + origin,
                size.x,
                size.y
            };
            for (var control in scheme) {
                g->registerKeyHandler(control.second, {state}, [=]() {
                    player->velocity = Vec2::directionVector(control.first) * PLAYER_SPEED;
                });
                g->registerKeyHandler(control.second, {state}, [=]() {
                    player->velocity = {};
                }, true);
            }
            player->onCollide = [=](Entity* entity, float elapsed) {
                guard (entity->identifier == WALL_IDENTIFIER) else { return; }
                Collisions::penCheck(player, g)(entity, elapsed);
            };
        };
        g->frames[state].insert(player);
        return player;
    }
    
    inline Entity* generateBall(Game* g, State state) {
        Entity* ball = new Entity();
        ball->willSetup = [=]() {
            ball->texture = new Texture("whiteLine.png");
            ball->bounds = {
                g->window.uv.center() - BALL_SIZE * 0.5f,
                BALL_SIZE.x,
                BALL_SIZE.y
            };
            ball->velocity = {BALL_SPEED};
            ball->onCollide = [=](Entity* entity, float elapsed){
                guard (!(entity->identifier == WALL_IDENTIFIER && entity->bounds.height() == g->window.uv.height())) else { g->changeState(LOSE); return; }
                Collisions::penCheck(ball, g)(entity, elapsed);
            };
        };
        g->frames[state].insert(ball);
        return ball;
    }
    
    inline void setupGame(Game* g) {
        var font = loadFont("font1.png", 16, 16, 0.2f, alphabet);
        
        g->createState(RUNNING);
        Generation::generateWalls(g, RUNNING, false);
        generatePlayer(g, RUNNING, g->window.uv.topLeft(), EventFramework::ControlSchemes::WASD_UPDOWN);
        generatePlayer(g, RUNNING, g->window.uv.bottomRight(), EventFramework::ControlSchemes::ArrowKeys_UPDOWN);
        generateBall(g, RUNNING);
        
        g->createState(PAUSED);
        Generation::generateText(g, PAUSED, "The\ngame\nis\ncurrently\npaused.", 6.f, font, g->window.uv);
        
        g->createState(LOSE);
        Generation::generateText(g, LOSE, "Game Over!", 10.f, font, g->window.uv);
        
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
