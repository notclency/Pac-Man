#ifndef PACMAN_GAME_H
#define PACMAN_GAME_H

#include "TYPES.H"
#include "CONSTS.H"
#include "EVENTS.H"
#include "RASTER.H"
#include "SPRITES.H"
#include "MODEL.H"
#include "RENDERER.H"
#include "ISR.H"
#include "MENU.H"
#include "FONT.H"
#include "SPLASH.H"
#include "MAPS.H"
#include "MUSIC.H"

/*
    parameters:
        model: model struct
        player: number of players

    description:
        processes asyncronous events.
        in respect to the player

    return:
        void
*/
void process_sync_events(Model *model, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        processes syncronous events (ie key presses)
        in respect to the player

    return:
        void
*/
void process_async_events(Model *model, int player);

/*
    parameters:
        model: model struct
        player: player number

    description:
        proccesses all game events

    return:
        void
*/
void game_loop();

/*
    parameters:
        base: base address of screen

    description:
		sets the video base address

    return:
        void
*/
void set_screen(char *base);

/*
    parameters:
        base: base address of screen

    description:
        displays the splash screen

    return:
        void
*/
void display_splash_screen(char *base);

/*
    parameters:
        None

    description:
        starts a single player session

    return:
        void
*/
void start_single_player_session();

#endif