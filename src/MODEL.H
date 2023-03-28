#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "SPRITES.H"
#include "RASTER.H"

/*
    pacman struct
    x: x position of pacman
    y: y position of pacman
    direction: direction pacman is facing
    lives: number of lives pacman has
    score: score pacman has
    is_dead: is pacman dead
    snacks_eaten: number of snacks pacman has eaten
    frame: frame of pacman animation
    tick: tick of pacman animation
    mode: mode of pacman
*/
typedef struct
{
    float x, y;
    float prev_x, prev_y;
    direction direction;
    int lives;
    int score;
    int is_dead;
    int snacks_eaten;
    int frame;
    int tick;
    mode mode;
} pacman;

/*
    ghost struct
    x: x position of ghost
    y: y position of ghost
    direction: direction ghost is facing
    in_ghost_house: is ghost in ghost house
    is_dead: is ghost dead
    mode: mode of ghost
*/
typedef struct
{
    int x, y;
    direction direction;
    int in_ghost_house;
    int is_dead;
    mode mode;
} ghost;

/*
    snack struct
    x: x position of snack
    y: y position of snack
    eaten: has snack been eaten
*/
typedef struct
{
    int x, y;
    int eaten;
} snack;

/*
    cherry struct
    x: x position of cherry
    y: y position of cherry
    eaten: has cherry been eaten
*/
typedef struct
{
    int x, y;
    int eaten;
} cherry;

/*
    glow_ball struct
    x: x position of glow_ball
    y: y position of glow_ball
    eaten: has glow_ball been eaten
*/
typedef struct
{
    int x, y;
    int eaten;
} glow_ball;

/*
    scorebox struct
    x: x position of scorebox
    y: y position of scorebox
    player_name: name of player
    x_score: score of player 1
    y_score: score of player 2
    score: score of current player
*/
typedef struct
{
    int x, y;
    char player_name[5]; /* 4 characters + null terminator */

    int x_score;
    int y_score;
} scorebox;

/*
    livebox struct
    x: x position of livebox
    y: y position of livebox
    lives: number of lives
*/
typedef struct
{
    int x;
    int y;
} livebox;

/*
    model struct
    pacman: array of pacman structs
    game_over: is game over
    game_won: is game won
    ghosts: array of ghost structs
    snacks: array of snack structs
    cherries: array of cherry structs
    glow_balls: array of glow_ball structs
    scorebox: array of scorebox structs
    livebox: array of livebox structs
*/
typedef struct
{
    pacman pacman[2];
    int game_over;
    int game_won;
    ghost ghosts[3];
    snack snacks[510]; /* actually 197 snacks */
    cherry cherries[4];
    glow_ball glow_balls[4];
    scorebox scorebox[2];
    livebox livebox[2];
} Model;

/* move and initialize objects on screen */

/*
    paramters:
        pacman: pointer to pacman struct
        direction: direction to move pacman

    description:
        moves pacman in the specified direction

    return:
        void
*/
void move_pacman(Model *model, direction direction, int player);

/* Initialize objects on screen */

/*
    paramters:
        ghost: pointer to ghost struct
        pacman: pointer to pacman struct

    description:
        moves ghost depending on its mode

    return:
        void
*/
void move_ghost(ghost *ghost, pacman *pacman);

/* initialize objects on screen */
/*
    paramters:
        snacks: pointer to array of snacks

    description:
        initializes the snacks on screen at their positions

    return:
        void
*/
void ini_snacks(Model *model);

/*
    paramters:
        cherries: pointer to array of cherries

    description:
        initializes the cherries on screen at their positions

    return:
        void
*/
void ini_cherries(cherry cherries[]);

/*
    paramters:
        glowing_balls: pointer to array of glowing_balls

    description:
        initializes the glowing_balls on screen at their positions

    return:
        void
*/
void ini_glow_balls(Model *model);

/*
    paramters:
        scorebox: pointer to scorebox struct
        x: x position of scorebox
        y: y position of scorebox
        score: score to initialize scorebox with

    description:
        initializes the scorebox at the specified position with the specified score

    return:
        void
*/
void ini_scorebox(Model *model, int player_count);

/*
    paramters:
        livebox: pointer to livebox struct
        x: x position of livebox
        y: y position of livebox
        lives: lives to initialize livebox with

    description:
        initializes the livebox at the specified position with the specified lives

    return:
        void
*/
void ini_livebox(Model *model, int player_count);

/*
    paramters:
        pacman: pointer to pacman struct
        x: x position of pacman
        y: y position of pacman
        lives: lives to initialize pacman with

    description:
        initializes pacman at the specified position with the specified lives

    return:
        void
*/
void ini_pacman(Model *model, int player_count, int player);

/*
    paramters:
        ghosts: pointer to array of ghosts

    description:
        initializes the ghosts on screen at their positions

    return:
        void
*/
void ini_ghosts(Model *model);

/* wall checks */
/*
    paramters:
        x: x position of object
        y: y position of object

    description:
        checks if object is on a wall

    return:
        1 if object is on a wall
        0 if object is not on a wall
*/
int is_wall(int x, int y);

/*
    paramters:
        x: x position of object
        y: y position of object

    description:
        checks if object is on a wall for pacman
        (ghost house is a wall for pacman)

    return:
        1 if object is on a wall
        0 if object is not on a wall
*/
int is_wall_pacman(int x, int y);

/*
    paramters:
        model: pointer to model struct
    
    description:
        resets every ghost mode to ROAM

    return:
        void
*/
void reset_ghost_mode(Model *model);

/* pacman collisions */
/*
    paramters:
        model: pointer to model struct
        player: player number

    description:
        checks if pacman has collided with a snack, cherry, glowing ball or ghost

    return:
        void
*/
void pacman_collides_with_snack(Model *model, int player);
void pacman_collides_with_cherry(Model *model, int player);
void pacman_collides_with_glow_ball(Model *model, int player);
void pacman_collides_with_ghost(Model *model, int player);

/*
    paramters:
        model: pointer to model struct
        player: player number

    description:
        resets pacman to its starting position

    return:
        void
*/
void reset_pacman(Model *model, int player);

/*
    paramters:
        model: pointer to model struct
        player: player number

    description:
        checks if pacman has died for good (no lives left)

    return:
        void
*/
void is_dead(Model *model, int player);

/* Initializes/Close gmae session */
void ini_game_session(Model *model, int player_count, int player);
void reset_game_session(Model *model, int player);

void close_game_session(Model *model);
void won_game_session(Model *model);

/* ghost AI */
void ghost_roam(ghost *ghost);
void ghost_chase(ghost *ghost, pacman *pacman);
void ghost_scatter(ghost *ghost, pacman *pacman);

/*
    paramters:
        ghost: pointer to ghost struct

    description:
        resets ghost to its starting position in ghost house

    return:
        void
*/
void reset_ghost(ghost *ghost);

/*
    paramters:
        pacman: pointer to pacman struct

    description:
        gets the x and y position of pacman

    return:
        x and y position of pacman
*/
int get_pacman_x(pacman *pacman);
int get_pacman_y(pacman *pacman);

/*
    paramters:
        ghost: pointer to ghost struct

    description:
        gets the x and y position of ghost

    return:
        x and y position of ghost
*/
int get_ghost_x(ghost *ghost);
int get_ghost_y(ghost *ghost);

#endif