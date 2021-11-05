#pragma once
#ifndef DEFINE_H
#define DEFINE_H

// Screen defines.
#define IN_GAME_SCREEN_OFFSET_X 31
#define IN_GAME_SCREEN_OFFSET_Y 30
#define IN_GAME_SCREEN_OFFSET_W 768
#define IN_GAME_SCREEN_OFFSET_H 958
#define IN_GAME_SCREEN_W 768 - 31
#define IN_GAME_SCREEN_H 958 - 30

// Sprites defines.
#define DEFAULT_SPRITES_SIZE 64
#define DEFAULT_SPRITES_HALF_SIZE 32

// Player defines.
#define PLAYER_MAX_VELOCITY 10
#define PLAYER_TP_DELAY 10
#define PLAYER_COLLISION_SHAPES 6

// Bullet defines.
#define BULLET_MAX_AMOUNT 64
#define BULLET_SPEED 12
#define BULLET_LIFESPAN 80
#define FIREBALL_SPEED 6

// Mine defines.
#define MINE_MAX_AMOUNT 98
#define MINE_SPAWN_AREA_OFFSET 250
#define MINE_SPAWN_CENTER_DEAD_ZONE 192
#define MineSpriteSize(size) (size == MINE_SIZE_NULL ? 0 : (size == MINE_SMALL ? 32 : (size == MINE_MEDIUM ? 64 : 128))) // Returns the size of the sprite of a mine.

// Minelayer define.
#define MINELAYER_SPEED 2;

// Gamemode define.
#define DIFFICULTY_MAX 14

// Makes a given position wrap around the screen in function of the object's size.
static inline void screen_wrap(MyVector2 *pos, int size)
{
    if (pos->x + size < IN_GAME_SCREEN_OFFSET_X)
    {
        pos->x = IN_GAME_SCREEN_OFFSET_X + IN_GAME_SCREEN_OFFSET_W + size;
    }
    else if (pos->x - size > IN_GAME_SCREEN_OFFSET_X + IN_GAME_SCREEN_OFFSET_W)
    {
        pos->x = IN_GAME_SCREEN_OFFSET_X - size;
    }
    if (pos->y + size < IN_GAME_SCREEN_OFFSET_Y)
    {
        pos->y = IN_GAME_SCREEN_OFFSET_Y + IN_GAME_SCREEN_OFFSET_H + size;
    }
    else if (pos->y - size > IN_GAME_SCREEN_OFFSET_Y + IN_GAME_SCREEN_OFFSET_H)
    {
        pos->y = IN_GAME_SCREEN_OFFSET_Y - size;
    }
}

#endif