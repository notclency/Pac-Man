#ifndef RENDERER_H
#define RENDERER_H

#include "TYPES.H"
#include "RASTER.H"
#include "font.h"
#include "splash.h"
#include "map.h"
#include "model.h"
#include "sprites.h"
#include "events.h"
/* #include "MAZE_ARRAY.H" */

void render(Model *model, char *base, int player_count, int player);

void render_pacman(Model *model, UINT16 *base, int player);

void render_ghosts(Model *model, UINT16 *base, int player);

void render_snacks(Model *model, UINT16 *base, int player);

void render_cherries(Model *model, UINT16 *base, int player);

void render_glow_balls(Model *model, UINT16 *base, int player);

void render_scorebox(Model *model, UINT8 *base, int player_count);

void clear_livebox(UINT16 *base, int player_count);
void render_livebox(Model *model,UINT16 *base, int player_count);

void render_splash_screen(UINT32 *base);

void render_game_over_screen(UINT32 *base);

void render_win_screen(UINT32 *base);

/* void clear_snack(snack *snack, UINT16 *base); */

void clear_cherry(cherry *cherry, UINT16 *base);

void clear_glow_ball(glow_ball *glow_ball, UINT16 *base);

void clear_ghost(ghost *ghost, UINT16 *base);

void clear_pacman(pacman *pacman, UINT16 *base);

#endif