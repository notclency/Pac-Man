/*

---------------------------------------------------------------------------------------------------
File Name: MODEL.C
---------------------------------------------------------------------------------------------------
Purpose: This file is for the all character model, which initialize all the character's model, which 
allows us change or create each character's direction, and other attributes. We can change 
the model of each character by changing the specific character's model.
---------------------------------------------------------------------------------------------------
Functions: move_pacman, move_ghost,ini_snacks,ini_cherry,ini_glow_ball,ini_ghosts,ini_pacman,ini_
scorebox,ini_livebox,is_wall_pacman,is_wall,reset_ghost_mode,pacman_collides_with_snack,pacman_
collides_with_cherry,pacman_collides_with_glow_ball,pacman_collides_with_ghost,reset_pacman,
reset_pacman_mode, is_dead, ghost_roam,ghost_chase,ghost_scattter.,reset_ghost, pop_cherry, collapes_
cherry.
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\MODEL.H"
#include "include\EVENTS.H"

extern int CHERRY_TIMER;
extern int PACMAN_SUPER_TIMER;

/*
    parameters:
        model: pointer to the model
        direction: direction to move pacman
        player: player number

    description:
        moves pacman in the given direction if possible by changing it's direction.
        (ie checks if intended move is in bounds and not a wall)

    return:
        void
*/
void move_pacman(Model *model, direction direction, int player)
{

    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    switch (direction)
    {
    case UP:
        if ((in_bounds(pacman_x, pacman_y - 1) == TRUE) && !is_wall_pacman(pacman_x, pacman_y - 1))
            model->pacman[player].direction = UP;
        break;
    case DOWN:
        if ((in_bounds(pacman_x, pacman_y + 1) == TRUE) && !is_wall_pacman(pacman_x, pacman_y + 1))
            model->pacman[player].direction = DOWN;
        break;
    case LEFT:
        if ((in_bounds(pacman_x - 1, pacman_y) == TRUE) && !is_wall_pacman(pacman_x - 1, pacman_y))
            model->pacman[player].direction = LEFT;
        break;
    case RIGHT:
        if ((in_bounds(pacman_x + 1, pacman_y) == TRUE) && !is_wall_pacman(pacman_x + 1, pacman_y))
            model->pacman[player].direction = RIGHT;
        break;
    }
}

/*

    parameters:
        ghost: pointer to ghost struct
        pacman: pointer to pacman struct

    description:
        moves a single ghost depending on it's mode

    return:
        void

*/
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

/*
    parameters:
        model: pointer to model struct

    description:
        initializes all the snacks in the maze (ie setting their x and y values).
        it uses the snack_array defined in MAPS.H to check wether a snack should be
        placed at a certain position, and then converts the 2d array position to a 1d
        array position so all the snacks can be stored in a 1d array, they maintain their
        2d position though(ie x and y values) and are easily accessed by using the formula
        MAZE_ARRAY_WIDTH * y + x. (where x and y are the 2d position of the snack)
*/
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

/*
    parameters:
        model: pointer to model struct

    description:
        initializes the cherry struct in the model struct

    return:
        void
*/
void ini_cherries(Model *model) /* will define values as constants */
{
    model->cherries[0].x = 23;
    model->cherries[0].y = 6;
    model->cherries[0].eaten = TRUE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        sets the cherry eaten value to false so it renders on the screen

    return:
        void
*/
void pop_cherry(Model *model)
{
    model->cherries[0].eaten = FALSE;
}


/*
    parameters:
        model: pointer to model struct

    description:
        sets the cherry eaten value to true so it doesn't render on the screen

    return:
        void
*/
void collapse_cherry(Model *model)
{
    model->cherries[0].eaten = TRUE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        initializes the glow balls struct in the model struct

    return:
        void
*/
void ini_glow_balls(Model *model) /* will define values as constants */
{
    glow_ball *glow_balls = model->glow_balls;
    int i = 0;

    glow_balls[i].x = 1;
    glow_balls[i].y = 2;
    glow_balls[i].eaten = FALSE;

    i++;
    glow_balls[i].x = 1;
    glow_balls[i].y = 14;
    glow_balls[i].eaten = FALSE;

    i++;
    glow_balls[i].x = 28;
    glow_balls[i].y = 14;
    glow_balls[i].eaten = FALSE;

    i++;
    glow_balls[i].x = 28;
    glow_balls[i].y = 2;
    glow_balls[i].eaten = FALSE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        initializes the scorebox struct in the model structc depending on the number of players
        Where x and y are the position of the scorebox(PLAYER NAME eg PLAYER 1) and
        score_x and score_y are the position of the score(eg 1000)

    return:
        void
*/
void ini_scorebox(Model *model, int player_count)
{
    scorebox *scorebox = model->scorebox;

    scorebox[0].x = 100;
    scorebox[0].y = 20;

    scorebox[0].score_x = 100;
    scorebox[0].score_y = 40;

    if (player_count == 2)
    {
        scorebox[1].x = 500;
        scorebox[1].y = 20;

        scorebox[1].score_x = 500;
        scorebox[1].score_y = 40;
    }
}

/*
    parameters:
        model: pointer to model struct
    
    description:
        initializes the livebox struct in the model struct depending on the number of players
        Where x and y are the position of the livebox(PACMAN BITMAP displaying the number of lives)

    return:
        void
*/
void ini_livebox(Model *model, int player_count)
{
    livebox *livebox = model->livebox;

    livebox[0].x = 6;
    livebox[0].y = 53;

    if (player_count == 2)
    {
        livebox[1].x = 31;
        livebox[1].y = 53;
    }
}

/*
    parameters:
        model: pointer to model struct

    description:
        initializes the pacman struct to the spawn position and sets all it's
        values to default values

    return:
        void
*/
void ini_pacman(Model *model, int player)
{
    pacman *pacman = model->pacman;

    pacman[player].x = PACMAN_SPAWN_X;
    pacman[player].y = PACMAN_SPAWN_Y;
    pacman[player].direction = NONE;
    pacman[player].is_dead = FALSE;
    pacman[player].lives = PACMAN_LIVES;
    pacman[player].score = 0;
    pacman[player].snacks_eaten = 0;
}

/*
    parameters:
        model: pointer to model struct

    description:
        resets the pacman struct to the spawn position and sets all it's
        values to default values. This function is called when pacman dies
        but the game is not over so it preserves the score, lives, snacks eaten
        and map state.

    return:
        void
*/
void reset_pacman(Model *model, int player)
{
    pacman *pacman = model->pacman;

    pacman[player].x = PACMAN_SPAWN_X;
    pacman[player].y = PACMAN_SPAWN_Y;
    pacman[player].direction = NONE;
    pacman[player].is_dead = FALSE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        initializes all the ghosts in the model to the spawn position and sets all it's
        values to default values.

    return:
        void
*/
void ini_ghosts(Model *model)
{
    ghost *ghost = model->ghosts;
    int i = 0;

    for (i = 0; i < 3; i++)
    {
        ghost[i].x = GHOST_SPAWN_X + i;
        ghost[i].y = GHOST_SPAWN_Y;
        ghost[i].direction = NONE;
        ghost[i].mode = ROAM;
        ghost[i].is_dead = FALSE;
    }
}

/*
    parameters:
        ghost: pointer to ghost struct

    description:
        changes the direction of a ghost to an accessible random direction.
        This function loops till an accessible direction is found then returns.

    return:
        void
*/
void ghost_roam(ghost *ghost)
{
    int ghost_x = ghost->x;
    int ghost_y = ghost->y;

    ghost->direction = (direction)(rand() % 4);

    while (1)
    {
        if (ghost->direction == UP && !is_wall(ghost_x, ghost_y - 1))
        {
            ghost->direction = UP;
            return;
        }
        else if (ghost->direction == DOWN && !is_wall(ghost_x, ghost_y + 1))
        {
            ghost->direction = DOWN;
            return;
        }
        else if (ghost->direction == LEFT && !is_wall(ghost_x - 1, ghost_y))
        {
            ghost->direction = LEFT;
            return;
        }
        else if (ghost->direction == RIGHT && !is_wall(ghost_x + 1, ghost_y))
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

/*
    parameters:
        ghost: pointer to ghost struct
        pacman: pointer to pacman struct

    description:
        Depending on which half of the maze the pacman is in, the ghost will
        scout that half of the maze for the pacman. If the pacman is in the
        first half of the maze, the ghost will scout the first half of the maze
        and vice versa.

    return:
        void
*/
void ghost_chase(ghost *ghost, pacman *pacman)
{
    int ghost_x = ghost->x;
    int ghost_y = ghost->y;

    int pacman_x = pacman->x;
    int pacman_y = pacman->y;

    ghost->direction = (direction)(rand() % 4);

    if (ghost_x >= pacman_x) /* scout first half of maze */
    {
        while (1)
        {
            if (ghost->direction == UP && !is_wall(ghost_x, ghost_y - 1))
            {
                ghost->direction = UP;
                return;
            }
            else if (ghost->direction == DOWN && !is_wall(ghost_x, ghost_y + 1))
            {
                ghost->direction = DOWN;
                return;
            }
            else if (ghost->direction == LEFT && !is_wall(ghost_x - 1, ghost_y))
            {
                ghost->direction = LEFT;
                return;
            }
            else
            {
                ghost->direction = (direction)(rand() % 4);
            }
        }
    }
    else if (ghost_x <= pacman_x) /* scout second half of maze */
    {
        while (1)
        {
            if (ghost->direction == UP && !is_wall(ghost_x, ghost_y - 1))
            {
                ghost->direction = UP;
                return;
            }
            else if (ghost->direction == DOWN && !is_wall(ghost_x, ghost_y + 1))
            {
                ghost->direction = DOWN;
                return;
            }
            else if (ghost->direction == RIGHT && !is_wall(ghost_x + 1, ghost_y))
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
}
/*
    parameters:
        ghost: pointer to ghost struct
        pacman: pointer to pacman struct

    description:
        Depending on which half of the maze the pacman is in, the ghost will
        flee to the opposite half of the maze. If the pacman is in the
        first half of the maze, the ghost will flee to the second half of the maze
        and vice versa.

    return:
        void
*/
void ghost_scatter(ghost *ghost, pacman *pacman)
{
    int ghost_x = ghost->x;
    int ghost_y = ghost->y;

    int pacman_x = pacman->x;
    int pacman_y = pacman->y;

    ghost->direction = (direction)(rand() % 4);

    if (ghost_x <= pacman_x) /* flee to first half of maze */
    {
        while (1)
        {
            if (ghost->direction == UP && !is_wall(ghost_x, ghost_y - GHOST_MOVE_SPEED))
            {
                ghost->direction = UP;
                return;
            }
            else if (ghost->direction == DOWN && !is_wall(ghost_x, ghost_y + GHOST_MOVE_SPEED))
            {
                ghost->direction = DOWN;
                return;
            }
            else if (ghost->direction == LEFT && !is_wall(ghost_x - GHOST_MOVE_SPEED, ghost_y))
            {
                ghost->direction = LEFT;
                return;
            }
            else
            {
                ghost->direction = (direction)(rand() % 4);
            }
        }
    }
    else if (ghost_x >= pacman_x) /* flee to second halve of maze */
    {
        while (1)
        {
            if (ghost->direction == UP && !is_wall(ghost_x, ghost_y - GHOST_MOVE_SPEED))
            {
                ghost->direction = UP;
                return;
            }
            else if (ghost->direction == DOWN && !is_wall(ghost_x, ghost_y + GHOST_MOVE_SPEED))
            {
                ghost->direction = DOWN;
                return;
            }
            else if (ghost->direction == RIGHT && !is_wall(ghost_x + GHOST_MOVE_SPEED, ghost_y))
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
}

/*
    parameters:
        model: pointer to model struct
        player: player number

    description:
        Checks if pacman collides with a snack. If so, the appropriate event
        is triggered. To reduce the number of checks, the function only checks
        if the pacman is in the same position as the snack. It uses the
        MAZE_ARRAY_WIDTH, the x and y position of the pacman to find if a
        snack is in the same position as the pacman & is not eaten.

    return:
        void
*/
void pacman_collides_with_snack(Model *model, int player)
{
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    int snack_x = model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].x;
    int snack_y = model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].y;

    if ((pacman_x == snack_x) && (pacman_y == snack_y) && (model->snacks[MAZE_ARRAY_WIDTH * pacman_y + pacman_x].eaten == FALSE))
    {
        on_snack_eat(model, player);
    }
}

/*
    parameters:
        model: pointer to model struct
        player: player number
    
    description:
        Checks if pacman collides with a cherry. If so, the appropriate event
        is triggered.

    return:
        void
*/
void pacman_collides_with_cherry(Model *model, int player)
{
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    if ((pacman_x == model->cherries[0].x) && (pacman_y == model->cherries[0].y) && (model->cherries[0].eaten == FALSE))
    {
        on_cherry_eat(model, player);
    }
}

/*
    parameters:
        model: pointer to model struct
        player: player number

    description:
        Checks if pacman collides with a glow ball. If so, the appropriate event
        is triggered.

    return:
        void
*/
void pacman_collides_with_glow_ball(Model *model, int player)
{
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;
    int i;

    for (i = 0; i < 4; i++)
    {
        if ((pacman_x == model->glow_balls[i].x) && (pacman_y == model->glow_balls[i].y) && (model->glow_balls[i].eaten == FALSE))
        {
            PACMAN_SUPER_TIMER = 0;
            model->glow_balls[i].eaten = TRUE;
            on_glow_ball_eat(model, player);
        }
    }
}

/*
    parameters:
        model: pointer to model struct
        player: player number

    description:
        Checks if pacman collides with a ghost. If so, the appropriate event
        is triggered. To reduce the number of checks, the function only checks
        if the pacman is in the same position as any of the ghosts OR if the
        direction of the pacman is the opposite of the direction of the ghost AND
        the ghost is 1 square away from the pacman.

    return:
        void
*/
void pacman_collides_with_ghost(Model *model, int player)
{
    int i;
    int pacman_x = model->pacman[player].x;
    int pacman_y = model->pacman[player].y;

    int ghost_x;
    int ghost_y;

    for (i = 0; i < 3; i++)
    {
        ghost_x = model->ghosts[i].x;
        ghost_y = model->ghosts[i].y;

        if ((pacman_x == ghost_x) && (pacman_y == ghost_y))
        {
            on_ghost_eat(model, i, player);
        }
        else
        {
            switch (model->pacman[player].direction)
            {
            case UP:
                if ((pacman_x == ghost_x) && (pacman_y - PACMAN_MOVE_SPEED == ghost_y) && (model->ghosts[i].direction == DOWN))
                {
                    on_ghost_eat(model, i, player);
                }
                break;
            case DOWN:
                if ((pacman_x == ghost_x) && (pacman_y + PACMAN_MOVE_SPEED == ghost_y) && (model->ghosts[i].direction == UP))
                {
                    on_ghost_eat(model, i, player);
                }
                break;
            case LEFT:
                if ((pacman_y == ghost_y) && (pacman_x - PACMAN_MOVE_SPEED == ghost_x) && (model->ghosts[i].direction == RIGHT))
                {
                    on_ghost_eat(model, i, player);
                }
                break;
            case RIGHT:
                if ((pacman_y == ghost_y) && (pacman_x + PACMAN_MOVE_SPEED == ghost_x) && (model->ghosts[i].direction == LEFT))
                {
                    on_ghost_eat(model, i, player);
                }
                break;
            }
        }
    }
}

/*
    parameters:
        model: pointer to model struct

    description:
        resets a particular ghost to its spawn position and sets its mode to
        ROAM. This function is used when a ghost is eaten by pacman.

    return:
        void
*/
void reset_ghost(ghost *ghost)
{
    ghost->x = GHOST_SPAWN_X;
    ghost->y = GHOST_SPAWN_Y;
    ghost->direction = UP;
    ghost->mode = ROAM;
    ghost->is_dead = FALSE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        resets all ghosts to their spawn position and sets their mode to
        ROAM. This function is used when a new game round is started.

    return:
        void
*/
void reset_ghost_mode(Model *model)
{
    int i = 0;
    for (i = 0; i < 3; i++)
    {
        model->ghosts[i].mode = ROAM;
    }
}

/*
    parameters:
        model: pointer to model struct

    description:
        initia;izes a game session. This function is used when a new game session
        is started.
*/
void ini_game_session(Model *model, int player_count, int player)
{
    model->game_over = FALSE;
    model->game_won = FALSE;
    ini_glow_balls(model);
    ini_snacks(model);
    ini_ghosts(model);
    ini_cherries(model);
    ini_pacman(model, player);
    ini_scorebox(model, player_count);
    ini_livebox(model, player_count);
}

/*
    parameters:
        model: pointer to model struct

    description:
        resets a game session. This function is used when a game session is
        restarted(ie when pacman dies).

    return:
        void
*/
void reset_game_session(Model *model, int player)
{
    ini_ghosts(model);
    reset_pacman(model, player);
}

/*
    parameters:
        model: pointer to model struct
        player: player number

    description:
        this function is called when pacman dies. It checks if pacman has any
        lives left. If so, the game session is reset. If not, the game session
        is closed.

    return:
        void
*/
void is_dead(Model *model, int player)
{
    if (model->pacman[player].lives > 0)
    {
        reset_game_session(model, player);
        model->cherries[0].eaten = TRUE;
        CHERRY_TIMER = 0;
    }
    else
    {
        model->game_over = TRUE;
    }
}

/*
    parameters:
        model: pointer to model struct
        player: player number

    description:
        this function resets pacman mode to NORMAL. This function is used when
        it's super mode ends.

    return:
        void
*/
void reset_pacman_mode(Model *model, int player)
{
    model->pacman[player].mode = NORMAL;
}

/*
    parameters:
        model: pointer to model struct

    description:
        this function is called when a game session is closed. It 
        sets the game_over flag to true.

    return:
        void
*/
void close_game_session(Model *model)
{
    model->game_over = TRUE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        this function is called when a game session is won. It 
        sets the game_won flag to true.

    return:
        void
*/
void won_game_session(Model *model)
{
    model->game_won = TRUE;
}

/*
    parameters:
        model: pointer to model struct

    description:
        checks if x and y are within the bounds of the maze array.
        (ie not a collision with the walls). Primarily used by the
        ghosts.

    return:
        void
*/
int is_wall(int x, int y)
{
    return (maze_array[y][x] == 1);
}

/*
    parameters:
        model: pointer to model struct

    description:
        checks if x and y are within the bounds of the maze array & not a ghost house.
        Primarily used by pacman.

*/
int is_wall_pacman(int x, int y)
{
    return (maze_array[y][x] == 1 || maze_array[y][x] == -1);
}