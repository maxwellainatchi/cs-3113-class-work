//
//  Pong.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 2/20/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Pong_hpp
#define Pong_hpp

#include "Game.hpp"

namespace Games {
    class Pong: public Graphics::Game {
    public:
        // Configuration
        constexpr static const float wallSize = 0.1f;
        static const int lineCount = 10;
        constexpr static const float linePadding = 0.2f;
        constexpr static const float playerSpeed = 1.5f;
        constexpr static const float ballSpeed = 2.0f;
        
        // Class
        Pong();
        
        Graphics::SpriteSheet* spriteSheet = new Graphics::SpriteSheet("whiteline.png", {1,1}, {"whiteline"});
        
        Entities::Player* player1;
        Entities::Player* player2;
        Entities::Ball* ball;
        Position::Rectangle workingArea;
        std::vector<Entities::Entity*> walls;
        std::vector<Entities::Entity*> midLine;
        
        Position::Vector2D crownSize;
        std::vector<Entities::Entity*> player1Lives;
        std::vector<Entities::Entity*> player2Lives;
        
        bool paused;
        
        void checkPaddleCollision();
        void resetLives();
        void drawWalls();
        void drawCenterLine();
        int didLose();
        
        // Inherited
        virtual void setup();
        virtual void update(float elapsed);
        virtual void render();
    };
}

#endif /* Pong_hpp */
