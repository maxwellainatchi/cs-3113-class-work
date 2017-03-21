//
//  Space Invaders.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/2/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Space Invaders.hpp"

namespace Games {
    SpaceInvaders::SpaceInvaders(): Graphics::Game("Space Invaders") {}
    
    Entities::Player* SpaceInvaders::generatePlayer() {
        auto player = new Entities::Player(spriteSheet, "ship", window.uv);
        // Appearance
        player->scale({0.5,0.5});
        player->setOrigin({
            window.uv.center().x,
            window.uv.bounds().bottom
        });
        
        // Movement
        player->controlScheme = ControlSchemes::ArrowKeys_LEFTRIGHT;
        player->registerMovementHandlers(this, {RUNNING});
        player->speed = 2;
        
        // Shooting
        registerKeyHandler(SDL_SCANCODE_SPACE, {RUNNING}, [&] () { generateBullet(); });
        
        frames[RUNNING].insert(player);
        return player;
    }
    
    Entities::Sprite* SpaceInvaders::generateEnemy(Graphics::Coordinates::XY origin, int enemyType) {
        auto enemy = new Entities::Sprite(spriteSheet, "invader" + std::to_string(enemyType));
        if (!enemy->texture.loaded) { return nullptr; }
        enemy->scale(enemyScale);
        enemy->setOrigin(origin);
        enemies.push_back(enemy);
        frames[RUNNING].insert(enemy);
        return enemy;
    }
    
    void SpaceInvaders::generateEnemyGrid(int numRows, int numCols) {
        auto dummyEnemy = generateEnemy({0,0}, 1);
        float padding = window.uv.width()/numRows/2 + dummyEnemy->position.width()/2;
        Graphics::Coordinates::XY origin = {
            window.uv.bounds().right - padding,
            window.uv.bounds().top - dummyEnemy->position.height() - 0.1f
        };
        Graphics::Vector2D offset = {
            window.uv.width() / (numCols + 1),
            dummyEnemy->position.height()
        };
        frames[RUNNING].erase(dummyEnemy);
        for (int row = 0; row < numRows; ++row) {
            for (int col = 0; col < numCols; ++col) {
                generateEnemy(origin, (col % 2 + row % 2) % 2 + 1);
                origin.x -= offset.x;
                if (origin.x < window.uv.bounds().left) {
                    origin.x = window.uv.bounds().right - padding;
                    origin.y -= offset.y;
                }
            }
        }
    }
    
    void SpaceInvaders::generateBullet(bool fromEnemy) {
        Entities::Entity* entity;
        Graphics::Coordinates::XY origin ;
        Graphics::Vector2D velocity = {0,0};
        if (fromEnemy) {
            entity = enemies[arc4random_uniform((uint)enemies.size())];
            origin.y = entity->position.bounds().bottom - bulletSize.y;
            velocity.y = -2.0f;
        } else {
            if (!playerCanFire) { return; }
            playerCanFire = false;
            playerBulletTimer->start();
            entity = player1;
            origin.y = entity->position.bounds().top;
            velocity.y = 3.0f;
        }
        origin.x = entity->position.center().x;
        auto bullet = new Entities::Bullet("whiteline.png", window.uv, velocity);
        bullet->setCoordinates({
            origin,
            bulletSize.x,
            bulletSize.y
        });
        bullet->onCollide = [&, bullet, fromEnemy] (Entities::Entity* otherEntity) {
            if (otherEntity == bullet) return;
            if (fromEnemy && otherEntity != player1) return;
            otherEntity->hidden = true;
            otherEntity->intangible = true;
            bullet->hidden = true;
            bullet->intangible = true;
            if (!fromEnemy) {
                --livingEnemies;
//                auto iter = std::find(enemies.begin(), enemies.end(), otherEntity);
//                if (iter == enemies.end()) return;
//                enemies.erase(iter);
                if (!livingEnemies) {
                    this->state = WIN;
                }
            } else {
                this->state = LOSE;
            }
        };
        bullets.insert(bullet);
        frames[RUNNING].insert(bullet);
    }
    
    void SpaceInvaders::reset() {
        if (player1 != nullptr) {
            player1->hidden = false;
            player1->intangible = false;
        } else {
            player1 = generatePlayer();
        }
        if (enemies.size()) {
            for (auto enemy : enemies) {
                enemy->hidden = false;
                enemy->intangible = false;
            }
        } else {
            generateEnemyGrid(numRows, numCols);
        }
        livingEnemies = numRows*numCols;
        for (auto bullet : bullets) {
            frames[RUNNING].erase(bullet);
        }
        
    }
    
    void SpaceInvaders::setup() {
        pausekey = SDL_SCANCODE_P;
        registerKeyHandler(SDL_SCANCODE_SPACE, {WIN, LOSE}, [&] () {
            this->reset();
            this->state = RUNNING;
        });
        
        
        playerBulletTimer->action = [&] () {
            playerCanFire = true;
            this->playerBulletTimer->stop();
        };
        enemyMovementTimer->action = [&] () {
            if (enemies.size() == 0) { return; }
            auto offset = Graphics::Vector2D();
            auto without = enemies.back()->withoutness(window.uv);
            if (without.x < 0) {
                enemyVelocity.x = -enemyVelocity.x;
                offset.y = enemyVelocity.y;
            }
            without = enemies[0]->withoutness(window.uv);
            if (without.x > 0) {
                enemyVelocity.x = -enemyVelocity.x;
                offset.y = enemyVelocity.y;
            }
            offset.x = enemyVelocity.x;
            for (auto enemy: enemies) {
                enemy->translate(offset);
            }
        };
        enemyBulletTimer->action = [&] () {
            if (arc4random_uniform(UINT32_MAX) < enemyShootChance * UINT32_MAX) {
                this->generateBullet(true);
            }
        };
        
        // Add all the timers
        timers[RUNNING].insert(playerBulletTimer);
        timers[RUNNING].insert(enemyMovementTimer);
        timers[RUNNING].insert(enemyBulletTimer);
        
        // Running frame
        spriteSheet = new Graphics::SpriteSheet("invaderssheetnew.png", {0.33,1}, {"invader1", "invader2", "ship"});
        reset();
        
        
        // Paused frame
        pausedText = new Entities::TitleText(" GAME   IS  PAUSED", {});
        frames[WIN].insert(new Entities::TitleText("        YOU   WIN ", {}));
        frames[LOSE].insert(new Entities::TitleText("       DEAD  BEEF ", {}));
        frames[PAUSED].insert(pausedText);
    }
    
    void SpaceInvaders::willStart() {
        enemyMovementTimer->start();
        enemyBulletTimer->start();
        playerBulletTimer->start();
        state = RUNNING;
    }
}
