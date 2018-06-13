#include "sceneGraph.h"
// Implementacija

#include<list>
#include<math.h>
#include<cmath>
#include<stdexcept>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

SceneNode::SceneNode(std::__cxx11::string name):mChildren(),mName(name),mParent(nullptr)
{
}

void SceneNode::addComponent(SceneNode::Ptr pnode)
{
   pnode->mParent = this;
   mChildren.push_back(std::move(pnode));
}

void SceneNode::removeComponent(const std::__cxx11::string &name)
{
    auto i=mChildren.begin();
   for(;i!=mChildren.end();++i)
    if((*i)->getName()==name)break;

    if(i==mChildren.end())
    {
        auto j=mChildren.begin();
       for(;j!=mChildren.end();++j)(*j)->removeComponent(name);
        if(j==mChildren.end())return;
    }
    (*i)->mParent=nullptr;
    if((*i)->mChildren.empty())
        {   mChildren.erase(i);
            return;
        }
    for(auto j=(*i)->mChildren.begin();j!=(*i)->mChildren.end();) {
        if(name=="Raptor3") (*j)->setPosition(+150.f,+150.f);
        else (*j)->setPosition(-150.f,+150.f);
        addComponent(std::move(*j));
        j=(*i)->mChildren.erase(j);
        }
    mChildren.erase(i);

}

void SceneNode::update(sf::Time dt)
{
    updateCurrent(dt);
    for(auto i=mChildren.begin();i!=mChildren.end();++i)(*i)->update(dt);
}

void SceneNode::drawCurrent(sf::RenderTarget & target, sf::RenderStates states)const
{
}

void SceneNode::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    drawCurrent(target,states);
        for(auto li=mChildren.begin();li!=mChildren.end();++li)(*li)->draw(target,states);
}

BackgrNode::BackgrNode(sf::Texture& Tekstura):SceneNode("Pozadina")
{
    mTexture=Tekstura;
    mSprite.setTexture(mTexture);
    mSprite.setTextureRect({0,0,800,800});
    sf::FloatRect bounds=mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width/2.f,bounds.height/2.f);
}

void BackgrNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}

PlaneNode::PlaneNode(std::string name, sf::Texture& Tekstura):SceneNode(name),mVelocity(0.f,0.f),mDirection({0,0}),check(0){

    mTexture=Tekstura;
    mSprite.setTexture(mTexture);
    sf::FloatRect bounds=mSprite.getLocalBounds();
    mSprite.setOrigin(bounds.width/2.f,bounds.height/2.f);

}

void PlaneNode::updateCurrent(sf::Time dt){
    if(!check)return;
    sf::Vector2f movement(0,0);
    sf::Vector2f position=getPosition();
    sf::Vector2f vektor(mDirection.x-position.x,mDirection.y-position.y);
    float vel=sqrt(vektor.x*vektor.x+vektor.y*vektor.y);
    vektor.x/=vel;
    vektor.y/=vel;
    movement.x=mVelocity.x*vektor.x;
    movement.y=mVelocity.y*vektor.y;
    float angle =atan2(mDirection.y-position.y,mDirection.x-position.x);
        angle=angle*180/M_PI;
        setRotation(angle+90);
    move(movement*dt.asSeconds());
}

void PlaneNode::drawCurrent(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(mSprite, states);
}
