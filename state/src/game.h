#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <array>
#include "game_state.h"
#include "aux_states.h"
#include "playing_state.h"

// Klasa koja predstavlja igru.
class Game{
public:
    Game();
    void run();
    void changeState(GameState::State newState){ mpCurrentGameState = mpGameStates[newState]; }
    void settime(sf::Time t)
    {
        mTimePerFrame=t;
    }
    sf::Time gettime()
    {
        return mTimePerFrame;
    }
    sf::Font getfont()
    {
        return font;
    }
    int daj()
    {
        return mpGameStates[GameState::Playing]->getbodovi();
    }

    sf::RenderWindow mWindow;
    sf::Font font;
private:
    void processEvents();
    GameState *      mpCurrentGameState;
    std::array<GameState*,GameState::Count> mpGameStates;
    sf::Time         mTimePerFrame;
};

#endif // GAME-V1_H_INCLUDED
