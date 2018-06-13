#ifndef PLAYING_STATE_H
#define PLAYING_STATE_H

#include "game.h"
#include "game_state.h"
#include "snake.h"
#include "world.h"

class Game;

class PlayingState : public GameState{
public:
    PlayingState(Game* _game);
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();
    int getbodovi()
    {
        return koliko_bodova;
    }

private:
    World mWorld;
    Snake mSnake;
    int koliko_bodova;
};


#endif // PLAYING_STATE_H
