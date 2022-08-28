#include "spacedust.h"
#include "engine/util.h"
#include <math.h>

#define NUM_SPACEDUST_COLORS 3

const GLuint spacedustColors[NUM_SPACEDUST_COLORS] = {
    0xF5EDDF,
    0xDABD8B,
    0xB3FFFF
};

typedef struct {
    float x;
    float y;
    float rotX;
    float rotY;
    GLuint color;
} Spacedust;

Spacedust spacedust[NUM_SPACEDUST];

#define WINX 240
#define WINY 240
#define WINY_3D (WINY - 70)

void initSpacedust()
{
    for(uint8_t i = 0; i < NUM_SPACEDUST; i++)
    {
        //Initialize to out-of-bounds value so the first calculation run computes proper values
        spacedust[i].x = -1;
    }
}

void calcSpacedust(Ship* playerShip, uint32_t ticks)
{
    for(uint8_t i = 0; i < NUM_SPACEDUST; i++)
    {
        if(spacedust[i].x < 0 || spacedust[i].y < 0 || spacedust[i].x > 239 || spacedust[i].y > 239 - 70)
        {
            //Generate angle
            float angle = randf(M_PI * 2);
            spacedust[i].rotX = cosf(angle);
            spacedust[i].rotY = sinf(angle);
            //Generate position from angle
            spacedust[i].x = WINX / 2 + spacedust[i].rotX * randf(WINX / 2);
            spacedust[i].y = WINY_3D / 2 + spacedust[i].rotY * randf(WINY_3D / 2);
            //Generate speed (which basically represents distance to the player)
            float speed = (0.5f + randf(1.5f)) * 16;
            spacedust[i].rotX *= speed;
            spacedust[i].rotY *= speed;
            //Generate color
            spacedust[i].color = spacedustColors[randr(NUM_SPACEDUST_COLORS)];
        }
        else
        {
            spacedust[i].x += spacedust[i].rotX * playerShip->speed * ticks / 1000.0f;
            spacedust[i].y += spacedust[i].rotY * playerShip->speed * ticks / 1000.0f;
            //TODO: Adjust directions (e.g. a point that was going down should go up if the ship turns downwards)
            if(playerShip->turnSpeedY != 0)
            {
                //- because we have to move the points in the opposite direction
                spacedust[i].x -= playerShip->turnSpeedY * 128 * ticks / 1000.0f;
            }
            if(playerShip->turnSpeedX != 0)
            {
                //- because we have to move the points in the opposite direction
                spacedust[i].y -= playerShip->turnSpeedX * 128 * ticks / 1000.0f;
            }
        }
    }
}

void drawSpacedust()
{
    for(uint8_t i = 0; i < NUM_SPACEDUST; i++)
    {
        glPlotPixel((uint8_t) spacedust[i].x, (uint8_t) spacedust[i].y, spacedust[i].color);
    }
}