
#define STB_IMAGE_IMPLEMENTATION

#include "Game.hpp"

#include "Texturey2.cpp"

// Enum value corresponds to HW number
enum GameType: int {
    Texturey = 1,
    Pong = 2,
    SpaceInvaders = 3
};

int main(int argc, char *argv[]) {
    GameType current = Texturey;
    if (argc > 1) current = static_cast<GameType>(atoi(argv[1]));
    switch (current) {
        case Texturey:
            Games::Texturey::play();
            break;
        default: SDL_assert(false);
    }
    return 0;
}
