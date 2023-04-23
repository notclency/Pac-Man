#ifndef RENDERER_H
#define RENDERER_H

#include "TYPES.H"
#include "RASTER.H"
#include "FONT.H"
#include "SPLASH.H"
#include "GAMEOVER.H"
#include "GAMEWON.H"
#include "MAPS.H"
#include "MAZE.H"
#include "MODEL.H"
#include "SPRITES.H"

/*
    renders the game to the screen
*/
void render(Model *model, char *base, int player_count, int player);

/*
    renders pacman to the screen
*/
void render_pacman(Model *model, UINT16 *base, int player);

/*
    renders ghosts to the the screen
*/
void render_ghosts(Model *model, UINT16 *base);

/*
    renders snacks to the screen
*/
void render_snacks(Model *model, UINT16 *base);

/*
    renders cherries to the screen
*/
void render_cherries(Model *model, UINT16 *base);

/*
    renders glow balls to the screen
*/
void render_glow_balls(Model *model, UINT16 *base);

/*
    render score boxes to the screen
*/
void render_scorebox(Model *model, UINT8 *base, int player_count);

/*
    render live boxes to the screen
*/
void render_livebox(Model *model,UINT16 *base, int player_count);

/*
    render the splash screen
*/
void render_splash_screen(UINT32 *base);

/*
    render the game over screen
*/
void render_game_over_screen(UINT32 *base, Model *model, int player);

/*
    render the game won screen
*/
void render_game_won_screen(UINT32 *base, Model *model, int player);

/*
    save the background of the mouse
*/
void save_mouse_bg(UINT16 *base, int x, int y);

/*
    restore the background of the mouse
*/
void restore_mouse_bg(UINT16 *base, int x, int y);

/*
    render the mouse cursor
*/
void render_mouse(UINT16 *base, int x, int y);

#endif
