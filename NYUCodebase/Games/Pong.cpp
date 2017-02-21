//
//  Pong.cpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#include "Pong.hpp"

namespace Games {
    void Pong::checkPaddleCollision() {
        auto paddle1Bounds = player1->position.bounds();
        auto paddle2Bounds = player2->position.bounds();
        auto bounds = ball->position.bounds();
        if (paddle1Bounds.right > bounds.left && paddle1Bounds.left < bounds.left && paddle1Bounds.top > bounds.top && paddle1Bounds.bottom < bounds.bottom) {
            ball->velocity = {-ball->velocity.x, ball->velocity.y};
        }
        if (paddle2Bounds.left < bounds.right && paddle2Bounds.right > bounds.left && paddle2Bounds.top > bounds.top && paddle2Bounds.bottom < bounds.bottom) {
            ball->velocity = {-ball->velocity.x, ball->velocity.y};
        }
    }
    
    void Pong::resetLives() {
        player1Lives.clear();
        player2Lives.clear();
        
        int numLives = 5;
        float lifePadding = 0.1f;
        float lifeMargin = 0.7f;
        float lifeSize = 0.1f;
        for (int i = 0; i < numLives; ++i) {
            Entities::Entity* life = new Entities::Entity("whiteLine.png");
            life->setCoordinates({
                {
                    workingArea.bounds().left + i*(lifeSize + lifePadding) + lifeMargin,
                    workingArea.bounds().top - lifeSize - lifePadding
                },
                {
                    workingArea.bounds().left + (i+1)*lifeSize + i*lifePadding + lifeMargin,
                    workingArea.bounds().top - lifePadding
                }
            });
            player1Lives.push_back(life);
        }
        
        for (int i = 0; i < numLives; ++i) {
            Entities::Entity* life = new Entities::Entity("whiteLine.png");
            life->setCoordinates({
                {
                    workingArea.bounds().right - i*(lifeSize + lifePadding) - lifeMargin,
                    workingArea.bounds().top - lifeSize - lifePadding
                },
                {
                    workingArea.bounds().right - (i+1)*lifeSize - i*lifePadding - lifeMargin,
                    workingArea.bounds().top - lifePadding
                }
            });
            player2Lives.push_back(life);
        }
    }
    
    void Pong::drawWalls() {
        for (int i = 0; i < 2; ++i) {
            walls.push_back(new Entities::Entity("blueLine.png"));
        }
        walls[0]->setCoordinates({window.uv.topLeft, {
            window.uv.topRight.x,
            window.uv.topRight.y - wallSize
        }});
        walls[1]->setCoordinates({window.uv.bottomLeft, {
            window.uv.bottomRight.x,
            window.uv.bottomRight.y + wallSize
        }});
        
        workingArea = Graphics::Coordinates({
            {window.uv.bounds().left, window.uv.bounds().bottom + wallSize},
            {window.uv.bounds().right, window.uv.bounds().top - wallSize}
        });
    }
    
    void Pong::drawCenterLine() {
        float lineLength = workingArea.height() / lineCount;      for (int i = 0; i < lineCount; ++i) {
            Entities::Entity* segment = new Entities::Entity("blueLine.png");
            segment->setCoordinates({
                {
                    workingArea.center().x - wallSize/2.0f,
                    workingArea.bounds().top - i * lineLength - 0.5f*linePadding
                }, {
                    workingArea.center().x + wallSize/2.0f,
                    workingArea.bounds().top - (i + 1) * lineLength + 0.5f*linePadding
                }
            });
            midLine.push_back(segment);
        }
    }
    
    int Pong::didLose() {
        auto ballBounds = ball->position.bounds();
        auto windowBounds = window.uv.bounds();
        if (ballBounds.right > windowBounds.right)
            return 2;
        else if (ballBounds.left < windowBounds.left)
            return 1;
        else
            return 0;
    }
    
    void Pong::setup() {
        drawWalls();
        drawCenterLine();
        
        resetLives();
        
        //MARK: Mechanics
        player1 = new Entities::Player("whiteLine.png", workingArea);
        player2 = new Entities::Player("whiteLine.png", workingArea);
        ball = new Entities::Ball("whiteLine.png", workingArea);
        
        Graphics::Vector2D paddleSize = {0.1, 0.75};
        Graphics::Vector2D ballSize = {0.1, 0.1};
        Graphics::Vector2D padding = {0.2,0};
        
        Graphics::Coordinates::XY origin1 = {workingArea.bounds().left, workingArea.bounds().top - paddleSize.y};
        origin1 = origin1 + padding;
        
        Graphics::Coordinates::XY origin2 = {workingArea.bounds().right - paddleSize.x, workingArea.bounds().top - paddleSize.y};
        origin2 = origin2 - padding;
        
        Graphics::Coordinates::XY ballOrigin = {
            window.uv.center().x - paddleSize.x / 2,
            window.uv.center().y + paddleSize.y / 2
        };
        
        Graphics::Coordinates bounds1 = Graphics::Coordinates(origin1, origin1 + paddleSize);
        Graphics::Coordinates bounds2 = Graphics::Coordinates(origin2, origin2 + paddleSize);
        Graphics::Coordinates ballBounds = Graphics::Coordinates(ballOrigin, ballOrigin + ballSize);
        
        player1->setCoordinates(bounds1);
        player2->setCoordinates(bounds2);
        ball->setCoordinates(ballBounds);
        
        player1->controlScheme = Graphics::EventFramework::ControlSchemes::ArrowKeys_UPDOWN;
        player2->controlScheme = Graphics::EventFramework::ControlSchemes::WASD_UPDOWN;
        
        player1->registerMovementHandlers(this);
        player2->registerMovementHandlers(this);
        
        registerKeyHandler(SDL_SCANCODE_R, [&] () {
            ball->reset(window.uv);
            if (paused) { paused = false; }
            resetLives();
        });
        
        registerKeyHandler(SDL_SCANCODE_SPACE, [&] () {
            if (player1Lives.size() > 0 && player2Lives.size() > 0) {
                if (ball->paused) {
                    ball->paused = false;
                } else {
                    paused = !paused;
                }
            } else {
                resetLives();
            }
        });
        
        player1->speed = playerSpeed;
        player2->speed = playerSpeed;
        ball->velocity = {ballSpeed, ballSpeed};
        
        //MARK: Rendering
        frame.push_back(player1);
        frame.push_back(player2);
        frame.push_back(ball);
        for (Entities::Entity* wall : walls) {
            frame.push_back(wall);
        }
        for (Entities::Entity* segment : midLine) {
            frame.push_back(segment);
        }
        
        ball->reset(window.uv);
    }
    
    void Pong::update(float elapsed) {
        checkPaddleCollision();
        int loser = didLose();
        if (!ball->paused && loser) {
            if (loser == 1) {
                player1Lives.pop_back();
            } else {
                player2Lives.pop_back();
            }
            ball->reset(workingArea);
            //TODO: TODO: Render losing text
        }
        if (!paused) {
            Graphics::Game::update(elapsed);
            // These are separate because they get removed
            for (Entities::Entity* life : player1Lives) {
                life->update(elapsed);
            }
            for (Entities::Entity* life : player2Lives) {
                life->update(elapsed);
            }
        }
    }
    
    void Pong::render() {
        Game::render();
        for (Entities::Entity* life : player1Lives) {
            life->draw(shader);
        }
        for (Entities::Entity* life : player2Lives) {
            life->draw(shader);
        }
    }
}
