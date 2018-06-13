#include "aux_states.h"
#include "game.h"
// Implementacija pomoćnih stanja.
#include <string>
#include "playing_state.h"

WelcomeState::WelcomeState(Game *game):GameState(game)
{
    text.setFont(game->font);

    text.setString("\t\t\tSnake game\n by Mihaela Gamulin (migamul)");
    text.setCharacterSize(28);
    text.setPosition(200,200);

    obavijest.setFont(game->font);
    obavijest.setString("Hit any key to continue");
    obavijest.setCharacterSize(16);
    obavijest.setPosition(500,500);
}

void WelcomeState::update(sf::Time dt)
{

}

void WelcomeState::handlePlayerInput(sf::Keyboard::Key code)
{
    mpGame->changeState(GameState::Playing);
}

void WelcomeState::render()
{
   mpGame->mWindow.draw(text);
   mpGame->mWindow.draw(obavijest);
}

ExitingState::ExitingState(Game *game):GameState(game)
{
    koliko = 3;
    title1.setFont(game->font);
    title1.setString("Game over 1");
    title1.setCharacterSize(28);
    title1.setPosition(300,200);

    title2.setFont(game->font);
    title2.setString("Game over 2");
    title2.setCharacterSize(28);
    title2.setPosition(300,200);

    title3.setFont(game->font);
    title3.setString("Game over 3");
    title3.setCharacterSize(28);
    title3.setPosition(300,200);
}

void ExitingState::update(sf::Time dt)
{
    mpGame->settime(sf::seconds(1.0));

    if(dt >= mpGame->gettime())
    {
       mpGame->changeState(GameState::Exiting);
       koliko--;
    }
}

void ExitingState::handlePlayerInput(sf::Keyboard::Key code)
{

}

void ExitingState::render()
{
    if(koliko == 3)
        mpGame->mWindow.draw(title3);
    if(koliko == 2)
        mpGame->mWindow.draw(title2);
    if(koliko == 1)
        mpGame->mWindow.draw(title1);
    if(koliko == 0)
        mpGame->mWindow.close();
}


WonState::WonState(Game *game):GameState(game)
{
    text.setFont(game->font);
    text.setString("You won! The score: ");
    text.setCharacterSize(28);
    text.setPosition(200,200);

    obavijest1.setFont(game->font);
    obavijest1.setString("Hit C to continue, X to exit");
    obavijest1.setCharacterSize(16);
    obavijest1.setPosition(500,500);
}

void WonState::update(sf::Time dt)
{
    int bodovi = mpGame->daj();
    text1.setFont(mpGame->font);
    std::string koliko = (bodovi < 10 ? "0" : "") + std::to_string(bodovi);
    text1.setString(koliko);
    text1.setCharacterSize(28);
    text1.setPosition(500,200);
}

void WonState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code == sf::Keyboard::C)
    {
        mpGame->changeState(GameState::Playing);
    }
    else if(code == sf::Keyboard::X)
    {
        mpGame->changeState(GameState::Exiting);
    }
}

void WonState::render()
{
    mpGame->mWindow.draw(text);
    mpGame->mWindow.draw(text1);
    mpGame->mWindow.draw(obavijest1);
}

LostState::LostState(Game *game):GameState(game){

    text.setFont(game->font);
    text.setString("You lost! The score: ");
    text.setCharacterSize(28);
    text.setPosition(200,200);

    obavijest1.setFont(game->font);
    obavijest1.setString("Hit C to continue, X to exit");
    obavijest1.setCharacterSize(16);
    obavijest1.setPosition(500,500);
}

void LostState::update(sf::Time dt)
{
    int bodovi=mpGame->daj();
    text1.setFont(mpGame->font);
    std::string koliko=(bodovi < 10 ? "0" : "") + std::to_string(bodovi);
    text1.setString(koliko);
    text1.setCharacterSize(28);
    text1.setPosition(500,200);
}

void LostState::handlePlayerInput(sf::Keyboard::Key code)
{
    if(code==sf::Keyboard::C)
    {
        mpGame->changeState(GameState::Playing);
    }
    else if(code==sf::Keyboard::X)
    {
        mpGame->changeState(GameState::Exiting);
    }
}
void LostState::render()
{
     mpGame->mWindow.draw(text);
     mpGame->mWindow.draw(text1);
     mpGame->mWindow.draw(obavijest1);
}
