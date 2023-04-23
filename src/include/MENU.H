#ifndef PACMAN_MENU_H
#define PACMAN_MENU_H

#include "TYPES.H"
#include "CONSTS.H"
#include "EVENTS.H"
#include "RASTER.H"
#include "SPRITES.H"
#include "GAME.H"

extern int valid_click;

/*
    parameters:
        void

    description:
        starts the menu

    return:
        void
*/
void menu();

/*
    parameters:
        void

    description:
        processes the menu choice

    return:
        void
*/
void process_menu_choice();

/*
    parameters:
        choice: menu choice
        base: base address of screen

    description:
        draws the menu selector

    return:
        void
*/
void draw_selector(int choice, char *base);

/*
    parameters:
        choice: menu choice

    description:
        starts the game

    return:
        void
*/
void start_game(int choice);

/*
    parameters:
        void

    description:
        gets the mouse location and returns if it's
        on a valid menu choice pr not

    return:
        mouse location
*/
int mouse_location();

#endif
