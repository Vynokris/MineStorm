#include "draw.h"

// ----- Draw functions ----- //

void screen_shake(MyVector2 *rendertexture_offset, int multiplier)
{
    *rendertexture_offset = Vector2Create(GetRandomValue(-multiplier, multiplier), 
                                          GetRandomValue(-multiplier, multiplier));
}

void draw_main_menu(Game game)
{
    // Draw main title.
    DrawTextEx(game.ui.font, "MINESTORM",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "MINESTORM", 50, 0).x / 2,
                                      GetScreenHeight() * 1 / 5 + MeasureTextEx(game.ui.font, "MINESTORM", 50, 0).y / 2 + 50)),
               50, 0, Fade(RAYWHITE, 1.0f));

    // Draw solo mode title.
    DrawTextEx(game.ui.font, IsGamepadAvailable(0) ? "[F/START] 1P GAME" : "[F] 1P GAME",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "[F/START] 1P GAME" : "[F] 1P GAME", 25, 0).x / 2,
                                      GetScreenHeight() * 2 / 5 - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "[F/START] 1P GAME" : "[F] 1P GAME", 25, 0).y / 2)),
               25, 0, Fade(RAYWHITE, 1.0f));

    // Draw multiplayer mode title.
    DrawTextEx(game.ui.font, IsGamepadAvailable(0) ? "[K/SELECT] 2P GAME" : "[K] 2P GAME",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "[K/SELECT] 2P GAME" : "[K] 2P GAME", 25, 0).x / 2,
                                      GetScreenHeight() * 2 / 5 + MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "[K/SELECT] 2P GAME" : "[K] 2P GAME", 25, 0).y / 2 + 25)),
               25, 0, Fade(RAYWHITE, 1.0f));

    // Draw highscore title.
    DrawTextEx(game.ui.font, "HIGHSCORE",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "HIGHSCORES", 25, 0).x / 2,
                                      GetScreenHeight() * 3 / 5 - MeasureTextEx(game.ui.font, "HIGHSCORES", 25, 0).y / 2 - 50)),
               25, 0, Fade(RAYWHITE, 1.0f));

    // Draw highscore from highscore.bin
    DrawTextEx(game.ui.font, TextFormat("%d\n", game.highscore),
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, TextFormat("%d\n", game.highscore), 50, 0).x / 2,
                                      GetScreenHeight() * 3 / 5 + MeasureTextEx(game.ui.font, TextFormat("%d\n", game.highscore), 50, 0).y / 2 - 50)),
               50, 0, Fade(RAYWHITE, 1.0f));

    // Draw quit title.
    DrawTextEx(game.ui.font, "[ESC] QUIT GAME",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "[ESC] QUIT GAME", 25, 0).x / 2,
                                      GetScreenHeight() * 4 / 5 - MeasureTextEx(game.ui.font, "[ESC] QUIT GAME", 25, 0).y / 2)),
               25, 0, Fade(RAYWHITE, 1.0f));

    // Keybinds draw
    if (IsGamepadAvailable(0)) DrawTextureEx(game.ui.sprites[10], toRayVec(Vector2Create(65, 85)), 0, 0.70, RAYWHITE);
    else                       DrawTexture(game.ui.sprites[8], 65, 50, RAYWHITE);

    if (IsGamepadAvailable(1)) DrawTextureEx(game.ui.sprites[10], toRayVec(Vector2Create(GetScreenWidth() - 65 - game.ui.sprites[9].width, 85)), 0, 0.70, RAYWHITE);
    else                       DrawTexture(game.ui.sprites[9], GetScreenWidth() - 65 - game.ui.sprites[9].width, 50, RAYWHITE);
}

void draw_player(Game *game)
{
    for (int player_id = 0; player_id < (game->solo ? 1 : 2); player_id++)
    {
        // Player alive.
        if (game->player[player_id].hp > 0 && !game->player[player_id].destroyed && (game->solo ? !game->player[0].is_teleporting : true))
        {
            DrawTexturePro(game->ui.sprites[0],
                           toRayRec(RectangleCreate(Vector2Zero(),               DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayRec(RectangleCreate(game->player[player_id].pos, DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE, DEFAULT_SPRITES_HALF_SIZE)),
                           radToDeg(game->player[player_id].rotation + PI / 2),
                           player_id == 0 ? Fade(RAYWHITE, 1.0f) : Fade(SKYBLUE, 1.0f));
        }

        // Player destroyed.
        if (game->player[player_id].destroyed && game->ui.animations[2].key < game->ui.animations[2].end)
        {
            // Draw player's explosion animation.
            game->ui.animations[2].key += game->ui.animations[2].speed;
            for (int i = 0; i < 4; i++)
            {
                DrawTexturePro(game->ui.sprites[0],
                               toRayRec(RectangleCreate
                                        (
                                            Vector2Create(i < 2 ? DEFAULT_SPRITES_HALF_SIZE * i : DEFAULT_SPRITES_HALF_SIZE * (i - 2),
                                                          i < 2 ? 0 : DEFAULT_SPRITES_HALF_SIZE),
                                            DEFAULT_SPRITES_HALF_SIZE,
                                            DEFAULT_SPRITES_HALF_SIZE)
                                        ),
                               toRayRec(RectangleCreate
                                        (
                                            Vector2Add(game->player[player_id].pos,
                                                       Vector2MultiplyVal(game->player[player_id].debris_trajectory[i],
                                                                          game->ui.animations[2].key)),
                                            DEFAULT_SPRITES_HALF_SIZE,
                                            DEFAULT_SPRITES_HALF_SIZE)
                                        ),
                               toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE, DEFAULT_SPRITES_HALF_SIZE)),
                               radToDeg(game->player[player_id].rotation + PI / 2) + game->player[player_id].debris_rotation[i] + game->ui.animations[2].key,
                               player_id == 0 ? Fade(RAYWHITE, 1.0f) : Fade(SKYBLUE, 1.0f));
            }
            
            // Shake the screen during 1/3 of the animation.
            if (game->ui.animations[2].key < game->ui.animations[2].end / 2) {
                screen_shake(&game->rendertexture_offset, 3);
            }
        }

        // Wait until the end of the player's explosion animation to go to next round
        else if (game->player[player_id].hp > 0 && game->ui.animations[2].key >= game->ui.animations[2].end)
        {
            round_next(game);
        }

        // Player teleporting (only available in solo mode)
        if (game->solo && !game->player[0].destroyed && game->player[0].is_teleporting && game->ui.animations[3].key < game->ui.animations[3].end)
        {
            game->ui.animations[3].key += game->ui.animations[3].speed;
            for (int i = 0; i < 4; i++)
            {
                DrawTexturePro(game->ui.sprites[0],
                               toRayRec(RectangleCreate
                                        (
                                            Vector2Create(i < 2 ? DEFAULT_SPRITES_HALF_SIZE * i 
                                                                : DEFAULT_SPRITES_HALF_SIZE * (i - 2),
                                                          i < 2 ? 0 
                                                                : DEFAULT_SPRITES_HALF_SIZE),
                                            DEFAULT_SPRITES_HALF_SIZE,
                                            DEFAULT_SPRITES_HALF_SIZE)
                                        ),
                               toRayRec(RectangleCreate
                                        (
                                            Vector2Add(Vector2Create(i % 2 == 0 ? game->player[player_id].pos.x - DEFAULT_SPRITES_HALF_SIZE
                                                                                : game->player[player_id].pos.x + DEFAULT_SPRITES_HALF_SIZE,
                                                                     i < 2      ? game->player[player_id].pos.y - DEFAULT_SPRITES_HALF_SIZE
                                                                                : game->player[player_id].pos.y + DEFAULT_SPRITES_HALF_SIZE),
                                            Vector2MultiplyVal(Vector2Create(i % 2 == 0 ? 1 : -1, i < 2 ? 1 : -1),
                                                               DEFAULT_SPRITES_HALF_SIZE / 2 * game->ui.animations[3].key / game->ui.animations[3].end)),
                                            DEFAULT_SPRITES_HALF_SIZE,
                                            DEFAULT_SPRITES_HALF_SIZE)
                                        ),
                               toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE / 2, DEFAULT_SPRITES_HALF_SIZE / 2)),
                               radToDeg(game->player[player_id].rotation + PI / 2),
                               player_id == 0 ? Fade(RAYWHITE, 1.0f) : Fade(SKYBLUE, 1.0f));
            }
        }
    }
}

void draw_projectiles(Game game)
{
    for (int i = 0; i < BULLET_MAX_AMOUNT; i++)
    {
        // Player 1 bullets.
        if (game.player[0].bullets[i].lifespan > 0)
            DrawTexturePro(game.ui.sprites[3],
                           toRayRec(RectangleCreate(Vector2Create(0, 0),           DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayRec(RectangleCreate(game.player[0].bullets[i].pos, DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE,       DEFAULT_SPRITES_HALF_SIZE)),
                           0, Fade(RAYWHITE, 1.0f));

        // Player 2 bullets.
        if (!game.solo && game.player[1].bullets[i].lifespan > 0)
            DrawTexturePro(game.ui.sprites[3],
                           toRayRec(RectangleCreate(Vector2Create(0, 0),           DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayRec(RectangleCreate(game.player[1].bullets[i].pos, DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE, DEFAULT_SPRITES_HALF_SIZE)),
                           0, Fade(SKYBLUE, 1.0f));
    }

    // Fireball from mines of certain types.
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        if ((game.mines[i].type == MINE_FIREBALL || game.mines[i].type == MINE_MAGNETIC_FIREBALL) && game.mines[i].destroyed && !game.mines[i].has_shot)
            DrawTexturePro(game.ui.sprites[1],
                           toRayRec(RectangleCreate(Vector2Create(0, 0),           DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayRec(RectangleCreate(game.mines[i].fireball.pos,    DEFAULT_SPRITES_SIZE, DEFAULT_SPRITES_SIZE)),
                           toRayVec(Vector2Create(DEFAULT_SPRITES_HALF_SIZE,       DEFAULT_SPRITES_HALF_SIZE)),
                           0, Fade(RAYWHITE, 1.0f));
    }
}

void draw_mines(Game *game)
{
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        // Show the spawned mines.
        if (game->mines[i].type != MINE_NULL && !game->mines[i].destroyed && game->mines[i].spawned)
        {
            switch (game->mines[i].type)
            {
            case MINE_FLOATING:
                DrawTextureEx(game->ui.sprites[4], toRayVec(game->mines[i].pos), 0, (double)MineSpriteSize(game->mines[i].size) / 256, RAYWHITE);
                break;

            case MINE_MAGNETIC:
                DrawTextureEx(game->ui.sprites[5], toRayVec(game->mines[i].pos), 0, (double)MineSpriteSize(game->mines[i].size) / 256, RAYWHITE);
                break;

            case MINE_MAGNETIC_FIREBALL:
                DrawTextureEx(game->ui.sprites[6], toRayVec(game->mines[i].pos), 0, (double)MineSpriteSize(game->mines[i].size) / 256, RAYWHITE);
                break;

            case MINE_FIREBALL:
                DrawTextureEx(game->ui.sprites[7], toRayVec(game->mines[i].pos), 0, (double)MineSpriteSize(game->mines[i].size) / 256, RAYWHITE);
                break;

            default:
                break;
            }
        }

        // Show explosion when mines are destroyed.
        if (game->mines[i].type != MINE_NULL && game->mines[i].destroyed && game->mines[i].spawned && !game->mines[i].has_exploded)
        {
            game->ui.animations[1].key += game->ui.animations[1].speed;
            if (game->ui.animations[1].key < game->ui.animations[1].end)
            {
                for (int i = 0; i < 10; i++)
                {
                    DrawSegment(SegmentCreate(game->ui.mines_explosion[i].a,
                                              Vector2Add(game->ui.mines_explosion[i].a,
                                                         Vector2DivideVal(Vector2Create(game->ui.mines_explosion[i].a.x > game->ui.mines_explosion[i].b.x ? game->ui.mines_explosion[i].b.x  * game->ui.animations[1].key / game->ui.animations[1].end
                                                                                                                                                            : -game->ui.mines_explosion[i].b.x * game->ui.animations[1].key / game->ui.animations[1].end,
                                                                                        game->ui.mines_explosion[i].a.y > game->ui.mines_explosion[i].b.y ? game->ui.mines_explosion[i].b.y  * game->ui.animations[1].key / game->ui.animations[1].end
                                                                                                                                                            : -game->ui.mines_explosion[i].b.y * game->ui.animations[1].key / game->ui.animations[1].end),
                                                                        8))), RAYWHITE);
                }
                    
                // Power of the screen shake according to the mine size.
                screen_shake(&game->rendertexture_offset, 3 * game->mines[i].size);
            }
            else
            {
                game->ui.animations[1].key  = 0;
                game->mines[i].has_exploded = true;
                game->mines[i].spawned      = false;
            }
        }

        // Show the mine spawn points.
        if (game->mines[i].type != MINE_NULL && !game->mines[i].destroyed && !game->mines[i].spawned)
            DrawCircle(game->mines[i].pos.x + (double)MineSpriteSize(game->mines[i].size) / 2, game->mines[i].pos.y + (double)MineSpriteSize(game->mines[i].size) / 2, 2, WHITE);
    }
}

void draw_minelayer(Game *game)
{
    // Draw the minelayer texture.
    if (!game->minelayer.destroyed && game->minelayer.has_spawned)
        DrawTextureEx(game->ui.sprites[2], toRayVec(Vector2Create(game->minelayer.pos.x - 20, game->minelayer.pos.y)), 0, 0.125, RAYWHITE);
}

void draw_game(Game *game)
{
    draw_player(game);
    draw_projectiles(*game);
    draw_mines(game);
    draw_minelayer(game);
}

void draw_pause(Game game)
{
    // Text draw
    DrawTextEx(game.ui.font, "PAUSE",
               toRayVec(Vector2Create(GetScreenWidth()  / 2     - MeasureTextEx(game.ui.font, "PAUSE", 50, 0).x / 2,
                                      GetScreenHeight() * 1 / 5 - MeasureTextEx(game.ui.font, "PAUSE", 50, 0).y / 2)),
               50, 0, Fade(RAYWHITE, 1.0f));
    DrawTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to continue or [START] to quit" : "Press [SPACE] to continue or [ESC] to quit",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to continue or [START] to quit" : "Press [SPACE] to continue or [ESC] to quit", 16, 0).x / 2,
                                      GetScreenHeight() * 3 / 4 - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to continue or [START] to quit" : "Press [SPACE] to continue or [ESC] to quit", 16, 0).y / 2)),
               16, 0, Fade(RAYWHITE, 1.0f));

    // Keybinds draw
    if (IsGamepadAvailable(0)) DrawTextureEx(game.ui.sprites[10], toRayVec(Vector2Create(65, 85)), 0, 0.70, RAYWHITE);
    else                       DrawTexture(game.ui.sprites[8], 65, 50, RAYWHITE);

    if (IsGamepadAvailable(1)) DrawTextureEx(game.ui.sprites[10], toRayVec(Vector2Create(GetScreenWidth() - 65 - game.ui.sprites[9].width, 85)), 0, 0.70, RAYWHITE);
    else                       DrawTexture(game.ui.sprites[9], GetScreenWidth() - 65 - game.ui.sprites[9].width, 50, RAYWHITE);
}

void draw_game_over(Game game)
{
    DrawTextEx(game.ui.font, "GAME OVER",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "GAME OVER", 50, 0).x / 2,
                                      GetScreenHeight() * 1 / 5 - MeasureTextEx(game.ui.font, "GAME OVER", 50, 0).y / 2)),
               50, 0, Fade(RED, 1.0f));

    // Solo and multiplayer game over messages.
    if (game.solo)
    {
        if (game.player[0].score >= game.highscore)
        {
            DrawTextEx(game.ui.font, "NEW HIGHSCORE !",
                       toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "NEW HIGHSCORE !", 25, 0).x / 2,
                                              GetScreenHeight() * 2 / 5 - MeasureTextEx(game.ui.font, "NEW HIGHSCORE !", 25, 0).y / 2)),
                       25, 0, Fade(RAYWHITE, 1.0f));
        }
        else
        {
            DrawTextEx(game.ui.font, "YOUR SCORE:",
                       toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, "YOUR SCORE:", 25, 0).x / 2,
                                              GetScreenHeight() * 2 / 5 - MeasureTextEx(game.ui.font, "YOUR SCORE:", 25, 0).y / 2)),
                       25, 0, Fade(RAYWHITE, 1.0f));
        }
        DrawTextEx(game.ui.font, TextFormat("%d", game.player[0].score),
                   toRayVec(Vector2Create(GetScreenWidth() / 2           - MeasureTextEx(game.ui.font, TextFormat("%d", game.player[0].score), 25, 0).x / 2,
                                          25 + GetScreenHeight() * 2 / 5 + MeasureTextEx(game.ui.font, TextFormat("%d", game.player[0].score), 25, 0).y / 2)),
                   25, 0, Fade(RAYWHITE, 1.0f));
    }
    else if (!game.solo)
    {
        DrawTextEx(game.ui.font, TextFormat("TOTAL SCORE: %d", game.player[0].score + game.player[1].score),
                   toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, TextFormat("TOTAL SCORE: %d", game.player[0].score + game.player[1].score), 25, 0).x / 2,
                                          GetScreenHeight() * 2 / 5 - MeasureTextEx(game.ui.font, TextFormat("TOTAL SCORE: %d", game.player[0].score + game.player[1].score), 25, 0).y / 2)),
                   25, 0, Fade(RAYWHITE, 1.0f));
    }

    DrawTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to go back to main menu" : "Press [Esc] to go back to main menu",
               toRayVec(Vector2Create(GetScreenWidth() / 2      - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to go back to main menu" : "Press [Esc] to go back to main menu", 16, 0).x / 2,
                                      GetScreenHeight() * 4 / 5 - MeasureTextEx(game.ui.font, IsGamepadAvailable(0) ? "Press [GAMEPAD B] to go back to main menu" : "Press [Esc] to go back to main menu", 16, 0).y / 2)),
               16, 0, Fade(RED, 1.0f));
}

void draw_ui(Game game)
{
    switch (game.scene_id)
    {
    case SC_MAIN_MENU:
        draw_main_menu(game);
        break;

    case SC_LOADING:
    case SC_IN_GAME:
        // Player 1 life and score.
        DrawTextEx(game.ui.font, TextFormat("%d", game.player[0].score),
                   toRayVec(Vector2Create(275 - MeasureTextEx(game.ui.font, TextFormat("%d", game.player[0].score), 15, 0).x, 100)),
                   15, 0, RAYWHITE);
        for (int i = 0; i < game.player[0].hp; i++)
        {
            DrawTexturePro(game.ui.sprites[0],
                           toRayRec(RectangleCreate(Vector2Zero(), game.ui.sprites[0].width, game.ui.sprites[0].height)),
                           toRayRec(RectangleCreate(Vector2Create(50 + i * game.ui.sprites[0].width / 3, 100), game.ui.sprites[0].width / 3, game.ui.sprites[0].height / 3)),
                           toRayVec(Vector2Zero()), 0, RAYWHITE);
        }
        if (!game.solo)
        {
            DrawTextEx(game.ui.font, TextFormat("%d", game.player[1].score),
                       toRayVec(Vector2Create(GetScreenWidth() - 50 - MeasureTextEx(game.ui.font, TextFormat("%d", game.player[1].score), 15, 0).x, 100)),
                       15, 0, SKYBLUE);
            for (int i = 0; i < game.player[1].hp; i++)
            {
                DrawTexturePro(game.ui.sprites[0],
                               toRayRec(RectangleCreate(Vector2Zero(), game.ui.sprites[0].width, game.ui.sprites[0].height)),
                               toRayRec(RectangleCreate(Vector2Create(GetScreenWidth() - 275 + i * game.ui.sprites[0].width / 3, 100), game.ui.sprites[0].width / 3, game.ui.sprites[0].height / 3)),
                               toRayVec(Vector2Zero()), 0, SKYBLUE);
            }
        }
        break;

    case SC_PAUSE:
        draw_pause(game);
        break;

    case SC_GAME_OVER:
        draw_game_over(game);
        break;

    default:
        break;
    }

    // Draw overlay.
    DrawTexture(game.ui.overlay, 0, 0, RAYWHITE);
}

void intro_animation(Game *game)
{
    game->ui.animations[0].key += game->ui.animations[0].speed;
    static int  mine_drop_keys[MINE_MAX_AMOUNT];
    static bool mine_dropped[MINE_MAX_AMOUNT];

    if (game->ui.animations[0].key < game->ui.animations[0].end)
    {
        // Move the mothership down on the screen
        DrawTextureEx(game->ui.sprites[2],
                      toRayVec(Vector2Create(GetScreenWidth() / 2    - game->ui.sprites[2].width / 2 + (game->ui.sprites[2].width * game->ui.animations[0].key / game->ui.animations[0].end) / 2,
                                             IN_GAME_SCREEN_OFFSET_Y - game->ui.sprites[2].height    + game->ui.animations[0].key)),
                      0, 1 - game->ui.animations[0].key / game->ui.animations[0].end, RAYWHITE);

        // Make it drop the mine spawn points.
        for (int i = 0; i < MINE_MAX_AMOUNT && game->mines[i].type != MINE_NULL; i++)
        {
            // Make the ship drop mines.
            if (game->mines[i].pos.y + (double)MineSpriteSize(game->mines[i].size) / 2 < IN_GAME_SCREEN_OFFSET_Y - game->ui.sprites[2].height + game->ui.animations[0].key + game->ui.sprites[2].height * (1 - game->ui.animations[0].key / game->ui.animations[0].end) / 2)
                if (!mine_dropped[i])
                {
                    mine_drop_keys[i] = game->ui.animations[0].key;
                    mine_dropped[i]   = true;
                }

            // Make the dropped mines go to their position.
            if (mine_dropped[i])
                DrawCircle(remap(clampUnder(game->ui.animations[0].key,                          game->ui.animations[0].end - 60),
                                 clampUnder(mine_drop_keys[i], game->ui.animations[0].end - 60), game->ui.animations[0].end - 60,
                                 GetScreenWidth() / 2, game->mines[i].pos.x + (double)MineSpriteSize(game->mines[i].size) / 2),
                           game->mines[i].pos.y + (double)MineSpriteSize(game->mines[i].size) / 2,
                           2, WHITE);
        }
    }
    else
    {
        // Reset animations keys.
        game->ui.animations[0].key = 0;
        game->ui.animations[0].end = IN_GAME_SCREEN_OFFSET_H + game->ui.sprites[2].height;

        // Reset mine dropping arrays.
        for (int i = 0; i < MINE_MAX_AMOUNT; i++)
        {
            mine_drop_keys[i] = -1;
            mine_dropped[i]   = false;
        }

        game->scene_id = SC_IN_GAME;
    }
}

void main_draw(Game *game)
{
    BeginBlendMode(BLEND_ADDITIVE);

    switch ((*game).scene_id)
    {
    case SC_LOADING:
        intro_animation(game);
        break;

    case SC_IN_GAME:
        draw_game(game);
        break;

    default:
        break;
    }

    EndBlendMode();
}