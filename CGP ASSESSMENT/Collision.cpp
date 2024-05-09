#include "Collision.h"
#include <corecrt_math.h>

bool Collision::CircleCollision(float c1X, float c1Y, float r1, float c2X, float c2Y, float r2)
{
    //calculate deltas (delta x and delta y)
    float dx = c2X - c1X;
    float dy = c2Y - c1Y;

    //calculate distance
    float distance = sqrt((dx * dx) + (dy * dy));

    //if distance between circles is less than sum of radii -> overlap detected

    if (distance <= r1 + r2)
    {
        return true;
    }
    else
    {
        return false;
    }
    
    
    
    
    
}

bool Collision::SquareCollision(BoxCollider collider1, BoxCollider collider2)  ////checking for collision between 2 game objects 
{
    /*if (box1MaxX > box2MinX && box1MinX < box2MaxX && box1MaxY > box2MaxY && box1MinY < box2MaxY)
    {
        return true;
    }
    else
    {
        return false;
    }*/
    
    //return box1MaxX > box2MinX && box1MinX < box2MaxX && box1MaxY > box2MinY && box1MinY < box2MaxY;
    float minX1 = collider1.x;
    float maxX1 = collider1.x + collider1.m_width;
    float minY1 = collider1.y;
    float maxY1 = collider1.y + collider1.m_height;

    float minX2 = collider2.x;
    float maxX2 = collider2.x + collider2.m_width;
    float minY2 = collider2.y;
    float maxY2 = collider2.y + collider2.m_height;


    return maxX1 > minX2 && minX1 < maxX2 && maxY1 > minY2 && minY1 < maxY2;
    
}
