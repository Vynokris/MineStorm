#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <my_math.h>

#include "define.h"

// Structure for a bullet.
typedef struct Bullet
{
    int       lifespan; // Number of frames until the bullet is destroyed.
    double    rotation;
    MyVector2 pos;
} Bullet;

// ------ Bullet related functions ------ //

// Initialises all the bullets.
void bullet_init(Bullet *bullets);

// Update all the bullets of the given array.
void bullet_update(Bullet *bullet);

#endif