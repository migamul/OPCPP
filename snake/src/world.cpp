#include "world.h"
#include <ctime>
#include <random>

using namespace sf;

// Implementacija klase World dolazi ovdje.


World::World(sf::Vector2i windowSize)
{
    mBlockSize = 16;

    mWindowSize = windowSize;
    respawnApple();
    mApple.setFillColor(Color::Red);
    mApple.setRadius(mBlockSize / 2);

    int i;
    for(i = 0; i < 4; ++i)
    {
        mBounds[i].setFillColor(Color(150,0,0));
        if(!( (i + 1) % 2 ))
            mBounds[i].setSize(Vector2f(mWindowSize.x, mBlockSize));
        else
            mBounds[i].setSize(Vector2f(mBlockSize, mWindowSize.y));
        if(i < 2)
            mBounds[i].setPosition(0,0);
        else
        {
            mBounds[i].setOrigin(mBounds[i].getSize());
            mBounds[i].setPosition(Vector2f(mWindowSize));
        }
    }
}

void World::respawnApple()
{
    int X = (mWindowSize.x / mBlockSize) - 2;
    int Y = (mWindowSize.y / mBlockSize) - 2;

    apple = Vector2i(rand() % X + 1, rand() % Y + 1);
    mApple.setPosition(apple.x * mBlockSize, apple.y * mBlockSize);
}

void World::update(Snake &snake)
{
    if(snake.getPosition() == apple)
    {
        snake.extend();
        snake.increaseScore();
        respawnApple();
    }

    int gridX = mWindowSize.x / mBlockSize;
    int gridY = mWindowSize.y / mBlockSize;

    if(snake.getPosition().x <= 0 || snake.getPosition().y <= 0
            || snake.getPosition().x >= gridX - 1 || snake.getPosition().y >= gridY - 1)
        snake.lose();
}

void World::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    for(int i = 0; i < 4; ++i)
      target.draw(mBounds[i]);
    target.draw(mApple);
}
