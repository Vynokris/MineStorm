#pragma once
#ifndef GAME_H
#define GAME_H

#include <time.h>
#include "player.h"
#include "bullet.h"
#include "mine.h"

// Enum for all of the game's scenes.
typedef enum SceneID
{
    SC_MAIN_MENU,
    SC_LOADING,
    SC_IN_GAME,
    SC_PAUSE,
    SC_GAME_OVER,
} SceneID;

// Structure for the animations
typedef struct Animation
{
    double key;
    double end;
    double speed;
} Animation;

// Structure for the user interface.
typedef struct Ui
{
    Texture2D overlay;
    Animation animations[4];
    Texture2D sprites[11];
    Font      font;
    Segment   mines_explosion[10];
} Ui;

// Main game structure.
typedef struct Game
{
    bool            solo;
    int             highscore;
    int             difficulty;
    MyVector2       rendertexture_offset;
    RenderTexture2D rendertexture;
    SceneID         scene_id;
    Sound           sfx[6];
    Music           music;
    Minelayer       minelayer;
    Player          player[2];
    Ui              ui;
    Mine            mines[MINE_MAX_AMOUNT];
} Game;

// ------ User Interface and Audio initialization functions ------- //

// Initialize the audio and load it into the game structure.
void audio_init(Game *game);

// Update the game sfx and music.
void audio_update(Game *game);

// Initialize the ui structure and its values.
void ui_init(Game *game);

// Unload all the ui textures.
void unload_game_ressources(Game *game);

// ----------------------- Game functions ----------------------- //

// Open highscores binary file and load it into the game structure.
void load_highscore(Game *game);

// Save a highscore at the end of a solo game.
void save_highscore(Game *game);

// Initializes all game values and objects.
void game_init(Game *game);

// Starts a solo game.
void game_start_solo(Game *game);

// Starts a 2 player game.
void game_start_duo(Game *game);

// Starts a round.
void round_next(Game *game);

// Set all the segments for the mine explosion animation
void set_mines_explosion_segments(Game *game, int mine_i);

// Updates all the collisions in the game.
void collision_update(Game *game);

// Update all the game objects.
void game_update(Game *game);

// Check if round is over.
bool is_round_over(Game *game);

// Check if the game is over.
bool is_game_over(Game *game);

// Update the game and listen to input depending on the current scene.
void main_update(Game *game);

#endif