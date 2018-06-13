#include "snake.h"

using namespace sf;

//  Implementacija klase Snake dolazi ovdje.

Snake::Snake(int blockSize)
{
    msize=blockSize;
    mbodyRect.setSize(Vector2f(msize-1,msize-1));
    reset();
}

Vector2i Snake::getPosition()
{
    Vector2i position(mSnakeBody.front().x, mSnakeBody.front().y);
    return (!mSnakeBody.empty() ? position : Vector2i(1,1));
}

void Snake::extend()
{
    if(mSnakeBody.empty())
        return;

    SnakeSegment& tail_head = mSnakeBody[mSnakeBody.size()-1];
    if(mSnakeBody.size() > 1)
    {
        SnakeSegment& tail_bone = mSnakeBody[mSnakeBody.size()-2];
        if(tail_head.x == tail_bone.x)
        {
            if(tail_head.y > tail_bone.y)
                mSnakeBody.push_back(SnakeSegment(tail_head.x, tail_head.y+1));
            else
                mSnakeBody.push_back(SnakeSegment(tail_head.x, tail_head.y-1));
        }
        else if(tail_head.y == tail_bone.y)
        {
                if(tail_head.x > tail_bone.x)
                    mSnakeBody.push_back(SnakeSegment(tail_head.x+1, tail_head.y));
                else
                    mSnakeBody.push_back(SnakeSegment(tail_head.x-1, tail_head.y));
        }
    }
    else
    {
        if(mdir == Direction::Up)
            mSnakeBody.push_back(SnakeSegment(tail_head.x, tail_head.y+1));
        else if(mdir == Direction::Down)
            mSnakeBody.push_back(SnakeSegment(tail_head.x, tail_head.y-1));
        else if(mdir == Direction::Left)
            mSnakeBody.push_back(SnakeSegment(tail_head.x+1, tail_head.y));
        else if(mdir == Direction::Right)
            mSnakeBody.push_back(SnakeSegment(tail_head.x-1, tail_head.y));
    }
}

void Snake::reset()
{
    mSnakeBody.clear();
    mSnakeBody.push_back(SnakeSegment(5,7));
    mSnakeBody.push_back(SnakeSegment(5,6));
    mSnakeBody.push_back(SnakeSegment(5,5));
    setDirection(Direction::None);
    mspeed = 15;
    mlives = 3;
    mscore = 0;
    mlost = false;
}

void Snake::update()
{
    if(mSnakeBody.empty())
        return;
    if(mdir == Direction::None)
        return;
    move();
    checkCollision();
}

void Snake::cut(int n)
{
    for(int i = 0; i < n; i++)
    {
        mSnakeBody.pop_back();
    }
    --mlives;
    if(!mlives)
    {
        lose();
        return;
    }
}

void Snake::move()
{
    for(int i = mSnakeBody.size()-1; i > 0; --i)
    {
        mSnakeBody[i].x = mSnakeBody[i-1].x;
        mSnakeBody[i].y = mSnakeBody[i-1].y;
    }
    if(mdir == Direction::Left)
        --mSnakeBody[0].x;
    else if(mdir == Direction::Right)
        ++mSnakeBody[0].x;
    else if(mdir == Direction::Up)
        --mSnakeBody[0].y;
    else if(mdir == Direction::Down)
        ++mSnakeBody[0].y;
}

void Snake::checkCollision()
{
    if(mSnakeBody.size() < 5)
        return;
    SnakeSegment& head = mSnakeBody.front();
    for(auto iter = mSnakeBody.begin()+1; iter != mSnakeBody.end(); ++iter)
    {
        if(iter->x == head.x && iter->y == head.y)
        {
            int segments = mSnakeBody.end() - iter;
            cut(segments);
            break;
        }
    }
}

void Snake::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    if(mSnakeBody.empty())
        return;
    auto head=mSnakeBody.begin();

    mbodyRect.setFillColor(Color::Yellow);
    mbodyRect.setPosition(head->x*msize, head->y*msize);

    target.draw(mbodyRect);
    mbodyRect.setFillColor(Color::Green);

    for(auto iter = mSnakeBody.begin()+1; iter != mSnakeBody.end(); ++iter)
    {
        mbodyRect.setPosition(iter->x*msize, iter->y*msize);
        target.draw(mbodyRect);
    }
}

