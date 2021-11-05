#include "mine.h"

// ------------------------------ Mine related functions ------------------------------ //

int mines_score(MineType type, MineSize size)
{
    // The base score yeild of each mine type.
    int mine_scores[5] = {0, 100, 500, 750, 325};

    // The score bonuses depending on the size (null, small, medium, large).
    int score_bonus[4] = {0, 100, 35, 0};

    return mine_scores[type] + score_bonus[size];
}

void mines_update_hitboxes(Mine *mines)
{
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        if (mines[i].type != MINE_NULL && mines[i].size != MINE_SIZE_NULL)
        {
            // All the hitboxes were done for mines of size 256x256, the hitboxes are resized with this coefficient to fit the mine's actual size.
            double size_coefficient = (double)MineSpriteSize(mines[i].size) / 256;

            // For each mine type, between 3 and 6 triangles are created to act as pixel perfect hitboxes.
            switch (mines[i].type)
            {
            case MINE_FLOATING:
                mines[i].hitboxes[0].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(128, 77 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(146, 136), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(110, 136), size_coefficient), mines[i].pos));
                mines[i].hitboxes[1].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(146, 136), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(185, 184), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(128, 170), size_coefficient), mines[i].pos));
                mines[i].hitboxes[2].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(127, 170), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(71 , 184), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(110, 136), size_coefficient), mines[i].pos));
                break;

            case MINE_MAGNETIC:
                mines[i].hitboxes[0].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(81 , 81 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(128, 103), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(104, 128), size_coefficient), mines[i].pos));
                mines[i].hitboxes[1].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(129, 103), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(177, 77 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(153, 126), size_coefficient), mines[i].pos));
                mines[i].hitboxes[2].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(153, 127), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(175, 175), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(128, 153), size_coefficient), mines[i].pos));
                mines[i].hitboxes[3].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(128, 153), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(80 , 178), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(104, 129), size_coefficient), mines[i].pos));
                break;

            case MINE_MAGNETIC_FIREBALL:
                mines[i].hitboxes[0].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(85 , 53 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(97 , 82 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(85 , 82 ), size_coefficient), mines[i].pos));
                mines[i].hitboxes[1].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(173, 83 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(201, 83 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(173, 96 ), size_coefficient), mines[i].pos));
                mines[i].hitboxes[2].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(173, 173), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(173, 204), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(160, 173), size_coefficient), mines[i].pos));
                mines[i].hitboxes[3].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(84 , 173), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(55 , 173), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(84 , 160), size_coefficient), mines[i].pos));
                mines[i].hitboxes[4].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(85 , 173), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(85 , 83 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(173, 173), size_coefficient), mines[i].pos));
                mines[i].hitboxes[5].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(173, 173), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(173, 83 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(85 , 83 ), size_coefficient), mines[i].pos));
                break;

            case MINE_FIREBALL:
                mines[i].hitboxes[0].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(78 , 76 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(129, 89 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(91 , 128), size_coefficient), mines[i].pos));
                mines[i].hitboxes[1].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(130, 89 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(181, 76 ), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(168, 127), size_coefficient), mines[i].pos));
                mines[i].hitboxes[2].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(168, 128), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(180, 181), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(130, 168), size_coefficient), mines[i].pos));
                mines[i].hitboxes[3].triangle = TriangleCreate(Vector2Add(Vector2MultiplyVal(Vector2Create(129, 168), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(78 , 181), size_coefficient), mines[i].pos),
                                                               Vector2Add(Vector2MultiplyVal(Vector2Create(91 , 129), size_coefficient), mines[i].pos));
                break;

            default:
                break;
            }
        }
    }
}

void mines_init(Mine *mines)
{
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        if (mines[i].type != MINE_NULL)
        {
            // Set the position.
            if (mines[i].size == MINE_LARGE)
            {
                // Large mines will not spawn in the center of the screen. This makes them unable to spawn kill the players.
                mines[i].pos = Vector2Create((GetRandomValue(0, 1) ? GetRandomValue(                        MINE_SPAWN_AREA_OFFSET     , GetScreenWidth()  / 2 - MINE_SPAWN_CENTER_DEAD_ZONE)
                                                                   : GetRandomValue(GetScreenWidth()  / 2 + MINE_SPAWN_CENTER_DEAD_ZONE, GetScreenWidth()      - MINE_SPAWN_AREA_OFFSET)),
                                             (GetRandomValue(0, 1) ? GetRandomValue(                        MINE_SPAWN_AREA_OFFSET     , GetScreenHeight() / 2 - MINE_SPAWN_CENTER_DEAD_ZONE)
                                                                   : GetRandomValue(GetScreenHeight() / 2 + MINE_SPAWN_CENTER_DEAD_ZONE, GetScreenHeight()     - MINE_SPAWN_AREA_OFFSET)));
            }
            else
            {
                // Smaller mines can spawn anywhere since they don't appear at the very start of the round.
                mines[i].pos = Vector2Create(GetRandomValue(MINE_SPAWN_AREA_OFFSET, GetScreenWidth()  - MINE_SPAWN_AREA_OFFSET),
                                             GetRandomValue(MINE_SPAWN_AREA_OFFSET, GetScreenHeight() - MINE_SPAWN_AREA_OFFSET));
            }

            // Set a velocity with a random direction.
            mines[i].velocity = Vector2FromAngle(GetRandomValue(0, 2 * PI), 1);

            // Set booleans.
            mines[i].has_shot     = false;
            mines[i].has_exploded = false;

            // Set the fireball if the mine is a fireball or a magnetic fireball one.
            if (mines[i].type == MINE_FIREBALL || mines[i].type == MINE_MAGNETIC_FIREBALL) {
                mines[i].fireball = (Fireball){ 0, 0, mines[i].pos };
            }
        }

        // Set the hitboxes.
        mines_update_hitboxes(mines);
    }
}

void mines_spawn_point(Mine *mines, int large_mine_amount)
{
    // Calculate the amount of mines of each size.
    int medium_mine_amount = large_mine_amount * 2;
    int small_mine_amount  = medium_mine_amount * 2;
    int mine_amount        = large_mine_amount + medium_mine_amount + small_mine_amount;

    // Make sure there aren't too many or not enough mines.
    assert(0 < mine_amount && mine_amount <= MINE_MAX_AMOUNT);

    // Create the spawn points of the mines.
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        // Set the mine to not spawned, not destroyed and to hasn't shot.
        mines[i].spawned   = false;
        mines[i].destroyed = false;
        mines[i].has_shot  = false;

        // Set the type.
        mines[i].type = GetRandomValue(MINE_FLOATING, MINE_FIREBALL);

        // Set the mine size.
        if (i < large_mine_amount)
        {
            mines[i].size    = MINE_LARGE;
            mines[i].spawned = true; // Large mines should spawn at the start of the round.
        }
        else if (i < large_mine_amount + medium_mine_amount) {
            mines[i].size = MINE_MEDIUM;
        }
        else if (i < large_mine_amount + medium_mine_amount + small_mine_amount)
        {
            mines[i].size = MINE_SMALL;
        }
        else
        {
            // Other mines are set as null mines, since they are not going to be used in the round.
            mines[i].type      = MINE_NULL;
            mines[i].size      = MINE_SIZE_NULL;
            mines[i].destroyed = true;
        }

        // Set the number of hitboxes per mine.
        switch (mines[i].type)
        {
        case MINE_FLOATING:
            mines[i].hitbox_shapes_amount = 3;
            break;
        case MINE_MAGNETIC:
            mines[i].hitbox_shapes_amount = 4;
            break;
        case MINE_MAGNETIC_FIREBALL:
            mines[i].hitbox_shapes_amount = 6;
            break;
        case MINE_FIREBALL:
            mines[i].hitbox_shapes_amount = 4;
            break;
        default:
            break;
        }
    }

    // Initialize all the mines.
    mines_init(mines);
}

void mines_spawn(Mine *mines, MineSize size)
{
    int spawned_mines = 0;
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        // Spawn mines that are of the right size.
        if (mines[i].type != MINE_NULL && !mines[i].destroyed && !mines[i].spawned && mines[i].size == size)
        {
            mines[i].spawned = true;
            spawned_mines++;
        }

        // Stop if two mines have been spawned.
        if (spawned_mines >= 2)
            break;
    }
}

void fireball_spawn(Mine *mine, MyVector2 player_pos)
{
    // Make sure the given mine should shoot a fireball.
    if ((mine->type == MINE_FIREBALL || mine->type == MINE_MAGNETIC_FIREBALL) && mine->destroyed && !mine->has_shot)
    {
        // Spawn the fireball in the center of the mine and make it move towards the player.
        mine->fireball.pos      = Vector2AddVal(mine->pos, MineSpriteSize(mine->size) / 2);
        mine->fireball.rotation = Vector2GetAngle(Vector2FromPoints(mine->fireball.pos, player_pos));
        mine->fireball.lifespan = BULLET_LIFESPAN;
    }
}

MyVector2 find_closest_player_pos(MyVector2 mine_pos, MyVector2 *players_pos)
{
    // Get the player that is closest to the mine and the tistance from the mine to him.
    MyVector2 current_pos = (distancePoints(mine_pos, players_pos[0]) < distancePoints(mine_pos, players_pos[1]) ? players_pos[0] : players_pos[1]);
    int current_pos_dist  =  distancePoints(mine_pos, current_pos);

    // Set the minimum values for distance and the corresponding position.
    MyVector2 closest_pos       = current_pos;
    int       closest_pos_dist  = current_pos_dist;

    // Loop over both players.
    for (int i = 0; i < 2; i++)
    {
        // If the current player is playing (the given player_pos is {-10000, -10000} if he isn't playing).
        if (players_pos[i].x != -10000)
        {
            // Loop over all 4 screen sides.
            for (int j = 0; j < 4; j++)
            {
                // Update the current player position to check wrapping path options.
                switch (j)
                {
                case 0:
                    current_pos = Vector2Create(players_pos[i].x - IN_GAME_SCREEN_W - DEFAULT_SPRITES_SIZE, players_pos[i].y);
                    break;
                case 1:
                    current_pos = Vector2Create(players_pos[i].x + IN_GAME_SCREEN_W + DEFAULT_SPRITES_SIZE, players_pos[i].y);
                    break;
                case 2:
                    current_pos = Vector2Create(players_pos[i].x, players_pos[i].y - IN_GAME_SCREEN_H - DEFAULT_SPRITES_SIZE);
                    break;
                case 3:
                    current_pos = Vector2Create(players_pos[i].x, players_pos[i].y + IN_GAME_SCREEN_H + DEFAULT_SPRITES_SIZE);
                    break;
                }

                // Check if the new position is closer than the previous.
                current_pos_dist = distancePoints(mine_pos, current_pos);
                if (current_pos_dist < closest_pos_dist)
                {
                    closest_pos      = current_pos;
                    closest_pos_dist = current_pos_dist;
                }
            }
        }
    }

    return closest_pos;
}

void mines_update(Mine *mines, MyVector2 *players_pos)
{
    for (int i = 0; i < MINE_MAX_AMOUNT; i++)
    {
        if (mines[i].type != MINE_NULL && !mines[i].destroyed && mines[i].spawned)
        {
            // Make it so magnetic mines move towards the player.
            if (mines[i].type == MINE_MAGNETIC || mines[i].type == MINE_MAGNETIC_FIREBALL)
            {
                mines[i].velocity = Vector2Normalize(Vector2FromPoints(                        Vector2AddVal(mines[i].pos, MineSpriteSize(mines[i].size) / 2),
                                                                       find_closest_player_pos(Vector2AddVal(mines[i].pos, MineSpriteSize(mines[i].size) / 2), players_pos)));
            }

            // Move the mine according to the velocity.
            mines[i].pos = Vector2Add(mines[i].pos, mines[i].velocity);

            // Screen wrapping.
            screen_wrap(&mines[i].pos, MineSpriteSize(mines[i].size));

            // Move the mine hitbox shapes in function of the mine's position.
            mines_update_hitboxes(mines);
        }

        // Update the fireball of mines that can shoot fireballs.
        if ((mines[i].type == MINE_FIREBALL || mines[i].type == MINE_MAGNETIC_FIREBALL) && mines[i].destroyed && !mines[i].has_shot)
        {
            fireball_update(&mines[i]);
        }
    }
}

void fireball_update(Mine *mine)
{
    if (mine->fireball.lifespan >= 0 && !mine->has_shot)
    {
        // Move the fireball in function of its rotation.
        mine->fireball.pos.x += cos(mine->fireball.rotation) * FIREBALL_SPEED;
        mine->fireball.pos.y += sin(mine->fireball.rotation) * FIREBALL_SPEED;

        // Screen wrapping (fireball sprites are half as big as the player).
        screen_wrap(&mine->fireball.pos, DEFAULT_SPRITES_HALF_SIZE);

        // Decrease the fireball's lifespan.
        mine->fireball.lifespan -= 1;
        if (mine->fireball.lifespan <= 0)
            mine->has_shot = true;
    }
}

// ---------------------------- Minelayer related functions --------------------------- //

void minelayer_init(Minelayer *minelayer, Mine *mines)
{
    // Set the Minelayer position.
    minelayer->pos = Vector2Create(GetRandomValue(0, 1) ? IN_GAME_SCREEN_OFFSET_X - 32 : IN_GAME_SCREEN_OFFSET_X + IN_GAME_SCREEN_OFFSET_W + 32,
                                   GetRandomValue(0, 1) ? IN_GAME_SCREEN_OFFSET_Y - 32 : IN_GAME_SCREEN_OFFSET_Y + IN_GAME_SCREEN_OFFSET_H + 32);

    // Set the velocity to 0.
    minelayer->velocity = Vector2Zero();

    // Set the checkpoint positions.
    minelayer->checkpoint_pos[0] = minelayer->pos;
    for (int i = 1; i < 4; i++) {
        minelayer->checkpoint_pos[i] = Vector2Create(GetRandomValue(MINE_SPAWN_AREA_OFFSET, GetScreenWidth()  - MINE_SPAWN_AREA_OFFSET),
                                                     GetRandomValue(MINE_SPAWN_AREA_OFFSET, GetScreenHeight() - MINE_SPAWN_AREA_OFFSET));
    }
    minelayer->checkpoint_pos[4] = Vector2Create(GetRandomValue(0, 1) ? IN_GAME_SCREEN_OFFSET_X - 32 : IN_GAME_SCREEN_OFFSET_X + IN_GAME_SCREEN_OFFSET_W + 32,
                                                 GetRandomValue(0, 1) ? IN_GAME_SCREEN_OFFSET_Y - 32 : IN_GAME_SCREEN_OFFSET_Y + IN_GAME_SCREEN_OFFSET_H + 32);

    // Set the Minelayer trajectory.
    for (int i = 0; i < 4; i++)
        minelayer->trajectory[i] = Vector2FromPoints(minelayer->checkpoint_pos[i], 
                                                     minelayer->checkpoint_pos[i + 1]);

    // Set booleans.
    minelayer->has_spawned = false;
    minelayer->destroyed   = false;

    // Set the checkpoints.
    for (int i = 0; i < 4; i++)
        minelayer->checkpoints[i] = false;
}

bool minelayer_spawn(Minelayer *minelayer, Mine *mines)
{
    if (!minelayer->has_spawned)
    {
        // If some mines still haven't spawned, don't spawn the minelayer.
        for (int mine_i = 0; mine_i < MINE_MAX_AMOUNT; mine_i++) {
            if (mines[mine_i].type != MINE_NULL && !mines[mine_i].spawned && !mines[mine_i].destroyed) {
                return false;
            }
        }

        // If all mines are spawned and the minelayer didn't spawn, spawn it.
        minelayer->has_spawned    = true;
        minelayer->velocity       = Vector2Normalize(minelayer->trajectory[0]);
        minelayer->checkpoints[0] = true;
        return true;
    }
    return false;
}

void minelayer_update(Minelayer *minelayer, Mine *mines)
{
    if (!minelayer->destroyed && (minelayer->has_spawned || minelayer_spawn(minelayer, mines)))
    {
        // Move the minelayer according to its velocity.
        minelayer->pos = Vector2Add(minelayer->pos, minelayer->velocity);

        // Update the minelayer's hitbox.
        minelayer->hitbox.rectangle = RectangleCreate(Vector2Create(minelayer->pos.x - 20, minelayer->pos.y + 20), 64, 21);

        // Trajectory update.
        for (int i = 0; i < 5; i++)
        {
            // If a checkpoint was reached.
            if (roundInt(minelayer->pos.x) == roundInt(minelayer->checkpoint_pos[i].x) &&
                roundInt(minelayer->pos.y) == roundInt(minelayer->checkpoint_pos[i].y))
            {
                // End of the trajectory.
                if (i == 4)
                {
                    // Spawn the minelayer's mines.
                    for (int i = 0; i < MINE_MAX_AMOUNT; i++) {
                        if (!mines[i].spawned && !mines[i].destroyed && mines[i].type != MINE_NULL) {
                            mines[i].spawned = true;
                        }
                    }

                    // Destroy the minelayer.
                    minelayer->destroyed = true;
                }

                // Trajectory change.
                else
                {
                    minelayer->pos            = minelayer->checkpoint_pos[i];
                    minelayer->velocity       = Vector2Normalize(minelayer->trajectory[i]);
                    minelayer->checkpoints[i] = true;
                }

                // Drop the mines.
                if (0 < i && i < 4)
                {
                    int mine_i = 0;
                    while (mine_i < MINE_MAX_AMOUNT && mines[mine_i].type != MINE_NULL)
                        mine_i++;
                    mines[mine_i] = (Mine){ false,                                          // destroyed
                                            false,                                          // spawned
                                            false,                                          // has_shot
                                            false,                                          // has_exploded
                                            3,                                              // hitbox_shapes_amount
                                            MINE_FLOATING,                                  // type
                                            MINE_SMALL,                                     // size
                                            minelayer->checkpoint_pos[i],                   // position
                                            Vector2FromAngle(GetRandomValue(0, 2 * PI), 1), // velocity
                                            (Fireball){ 0, 0, Vector2Zero() },              // fireball
                                            {{ Vector2Zero() }} };                          // hitboxes
                }
            }
        }
    }
}