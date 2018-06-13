#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "sceneGraph.h"
#include "world.h"

class Game{
public:
    Game();
    void run();
private:
    // Procesiraj događaje
    void processEvents();
    // konstruiraj novo stanje igre
    void update(sf::Time const &);
    // iscrtaj novo stanje
    void render();
private:
    // implementacijski detalji
    void handleKeyInput(sf::Keyboard::Key code);
    void handleMouseInput(sf::Mouse::Button button, bool isPressed);
    void handleMovement(sf::Event::MouseMoveEvent);

    sf::RenderWindow mWindow;
    sf::Vector2i Pocpozmisa; // ovo ja imam
    sf::Vector2i Novapozmisa;    // ovo ja imam
    sf::Time mTimePerFrame;

    World mWorld;
};


#endif

