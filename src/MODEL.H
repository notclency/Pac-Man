#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"
#include "SPRITES.H"
/* #include "MAZE_ARRAY.H" */
#include "RASTER.H"

typedef struct {
    unsigned int x, y;
    int delta_x, delta_y;   /* displcement per clock tick / speed */
    direction direction, last_direction;
    int lives;
    int score;
    int is_dead;
    int snacks_eaten;
    mode mode;
} pacman;

typedef struct {
    unsigned int x, y;
    int delta_x, delta_y;   /* displcement per clock tick / speed */
    direction direction;
    int in_ghost_house;
    int is_dead;
    mode mode;
} ghost;

typedef struct 
{
    int map_start_x;
    int map_start_y;

    int ghost_house[25][11]; /* reference to screen not map */
    int pacman_spwan[21][18]; /* reference to screen not map */

    int snacks;
    int cherries;
    int glow_balls;
    
    int pacman_location[21][18]; /* reference to screen not map */

    int cherry_spwan[4][2]; /* dont know the position of the cherry spwan yet */
    int glowing_ball_spwan[4][2]; /* dont know the position of the glowing ball spwan yet */
    int snack_spwan[280][2]; /* dont know the position of the snack spwan yet */
} map;


typedef struct {
    unsigned int x;
    unsigned int y;
    int eaten;
} snack;

typedef struct {
    unsigned int x;
    unsigned int y;
    int eaten;
} cherry;

typedef struct {
    unsigned int x;
    unsigned int y;
    int eaten;
} glow_ball;

typedef struct {
    unsigned int x;
    unsigned int y;
    char player_name[5];    /* 4 characters + null terminator */

    unsigned int x_score;
    unsigned int y_score;
    int score;
} scorebox;

typedef struct {
    unsigned int x;
    unsigned int y;
    int lives;
} livebox;

typedef struct {
    map map;
    pacman pacman[2];
    int game_over;
    int game_won;
    ghost ghosts[3];
    snack snacks[510];
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
void move_pacman(pacman pacman[], direction direction, int player);

int get_pacman_x(pacman pacman[], int player);
int get_pacman_y(pacman pacman[], int player);

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
        scorebox: pointer to scorebox struct
        score: score to update scorebox with

    description:
        updates scorebox with the specified score

    return:
        void
*/
void update_scorebox(Model *model, int player);

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

void update_livebox(Model *model, int player);

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

int is_wall(int x, int y);

void reset_pacman_mode(pacman pacman[], int player);
void reset_ghost_mode(ghost *ghost);

/* pacman collisions */
int pacman_collides_with_snack(Model *model, int player);
int pacman_collides_with_cherry(Model *model, int player);
int pacman_collides_with_glow_ball(Model *model, int player);
int pacman_collides_with_ghost(Model *model, int player);
int pacman_collides_with_ghost_house(pacman pacman[], direction direction, int player);
int pacman_collides_with_wall(pacman pacman[], direction direction, int player);     /* wall object or background? */

/* ghost collisions */
int ghost_collides_with_snack(ghost *ghost, snack *snacks);
int ghost_collides_with_cherry(ghost *ghost, cherry *cherries);
int ghost_collides_with_glow_ball(ghost *ghost, glow_ball *glow_ball);
int ghost_collides_with_ghost(ghost *ghost_1, ghost *ghost_2);
int ghost_collides_with_wall(ghost *ghost, direction direction);     /* wall object or background? */

/* !!! EVENTS !!! */
/* destroy snack, cherry and glowing ball */
void destroy_snack(snack *snack);
void destroy_cherry(cherry *cherry);
void destroy_glow_ball(glow_ball *glow_ball);

/* Initializes/Close gmae session */
void ini_game_session(Model *model, int player_count, int player);
void close_game_session(Model *model);
void won_game_session(Model *model);


/* ghost AI */
void ghost_roam(ghost *ghost);
void ghost_chase(ghost *ghost, pacman *pacman);
void ghost_scatter(ghost *ghost, pacman *pacman);

void reset_ghost(ghost *ghost);

#endif