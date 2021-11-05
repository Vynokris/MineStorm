#pragma once
#ifndef MINE_H
#define MINE_H

#include <my_math.h>

#include "define.h"

typedef enum MineType
{
    MINE_NULL,
    MINE_FLOATING,
    MINE_MAGNETIC,
    MINE_MAGNETIC_FIREBALL,
    MINE_FIREBALL,
} MineType;

typedef enum MineSize
{
    MINE_SIZE_NULL,
    MINE_SMALL,
    MINE_MEDIUM,
    MINE_LARGE,
} MineSize;

typedef struct Fireball
{
    int       lifespan;          // Number of frames until the fireball is destroyed.
    double    rotation;
    MyVector2 pos;
} Fireball;

typedef struct Mine
{
    bool      destroyed;
    bool      spawned;
    bool      has_shot;
    bool      has_exploded;
    int       hitbox_shapes_amount;
    MineType  type;
    MineSize  size;
    MyVector2 pos;
    MyVector2 velocity;
    Fireball  fireball;
    Shape     hitboxes[6];
} Mine;

typedef struct Minelayer
{
    bool      has_spawned;
    bool      destroyed;
    bool      checkpoints[4];    // Set to true once the minelayer is past each checkpoint.
    MyVector2 pos;
    MyVector2 velocity;
    Shape     hitbox;
    MyVector2 trajectory[4];
    MyVector2 checkpoint_pos[5]; // Start point, checkpoints, and end point.
} Minelayer;

// ------------------------------ Mine related functions ------------------------------ //

// Returns the score yeild of a mine depending on its type and size.
int mines_score(MineType type, MineSize size);

// Update the mines hitboxes depending on the mines position.
void mines_update_hitboxes(Mine *mines);

// Initializes all of the mines and their values.
void mines_init(Mine *mines);

// Creates multiple spawn points for mines, given the number of large mines of the level.
// Returns the total number of mines that were spawned.
void mines_spawn_point(Mine *mines, int large_mine_amount);

// Spawns 2 mines of the given size.
void mines_spawn(Mine *mines, MineSize size);

// Spawn a fireball when a fireball or a magnetic fireball mine has been destroyed
void fireball_spawn(Mine *mine, MyVector2 player_pos);

// Returns the closest player position (considering screen wrapping) to a given mine position.
MyVector2 find_closest_player_pos(MyVector2 mine_pos, MyVector2 *players_pos);

// Updates all of the mines' positions.
void mines_update(Mine *mines, MyVector2 *players_pos);

// Updates the fireball of a given mine.
void fireball_update(Mine *mine);

// ---------------------------- Minelayer related functions --------------------------- //

// Initialize the minelayer.
void minelayer_init(Minelayer *minelayer, Mine *mines);

// Check if the minelayer can spawn once all mines spawned.
bool minelayer_spawn(Minelayer *minelayer, Mine *mines);

// Update the minelayer.
void minelayer_update(Minelayer *minelayer, Mine *mines);

#endif