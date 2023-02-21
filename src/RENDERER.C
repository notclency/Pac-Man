#include "RENDERER.H"

void render(Model *model, char *base, int player_count, int player)
{
    clear_screen((char *)base);
    plot_screen((UINT32 *)base, (UINT32 *)map_display);
    render_glow_balls(model, (UINT16 *)base, player);

    render_pacman(model->pacman, (UINT16 *)base, player);
    render_snacks(model, (UINT16 *)base, player);
    render_ghosts(model->ghosts, (UINT16 *)base);
    render_scorebox(model, (UINT8 *)base, player_count);
    render_livebox(model, (UINT16 *)base, player_count);
    /*

    render_cherries(model->cherries, (UINT16 *)base);
    render_glow_balls(model->glow_balls, (UINT16 *)base);

    */
}

void render_pacman(pacman *pacman, UINT16 *base, int player)
{
    /* render according ot direction */
    if (pacman->is_dead == FALSE)
    {
        plot_bitmap_16(base, pacman[player].x + ALIGN_ITEM_X, (pacman[player].y + ALIGN_ITEM_Y) * 16, pacman_left, CHARACTER_SIZE);
    }
}

void render_ghosts(ghost ghosts[], UINT16 *base)
{
    int i;
    /* render according to state & direction */
    for (i = 0; i < 3; i++)
    {
        if (ghosts[i].is_dead == FALSE)
        {
            plot_bitmap_16(base, ghosts[i].x + ALIGN_ITEM_X, (ghosts[i].y + ALIGN_ITEM_Y) * 16, ghost_sprite, CHARACTER_SIZE);
        }
    }
}

void render_snacks(Model *model, UINT16 *base, int player)
{
    int i;

    for (i = 0; i < 196; i++)
    {
        if (model->snacks[i].eaten == FALSE)
        {
            plot_bitmap_16(base, model->snacks[i].x + ALIGN_ITEM_X, (model->snacks[i].y + ALIGN_ITEM_Y) * 16, snack_sprite, CHARACTER_SIZE);
        } else {
            plot_bitmap_16(base, model->snacks[i].x + ALIGN_ITEM_X, (model->snacks[i].y + ALIGN_ITEM_Y) * 16, emp, CHARACTER_SIZE);
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
        if (model->glow_balls[i].eaten == FALSE && pacman_collides_with_glow_ball(model, player) == FALSE)
        {
            plot_bitmap_16(base, model->glow_balls[i].x + ALIGN_ITEM_X, (model->glow_balls[i].y + ALIGN_ITEM_Y) * 16, glow_ball_sprite, CHARACTER_SIZE);
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
        clear_region_16(base, 6 + i, 80);
    }
    if (player_count == 2)
    {
        for (i = 0; i < 3; i++)
        {
            clear_region_16(base, 31 + i, 80);
        }
    }
}

void render_livebox(Model *model, UINT16 *base, int player_count)
{

    int i;
    int j = 0;

    for (i = 0; i < model->pacman[0].lives; i++)
    {
        plot_bitmap_16(base, model->livebox[0].x + j, model->livebox[0].y, pacman_left, CHARACTER_SIZE);
        j += 1;
    }
    if (player_count == 2)
    {
        j = 0;
        for (i = 0; i < model->pacman[1].lives; i++)
        {
            plot_bitmap_16(base, model->livebox[1].x + j, model->livebox[1].y, pacman_left, CHARACTER_SIZE);
            j += 1;
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
