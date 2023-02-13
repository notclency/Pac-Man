#ifndef MODEL_H
#define MODEL_H

#include "TYPES.H"

typedef struct {
    unsigned int x, y;
    int delta_x, delta_y;   /* displcement per clock tick / speed */
    int lives;
    int score;
    state state;
    mode mode;
} pacman;

typedef struct {
    unsigned int x, y;
    int delta_x, delta_y;   /* displcement per clock tick / speed */
    state state;
    mode mode;
} ghost;

typedef struct {
    unsigned int x;
    unsigned int y;
    int state;
} snack;

typedef struct {
    unsigned int x;
    unsigned int y;
    int state;
} cherry;

typedef struct {
    unsigned int x;
    unsigned int y;
    int state;
} glowing_ball;

typedef struct {
    unsigned int x;
    unsigned int y;
    int score;
} scorebox;

typedef struct {
    unsigned int x;
    unsigned int y;  
    char player_name[5];    /* 4 characters + null terminator */  
    int lives;
} livebox;

typedef struct Model {
    pacman pacman;
    ghost ghosts[4];
    snack snacks[280];
    cherry cherries[4];
    glowing_ball glowing_balls[4];
    scorebox scorebox_1;
    scorebox scorebox_2;
    livebox livebox_1;
    livebox livebox_2;
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
void move_pacman(pacman *pacman, direction direction);

/*
    paramters:
        ghost: pointer to ghost struct
        direction: direction to move ghost

    description:
        moves ghost in the specified direction

    return:
        void
*/
void move_ghost(ghost *ghost, direction direction);


/*
    paramters:
        scorebox: pointer to scorebox struct
        score: score to update scorebox with

    description:
        updates scorebox with the specified score

    return:
        void
*/
void update_scorebox(scorebox *scorebox, int score);


/*
    paramters:
        livebox: pointer to livebox struct
        lives: lives to update livebox with

    description:
        updates livebox with the specified lives

    return:
        void
*/
void update_livebox(livebox *livebox, int lives);


/* Initialize objects on screen */

/*
    paramters:
        snacks: pointer to array of snacks

    description:
        initializes the snacks on screen at their positions

    return:
        void
*/
void ini_snacks(snack *snacks);

/*
    paramters:
        cherries: pointer to array of cherries

    description:
        initializes the cherries on screen at their positions

    return:
        void
*/
void ini_cherries(cherry *cherries);

/*
    paramters:
        glowing_balls: pointer to array of glowing_balls

    description:
        initializes the glowing_balls on screen at their positions

    return:
        void
*/
void ini_glowing_balls(glowing_ball *glowing_balls);

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
void ini_scorebox(scorebox *scorebox, int x, int y, int score);

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
void ini_livebox(livebox *livebox, int x, int y, int lives);

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
void ini_pacman(pacman *pacman);

/*
    paramters:
        ghosts: pointer to array of ghosts

    description:
        initializes the ghosts on screen at their positions

    return:
        void
*/
void ini_ghosts(ghost *ghosts);


/* pacman collisions */
void pacman_collides_with_snack(pacman *pacman, snack *snacks);
void pacman_collides_with_cherry(pacman *pacman, cherry *cherries);
void pacman_collides_with_glowing_ball(pacman *pacman, glowing_ball *glowing_balls);
void pacman_collides_with_ghost(pacman *pacman, ghost *ghosts);
void pacman_collides_with_wall(pacman *pacman);     /* wall object or background? */


/* ghost collisions */
void ghost_collides_with_snack(ghost *ghost, snack *snacks);
void ghost_collides_with_cherry(ghost *ghost, cherry *cherries);
void ghost_collides_with_glowing_ball(ghost *ghost, glowing_ball *glowing_balls);
void ghost_collides_with_ghost(ghost *ghost);
void ghost_collides_with_wall(ghost *ghost);     /* wall object or background? */

/* !!! EVENTS !!! */
/* destroy snack, cherry and glowing ball */
void destroy_snack(snack *snack);
void destroy_cherry(cherry *cherry);
void destroy_glowing_ball(glowing_ball *glowing_ball);

/* Initializes/Close gmae session */
void ini_game_session(Model *model, int lives);
void close_game_session(Model *model);


/* ghost AI */
void ghost_roam(ghost *ghost);
void ghost_chase(ghost *ghost, pacman *pacman);
void ghost_flee(ghost *ghost, pacman *pacman);

void reset_ghost(ghost *ghost);

#endif