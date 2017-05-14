
#define STB_IMAGE_IMPLEMENTATION

#define DEBUG 1

#include "Game.hpp"

#include "Texturey2.cpp"
#include "Pong.cpp"
#include "SpaceInvaders.cpp"
#include "Platformer.cpp"

// Enum value corresponds to HW number
enum class GameType: int {
    Texturey = 1,
    Pong = 2,
    SpaceInvaders = 3,
    Platformer = 4
};

int main(int argc, char *argv[]) {
    LOG("Starting Logger", INFO);
    GameType current = GameType::Platformer;
    if (argc > 1) current = static_cast<GameType>(atoi(argv[1]));
    switch (current) {
        case GameType::Texturey:
            Games::Texturey::play();
            break;
        case GameType::Pong:
            Games::Pong::play();
            break;
        case GameType::SpaceInvaders:
            Games::SpaceInvaders::play();
            break;
        case GameType::Platformer:
            Games::Platformer::play();
            break;
        default: Games::Platformer::play();
    }
    return 0;
}
