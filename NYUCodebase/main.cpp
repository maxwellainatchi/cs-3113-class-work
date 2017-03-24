
#define STB_IMAGE_IMPLEMENTATION

#include "Game.hpp"
#include "games.h"

// Enum value corresponds to HW number
enum GameType: int {
    Texturey = 1,
    Pong = 2,
    SpaceInvaders = 3
};

int main(int argc, char *argv[]) {
    GameType current;
    if (argc > 1)
        current = static_cast<GameType>(atoi(argv[1]));
    Graphics::Game* game;
    switch (current) {
        case Texturey:
            game = new Games::Texturey();
            break;
        case Pong:
            game = new Games::Pong();
            break;
        case SpaceInvaders:
            game = new Games::SpaceInvaders();
            break;
    }
    game->start();
    return 0;
}
