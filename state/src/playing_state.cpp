#include "playing_state.h"

// Implementacija PlayingState klase

PlayingState::PlayingState(Game *_game):GameState(_game), mSnake(mWorld.getBlockSize()),mWorld(sf::Vector2i(800,600))
{
    mpGame->settime(sf::seconds(1.0/mSnake.getSpeed()));
}

void PlayingState::update(sf::Time dt)
{
        mSnake.update();
        mWorld.update(mSnake);
        if(mSnake.hasLost()){

            if(mSnake.getScore()<100)
            {
             mpGame->changeState(GameState::Lost);

            }
            else
            {
                mpGame->changeState(GameState::Won);
            }
            koliko_bodova=mSnake.getScore();
            mSnake.reset();

            mpGame->settime(sf::seconds(1.0/(mSnake.getSpeed()*2)));
        }

}

void PlayingState::render()
{
    mpGame->mWindow.draw(mWorld);
    mpGame->mWindow.draw(mSnake);

}

void PlayingState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code==sf::Keyboard::Up && mSnake.getDirection()!=Direction::Down)
        mSnake.setDirection(Direction::Up);
    else if(code==sf::Keyboard::Down && mSnake.getDirection()!=Direction::Up)
        mSnake.setDirection(Direction::Down);
    else if(code==sf::Keyboard::Left && mSnake.getDirection()!=Direction::Right)
        mSnake.setDirection(Direction::Left);
    else if(code==sf::Keyboard::Right && mSnake.getDirection()!=Direction::Left)
        mSnake.setDirection(Direction::Right);
}
