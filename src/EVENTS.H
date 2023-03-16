#include "TYPES.H"
#include "MODEL.H"
#include "SPRITES.H"
#include "RASTER.H"

void on_pacman_move(Model *model, UINT32 key, int player);

void on_ghost_move(Model *model, int player);

void on_snack_eat(Model *model, int player);

void on_cherry_eat(Model *model, int player);

void on_glow_ball_eat(Model *model, int player);

void on_ghost_eat(Model *model, int ghost_i, int player);

void on_game_over(Model *model);

void on_game_win(Model *model, int player_count);

void on_game_start(Model *model, int player_count, int player);

void on_game_reset(Model *model);

void on_game_exit(Model *model);

