#pragma once
#ifndef DRAW_H
#define DRAW_H

#include "game.h"

// ----------------------- Draw functions ------------------------ //

// Screen shake function.
void screen_shake(MyVector2 *rendertexture_offset, int multiplier);

// Renders the main menu.
void draw_main_menu(Game game);

// Renders the player.
void draw_player(Game *game);

// Renders the bullets.
void draw_projectiles(Game game);

// Renders the mines and their explosions when destroyed
void draw_mines(Game *game);

// Render the minelayer.
void draw_minelayer(Game *game);

// Renders in-game scene (regroup player / mine draw functions).
void draw_game(Game *game);

// Renders the pause menu.
void draw_pause(Game game);

// Renders the game over screen.
void draw_game_over(Game game);

// Renders the game HUD and MineStorm original overlay.
void draw_ui(Game game);

// Renders the intro animation at the begining of a game
void intro_animation(Game *game);

// Draws the right UI depending on the game scene.
void main_draw(Game *game);

#endif
