#include "game.h"
#include "stdio.h"
#include "stdlib.h"

// ----------- User Interface and Audio initialization functions ------------ //

void audio_init(Game *game)
{
    game->sfx[0] = LoadSound("./assets/audio/mothership.ogg");
    game->sfx[1] = LoadSound("./assets/audio/spaceship_explosion.ogg");
    game->sfx[2] = LoadSound("./assets/audio/bullet_shot.ogg");
    game->sfx[3] = LoadSound("./assets/audio/floating_mine_explosion.ogg");
    game->sfx[4] = LoadSound("./assets/audio/fireball_mine_explosion.ogg");
    game->sfx[5] = LoadSound("./assets/audio/teleport.ogg");

    // Set the default SFX volume.
    for (int i = 0; i < 6; i++) SetSoundVolume(game->sfx[i], 0.25);

    // Set the mothership SFX volume.
    SetSoundVolume(game->sfx[0], 1);

    // Load the music.
    game->music         = LoadMusicStream("./assets/audio/MineStormMind.ogg");
    game->music.looping = true;
}

void audio_update(Game *game)
{
    switch (game->scene_id)
    {
    case SC_LOADING:
        // Reset music and player explosion SFX.
        StopMusicStream(game->music);
        StopSound(game->sfx[1]);

        // Play UFO intro SFX.
        if (!IsSoundPlaying(game->sfx[0]))
            PlaySound(game->sfx[0]);

        break;

    case SC_IN_GAME:
        // Music loop.
        if (!IsMusicStreamPlaying(game->music))
        {
            StopSound(game->sfx[0]);
            PlayMusicStream(game->music);
        }
        else
        {
            UpdateMusicStream(game->music);
        }

        // Bullet sound.
        if (IsKeyPressed(KEY_SPACE) || IsKeyPressed(KEY_KP_0) || 
            IsGamepadButtonPressed(0, 12) || (!game->solo && IsGamepadButtonPressed(1, 12)))
        {
            PlaySoundMulti(game->sfx[2]);
        }

        // Explosions (according to mines type).
        for (int i = 0; i < MINE_MAX_AMOUNT; i++)
        {
            if (game->mines[i].type != MINE_NULL && game->mines[i].destroyed && !game->mines[i].has_exploded)
            {
                if (game->mines[i].type == MINE_FIREBALL || game->mines[i].type == MINE_MAGNETIC_FIREBALL) {
                    if (!IsSoundPlaying(game->sfx[4])) {
                        PlaySound(game->sfx[4]);
                    }
                }
                else {
                    if (!IsSoundPlaying(game->sfx[3])) {
                        PlaySound(game->sfx[3]);
                    }
                }
            }
        }

        // Teleportation sound.
        for (int player_id = 0; player_id < (game->solo ? 1 : 2); player_id++)
            if (!IsSoundPlaying(game->sfx[5]) && game->player[player_id].tp_delay == PLAYER_TP_DELAY - 1)
                PlaySound(game->sfx[5]);
                
        break;

    default:
        break;
    }
}

void ui_init(Game *game)
{
    // Sprites initialization.
    game->ui.overlay = LoadTexture("./assets/sprites/overlay.png");
    game->ui.font    = LoadFont("./assets/font/ARCADE_I.ttf");
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Image sprite = LoadImage("./assets/sprites/spritesheet.png");
            ImageCrop(&sprite, toRayRec(RectangleCreate(Vector2Create(j * 256, i * 256), 256, 256)));
            
            if (i == 0)
            {
                // Resize all sprites.
                if (j != 2) {
                    ImageResize(&sprite, 64, 64);
                }

                // Resize mothership.
                else {
                    ImageResize(&sprite, 512, 512);
                }
                game->ui.sprites[i + j]     = LoadTextureFromImage(sprite);
            }
            else
            {
                game->ui.sprites[i + j + 3] = LoadTextureFromImage(sprite);
            }
            UnloadImage(sprite);
        }
    }
    game->ui.sprites[8]  = LoadTexture("./assets/sprites/binds_player_1.png");
    game->ui.sprites[9]  = LoadTexture("./assets/sprites/binds_player_2.png");
    game->ui.sprites[10] = LoadTexture("./assets/sprites/binds_gamepad.png");

    // Animations initialization
    for (int i = 0; i < 4; i++) game->ui.animations[i].key = 0;

    // Intro animation initialization
    game->ui.animations[0].end   = IN_GAME_SCREEN_OFFSET_H + game->ui.sprites[2].height;
    game->ui.animations[0].speed = 5.0f;

    // Mine destroyed animation initialization
    game->ui.animations[1].end   = 30;
    game->ui.animations[1].speed = 1.0f;

    // Player destroyed animation initialization
    game->ui.animations[2].end   = 60;
    game->ui.animations[2].speed = 1.0f;

    // Player teleporting animation initialization
    game->ui.animations[3].end   = PLAYER_TP_DELAY;
    game->ui.animations[3].speed = 1.0f;
}

void unload_game_ressources(Game *game)
{
    // Unload overlay and font.
    UnloadTexture(game->ui.overlay);
    UnloadFont(game->ui.font);

    // Unload object sprites.
    for (int i = 0; i < 11; i++) UnloadTexture(game->ui.sprites[i]);

    // Unload audio
    StopSoundMulti();
    for (int i = 0; i < 6; i++)  UnloadSound(game->sfx[i]);
    UnloadMusicStream(game->music);
}

// ----------- Game related functions ----------- //

void load_highscore(Game *game)
{
    // Get the player's highscore.
    FILE *f = fopen("./data/highscore.bin", "rb");
    if (f)
    {
        fread(&game->highscore, sizeof(int), 1, f);
    }
    else
    {
        game->highscore = 0;
        fprintf(stderr, "fopen() failed for ./data/highscore.bin\n");
    }
    fclose(f);
}

void save_highscore(Game *game)
{
    // Get the player's highscore.
    FILE *f = fopen("./data/highscore.bin", "rb");
    if (f) fread(&game->highscore, sizeof(int), 1, f);
    else   game->highscore = 0;
    fclose(f);

    // If the player's score is higher than the highscore, overwrite the highscore.
    if (game->player[0].score > game->highscore)
        game->highscore = game->player[0].score;
    // If the game is multiplayer, add the two players' scores together to make the final score.
    if (!game->solo && game->player[0].score + game->player[1].score > game->highscore)
        game->highscore = game->player[0].score + game->player[1].score;

    // Save the highscore.
    f = fopen("./data/highscore.bin", "wb");
    fwrite(&game->highscore, sizeof(int), 1, f);
    fclose(f);
}

void game_init(Game *game)
{
    // Set the scene ID.
    game->scene_id = SC_MAIN_MENU;

    // Set difficulty.
    game->difficulty = 1;

    // Set the render texture.
    game->rendertexture = LoadRenderTexture(GetScreenWidth(), GetScreenHeight());

    // Set the render texture's offset.
    game->rendertexture_offset = Vector2Zero();

    // Initialize the audio.
    audio_init(game);

    // Initialize the user interface.
    ui_init(game);

    // Load highscore.
    load_highscore(game);

    // Initialize the player.
    player_init(&game->player[0]);
    player_init(&game->player[1]);

    // Initialize the bullets.
    bullet_init(game->player[0].bullets);
    bullet_init(game->player[1].bullets);

    // Initialize the mines.
    mines_spawn_point(game->mines, 1);

    // Initialize the minelayer.
    minelayer_init(&game->minelayer, game->mines);
}

void game_start_solo(Game *game)
{
    game->solo       = true;
    game->difficulty = 1;
    player_init(&game->player[0]);
    round_next(game);

    game->scene_id = SC_LOADING;
}

void game_start_duo(Game *game)
{
    game->solo       = false;
    game->difficulty = 1;
    player_init(&game->player[0]);
    player_init(&game->player[1]);
    round_next(game);

    game->scene_id = SC_LOADING;
}

void round_next(Game *game)
{
    // Increase difficulty.
    if (game->difficulty < DIFFICULTY_MAX && is_round_over(game)) game->difficulty++;

    // Move the players back to the center of the screen.
    for (int i = 0; i < 2; i++)
    {
        game->player[i].pos        = Vector2Create(GetScreenWidth() / 2, GetScreenHeight() / 2);
        game->player[i].rotation   = -PI / 2;
        game->player[i].velocity   = Vector2Zero();
        game->player[i].destroyed  = false;
        game->ui.animations[2].key = 0;
        player_update_hitbox(&game->player[i]);
    }

    // Initialize the bullets.
    bullet_init(game->player[0].bullets);
    bullet_init(game->player[1].bullets);

    // Initialize the mines.
    mines_spawn_point(game->mines, game->difficulty);

    // Initialize the minelayer.
    minelayer_init(&game->minelayer, game->mines);

    // Set the scene ID.
    game->scene_id = SC_LOADING;
}

void set_mines_explosion_segments(Game *game, int mine_i)
{
    // Set mines explosions segments.
    game->ui.mines_explosion[0] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x,       game->mines[mine_i].pos.y - 75));
    game->ui.mines_explosion[1] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x + 90,  game->mines[mine_i].pos.y - 50));
    game->ui.mines_explosion[2] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x + 95,  game->mines[mine_i].pos.y - 10));
    game->ui.mines_explosion[3] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x + 150, game->mines[mine_i].pos.y + 50));
    game->ui.mines_explosion[4] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x + 100, game->mines[mine_i].pos.y + 65));
    game->ui.mines_explosion[5] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x,       game->mines[mine_i].pos.y + 75));
    game->ui.mines_explosion[6] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x - 100, game->mines[mine_i].pos.y + 75));
    game->ui.mines_explosion[7] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x - 100, game->mines[mine_i].pos.y + 10));
    game->ui.mines_explosion[8] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x - 50,  game->mines[mine_i].pos.y - 40));
    game->ui.mines_explosion[9] = SegmentCreate(Vector2AddVal(game->mines[mine_i].pos, (double)MineSpriteSize(game->mines[mine_i].size) / 2), Vector2Create(game->mines[mine_i].pos.x - 20,  game->mines[mine_i].pos.y - 150));
}

void collision_update(Game *game)
{
    // Create shapes for bullets, to be used for bullet-object collision.
    Shape bullet_shape, bullet_shape_bis;

    for (int player_id = 0; player_id < (game->solo ? 1 : 2); player_id++) // Loop over the players.
    {
        if (game->player[player_id].hp > 0) // Don't consider dead players.
        {
            for (int mine_i = 0; mine_i < MINE_MAX_AMOUNT; mine_i++) // Loop over the mines.
            {
                if (game->mines[mine_i].type != MINE_NULL && !game->mines[mine_i].destroyed && game->mines[mine_i].spawned) // Don't consider non-spawned, destroyed and null mines.
                {
                    for (int hitbox_i = 0; hitbox_i < game->mines[mine_i].hitbox_shapes_amount; hitbox_i++) // Loop over the mine hitboxes.
                    {
                        for (int bullet_i = 0; bullet_i < BULLET_MAX_AMOUNT; bullet_i++) // Loop over the bullets.
                        {
                            if (game->player[player_id].bullets[bullet_i].lifespan > 0) // Don't consider non-shot bullets.
                            {
                                // ---------- BULLET - MINE COLLISIONS ---------- //

                                // Check collision between the current bullet and the current mine hitbox.
                                bullet_shape.circle = CircleCreate(game->player[player_id].bullets[bullet_i].pos, 3);
                                if (collisionSAT(bullet_shape, CIRCLE, game->mines[mine_i].hitboxes[hitbox_i], TRIANGLE))
                                {
                                    // If the mine was hit, destroy it and the bullet.
                                    game->mines[mine_i].destroyed                      = true;
                                    game->player[player_id].bullets[bullet_i].lifespan = 0;
                                    game->player[player_id].score                     += mines_score(game->mines[mine_i].type, game->mines[mine_i].size);

                                    // Create the segments for the explosion of the mine.
                                    set_mines_explosion_segments(game, mine_i);

                                    // Spawn the new mines as well as a fireball if the mine was of certain types and sizes.
                                    fireball_spawn(&game->mines[mine_i], game->player[player_id].pos);
                                    mines_spawn(game->mines, game->mines[mine_i].size - 1);
                                }
                            }

                            // ------------ PLAYER - MINE COLLISIONS ------------ //

                            if (collisionSAT(game->player[player_id].hitbox, TRIANGLE, game->mines[mine_i].hitboxes[hitbox_i], TRIANGLE))
                            {
                                // Play a sound for the player's explosion.
                                if (!game->player[player_id].destroyed)
                                {
                                    game->player[player_id].hp--;
                                    if (!IsSoundPlaying(game->sfx[1])) PlaySound(game->sfx[1]);
                                }

                                // Set debris trajectory array.
                                for (int i = 0; i < 4; i++)
                                {
                                    game->player[player_id].debris_trajectory[i] = Vector2Create(GetRandomValue(-10, 10) * pow(-1, i), GetRandomValue(-10, 10) * pow(-1, i));
                                    game->player[player_id].debris_rotation[i]   = (float)GetRandomValue(0, 360);
                                }

                                // Explode the player and the mine.
                                game->player[player_id].destroyed = true;
                                game->mines[mine_i].destroyed     = true;
                        
                                // Create the segments for the explosion of the mine.
                                set_mines_explosion_segments(game, mine_i);
                            }
                        }
                    }
                }

                if ((game->mines[mine_i].type == MINE_FIREBALL ||  game->mines[mine_i].type == MINE_MAGNETIC_FIREBALL) && // Consider only mines that can shoot.
                     game->mines[mine_i].fireball.lifespan > 0 && !game->mines[mine_i].has_shot)                          // Consider only mines that have shot.
                {
                    // ------------------- FIREBALL - PLAYER COLLISIONS ------------------- //

                    // Check if a fireball hit the current player.
                    bullet_shape.circle = CircleCreate(game->mines[mine_i].fireball.pos, 5);
                    if (collisionSAT(game->player[player_id].hitbox, TRIANGLE, bullet_shape, CIRCLE))
                    {
                        // Destroy the fireball.
                        game->mines[mine_i].fireball.lifespan = 0;

                        // Destroy the player.
                        if (!game->player[player_id].destroyed)
                        {
                            game->player[player_id].hp--;
                            game->player[player_id].destroyed = true;
                            if (!IsSoundPlaying(game->sfx[1])) PlaySound(game->sfx[1]);
                        }
                    }

                    // ------------------- BULLET - FIREBALL COLLISIONS ------------------- //
                    
                    for (int bullet_i = 0; bullet_i < BULLET_MAX_AMOUNT; bullet_i++) // Loop over the bullets.
                    {
                        if (game->player[player_id].bullets[bullet_i].lifespan > 0)  // Don't consider non-shot bullets.
                        {
                            // Check if a bullet hit a fireball.
                            bullet_shape.circle     = CircleCreate(game->player[player_id].bullets[bullet_i].pos, 3);
                            bullet_shape_bis.circle = CircleCreate(game->mines[mine_i].fireball.pos,              5);
                            if (collisionCircles(bullet_shape.circle, bullet_shape_bis.circle))
                            {
                                // Destroy the bullet and the fireball.
                                game->player[player_id].bullets[bullet_i].lifespan = 0;
                                game->mines[mine_i].fireball.lifespan              = 0;
                            }
                        }
                    }
                }
            }

            if (game->minelayer.has_spawned && !game->minelayer.destroyed)
            {
                // ------------------- MINELAYER - PLAYER COLLISIONS ------------------- //

                // Check if the player hit the minelayer.
                if (collisionSAT(game->player[player_id].hitbox, TRIANGLE, game->minelayer.hitbox, RECTANGLE))
                {
                    // Destroy the player.
                    if (!game->player[player_id].destroyed)
                    {
                        game->player[player_id].hp--;
                        game->player[player_id].destroyed = true;
                        if (!IsSoundPlaying(game->sfx[1])) PlaySound(game->sfx[1]);
                    }
                }

                // ------------------- MINELAYER - BULLET COLLISIONS ------------------- //

                for (int bullet_i = 0; bullet_i < BULLET_MAX_AMOUNT; bullet_i++) // Loop over the bullets.
                {
                    if (game->player[player_id].bullets[bullet_i].lifespan > 0)  // Don't consider non-shot bullets.
                    {
                        bullet_shape.circle = CircleCreate(game->player[player_id].bullets[bullet_i].pos, 3);
                        if (collisionSAT(bullet_shape, CIRCLE, game->minelayer.hitbox, RECTANGLE))
                        {
                            game->player[player_id].score += 1000;
                            game->minelayer.destroyed      = true;

                            // Spawn the minelayer's mines.
                            for (int i = 0; i < MINE_MAX_AMOUNT; i++)
                            {
                                if (!game->mines[i].spawned && !game->mines[i].destroyed && game->mines[i].type != MINE_NULL) {
                                    game->mines[i].spawned = true;
                                }
                            }
                            break;
                        }
                    }
                }
            }
        }

        if (!game->solo)
        {
            // -------------------- FRIENDLY FIRE -------------------- //
            // Loop over all the bullets.
            for (int bullet_i = 0; bullet_i < BULLET_MAX_AMOUNT; bullet_i++)
            {
                // Check if one of player 1's bullets hit player 2.
                bullet_shape.circle = CircleCreate(game->player[1].bullets[bullet_i].pos, 3);
                if (collisionSAT(game->player[0].hitbox, TRIANGLE, bullet_shape, CIRCLE) && game->player[0].hp > 0)
                {
                    if (!game->player[0].destroyed)
                    {
                        game->player[0].bullets[bullet_i].lifespan = 0;
                        game->player[0].hp--;
                        if (!IsSoundPlaying(game->sfx[1])) PlaySound(game->sfx[1]);
                    }
                    game->player[0].destroyed = true;
                    break;
                }

                // Check if one of player 2's bullets hit player 1.
                bullet_shape.circle = CircleCreate(game->player[0].bullets[bullet_i].pos, 3);
                if (collisionSAT(game->player[1].hitbox, TRIANGLE, bullet_shape, CIRCLE) && game->player[1].hp > 0)
                {
                    if (!game->player[1].destroyed)
                    {
                        game->player[1].bullets[bullet_i].lifespan = 0;
                        game->player[1].hp--;
                        if (!IsSoundPlaying(game->sfx[1])) PlaySound(game->sfx[1]);
                    }
                    game->player[1].destroyed = true;
                    break;
                }
            }

            // ------------------- BULLET - BULLET COLLISIONS ------------------- //
            for (int bullet_p1 = 0; bullet_p1 < BULLET_MAX_AMOUNT; bullet_p1++)
            {
                for (int bullet_p2 = 0; bullet_p2 < BULLET_MAX_AMOUNT; bullet_p2++)
                {
                    bullet_shape.circle = CircleCreate(game->player[0].bullets[bullet_p1].pos, 3);
                    bullet_shape_bis.circle = CircleCreate(game->player[1].bullets[bullet_p2].pos, 3);
                    if (collisionSAT(bullet_shape, CIRCLE, bullet_shape_bis, CIRCLE))
                    {
                        game->player[0].bullets[bullet_p1].lifespan = game->player[1].bullets[bullet_p2].lifespan = 0;
                        break;
                    }
                }
            }
        }
    }
}

void game_update(Game *game)
{
    if (is_game_over(game))
    {
        // Save the players' highscores.
        save_highscore(game);

        // Switch to the game over screen.
        game->scene_id = SC_GAME_OVER;
    }
    else
    {
        // Update the player and bullets.
        for (int player_id = 0; player_id < (game->solo ? 1 : 2); player_id++)
        {
            player_update(&game->player[player_id], player_id);
            // If teleporting, reset animation after it delay
            if (!game->player[player_id].is_teleporting) game->ui.animations[3].key = 0;
            bullet_update(game->player[player_id].bullets);
        }

        // Update the mines.
        MyVector2 players_pos[2] = {(game->player[0].hp > 0 ? game->player[0].pos : Vector2Create(-10000, -10000)),
                                    (!game->solo && game->player[1].hp > 0 ? game->player[1].pos : Vector2Create(-10000, -10000))};
        mines_update(game->mines, players_pos);

        // Update the minelayer.
        minelayer_update(&game->minelayer, game->mines);

        // Update all the collisions
        collision_update(game);

        // Pause menu bind.
        if (IsKeyPressed(KEY_ESCAPE) ||
            IsGamepadButtonPressed(0, 15) || IsGamepadButtonPressed(1, 15))
        {
            game->scene_id = SC_PAUSE;
        }

        // Check if all mines were destroyed.
        if (is_round_over(game)) round_next(game);
    }
}

bool is_round_over(Game *game)
{
    // Find the number of remaining mines.
    for (int i = 0; i < MINE_MAX_AMOUNT; i++) if (game->mines[i].type != MINE_NULL && !game->mines[i].destroyed) return false;
    return true;
}

bool is_game_over(Game *game)
{
    if (game->solo) return game->player[0].hp <= 0;
    else            return game->player[0].hp <= 0 && game->player[1].hp <= 0;
}

void main_update(Game *game)
{
    audio_update(game);

    switch (game->scene_id)
    {
    case SC_MAIN_MENU:
        SetExitKey(KEY_ESCAPE);
        
        // Start a solo game.
        if (IsKeyPressed(KEY_G) || 
            IsGamepadButtonPressed(0, 15) || IsGamepadButtonPressed(1, 15))
        {
            game_start_solo(game);
        }

        // Start a 2 player game.
        if (IsKeyPressed(KEY_J) ||
            IsGamepadButtonPressed(0, 13) || IsGamepadButtonPressed(1, 13))
        {
            game_start_duo(game);
        }
        break;

    case SC_LOADING:
        // Change exit key to delete
        SetExitKey(KEY_DELETE);
        break;

    case SC_IN_GAME:
        // Update the game.
        game_update(game);
        
        break;

    case SC_PAUSE:
        // Unpause.
        if (IsKeyPressed(KEY_G) || 
            IsGamepadButtonPressed(0, 6) || IsGamepadButtonPressed(1, 6))
        {
            game->scene_id = SC_IN_GAME;
        }
        // Go back to main menu.
        if (IsKeyPressed(KEY_ESCAPE) || 
            IsGamepadButtonPressed(0, 15) || IsGamepadButtonPressed(1, 15))
        {
            game->scene_id = SC_MAIN_MENU;
        }
        
        break;

    case SC_GAME_OVER:
        if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_G) ||
            IsGamepadButtonPressed(0, 6) || IsGamepadButtonPressed(1, 6))
        {
            game->scene_id = SC_MAIN_MENU;
        }

        break;

    default:
        break;
    }

    // Reset the rendertexture offset when the screen isn't shaking.
    static MyVector2 last_offset = (MyVector2){0, 0};
    if ((game->rendertexture_offset.x != 0 && game->rendertexture_offset.y != 0) &&                       // Make sure the game is shaking.
        (last_offset.x == game->rendertexture_offset.x && last_offset.y == game->rendertexture_offset.y)) // Check if the game just stopped shaking.
    {
        game->rendertexture_offset = Vector2Zero();
    }
    last_offset = game->rendertexture_offset;

    // Take screenshots.
    if (IsKeyPressed(KEY_F2))
    {
        // Get the current time.
        time_t now;
        time(&now);
        struct tm *timeInfo = localtime(&now);
        // Save a screenshot with the date and time in its name.
        char buf[256];
        strftime(buf, 256, "%F_%T", timeInfo);
        TakeScreenshot(TextFormat("./data/screenshots/screenshot_%s.png", buf));
        TraceLog(LOG_INFO, "Screenshot saved in ./data/screenshots/screenshot_%s.png", buf);
    }
}
