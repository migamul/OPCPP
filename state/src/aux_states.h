#ifndef AUX_STATES_H
#define AUX_STATES_H

#include "game_state.h"

// Sva pomoćna stanja (osim PlayingState). Njihove implementacije
// su prilično slične pa ih možemo grupirati u jedan file.

class Game;

class WelcomeState : public GameState
{
public:
    WelcomeState(Game *game);
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();
    int getbodovi(){}
private:
    sf::Text text;
    sf::Text obavijest;
};

class ExitingState : public GameState
{
public:
    ExitingState(Game *game);
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();
    int getbodovi(){}
private:
    sf::Text title1;
    sf::Text title2;
    sf::Text title3;

    int koliko;
};

class WonState : public GameState
{
public:
    WonState(Game *game);
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();
    int getbodovi(){}
private:
    sf::Text text;
    sf::Text text1;
    sf::Text obavijest1;
};

class LostState : public GameState
{
public:
    LostState(Game *game);
    void update(sf::Time dt);
    void handlePlayerInput(sf::Keyboard::Key code);
    void render();
    int getbodovi(){}
private:
    sf::Text text;
    sf::Text text1;
    sf::Text obavijest1;
};

#endif // AUX_STATES_H
