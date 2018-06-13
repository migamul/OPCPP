#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        void run();

    private:
        sf::RenderWindow mWindow;
        sf::Texture mTexture;
        sf::Sprite mSprite;

        bool mUp, mDown, mLeft, mRight;

        float mVelocity;

        sf::Time mDt;

        void processEvents();
        void update(sf::Time dt);
        void render();

        void handleUserInput(sf::Keyboard::Key code, bool isPressed);

};





#endif // GAME_H

