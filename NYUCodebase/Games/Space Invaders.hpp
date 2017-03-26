//
//  Space Invaders.hpp
//  NYUCodebase
//
//  Created by Max Ainatchi on 3/2/17.
//  Copyright © 2017 Ivan Safrin. All rights reserved.
//

#ifndef Space_Invaders_hpp
#define Space_Invaders_hpp

#define WIN "win"
#define LOSE "lose"

#include "Game.hpp"

namespace Games {
    struct Assets {
        struct Images {
            cstatic let whiteLine = "whiteline.png";
            cstatic let spritesheet = "invaderssheetnew.png";
        };
        struct Sprites {
            cstatic let player = "ship";
            struct Enemies {
                cstatic let base = "invader";
                cstatic let first = "invader1";
                cstatic let second = "invader2";
            };
        };
        struct Text {
            cstatic let paused = " GAME   IS  PAUSED";
            cstatic let win = "        YOU   WIN ";
            cstatic let lose = "       DEAD  BEEF ";
        };
    };
    
    class SpaceInvaders: public Graphics::Game {
    private:
        // Config
        const int numCols = 8;
        const int numRows = 3;
        const float enemyScale = 0.25;
        const Position::Vector2D bulletSize = {0.02f, 0.1f};
        Position::Vector2D enemyVelocity = {0.05f, -0.1f};
        const float enemyShootChance = 0.2;
        
        // Entities
        Entities::TitleText* pausedText;
        Graphics::SpriteSheet* spriteSheet;
        Entities::Player* player1;
        std::vector<Entities::Sprite*> enemies;
        std::set<Entities::Bullet*> bullets;
        
        // Timers
        Graphics::Timer* enemyMovementTimer = new Graphics::Timer(0.1);
        Graphics::Timer* playerBulletTimer = new Graphics::Timer(0.3);
        Graphics::Timer* enemyBulletTimer = new Graphics::Timer(0.3);
        
        // Misc
        bool playerCanFire = true;
        int livingEnemies;
    public:
        SpaceInvaders();
        
        /// Generates a player and adds it to the frame
        Entities::Player* generatePlayer();
        
        /// Generates an enemy and adds it to the frame
        Entities::Sprite* generateEnemy(Position::Point origin, int enemyType);
        
        /// Generates a grid of enemies centered onscreen
        void generateEnemyGrid(int numRows, int numCols);
        
        /// Generates a bullet from the player or a random enemy
        void generateBullet(bool fromEnemy = false);
        
        /// Resets the game
        void reset();
        
        // Inherited
        virtual void setup();
        virtual void willStart();
    };
}

#endif /* Space_Invaders_hpp */
