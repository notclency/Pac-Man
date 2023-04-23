#include "include\RENDERER.H"

/*
    parameters:
        model: game model
        base: base address of the screen
        player_count: number of players
        player: current player

    description:
        renders the everything on the screen ie the game model

    return:
        void

*/
void render(Model *model, char *base, int player_count, int player)
{
    /* render the map */
    plot_screen((UINT32 *)base, (UINT32 *)maze_display);

    render_scorebox(model, (UINT8 *)base, player_count);
    render_livebox(model, (UINT16 *)base, player_count);

    render_glow_balls(model, (UINT16 *)base);
    render_snacks(model, (UINT16 *)base);
    render_cherries(model, (UINT16 *)base);

    render_ghosts(model, (UINT16 *)base);
    render_pacman(model, (UINT16 *)base, player);
}

/*
    parameters:
        model: game model
        base: base address of the screen
        player: current player

    description:
        renders the pacman on the screen according to the direction and frame

    return:
        void
*/
void render_pacman(Model *model, UINT16 *base, int player)
{
    pacman *pacman = &model->pacman[player];

    int pacman_x = pacman->x;
    int pacman_y = pacman->y;

    int i;

    /* new function that renders to nothing. WHen ghost eat pacman and pacmna not in SUPER mode */
    /* shifts pacman into black */

    /* render according ot direction */
    if (pacman->is_dead == FALSE)
    {
        switch (pacman->direction)
        {
        case UP:
            if (!is_wall_pacman(pacman_x, pacman_y - 1))
            {
                pacman->y -= PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_up, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_up_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_up, CHARACTER_SIZE);
            }
            break;
        case DOWN:
            if (!is_wall_pacman(pacman_x, pacman_y + 1))
            {
                pacman->y += PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_down, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_down_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_down, CHARACTER_SIZE);
            }
            break;
        case LEFT:
            if (!is_wall_pacman(pacman_x - 1, pacman_y))
            {
                pacman->x -= PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_left, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_left_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_left, CHARACTER_SIZE);
            }
            break;
        case RIGHT:
            if (!is_wall_pacman(pacman_x + 1, pacman_y))
            {
                pacman->x += PACMAN_MOVE_SPEED;
                switch (model->pacman[player].frame)
                {
                case 0:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_right, CHARACTER_SIZE);
                    break;
                case 1:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_right_open, CHARACTER_SIZE);
                    break;
                case 2:
                    plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_closed, CHARACTER_SIZE);
                    break;
                }
            }
            else
            {
                plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_right, CHARACTER_SIZE);
            }
            break;

        case NONE:
            plot_bitmap_16(base, pacman->x + ALIGN_ITEM_X, (pacman->y + ALIGN_ITEM_Y) * 16, pacman_left, CHARACTER_SIZE);
            break;
        }

        pacman->frame++;
        if (pacman->frame > 2)
        {
            pacman->frame = 0;
        }
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the ghosts to the screen with their mode 
        deciding what bitmap to use

    returns:
        void

*/
void render_ghosts(Model *model, UINT16 *base)
{
    ghost *ghosts = model->ghosts;

    int i;

    for (i = 0; i < 3; i++)
    {
        switch (ghosts[i].direction)
        {
        case UP:
            ghosts[i].y -= GHOST_MOVE_SPEED;
            break;
        case DOWN:
            ghosts[i].y += GHOST_MOVE_SPEED;
            break;
        case LEFT:
            ghosts[i].x -= GHOST_MOVE_SPEED;
            break;
        case RIGHT:
            ghosts[i].x += GHOST_MOVE_SPEED;
            break;
        }

        switch (ghosts[i].mode)
        {
        case SCATTER:
            plot_bitmap_16(base, ghosts[i].x + ALIGN_ITEM_X, (ghosts[i].y + ALIGN_ITEM_Y) * 16, ghost_scatter_sprite, CHARACTER_SIZE);
            break;
        case CHASE:
        case ROAM:

            plot_bitmap_16(base, ghosts[i].x + ALIGN_ITEM_X, (ghosts[i].y + ALIGN_ITEM_Y) * 16, ghost_sprite, CHARACTER_SIZE);
            break;
        }
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the snacks to the screen

    returns:
        void
*/
void render_snacks(Model *model, UINT16 *base)
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
                    plot_bitmap_16(base, model->snacks[MAZE_ARRAY_WIDTH * i + j].x + ALIGN_ITEM_X, (model->snacks[MAZE_ARRAY_WIDTH * i + j].y + ALIGN_ITEM_Y) * 16, snack_sprite, CHARACTER_SIZE);
                }
            }
        }
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the cherries to the screen

    returns:
        void
*/
void render_cherries(Model *model, UINT16 *base)
{
    int i;

    for (i = 0; i < 1; i++)
    {
        if (model->cherries[i].eaten == FALSE)
        {
            plot_bitmap_16(base, model->cherries[i].x + ALIGN_ITEM_X, (model->cherries[i].y + ALIGN_ITEM_Y) * 16, cherry_sprite, CHARACTER_SIZE);
        }
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the glow balls to the screen

    returns:
        void
*/
void render_glow_balls(Model *model, UINT16 *base)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if (model->glow_balls[i].eaten == FALSE)
        {
            plot_bitmap_16(base, model->glow_balls[i].x + ALIGN_ITEM_X, (model->glow_balls[i].y + ALIGN_ITEM_Y) * 16, glow_ball_sprite, CHARACTER_SIZE);
        }
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the score box to the screen (player name and score),
        with the player count deciding if it should render the second player's
        score box

    returns:
        void
*/
void render_scorebox(Model *model, UINT8 *base, int player_count)
{
    pacman *pacman = model->pacman;
    scorebox *scorebox = model->scorebox;

    print_string_8(base, scorebox[0].x, scorebox[0].y, "P1 SCORE");
    print_num(base, scorebox[0].score_x, scorebox[0].score_y, pacman[0].score);
    if (player_count == 2)
    {
        print_string_8(base, scorebox[1].x, scorebox[1].y, "P2 SCORE");
        print_num(base, scorebox[1].score_x, scorebox[1].score_y, pacman[1].score);
    }
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the live box to the screen (player name and lives),
        with the player count deciding if it should render the second player's
        live box

    returns:
        void
*/
void render_livebox(Model *model, UINT16 *base, int player_count)
{

    int i;

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
    parameters:
        model - the model to render
        base - the base address of the screen

    description:
        renders the game's staring splash screen

    returns:
        void
*/
void render_splash_screen(UINT32 *base)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)splash_screen);

    print_string_8((UINT8 *)base, 288, 220, "1 PLAYER");
    print_string_8((UINT8 *)base, 288, 250, "2 PLAYERS");
    print_string_8((UINT8 *)base, 272, 280, "ESC QUIT");
    print_string_8((UINT8 *)base, 208, 325, "MADE BY CLENCY & GLENN - 2023");
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen
        player - the player to render the game over screen for

    description:
        renders the game's game over screen with the player's score

    returns:
        void
*/
void render_game_over_screen(UINT32 *base, Model *model, int player)
{
    plot_screen((UINT32 *)base, (UINT32 *)GAME_OVER);
    print_string_8((UINT8 *)base, 272, 240, "SCORE: ");
    print_num((UINT8 *)base, 328, 240, model->pacman[player].score);
}

/*
    parameters:
        model - the model to render
        base - the base address of the screen
        player - the player to render the game won screen for

    description:
        renders the game's game won screen with the player's score

    returns:
        void
*/
void render_game_won_screen(UINT32 *base, Model *model, int player)
{
    plot_screen((UINT32 *)base, (UINT32 *)GAME_WON);
    print_string_8((UINT8 *)base, 272, 248, "SCORE: ");
    print_num((UINT8 *)base, 328, 248, model->pacman[player].score);
}

/*
    parameters:
        base - the base address of the screen
        x - the x coordinate of curosr background
        y - the y coordinate of curosr background

    description:
        saves the background of the cursor to the mouse_bg_1 and mouse_bg_2
        arrays

    returns:
        void
*/
void save_mouse_bg(UINT16 *base, int x, int y)
{
    int i, j;

    for (i = 0, j = 0; i < MOUSE_SIZE; i++)
    {
        mouse_bg_1[j++] = *(base + (y + i) * 40 + (x >> 4));
        mouse_bg_2[j++] = *(base + (y + i) * 40 + (x >> 4) + 1);
    }
}

/*
    parameters:
        base - the base address of the screen
        x - the x coordinate of curosr background
        y - the y coordinate of curosr background

    description:
        restores the background of the cursor from the mouse_bg_1 and mouse_bg_2
        arrays

    returns:
        void
*/
void restore_mouse_bg(UINT16 *base, int x, int y)
{
    int i, j;

    for (i = 0, j = 0; i < MOUSE_SIZE; i++)
    {
        *(base + (y + i) * 40 + (x >> 4)) = mouse_bg_1[j++];
        *(base + (y + i) * 40 + (x >> 4) + 1) = mouse_bg_2[j++];
    }
}

/*
    parameters:
        base - the base address of the screen
        x - the x coordinate of curosr
        y - the y coordinate of curosr

    description:
        renders the mouse pointer to the screen

    returns:
        void
*/
void render_mouse(UINT16 *base, int x, int y)
{
    plot_bitmap_16_2(base, x, y, mouse_ptr, MOUSE_SIZE);
}
