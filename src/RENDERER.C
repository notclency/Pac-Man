#include "RENDERER.H"

void render(Model *model, char *base, int player_count, int player)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)map_display);
    render_glow_balls(model, (UINT16 *)base, player);

    render_pacman(model, (UINT16 *)base, player);
    render_ghosts(model, (UINT16 *)base, player);

    render_snacks(model, (UINT16 *)base, player);
    render_scorebox(model, (UINT8 *)base, player_count);
    render_livebox(model, (UINT16 *)base, player_count);
    /*

    render_cherries(model->cherries, (UINT16 *)base);
    render_glow_balls(model->glow_balls, (UINT16 *)base);

    */
}

void render_pacman(Model *model, UINT16 *base, int player)
{
    int i;
    int custom;
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);

    /* new function that renders to nothing. WHen ghost eat pacman and pacmna not in SUPER mode */
    /* shifts pacman into black */


    /* render according ot direction */
    switch (model->pacman[player].direction)
    {
    case UP:
        if ((in_bounds(pacman_x, pacman_y - 1) == TRUE) && !is_wall(pacman_x, pacman_y - 1))
        {

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y - i, pacman_up, CHARACTER_SIZE);
            }
            model->pacman[player].y -= 2;

            /* second frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y - i, pacman_up, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y -= 4;

            /* third frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y - i, pacman_up_open, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y -= 4;

            /* forth frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y - i, pacman_up, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y -= 4;

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y - i, pacman_up, CHARACTER_SIZE);
            }
            model->pacman[player].y -= 2;
        }
        break;

    case DOWN:
        if ((in_bounds(pacman_x, pacman_y + 1) == TRUE) && !is_wall(pacman_x, pacman_y + 1))
        {

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y + i, pacman_down, CHARACTER_SIZE);
            }
            model->pacman[player].y += 2;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y + i, pacman_down, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y += 4;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y + i, pacman_down_open, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y += 4;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y + i, pacman_down, CHARACTER_SIZE);
                }
            }
            model->pacman[player].y += 4;

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y + i, pacman_down, CHARACTER_SIZE);
            }
            model->pacman[player].y += 2;
        }
        break;

    case LEFT:
        if ((in_bounds(pacman_x - 1, pacman_y) == TRUE) && !is_wall(pacman_x - 1, pacman_y))
        {

            /* first frame */
            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x - i, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
            }
            model->pacman[player].x -= 2;

            /* second frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x - i, model->pacman[player].y, pacman_left_open, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x -= 4;

            /* third frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x - i, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x -= 4;

            /* forth frame */
            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x - i, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x -= 4;

            /* fifth frame */
            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x - i, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
            }
            model->pacman[player].x -= 2;
        }
        break;

    case RIGHT:
        if ((in_bounds(pacman_x + 1, pacman_y) == TRUE) && !is_wall(pacman_x + 1, pacman_y))
        {

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x + i, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
            }
            model->pacman[player].x += 2;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x + i, model->pacman[player].y, pacman_right_open, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x += 4;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x + i, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x += 4;

            for (i = 0; i < 4; i++)
            {
                for (custom = 0; custom < 16; custom++)
                {
                    plot_bitmap_16_2(base, model->pacman[player].x + i, model->pacman[player].y, pacman_closed, CHARACTER_SIZE);
                }
            }
            model->pacman[player].x += 4;

            for (i = 0; i < 2; i++)
            {
                plot_bitmap_16_2(base, model->pacman[player].x + i, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
            }
            model->pacman[player].x += 2;
        }
        break;

    case NONE:
        switch (model->pacman[player].last_direction)
        {
        case UP:
            plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y, pacman_up, CHARACTER_SIZE);
            break;

        case DOWN:
            plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y, pacman_down, CHARACTER_SIZE);
            break;

        case LEFT:
            plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y, pacman_left, CHARACTER_SIZE);
            break;

        case RIGHT:
            plot_bitmap_16_2(base, model->pacman[player].x, model->pacman[player].y, pacman_right, CHARACTER_SIZE);
            break;
        }
    }
}

void render_ghosts(Model *model, UINT16 *base, int player)
{
    int i;
    int j;
    int custom;

    /* render according to mode & direction */

    for (i = 0; i < 3; i++)
    {
        if (model->ghosts[i].is_dead == FALSE && (pacman_collides_with_ghost(model, player) == FALSE || model->pacman[player].mode != SUPER))
        {
            if (model->ghosts[i].mode == SCATTER)
            {
                switch (model->ghosts[i].direction)
                {
                case UP:
                    for (j = 0; j < 8; j++)
                    {
                        for (custom = 0; custom < 16; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y - j, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].y -= 8;
                    break;

                case DOWN:
                    for (j = 0; j < 8; j++)
                    {
                        for (custom = 0; custom < 16; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y + j, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].y += 8;
                    break;

                case LEFT:
                    for (j = 0; j < 8; j++)
                    {
                        for (custom = 0; custom < 16; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x - j, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].x -= 8;
                    break;

                case RIGHT:
                    for (j = 0; j < 8; j++)
                    {
                        for (custom = 0; custom < 16; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x + j, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].x += 8;
                    break;
                }
            }
            else
            {
                switch (model->ghosts[i].direction)
                {
                case UP:
                    for (j = 0; j < 16; j++)
                    {
                        for (custom = 0; custom < 2; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y - j, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].y -= 16;
                    break;

                case DOWN:
                    for (j = 0; j < 16; j++)
                    {
                        for (custom = 0; custom < 2; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x, model->ghosts[i].y + j, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].y += 16;
                    break;

                case LEFT:
                    for (j = 0; j < 16; j++)
                    {
                        for (custom = 0; custom < 2; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x - j, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].x -= 16;
                    break;

                case RIGHT:
                    for (j = 0; j < 16; j++)
                    {
                        for (custom = 0; custom < 2; custom++)
                        {
                            plot_bitmap_16_2(base, model->ghosts[i].x + j, model->ghosts[i].y, ghost_sprite, CHARACTER_SIZE);
                        }
                    }
                    model->ghosts[i].x += 16;
                    break;
                }
            }
        } else {
            plot_bitmap_16_2(base, get_ghost_x(&model->ghosts[i]), get_ghost_y(&model->ghosts[i]), emp, CHARACTER_SIZE);
        }
    }
}

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

void render_cherries(Model *model, UINT16 *base, int player)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if (model->cherries[i].eaten == FALSE && pacman_collides_with_cherry(model, player) == FALSE)
        {
            plot_bitmap_16(base, model->cherries[i].x + ALIGN_ITEM_X, (model->cherries[i].y + ALIGN_ITEM_Y) * 16, cherry_sprite, CHARACTER_SIZE);
        }
    }
}

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

void render_map(map *map, UINT32 *base)
{
    plot_screen((UINT32 *)base, (UINT32 *)map_display);
}

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

void clear_cherry(cherry *cherry, UINT16 *base)
{
    clear_region_16(base, cherry->x + ALIGN_ITEM_X, cherry->y + ALIGN_ITEM_Y);
}

void clear_glow_ball(glow_ball *glow_ball, UINT16 *base)
{
    clear_region_16(base, glow_ball->x + ALIGN_ITEM_X, glow_ball->y + ALIGN_ITEM_X);
}

void clear_ghost(ghost *ghost, UINT16 *base)
{
    clear_region_16(base, ghost->x + ALIGN_ITEM_X, ghost->y + ALIGN_ITEM_Y);
}

void clear_pacman(pacman *pacman, UINT16 *base)
{
    clear_region_16(base, pacman->x + ALIGN_ITEM_X, pacman->y + ALIGN_ITEM_Y);
}
