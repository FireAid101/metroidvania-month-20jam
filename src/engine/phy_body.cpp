#include "phy_body.h"

CollisionResults HandleCollisions(SDL_FRect rect1, SDL_FRect rect2, float &vX, float &vY)
{
    CollisionResults result;

    result.left = rect1.x + rect1.w + vX > rect2.x && rect1.x < rect2.x && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;                
    result.right = rect1.x + vX < rect2.x + rect2.w && rect1.x + rect1.w > rect2.x + rect2.w && rect1.y + rect1.h > rect2.y && rect1.y < rect2.y + rect2.h;                
    result.top = rect1.y + rect1.h + vY > rect2.y && rect1.y < rect2.y && rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w;                
    result.bottom = rect1.y + vY < rect2.y + rect2.h && rect1.y + rect1.h > rect2.y + rect2.h && rect1.x + rect1.w > rect2.x && rect1.x < rect2.x + rect2.w;               

    if ((vX > 0 && result.left == true) || (vX < 0 && result.right == true))
    {
        vX = 0;
    }

    if ((vY > 0 && result.top == true) || (vY < 0 && result.bottom == true))
    {
        vY = 0;
    } 

    return result;   
}