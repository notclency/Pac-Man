#include "MODEL.H"
#include "EVENTS.H"

void move_pacman(Model *model, direction direction, int player)
{

    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);

    /* check collisions here (ghost collisions) */
    /* pass in model. Change parameters */

    /* pass in x,y of pacman to check collisions with ghost */

    switch (direction)
    {
    case UP:
        if ((in_bounds(pacman_x, pacman_y - 1) == TRUE) && !is_wall(pacman_x, pacman_y - 1))
        {
            model->pacman[player].direction = UP;
        }
        break;
    case DOWN:
        if ((in_bounds(pacman_x, pacman_y + 1) == TRUE) && !is_wall(pacman_x, pacman_y + 1))
        {
            model->pacman[player].direction = DOWN;
        }
        break;
    case LEFT:
        if ((in_bounds(pacman_x - 1, pacman_y) == TRUE) && !is_wall(pacman_x - 1, pacman_y))
        {
            model->pacman[player].direction = LEFT;
        }
        break;
    case RIGHT:
        if ((in_bounds(pacman_x + 1, pacman_y) == TRUE) && !is_wall(pacman_x + 1, pacman_y))
        {
            model->pacman[player].direction = RIGHT;
        }
        break;
    }

    if (pacman_collides_with_ghost(model, player))
    {
        on_ghost_eat(model, player);
    }
}

int check_ghost(Model *model, int x, int y)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        if (x == get_ghost_x(&model->ghosts[i]) && y == get_ghost_y(&model->ghosts[i]))
        {
            return 1;
        }
    }

    return 0;
}

int get_pacman_x(pacman *pacman)
{
    return (pacman->x / 16) - ALIGN_ITEM_X;
}

int get_pacman_y(pacman *pacman)
{
    return (pacman->y / 16) - ALIGN_ITEM_Y;
}

int get_ghost_x(ghost *ghost)
{
    return (ghost->x / 16) - ALIGN_ITEM_X;
}

int get_ghost_y(ghost *ghost)
{
    return (ghost->y / 16) - ALIGN_ITEM_Y;
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

void ini_pacman(Model *model, int player_count, int player)
{
    model->pacman[player].x = (15 + ALIGN_ITEM_X) * 16;
    model->pacman[player].y = (13 + ALIGN_ITEM_Y) * 16;
    model->pacman[player].prev_x = (15 + ALIGN_ITEM_X) * 16;
    model->pacman[player].prev_y = (13 + ALIGN_ITEM_Y) * 16;
    model->pacman[player].direction = NONE;
    model->pacman[player].last_direction = LEFT;
    model->pacman[player].is_dead = FALSE;
    model->pacman[player].lives = 3;
    model->pacman[player].score = 0;

    if (player_count == 2)
    {
        model->pacman[1].x = (15 + ALIGN_ITEM_X) * 16;
        model->pacman[1].y = (13 + ALIGN_ITEM_Y) * 16;
        model->pacman[1].prev_x = (15 + ALIGN_ITEM_X) * 16;
        model->pacman[1].prev_y = (13 + ALIGN_ITEM_Y) * 16;
        model->pacman[1].direction = NONE;
        model->pacman[1].last_direction = LEFT;
        model->pacman[1].is_dead = FALSE;
        model->pacman[1].lives = 3;
        model->pacman[1].score = 0;
    }
}

void reset_pacman(Model *model, int player)
{
    model->pacman[player].x = (15 + ALIGN_ITEM_X) * 16;
    model->pacman[player].y = (13 + ALIGN_ITEM_Y) * 16;
    model->pacman[player].direction = NONE;
    model->pacman[player].last_direction = LEFT;
    model->pacman[player].is_dead = FALSE;
}

void ini_ghosts(Model *model)
{
    ghost *ghost = model->ghosts;

    int i = 0;
    for (i = 0; i < 3; i++)
    {
        ghost[i].x = (19 + i + ALIGN_ITEM_X) * 16;
        ghost[i].y = (6 + ALIGN_ITEM_Y) * 16;
        ghost[i].direction = NONE;
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
        if (ghost->direction == UP && !is_wall(get_ghost_x(ghost), get_ghost_y(ghost) - 1))
        {
            ghost->direction = UP;
            return;
        }
        else if (ghost->direction == DOWN && !is_wall(get_ghost_x(ghost), get_ghost_y(ghost) + 1))
        {
            ghost->direction = DOWN;
            return;
        }
        else if (ghost->direction == LEFT && !is_wall(get_ghost_x(ghost) - 1, get_ghost_y(ghost)))
        {
            ghost->direction = LEFT;
            return;
        }
        else if (ghost->direction == RIGHT && !is_wall(get_ghost_x(ghost) + 1, get_ghost_y(ghost)))
        {
            ghost->direction = RIGHT;
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
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);

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
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);
    int i;

    for (i = 0; i < 4; i++)
    {
        if ((pacman_x == model->glow_balls[i].x) && (pacman_y == model->glow_balls[i].y) && (model->glow_balls[i].eaten == FALSE))
        {
            model->glow_balls[i].eaten = TRUE;
            return 1;
        }
    }

    return 0;
}

int pacman_collides_with_ghost(Model *model, int player)
{
    int pacman_x = get_pacman_x(&model->pacman[player]);
    int pacman_y = get_pacman_y(&model->pacman[player]);
    int i;

    for (i = 0; i < 3; i++)
    {
        if (((pacman_x == get_ghost_x(&model->ghosts[i])) && (pacman_y == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE)) ||
            pacman_x + 1 == get_ghost_x(&model->ghosts[i]) && (pacman_y == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == RIGHT && model->ghosts[i].direction == LEFT ||
            pacman_x - 1 == get_ghost_x(&model->ghosts[i]) && (pacman_y == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == LEFT && model->ghosts[i].direction == RIGHT ||
            pacman_x == get_ghost_x(&model->ghosts[i]) && (pacman_y + 1 == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == DOWN && model->ghosts[i].direction == UP ||
            pacman_x == get_ghost_x(&model->ghosts[i]) && (pacman_y - 1 == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == UP && model->ghosts[i].direction == DOWN)
        {
            return 1;
        }

        /*
         ||
            pacman_x + 1 == get_ghost_x(&model->ghosts[i]) && (pacman_y == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == RIGHT && model->ghosts[i].direction == LEFT ||
            pacman_x - 1 == get_ghost_x(&model->ghosts[i]) && (pacman_y == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == LEFT && model->ghosts[i].direction == RIGHT ||
            pacman_x == get_ghost_x(&model->ghosts[i]) && (pacman_y + 1 == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == DOWN && model->ghosts[i].direction == UP ||
            pacman_x == get_ghost_x(&model->ghosts[i]) && (pacman_y - 1 == get_ghost_y(&model->ghosts[i])) && (model->ghosts[i].is_dead == FALSE) && model->pacman[player].direction == UP && model->ghosts[i].direction == DOWN
        */
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
    ghost->x = (19 + ALIGN_ITEM_X) * 16;
    ghost->y = (6 + ALIGN_ITEM_Y) * 16;
    ghost->direction = UP;
    ghost->mode = ROAM;
    ghost->is_dead = FALSE;
    ghost->in_ghost_house = TRUE;
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