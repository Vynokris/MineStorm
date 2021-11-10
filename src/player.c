#include "player.h"

void player_update_hitbox(Player *player)
{
    // Create the player's hitbox triangle in function of his position and rotation.
    MyVector2 points[3] =
        {
            Vector2Create((player->pos.x - cos(player->rotation) * 16) + sinf(player->rotation) * 12 - player->velocity.x,
                          (player->pos.y - sin(player->rotation) * 16) - cosf(player->rotation) * 12 - player->velocity.y),

            Vector2Create((player->pos.x - cos(player->rotation) * 16) - sinf(player->rotation) * 12 - player->velocity.x,
                          (player->pos.y - sin(player->rotation) * 16) + cosf(player->rotation) * 12 - player->velocity.y),

            Vector2Create((player->pos.x - cos(player->rotation) * 16) + cosf(player->rotation) * 38 - player->velocity.x,
                          (player->pos.y - sin(player->rotation) * 16) + sinf(player->rotation) * 38 - player->velocity.y),
        };
    player->hitbox.triangle = TriangleCreate(points[0], points[1], points[2]);
}

void player_init(Player *player)
{
    // Set player base data.
    player->destroyed      = false;
    player->has_explosed   = false;
    player->is_teleporting = false;
    player->hp             = 3;
    player->rotation       = -PI / 2;
    player->pos            = Vector2Create(GetScreenWidth() / 2, 
                                           GetScreenHeight() / 2);
    player->velocity       = Vector2Zero();
    player->score          = 0;
    player->tp_delay       = 0;
    player_update_hitbox(player);

    // Debris trajectory and rotation intialization.
    for (int i = 0; i < 4; i++)
    {
        // Random rotations and diagonal trajectories for debris.
        player->debris_trajectory[i] = Vector2Create(GetRandomValue(-10, 10) * pow(-1, GetRandomValue(1, 2)),
                                                     GetRandomValue(-10, 10) * pow(-1, GetRandomValue(1, 2)));
        player->debris_rotation[i]   = (float)GetRandomValue(0, 360);
    }
}

void player_shoot(Player *player)
{
    if (player->hp > 0)
    {
        // Add a bullet if there are some bullets that still haven't been fired.
        for (int i = 0; i < BULLET_MAX_AMOUNT; i++)
        {
            if (player->bullets[i].lifespan == 0)
            {
                // Set the bullet's values according to the player's.
                player->bullets[i].pos.x    = player->pos.x + cosf(player->rotation) * 32;
                player->bullets[i].pos.y    = player->pos.y + sinf(player->rotation) * 32;
                player->bullets[i].rotation = player->rotation;
                player->bullets[i].lifespan = BULLET_LIFESPAN;
                break;
            }
        }
    }
}

void player_update(Player *player, int player_id)
{
    // Update the player actions and movements.
    if (player->hp > 0 && !player->destroyed && !player->is_teleporting)
    {
        // -- Accelerate -- //
        if (IsKeyDown((player_id == 0 ? KEY_W : KEY_KP_8)) || 
           (IsGamepadAvailable(player_id == 0 ? 0 : 1) && IsGamepadButtonDown(player_id == 0 ? 0 : 1, 7)))
        {
            // If the player is under the maximum velocity, make him accelerate.
            if (Vector2Length(player->velocity) < PLAYER_MAX_VELOCITY)
                player->velocity = Vector2Add(Vector2MultiplyVal(player->velocity, 1), Vector2FromAngle(player->rotation, 0.6));

            // If the player is at maximum velocity, stop accelerating.
            else
                player->velocity = Vector2Add(Vector2MultiplyVal(player->velocity, 0.7), Vector2FromAngle(player->rotation, 0.3));
        }

        // -- Accelerate with joystick -- //
        else if (IsGamepadAvailable(player_id) && (fabs(GetGamepadAxisMovement(player_id, 0)) > 0.1 ||
                                                   fabs(GetGamepadAxisMovement(player_id, 1)) > 0.1))
        {
            // Get the direction of the joystick.
            MyVector2 dir = Vector2Create(GetGamepadAxisMovement(player_id, 0), GetGamepadAxisMovement(player_id, 1));

            // If the player is under the maximum velocity, make him accelerate.
            if (Vector2Length(player->velocity) < PLAYER_MAX_VELOCITY)
                player->velocity = Vector2Add(Vector2MultiplyVal(player->velocity, 1), Vector2SetLength(dir, 0.6));

            // If the player is at maximum velocity, stop accelerating.
            else
                player->velocity = Vector2Add(Vector2MultiplyVal(player->velocity, 0.7), Vector2SetLength(dir, 0.3));
        }

        // -- Slow down -- //
        else if (Vector2Length(player->velocity) > 0)
        {
            player->velocity = Vector2MultiplyVal(player->velocity, 0.96);
        }

        // -- Turn -- //
        if (IsKeyDown((player_id == 0 ? KEY_A : KEY_KP_4)) || 
           (IsGamepadAvailable(player_id) && IsGamepadButtonDown(player_id, 4)))
        {
            player->rotation -= PI / 48;
        }
        if (IsKeyDown((player_id == 0 ? KEY_D : KEY_KP_6)) || 
           (IsGamepadAvailable(player_id) && IsGamepadButtonDown(player_id, 2)))
        {
            player->rotation += PI / 48;
        }

        // -- Snap turn with gamepad joystick -- //
        if (IsGamepadAvailable(player_id) && (fabs(GetGamepadAxisMovement(player_id, 2)) > 0.1 || 
                                              fabs(GetGamepadAxisMovement(player_id, 3)) > 0.1))
        {
            player->rotation = Vector2GetAngle(Vector2Normalize(Vector2Create(GetGamepadAxisMovement(player_id, 2), 
                                                                              GetGamepadAxisMovement(player_id, 3))));
        }
 
        // -- Shoot -- //
        if (IsKeyPressed((player_id == 0 ? KEY_G : KEY_KP_0)) || 
            (IsGamepadAvailable(player_id) && IsGamepadButtonPressed(player_id, 12)))
        {
            player_shoot(player);
        }

        // -- Teleport -- //
        if ((player_id == 0 ? IsKeyPressed(KEY_J) : (IsKeyPressed(KEY_KP_7) || IsKeyPressed(KEY_KP_9))) ||
            (IsGamepadAvailable(player_id) && (IsGamepadButtonPressed(player_id, 8) || IsGamepadButtonPressed(player_id, 10))))
        {
            player_tp(player);
        }

        // Move according to velocity.
        player->pos = Vector2Add(player->pos, player->velocity);

        // Screen wrapping.
        screen_wrap(&player->pos, DEFAULT_SPRITES_SIZE);

        // Update the hitbox.
        player_update_hitbox(player);
    }

    // Decrement the teleportation delay.
    if (player->tp_delay > 0) player->tp_delay--;
    else                      player->is_teleporting = false;
}

void player_tp(Player *player)
{
    if (player->tp_delay <= 0)
    {
        // Move the player to a random position on the screen.
        player->pos = Vector2Create(GetRandomValue(IN_GAME_SCREEN_OFFSET_X + 50, IN_GAME_SCREEN_OFFSET_X + IN_GAME_SCREEN_OFFSET_W - 50),
                                    GetRandomValue(IN_GAME_SCREEN_OFFSET_X + 50, IN_GAME_SCREEN_OFFSET_Y + IN_GAME_SCREEN_OFFSET_H - 50));

        // Reset the player's velocity, rotation and tp delay.
        player->velocity       = Vector2Zero();
        player->rotation       = -PI / 2;
        player->tp_delay       = PLAYER_TP_DELAY;
        player->is_teleporting = true;
    }
}