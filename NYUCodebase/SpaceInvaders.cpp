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
    inline Vector PLAYER_SIZE = {1.f, 1.f};
    inline Vector PLAYER_PADDING = {0.2f, 0.1f};
    inline float PLAYER_SPEED = 3.f;
    
    inline void setupGame(Game* g) {
        var spriteSheet = Grid(IntPair(1,3));
        IntPair enemyGridSize = {5, 8};
        Vector enemySize = {3,-3}, enemyPadding = {.5f, .2f};
        var enemyGrid = Grid(enemyGridSize, {1}, enemySize, enemyPadding);
        
        var playerCollisionDetection = [](Entity* entity, Game* g) -> CollisionAction {
            return [entity, g](Entity* other, float elapsed) {
                guard (other->category == WALL_INFO.category) else { return; }
                Collisions::penCheck(entity, g, Collisions::moveWithout, Collisions::stopDead)(other, elapsed);
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
        player1->texture = new Texture("invaderssheetnew.png", *spriteSheet[{0, 2}]);
        
        var queueEnemyDownwardMovement = new bool(false);
        var queueEnemyReverseVelocity = new bool(false);
        std::vector<Entity*> enemies;
        for (int row = 0; row < enemyGrid.rows(); ++row) {
            for (int col = 0; col < enemyGrid.cols(); ++col) {
                var enemy = new Entity();
                enemy->category = "enemy";
                enemy->name = "("+std::to_string(row)+","+std::to_string(col)+")";
                enemy->bounds = *enemyGrid[{row, col}];
                enemy->bounds += {-g->window.uv.width()/2.f + 0.5f, g->window.uv.height()/2.f - 0.5f};
                enemy->paused = true;
                enemy->velocity = {20.f, 0.f};
                enemy->texture = new Texture("invaderssheetnew.png", *spriteSheet[{0, 1}]);
                enemy->willUpdate = [=](float elapsed) {
                    if (!enemy->paused) {
                        enemy->paused = true;
                    }
                    if (*queueEnemyReverseVelocity) {
                        enemy->velocity.x *= -1;
                        enemy->bounds = enemy->projectedPosition(elapsed, false);
                    }
                    if (*queueEnemyDownwardMovement) enemy->velocity.y = (enemySize.y + enemyPadding.y) * 5;
                    else enemy->velocity.y = 0;
                };
                enemy->onCollide = [=](Entity* other, float elapsed) {
                    guard (other->category == WALL_INFO.category) else { return; }
                    *queueEnemyReverseVelocity = true;
                    *queueEnemyDownwardMovement = true;
                };
                g->frames[RUNNING].insertDynamic(enemy);
                enemies.push_back(enemy);
            }
        }
        
        var enemyMovementTimer = new Timer(.05f, [=]() {
            for (var enemy in enemies) {
                enemy->paused = false;
            }
            // Timer happens before collision detection, so this will be triggered next cycle
            if (*queueEnemyDownwardMovement) *queueEnemyDownwardMovement = false;
            if (*queueEnemyReverseVelocity) *queueEnemyReverseVelocity = false;
        });
        g->timers[RUNNING].insert(enemyMovementTimer);
        
        g->registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING}, [=]() {
            var bullet = new Entity();
            Generation::configureAndInsertBullet(g, RUNNING, bullet, player1, category, Direction::up, 10.f, [](Entity* bullet, Game* g) {
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
