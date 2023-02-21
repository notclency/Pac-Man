#include "MODEL.H"

void move_pacman(pacman pacman[], direction direction, int player)
{

    switch (direction)
    {
    case UP:
        if ((in_bounds(pacman[player].x, pacman[player].y - PACMAN_MOVE_SPEED) == TRUE) && (maze_array[pacman[player].y - PACMAN_MOVE_SPEED][pacman[player].x] != 1))
            pacman->y -= PACMAN_MOVE_SPEED;
        break;
    case DOWN:
        if ((in_bounds(pacman[player].x, pacman[player].y + PACMAN_MOVE_SPEED) == TRUE) && (maze_array[pacman[player].y + PACMAN_MOVE_SPEED][pacman[player].x] != 1))
            pacman->y += PACMAN_MOVE_SPEED;
        break;
    case LEFT:
        if ((in_bounds(pacman[player].x - PACMAN_MOVE_SPEED, pacman[player].y) == TRUE) && (maze_array[pacman[player].y][pacman[player].x - PACMAN_MOVE_SPEED] != 1))
            pacman->x -= PACMAN_MOVE_SPEED;
        break;
    case RIGHT:
        if ((in_bounds(pacman[player].x + PACMAN_MOVE_SPEED, pacman[player].y) == TRUE) && (maze_array[pacman[player].y][pacman[player].x + PACMAN_MOVE_SPEED] != 1))
            pacman->x += PACMAN_MOVE_SPEED;
        break;
    }
}

void move_ghost(ghost *ghost, pacman pacman[], int player)
{
    switch (ghost->mode)
    {
    case ROAM:
        ghost_roam(ghost);
        break;
    case CHASE:
        ghost_chase(ghost, &pacman[player]);
        break;
    case SCATTER:
        ghost_scatter(ghost, &pacman[player]);
        break;
    }
}

void ini_snacks(Model *model)
{
    int i;
    int j;
    int count = 0;

    for (i = 0; i < MAZE_ARRAY_HEIGHT; i++)
    {
        for (j = 0; j < MAZE_ARRAY_WIDTH; j++)
        {
            if (snack_array[i][j] == 0)
            {
                model->snacks[count].x = j;
                model->snacks[count].y = i;
                model->snacks[count].eaten = FALSE;
                count++;
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
    model->pacman[player].x = 15;
    model->pacman[player].y = 13;
    model->pacman[player].direction = LEFT;
    model->pacman[player].is_dead = FALSE;
    model->pacman[player].lives = 3;
    model->pacman[player].score = 0;

    if (player_count == 2)
    {
        model->pacman[1].x = 15;
        model->pacman[1].y = 13;
        model->pacman[1].direction = LEFT;
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
    direction ghost_directon = ghost->direction;

    if (ghost_directon == LEFT)
    {
        if ((in_bounds(ghost->x - GHOST_MOVE_SPEED, ghost->y) == TRUE) && (maze_array[ghost->y][ghost->x - GHOST_MOVE_SPEED] != 1))
            ghost->x -= GHOST_MOVE_SPEED;
        else
            ghost->direction = (direction)(rand() % 4);
        return;
    }
    else if (ghost_directon == RIGHT)
    {
        if ((in_bounds(ghost->x + GHOST_MOVE_SPEED, ghost->y) == TRUE) && (maze_array[ghost->y][ghost->x + GHOST_MOVE_SPEED] != 1))
            ghost->x += GHOST_MOVE_SPEED;
        else
            ghost->direction = (direction)(rand() % 4);
        return;
        /* ghost->direction = direction(rand() % 4); */
    }
    else if (ghost_directon == UP)
    {
        if ((in_bounds(ghost->x, ghost->y - GHOST_MOVE_SPEED) == TRUE) && (maze_array[ghost->y - GHOST_MOVE_SPEED][ghost->x] != 1))
            ghost->y -= GHOST_MOVE_SPEED;
        else
            ghost->direction = (direction)(rand() % 4);

        return;
        /* ghost->direction = direction(rand() % 4); */
    }
    else if (ghost_directon == DOWN)
    {
        if ((in_bounds(ghost->x, ghost->y + GHOST_MOVE_SPEED) == TRUE) && (maze_array[ghost->y + GHOST_MOVE_SPEED][ghost->x] != 1))
            ghost->y += GHOST_MOVE_SPEED;
        else
            ghost->direction = (direction)(rand() % 4);
        return;
        /* ghost->direction = direction(rand() % 4); */
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
    int i;

    for (i = 0; i < 197; i++)
    {
        if ((model->pacman[player].x == model->snacks[i].x) && (model->pacman[player].y == model->snacks[i].y))
        {
            model->snacks[i].eaten = TRUE;
            return 1;
        }
    }

    return 0;
}

int pacman_collides_with_cherry(Model *model, int player)
{
    int i;

    for (i = 0; i < 4; i++)
    {
        if ((model->pacman[player].x == model->cherries[i].x) && (model->pacman[player].y == model->cherries[i].y) && (model->cherries[i].eaten == FALSE))
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
