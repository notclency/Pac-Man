/*

Purpose: Render the game to the screen. This is the main function that calls all the other render functions.
Anything that needs to be rendered to the screen is implemented in this file

*/

#include "RENDERER.H"

/*
Inputs: Model *model, char *base, int player_count, int player
Purpose: To render the everything that is needed in the game to the screen.
This function calls all the other render functions.

*/
void render(Model *model, char *base, int player_count, int player)
{
    /*clear_screen((char *)base);*/
    plot_screen((UINT32 *)base, (UINT32 *)map_display);

    render_scorebox(model, (UINT8 *)base, player_count);
    render_livebox(model, (UINT16 *)base, player_count);
    render_glow_balls(model, (UINT16 *)base, player);

    render_ghosts(model, (UINT16 *)base, player);
    render_snacks(model, (UINT16 *)base, player);
    render_pacman(model, (UINT16 *)base, player);

    /*
    render_cherries(model->cherries, (UINT16 *)base);
    render_glow_balls(model->glow_balls, (UINT16 *)base);
    */
}

/*

Inputs: Model *model, UINT16 *base, int player_count
Purpose: To render the pacman to the screen. Depending on the direction of the move it will face
pacman to that direction.

*/
void render_pacman(Model *model, UINT16 *base, int player)
{
    int i;
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);

    /* new function that renders to nothing. WHen ghost eat pacman and pacmna not in SUPER mode */
    /* shifts pacman into black */

    /* render according ot direction */
    if (model->pacman[player].is_dead == FALSE)
    {
        switch (model->pacman[player].direction)
        {
        case UP:
            if (!is_wall(pacman_x, pacman_y - 1))
            {
                model->pacman[player].y -= PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_up, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_up_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
            }
            break;
        case DOWN:
            if (!is_wall(pacman_x, pacman_y + 1))
            {
                model->pacman[player].y += PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_down, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_down_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
            }
            break;
        case LEFT:
            if (!is_wall(pacman_x - 1, pacman_y))
            {
                model->pacman[player].x -= PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_left_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
            }
            break;
        case RIGHT:
            if (!is_wall(pacman_x + 1, pacman_y))
            {
                model->pacman[player].x += PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_right_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
            }
            break;

        case NONE:
            plot_bitmap_16_2(base, (int)model->pacman[player].x, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
            break;
        }

        model->pacman[player].frame++;
        if (model->pacman[player].frame > 2)
        {
            model->pacman[player].frame = 0;
        }
    }
}


/*

Inputs: Model *model, UINT16 *base, int player
Purpose: Renders the ghosts on the screen.

*/
void render_ghosts(Model *model, UINT16 *base, int player)
{
    int i;
    int custom;

    /* render according to mode & direction */

    if (model->pacman[player].mode == SUPER)
    {
        model->pacman[player].tick++;
    }

    if (model->pacman[player].tick > 5)
    {
        model->pacman[player].mode = NORMAL;
        model->pacman[player].tick = 0;

        reset_ghost_mode(model);
    }

    for (i = 0; i < 3; i++)
    {
        switch (model->ghosts[i].mode)
        {
        case SCATTER:
            switch (model->ghosts[i].direction)
            {
            case UP:
                model->ghosts[i].y -= GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_scatter_sprite, CHARACTER_SIZE);
                break;
            case DOWN:
                model->ghosts[i].y += GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_scatter_sprite, CHARACTER_SIZE);
                break;
            case LEFT:
                model->ghosts[i].x -= GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_scatter_sprite, CHARACTER_SIZE);
                break;
            case RIGHT:
                model->ghosts[i].x += GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_scatter_sprite, CHARACTER_SIZE);
                break;
            }
            break;
        case CHASE:
        case ROAM:
            switch (model->ghosts[i].direction)
            {
            case UP:
                model->ghosts[i].y -= GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                break;
            case DOWN:
                model->ghosts[i].y += GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                break;
            case LEFT:
                model->ghosts[i].x -= GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                break;
            case RIGHT:
                model->ghosts[i].x += GHOST_MOVE_SPEED;
                plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                break;
            }
            break;
        }
    }
}

/*

Inputs: Model *model, UINT16 *base, int player
Purpose: Renders the snacks on the screen.

*/
void render_snacks(Model *model, UINT16 *base, int player)
{
    int i;
    int j;

    for (i = 0; i < MAZE_ARRAY_HEIGHT; i++)
    {
        for (j = 0; j < MAZE_ARRAY_WIDTH; j++)
        {
            if (snack_array[i][j] == 0)
            {
                if (model->snacks[MAZE_ARRAY_WIDTH * i + j].eaten == FALSE)
                {
                    if (!(model->snacks[MAZE_ARRAY_WIDTH * i + j].x == get_pacman_x(&model->pacman[player]) && model->snacks[MAZE_ARRAY_WIDTH * i + j].y == get_pacman_y(&model->pacman[player])) &&
                        !(model->snacks[MAZE_ARRAY_WIDTH * i + j].x == get_ghost_x(&model->ghosts[0]) && model->snacks[MAZE_ARRAY_WIDTH * i + j].y == get_ghost_y(&model->ghosts[0])) &&
                        !(model->snacks[MAZE_ARRAY_WIDTH * i + j].x == get_ghost_x(&model->ghosts[1]) && model->snacks[MAZE_ARRAY_WIDTH * i + j].y == get_ghost_y(&model->ghosts[1])) &&
                        !(model->snacks[MAZE_ARRAY_WIDTH * i + j].x == get_ghost_x(&model->ghosts[2]) && model->snacks[MAZE_ARRAY_WIDTH * i + j].y == get_ghost_y(&model->ghosts[2])))
                    {
                        plot_bitmap_16(base, model->snacks[MAZE_ARRAY_WIDTH * i + j].x + ALIGN_ITEM_X, (model->snacks[MAZE_ARRAY_WIDTH * i + j].y + ALIGN_ITEM_Y) * 16, snack_sprite, CHARACTER_SIZE);
                    }
                }
            }
        }
    }
}

/*

Inputs: Model *model, UINT16 *base, int player
Purpose: Renders the cherries on the screen.

*/
void render_cherries(Model *model, UINT16 *base, int player)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if (model->cherries[i].eaten == FALSE &&
            !(model->cherries[i].x == get_pacman_x(&model->pacman[player]) && model->cherries[i].y == get_pacman_y(&model->pacman[player])) &&
            !(model->cherries[i].x == get_ghost_x(&model->ghosts[0]) && model->cherries[i].y == get_ghost_y(&model->ghosts[0])) &&
            !(model->cherries[i].x == get_ghost_x(&model->ghosts[1]) && model->cherries[i].y == get_ghost_y(&model->ghosts[1])) &&
            !(model->cherries[i].x == get_ghost_x(&model->ghosts[2]) && model->cherries[i].y == get_ghost_y(&model->ghosts[2])))
        {
            plot_bitmap_16(base, model->cherries[i].x + ALIGN_ITEM_X, (model->cherries[i].y + ALIGN_ITEM_Y) * 16, cherry_sprite, CHARACTER_SIZE);
        }
    }
}


/*

Inputs: Model *model, UINT16 *base, int player
Purpose: Renders the glow balls on the screen.

*/
void render_glow_balls(Model *model, UINT16 *base, int player)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if (model->glow_balls[i].eaten == FALSE)
        {
            if (!(model->glow_balls[i].x == get_pacman_x(&model->pacman[player]) && model->glow_balls[i].y == get_pacman_y(&model->pacman[player]) &&
                  !(model->glow_balls[i].x == get_ghost_x(&model->ghosts[0]) && model->glow_balls[i].y == get_ghost_y(&model->ghosts[0])) &&
                  !(model->glow_balls[i].x == get_ghost_x(&model->ghosts[1]) && model->glow_balls[i].y == get_ghost_y(&model->ghosts[1])) &&
                  !(model->glow_balls[i].x == get_ghost_x(&model->ghosts[2]) && model->glow_balls[i].y == get_ghost_y(&model->ghosts[2]))))
            {
                plot_bitmap_16(base, model->glow_balls[i].x + ALIGN_ITEM_X, (model->glow_balls[i].y + ALIGN_ITEM_Y) * 16, glow_ball_sprite, CHARACTER_SIZE);
            }
        }
    }
}


/*

Inputs: Model *model, UINT16 *base, int player
Purpose: Renders the score box on the screen.

*/
void render_scorebox(Model *model, UINT8 *base, int player_count)
{
    print_string_8(base, model->scorebox[0].x, model->scorebox[0].y, "P1 SCORE");
    print_num(base, model->scorebox[0].x_score, model->scorebox[0].y_score, model->pacman[0].score);
    if (player_count == 2)
    {
        print_string_8(base, model->scorebox[1].x, model->scorebox[1].y, "P2 SCORE");
        print_num(base, model->scorebox[1].x_score, model->scorebox[1].y_score, model->pacman[1].score);
    }
}


/*

Inputs: UINT16 *base, int player_count
Purpose: Clears the live box on the screen.

*/

void clear_livebox(UINT16 *base, int player_count)
{
    int i;
    for (i = 0; i < 3; i++)
    {
        clear_region_16(base, 6 + i, 53);
    }
    if (player_count == 2)
    {
        for (i = 0; i < 3; i++)
        {
            clear_region_16(base, 31 + i, 53);
        }
    }
}

/*

Inputs: Model *model, UINT16 *base, int player_count
Purpose: Renders the live box on the screen.

*/
void render_livebox(Model *model, UINT16 *base, int player_count)
{

    int i;

    clear_livebox(base, player_count);

    for (i = 0; i < model->pacman[0].lives; i++)
    {
        plot_bitmap_16(base, model->livebox[0].x + i, model->livebox[0].y, pacman_right, CHARACTER_SIZE);
    }
    if (player_count == 2)
    {
        for (i = 0; i < model->pacman[1].lives; i++)
        {
            plot_bitmap_16(base, model->livebox[1].x + i, model->livebox[1].y, pacman_right, CHARACTER_SIZE);
        }
    }
}
/*

Inputs: UINT32 *base
Purpose: Renders the splash screen on the screen. (Main Menu)

*/
void render_splash_screen(UINT32 *base)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)splash_screen);

    print_string_8((UINT8 *)base, 288, 220, "1 PLAYER");
    print_string_8((UINT8 *)base, 288, 250, "2 PLAYERS");
    print_string_8((UINT8 *)base, 212, 325, "MADE BY CLENCY & GLENN - 2023");
}

/* change map files to screen files. */

/*
void render_game_over_screen(UINT32 *base)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)game_over_screen);
}

void render_win_screen(UINT32 *base)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)win_screen);
}
*/

/*
void clear_snack(snack *snack, UINT16 *base)
{
    clear_region_16(base, snack->x + ALIGN_ITEM_X, snack->y + ALIGN_ITEM_Y);
}
*/

/*

Inputs: cherry *cherry, UINT16 *base
Purpose: Clears the cherry on the screen.

*/
void clear_cherry(cherry *cherry, UINT16 *base)
{
    clear_region_16(base, cherry->x + ALIGN_ITEM_X, cherry->y + ALIGN_ITEM_Y);
}

/*

INPUTS: glow_ball *glow_ball, UINT16 *base
PURPOSE: Clears the glow ball on the screen.

*/
void clear_glow_ball(glow_ball *glow_ball, UINT16 *base)
{
    clear_region_16(base, glow_ball->x + ALIGN_ITEM_X, glow_ball->y + ALIGN_ITEM_X);
}

/*

Inputs: ghost *ghost, UINT16 *base
Purpose: Clears the ghost on the screen.

*/
void clear_ghost(ghost *ghost, UINT16 *base)
{
    clear_region_16(base, ghost->x + ALIGN_ITEM_X, ghost->y + ALIGN_ITEM_Y);
}
/*

Inputs: pacman *pacman, UINT16 *base
Purpose: Clears the pacman on the screen.

*/
void clear_pacman(pacman *pacman, UINT16 *base)
{
    clear_region_16(base, pacman->x + ALIGN_ITEM_X, pacman->y + ALIGN_ITEM_Y);
}
