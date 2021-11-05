#include "draw.h"

int main(void)
{
    // ---------- INITIALIZATION ---------- //

    // Define the screen size.
    const int screenWidth  = 830;
    const int screenHeight = 1060;

    // Initialize the game window.
    InitWindow(screenWidth, screenHeight,
    "MineStorm - Alexandre Perché & Rémi Serra");

    SetTargetFPS(60);
    InitAudioDevice();
    HideCursor();
    SetTraceLogLevel(LOG_ERROR);

    // Initialize the game object.
    Game game;
    game_init(&game);

    /*------------------------------------------------------//
     Load the game's shader (from raylib examples).
     Loading shaders always shows warnings in raylib's logs.
    /-------------------------------------------------------*/
    Shader shader = LoadShader(0, "assets/shaders/scanlines.fs");

    // ------ GAME LOOP ------ //
    while (!WindowShouldClose())
    {
        // -------------------------- UPDATE -------------------------- //
        main_update(&game);

        // ----------------- DISPLAY ON RENDER TEXTURE --------------- //
        BeginTextureMode(game.rendertexture);
        {
            ClearBackground(BLACK);
            main_draw(&game);
        }
        EndTextureMode();

        // ------- DISPLAY ON SCREEN WITH POST-PROCESS EFFECTS ------ //
        BeginDrawing();
        {
            ClearBackground(BLACK);

            // Apply the scanlines shader to game objects.
            BeginShaderMode(shader);
            {
                // Render texture must be y-flipped due to default OpenGL coordinates (left-bottom).
                DrawTextureRec(game.rendertexture.texture,
                               (Rectangle){0, 0, screenWidth, -screenHeight},
                               toRayVec(game.rendertexture_offset), // Apply the screen shake.
                               WHITE);
            }
            EndShaderMode();

            // Draw the ui.
            draw_ui(game);
        }
        EndDrawing();
    }

    // ---- DE-INITIALIZATION ---- //
    unload_game_ressources(&game);

    CloseAudioDevice();
    CloseWindow();

    return 0;
}