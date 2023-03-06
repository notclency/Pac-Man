#include "MODEL.H"

void move_pacman(pacman pacman[], direction direction, int player)
{

    switch (direction)
    {
    case UP:
        if ((in_bounds(get_pacman_x(pacman, player), get_pacman_y(pacman, player) - 1) == TRUE) && !is_wall(get_pacman_x(pacman, player), get_pacman_y(pacman, player) - 1))
            pacman[player].direction = UP;
        else
            pacman[player].direction = NONE;
        break;
    case DOWN:
        if ((in_bounds(get_pacman_x(pacman, player), get_pacman_y(pacman, player) + 1) == TRUE) && !is_wall(get_pacman_x(pacman, player), get_pacman_y(pacman, player) + 1))
            pacman[player].direction = DOWN;
        else
            pacman[player].direction = NONE;
        break;
    case LEFT:
        if ((in_bounds(get_pacman_x(pacman, player) - 1, get_pacman_y(pacman, player)) == TRUE) && !is_wall(get_pacman_x(pacman, player) - 1, get_pacman_y(pacman, player)))
            pacman[player].direction = LEFT;
        else
            pacman[player].direction = NONE;
        break;
    case RIGHT:
        if ((in_bounds(get_pacman_x(pacman, player) + 1, get_pacman_y(pacman, player)) == TRUE) && !is_wall(get_pacman_x(pacman, player) + 1, get_pacman_y(pacman, player)))
            pacman[player].direction = RIGHT;
        else
            pacman[player].direction = NONE;
        break;
    }
}

int get_pacman_x(pacman pacman[], int player)
{
    return (pacman[player].x / 16) - ALIGN_ITEM_X;
}

int get_pacman_y(pacman pacman[], int player)
{
    return (pacman[player].y / 16) - ALIGN_ITEM_Y;
}

void move_ghost(ghost *ghost, pacman *pacman)
{
    switch (ghost->mode)
    {
    case ROAM:
        ghost_roam(ghost);
        break;
    case CHASE:
        ghost_chase(ghost, pacman);
        break;
    case SCATTER:
        ghost_scatter(ghost, pacman);
        break;
    }
}

void ini_snacks(Model *model)
{
    int i;
    int j;

    for (i = 0; i < MAZE_ARRAY_HEIGHT; i++)
    {
        for (j = 0; j < MAZE_ARRAY_WIDTH; j++)
        {
            if (snack_array[i][j] == 0)
            {
                model->snacks[MAZE_ARRAY_WIDTH * i + j].x = j;
                model->snacks[MAZE_ARRAY_WIDTH * i + j].y = i;
                model->snacks[MAZE_ARRAY_WIDTH * i + j].eaten = FALSE;
            }
        }
    }
}

void ini_cherries(cherry cherry[]) /* will define values as constants */
{
    int i = 0;
    cherry[i].x = 13;
    cherry[i].y = 21;
    i++;

    cherry[i].x = 15;
    cherry[i].y = 11;
    i++;

    cherry[i].x = 22;
    cherry[i].y = 6;
    i++;

    cherry[i].x = 26;
    cherry[i].y = 13;
}

void ini_glow_balls(Model *model) /* will define values as constants */
{
    int i = 0;

    model->glow_balls[i].x = 1;
    model->glow_balls[i].y = 2;
    model->glow_balls[i].eaten = FALSE;

    i++;
    model->glow_balls[i].x = 1;
    model->glow_balls[i].y = 14;
    model->glow_balls[i].eaten = FALSE;

    i++;
    model->glow_balls[i].x = 28;
    model->glow_balls[i].y = 14;
    model->glow_balls[i].eaten = FALSE;

    i++;
    model->glow_balls[i].x = 28;
    model->glow_balls[i].y = 2;
    model->glow_balls[i].eaten = FALSE;
}

void ini_scorebox(Model *model, int player_count)
{
    scorebox *scorebox = model->scorebox;

    scorebox[0].x = 100;
    scorebox[0].y = 20;

    scorebox[0].x_score = 100;
    scorebox[0].y_score = 40;
    scorebox[0].score = 00000;

    if (player_count == 2)
    {
        scorebox[1].x = 500;
        scorebox[1].y = 20;

        scorebox[1].x_score = 500;
        scorebox[1].y_score = 40;
        scorebox[1].score = 00000;
    }
}

void update_scorebox(Model *model, int player)
{
    model->scorebox[player].score = model->pacman[player].score;
}

void ini_livebox(Model *model, int player_count)
{
    model->livebox[0].x = 6;
    model->livebox[0].y = 53;

    if (player_count == 2)
    {
        model->livebox[1].x = 31;
        model->livebox[1].y = 53;
    }
}

void update_livebox(Model *model, int player)
{
    model->livebox[player].lives = model->pacman[player].lives;
}

void ini_pacman(Model *model, int player_count, int player)
{
    model->pacman[player].x = (15 + ALIGN_ITEM_X) * 16;
    model->pacman[player].y = (13 + ALIGN_ITEM_Y) * 16;
    model->pacman[player].direction = NONE;
    model->pacman[player].is_dead = FALSE;
    model->pacman[player].lives = 3;
    model->pacman[player].score = 0;

    if (player_count == 2)
    {
        model->pacman[1].x = (15 + ALIGN_ITEM_X) * 16;
        model->pacman[1].y = (13 + ALIGN_ITEM_Y) * 16;
        model->pacman[1].direction = NONE;
        model->pacman[1].is_dead = FALSE;
        model->pacman[1].lives = 3;
        model->pacman[1].score = 0;
    }
}

void ini_ghosts(Model *model)
{
    ghost *ghost = model->ghosts;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        ghost[i].x = 19 + i;
        ghost[i].y = 6;
        ghost[i].direction = UP;
        ghost[i].mode = ROAM;
        ghost[i].is_dead = FALSE;
        ghost[i].in_ghost_house = TRUE;
    }
}

void destroy_snack(snack *snack)
{
    snack->eaten = TRUE;
}

void destroy_cherry(cherry *cherry)
{
    cherry->eaten = TRUE;
}

void destroy_glow_ball(glow_ball *glow_ball)
{
    glow_ball->eaten = TRUE;
}

void ghost_roam(ghost *ghost)
{
    ghost->direction = (direction)(rand() % 4);

    while (1)
    {
        if (ghost->direction == UP && !is_wall(ghost->x, ghost->y - 1))
        {
            ghost->y--;
            return;
        }
        else if (ghost->direction == DOWN && !is_wall(ghost->x, ghost->y + 1))
        {
            ghost->y++;
            return;
        }
        else if (ghost->direction == LEFT && !is_wall(ghost->x - 1, ghost->y))
        {
            ghost->x--;
            return;
        }
        else if (ghost->direction == RIGHT && !is_wall(ghost->x + 1, ghost->y))
        {
            ghost->x++;
            return;
        }
        else
        {
            ghost->direction = (direction)(rand() % 4);
        }
    }
}

void ghost_chase(ghost *ghost, pacman *pacman)
{
    if (ghost->x > pacman->x)
        ghost->direction = LEFT;
    else if (ghost->x < pacman->x)
        ghost->direction = RIGHT;
    else if (ghost->y > pacman->y)
        ghost->direction = UP;
    else if (ghost->y < pacman->y)
        ghost->direction = DOWN;
}

void ghost_scatter(ghost *ghost, pacman *pacman)
{
    if (ghost->x > pacman->x)
        ghost->direction = RIGHT;
    else if (ghost->x < pacman->x)
        ghost->direction = LEFT;
    else if (ghost->y > pacman->y)
        ghost->direction = DOWN;
    else if (ghost->y < pacman->y)
        ghost->direction = UP;
}

int pacman_collides_with_snack(Model *model, int player)
{
    int pacman_x = (model->pacman[player].x / 16) - ALIGN_ITEM_X;
    int pacman_y = (model->pacman[player].y / 16) - ALIGN_ITEM_Y;

    int snack_x = model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].x;
    int snack_y = model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].y;

    if ((pacman_x == snack_x) && (pacman_y == snack_y) && (model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten == FALSE))
    {
        /* model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten = TRUE; */
        return 1;
    }

    return 0;
}

int pacman_collides_with_cherry(Model *model, int player)
{
    int i;
    int pacman_x = (model->pacman[player].x / 16) - ALIGN_ITEM_X;
    int pacman_y = (model->pacman[player].y / 16) - ALIGN_ITEM_Y;

    for (i = 0; i < 4; i++)
    {
        if ((pacman_x == model->cherries[i].x) && (pacman_y == model->cherries[i].y) && (model->cherries[i].eaten == FALSE))
        {
            model->cherries[i].eaten = TRUE;
            return 1;
        }
    }

    return 0;
}

int pacman_collides_with_glow_ball(Model *model, int player)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if ((model->pacman[player].x == model->glow_balls[i].x) && (model->pacman[player].y == model->glow_balls[i].y) && (model->glow_balls[i].eaten == FALSE))
        {
            model->glow_balls[i].eaten = TRUE;
            return 1;
        }
    }

    return 0;
}

int pacman_collides_with_ghost(Model *model, int player)
{
    int i;

    for (i = 0; i < 3; i++)
    {
        if ((model->pacman[player].x == model->ghosts[i].x) && (model->pacman[player].y == model->ghosts[i].y) && (model->ghosts[i].is_dead == FALSE))
        {
            return 1;
        }
    }

    return 0;
}

int pacman_collides_with_ghost_house(pacman pacman[], direction direction, int player)
{
    if (direction == DOWN)
    {
        return ((pacman[player].x == 25) && (pacman[player].y + PACMAN_MOVE_SPEED == 11) ||
                (pacman[player].x == 26) && (pacman[player].y + PACMAN_MOVE_SPEED == 11) ||
                (pacman[player].x == 27) && (pacman[player].y + PACMAN_MOVE_SPEED == 11) ||
                (pacman[player].x == 25) && (pacman[player].y + PACMAN_MOVE_SPEED == 10) ||
                (pacman[player].x == 26) && (pacman[player].y + PACMAN_MOVE_SPEED == 10) ||
                (pacman[player].x == 27) && (pacman[player].y + PACMAN_MOVE_SPEED == 10));
    }
}

int pacman_collides_with_wall(pacman pacman[], direction direction, int player)
{
    if (direction == LEFT)
    {
        return (maze_array[pacman[player].y][pacman[player].x - PACMAN_MOVE_SPEED] == 1);
    }
    else if (direction == RIGHT)
    {
        return (maze_array[pacman[player].y][pacman[player].x + PACMAN_MOVE_SPEED] == 1);
    }
    else if (direction == UP)
    {
        return (maze_array[pacman[player].y - PACMAN_MOVE_SPEED][pacman[player].x] == 1);
    }
    else if (direction == DOWN)
    {
        return (maze_array[pacman[player].y + PACMAN_MOVE_SPEED][pacman[player].x] == 1);
    }
}

int ghost_collides_with_snack(ghost *ghost, snack *snack)
{
    if ((ghost->x == snack->x) && (ghost->y == snack->y) && (snack->eaten == TRUE))
    {
        destroy_snack(snack);
        return 1;
    }

    return 0;
}

int ghost_collides_with_cherry(ghost *ghost, cherry *cherry)
{
    return ((ghost->x == cherry->x) && (ghost->y == cherry->y) && (cherry->eaten == FALSE));
}

int ghost_collides_with_glow_ball(ghost *ghost, glow_ball *glow_ball)
{
    return ((ghost->x == glow_ball->x) && (ghost->y == glow_ball->y) && (glow_ball->eaten == FALSE));
}

int ghost_collides_with_ghost(ghost *ghost_1, ghost *ghost_2)
{
    return ((ghost_1->x == ghost_2->x) && (ghost_1->y == ghost_2->y));
}

int ghost_collides_with_wall(ghost *ghost, direction direction)
{
    if (direction == LEFT)
        return (maze_array[ghost->y][ghost->x - GHOST_MOVE_SPEED] == 1);
    else if (direction == RIGHT)
        return (maze_array[ghost->y][ghost->x + GHOST_MOVE_SPEED] == 1);
    else if (direction == UP)
        return (maze_array[ghost->y - GHOST_MOVE_SPEED][ghost->x] == 1);
    else if (direction == DOWN)
        return (maze_array[ghost->y + GHOST_MOVE_SPEED][ghost->x] == 1);
}

void reset_ghost(ghost *ghost)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        ghost->x = 25;
        ghost->y = 11;
        ghost->direction = LEFT;
        ghost->mode = NORMAL;
        ghost->is_dead = FALSE;
        ghost->in_ghost_house = TRUE;
    }
}

void reset_pacman_mode(pacman pacman[], int player)
{
    pacman[player].mode = NORMAL;
}

void reset_ghost_mode(ghost *ghost)
{
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        ghost->mode = NORMAL;
    }
}

void ini_game_session(Model *model, int player_count, int player)
{
    model->game_over = FALSE;
    ini_cherries(model->cherries);
    ini_glow_balls(model);
    ini_snacks(model);
    ini_ghosts(model);
    ini_pacman(model, player_count, player);
    ini_scorebox(model, player_count);
    ini_livebox(model, player_count);
}

void close_game_session(Model *model)
{
    model->game_over = TRUE;
}

void won_game_session(Model *model)
{
    model->game_won = TRUE;
}

int is_wall(int x, int y)
{
    return (maze_array[y][x] == 1);
}