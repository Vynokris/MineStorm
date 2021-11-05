#include "bullet.h"

void bullet_init(Bullet *bullets)
{
    // Set the values of all the bullets in the list.
    for (int i = 0; i < BULLET_MAX_AMOUNT; i++)
    {
        bullets[i].pos = Vector2Zero();
        bullets[i].rotation = 0;
        bullets[i].lifespan = 0;
    }
}

void bullet_update(Bullet *bullets)
{
    for (int i = 0; i < BULLET_MAX_AMOUNT; i++)
    {
        if (bullets[i].lifespan > 0)
        {
            // Move according to velocity.
            bullets[i].pos.x += cos(bullets[i].rotation) * BULLET_SPEED;
            bullets[i].pos.y += sin(bullets[i].rotation) * BULLET_SPEED;

            // Decrement lifetime each frame.
            bullets[i].lifespan--;

            // Screen wrapping.
            screen_wrap(&bullets[i].pos, DEFAULT_SPRITES_SIZE);
        }
    }
}