#include "game.h"
#include<math.h>
#include<cmath>
// Implementacija Game klase dolazi ovdje.

using namespace sf;

Game::Game():mWindow(VideoMode(800, 600), "Snake game"),mSnake(mWorld.getBlockSize()),mWorld(Vector2i(800,600))
{
    mTimePerFrame = seconds(1.0/mSnake.getSpeed());
}

void Game::run()
{
    Clock clock;
    Time timeSinceLastUpdate = Time::Zero;

       while(mWindow.isOpen())
       {
           processEvents();
           timeSinceLastUpdate += clock.restart();
           while(timeSinceLastUpdate > mTimePerFrame)
           {
               processEvents();
               update(mTimePerFrame);
               timeSinceLastUpdate -= mTimePerFrame;
               render();
           }
           render();
       }

}

void Game::processEvents()
{
    Event event;
    while(mWindow.pollEvent(event))
    {
        switch (event.type)
        {
            case Event::Closed:
                mWindow.close();
                break;
            case Event::KeyPressed:
                handlePlayerInput(event.key.code);
                break;
        }
    }
}

void Game::update(Time dt)
{
        mSnake.update();
        mWorld.update(mSnake);

        if(mSnake.hasLost()){
            mSnake.reset();
        }
}

void Game::render()
{
    mWindow.clear();

    mWindow.draw(mWorld);
    mWindow.draw(mSnake);

    mWindow.display();
}

void Game::handlePlayerInput(Keyboard::Key code)
{
    if(code==Keyboard::Up && mSnake.getDirection()!=Direction::Down)
        mSnake.setDirection(Direction::Up);
    else if(code==Keyboard::Down && mSnake.getDirection()!=Direction::Up)
        mSnake.setDirection(Direction::Down);
    else if(code==Keyboard::Left && mSnake.getDirection()!=Direction::Right)
        mSnake.setDirection(Direction::Left);
    else if(code==Keyboard::Right && mSnake.getDirection()!=Direction::Left)
        mSnake.setDirection(Direction::Right);
}
