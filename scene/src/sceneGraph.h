#ifndef SCENE_GRAPH_IS_INCLUDED
#define SCENE_GRAPH_IS_INCLUDED

#include <memory>
#include <list>
#include <string>

#include <SFML/Graphics.hpp>

class SceneNode : public sf::Transformable, public sf::Drawable
{
    public:
        SceneNode(std::string name="");
        using Ptr = std::unique_ptr<SceneNode>;

        void addComponent(Ptr pnode);
        void removeComponent(std::string const & name);

        void update(sf::Time dt);
        std::string getName() const { return mName; }

        virtual void updateCurrent(sf::Time dt){}

    private:
        virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
        // Implementacijski detalji
    //
        virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
        std::list<Ptr> mChildren;
        std::string    mName;
        //
        SceneNode* mParent;
};


// BackgrNode služi za crtanje background-a. On se ne miče
// niti ne centriramo njegov Sprite.
class BackgrNode : public SceneNode {
    public:
      // ...
      BackgrNode(sf::Texture& Tekstura);
      virtual void updateCurrent(sf::Time dt){}
    private:
        virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
        sf::Sprite   mSprite;
        sf::Texture	mTexture;

};


// SpriteNode služi za crtanje aviona.
class  PlaneNode : public SceneNode{
    public:
        explicit PlaneNode(std::string name, sf::Texture& Tekstura);
        // ....
        void setVelocity(sf::Vector2f v) {mVelocity = v; }
        void setVelocity(float vx, float vy) { mVelocity.x = vx; mVelocity.y = vy; }
        sf::Vector2f getVelocity() const { return mVelocity; }

        virtual void updateCurrent(sf::Time dt);
        sf::Vector2i Pocpoz;
        sf::Vector2i Novapoz;

         void setDirection(sf::Vector2i v){mDirection=v;}
         void PostaviP(int i) {check=i;}
    private:
        virtual void drawCurrent(sf::RenderTarget & target, sf::RenderStates states) const;
    // ........
        sf::Texture	mTexture;
        sf::Sprite   mSprite;
        sf::Vector2f mVelocity;
        sf::Vector2i mDirection;
        std::string mName;
         int check;

};



#endif
