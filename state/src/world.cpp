
// Implementacija World klase.
#include "world.h"
#include <ctime>
#include <random>

// Implementacija klase World dolazi ovdje.


World::World(sf::Vector2i windowSize)
{
    mBlockSize=16;
    mWindowSize=windowSize;
    respawnApple();
    mApple.setFillColor(sf::Color::Red);
    mApple.setRadius(mBlockSize/2);
    for(int i=0;i<4;++i){
        mBounds[i].setFillColor(sf::Color(150,0,0));
        if(!((i+1)%2)){
            mBounds[i].setSize(sf::Vector2f(mWindowSize.x,mBlockSize));
        }else{
            mBounds[i].setSize(sf::Vector2f(mBlockSize,mWindowSize.y));
        }
        if(i<2){
            mBounds[i].setPosition(0,0);
        }else{
            mBounds[i].setOrigin(mBounds[i].getSize());
            mBounds[i].setPosition(sf::Vector2f(mWindowSize));
        }
    }
}

void World::respawnApple()
{
    int maxX=(mWindowSize.x/mBlockSize)-2;
    int maxY=(mWindowSize.y/mBlockSize)-2;
    mitem=sf::Vector2i(rand()%maxX+1, rand()%maxY+1);
    mApple.setPosition(mitem.x*mBlockSize,mitem.y*mBlockSize);
}

void World::update(Snake &snake)
{
    if(snake.getPosition()==mitem){
        snake.extend();
        snake.increaseScore();
        respawnApple();
    }
    int gridSize_x=mWindowSize.x/mBlockSize;
    int gridSize_y=mWindowSize.y/mBlockSize;
    if(snake.getPosition().x<=0 || snake.getPosition().y<=0 || snake.getPosition().x>=gridSize_x-1 || snake.getPosition().y>=gridSize_y-1){
        snake.lose();
    }
}


void World::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    for(int i=0; i<4; ++i){
      target.draw(mBounds[i]);
    }
    target.draw(mApple);

}
