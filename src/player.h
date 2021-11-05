#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <stdbool.h>

#include "bullet.h"

// Structure for the player.
typedef struct Player
{
    bool      destroyed;
    bool      has_explosed;
    bool      is_teleporting;
    int       hp;
    int       tp_delay;
    int       score;
    double    rotation;
    MyVector2 pos;
    MyVector2 velocity;
    Shape     hitbox;
    double    debris_rotation[4];
    MyVector2 debris_trajectory[4];
    Bullet    bullets[BULLET_MAX_AMOUNT];
} Player;

// ---------- Player related functions ---------- //

// Updates the player's hitbox.
void player_update_hitbox(Player *player);

// Initializes the player structure and its values.
void player_init(Player *player);

// Makes the player shoot a bullet.
void player_shoot(Player *player);

// Updates the player's position.
void player_update(Player *player, int player_id);

// Teleports the player to a random location on the screen.
void player_tp(Player *player);

#endif