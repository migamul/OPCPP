#ifndef GAME_STATE_H
#define GAME_STATE_H
#include <SFML/Graphics.hpp>
// includes ...

class Game;

class GameState
{
public:
    // Sva moguća stanja igre.
    enum State {
        Welcome,
        Playing,
        Won,
        Lost,
        Exiting,
        Count     // Count će dati broj stanja.
    };
    GameState(Game * game) : mpGame(game) {}

    virtual void update(sf::Time dt) = 0;
    virtual void handlePlayerInput(sf::Keyboard::Key code)= 0;
    virtual void render() = 0;
    virtual int getbodovi()=0;
protected:
    Game * mpGame;
    int bodovi=0;
};

#endif // GAME_STATE_H
