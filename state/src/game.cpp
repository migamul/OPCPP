#include "game.h"

// Implementacija Game klase

Game::Game():mWindow(sf::VideoMode(800, 600), "Snake game")
{
    mTimePerFrame = sf::seconds(1.0);
    mpGameStates[GameState::Welcome] = new WelcomeState(this);
    mpGameStates[GameState::Playing] = new PlayingState(this);
    mpGameStates[GameState::Won] = new WonState(this);
    mpGameStates[GameState::Lost] = new LostState(this);
    mpGameStates[GameState::Exiting] = new ExitingState(this);
    mpCurrentGameState=mpGameStates[GameState::Welcome];

    if(!font.loadFromFile("Comfortaa-Bold.ttf"))
            throw std::runtime_error("Cannot load fonts Comfortaa-Bold.ttf");
}

void Game::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while(mWindow.isOpen())
    {
       processEvents();
       timeSinceLastUpdate += clock.restart();
       while(timeSinceLastUpdate > mTimePerFrame)
       {
          timeSinceLastUpdate -= mTimePerFrame;
          processEvents();

          mpCurrentGameState->update(mTimePerFrame);
       }
       mWindow.clear();
       mpCurrentGameState->render();
       mWindow.display();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while(mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                mWindow.close();
                break;
            case sf::Event::KeyPressed:
                mpCurrentGameState->handlePlayerInput(event.key.code);
                break;
        }
    }
}
