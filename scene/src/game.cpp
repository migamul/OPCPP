#include "game.h"
#include "world.h"

// Implementacija klase Game.

#include <list>

Game::Game() : mWindow(sf::VideoMode(800,800), "Prozor"), mWorld(mWindow)
{
    mTimePerFrame=sf::seconds(1.f/50.f);
}

void Game::run()
{
    sf::Clock clock; // defaultni konstruktor starta sat
    // vrijeme od zadnjeg poziva funkciji update()
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       // stavi clock na nulu i vrati protekli interval
       timeSinceLastUpdate += clock.restart();
       // updatiraj eventualno više puta ako je iscrtavanje bilo sporo
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();
          update(mTimePerFrame);
       }
       render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while( mWindow.pollEvent(event))
    {
        switch(event.type){
        case sf::Event::Closed:
                mWindow.close();break;
        case sf::Event::MouseButtonPressed:
                handleMouseInput(event.mouseButton.button,true);
                    break;

        case sf::Event::MouseMoved:
            handleMovement(event.mouseMove);
            break;
        case sf::Event::MouseButtonReleased:
        handleMouseInput(event.mouseButton.button,false);
            break;
        case sf::Event::KeyPressed:
            handleKeyInput(event.key.code);
            break;
        default:
            break;
        }

    }
}

void Game::update(const sf::Time &t)
{
mWorld.update(t);
}

void Game::render()
{
     mWindow.clear();

    mWorld.draw();

     mWindow.display();
}

void Game::handleMouseInput(sf::Mouse::Button button, bool isPressed){
    if(!isPressed) mWorld.Eagle->PostaviP(0);
    else if(button!=sf::Mouse::Left)return;
    else mWorld.Eagle->PostaviP(1);
}

void Game::handleMovement(sf::Event::MouseMoveEvent event){

            sf::Vector2i Mis=sf::Mouse::getPosition(mWindow);
            mWorld.Eagle->setDirection(Mis);
}

void Game::handleKeyInput(sf::Keyboard::Key code){
            if(code == sf::Keyboard::H)mWorld.Eagle->removeComponent("Raptor2");
            if(code == sf::Keyboard::J)mWorld.Eagle->removeComponent("Raptor1");
            if(code == sf::Keyboard::K)mWorld.Eagle->removeComponent("Raptor3");
            if(code == sf::Keyboard::L)mWorld.Eagle->removeComponent("Raptor4");
}
