/*

---------------------------------------------------------------------------------------------------
File Name: MENU.C
---------------------------------------------------------------------------------------------------
Purpose: This file contains anything that is apart of the menu. This includes the menu itself and the
         functions that are called when the menu is running. We take in the user choice from the menu
         using keyboard or mouse input and we process it and set up their choice of 
         gameplay. 

---------------------------------------------------------------------------------------------------
Functions: menu,process_menu_choice,draw_selector,mouse_location,start_game
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\MENU.H"

#define INVALID_MOUSE_CHOICE -1

int choice = PLAYER_1;
int mouse_choice;
int prev_mouse_choice;

int valid_click = FALSE;

/*
    parameters:
        void

    description:
        starts the menu

    return:
        void
*/
void menu()
{
    process_menu_choice();
}

/*
    parameters:
        void

    description:
        processes the menu choice

    return:
        void
*/
void process_menu_choice()
{
    UINT32 input;
    char *base_1 = (char *)get_video_base();
    choice = PLAYER_1;

    ini_mouse((UINT16 *)base_1);
    draw_selector(choice, base_1);

    while (input != ESC_KEY && input != ENTER_KEY)
    {
        update_mouse((UINT16 *)base_1);

        if (key_input()) /* check for input */
        {
            input = read_from_ikbd(); /* read input */

            if (input == DOWN_KEY || input == UP_KEY)
            {
                choice = !choice;
            }

            draw_selector(choice, base_1);
        }
        else if (mouse_input())
        {
            mouse_choice = mouse_location();

            if (mouse_choice != INVALID_MOUSE_CHOICE)
            {
                draw_selector(mouse_choice, base_1);

                if (valid_click && MOUSE_LEFT_CLICK)
                {
                    start_game(mouse_choice);
                    return;
                }
            }
        }

        if (input == ENTER_KEY) /* if enter key is pressed */
        {
            start_game(choice);
        }
        else if (input == ESC_KEY) /* if esc key is pressed */
        {
            return;
        }
    }
}

/*
    parameters:
        choice: menu choice
        base: base address of screen

    description:
        draws the menu selector

    return:
        void
*/
void draw_selector(int choice, char *base)
{
    if (!choice)
    {
        print_string_8((UINT8 *)base, 272, 220, "=");
        print_string_8((UINT8 *)base, 272, 250, " ");
    }
    else
    {
        print_string_8((UINT8 *)base, 272, 220, " ");
        print_string_8((UINT8 *)base, 272, 250, "=");
    }
}

/*
    parameters:
        void

    description:
        gets the mouse location and returns if it's
        on a valid menu choice pr not

    return:
        mouse location
*/
int mouse_location()
{
    int mouse_location = INVALID_MOUSE_CHOICE;

    int valid_x = (MOUSE_X >= 288 && MOUSE_X <= 352);
    int valid_y_1 = (MOUSE_Y >= 212 && MOUSE_Y <= 228);
    int valid_y_2 = (MOUSE_Y >= 244 && MOUSE_Y <= 260);

    if (valid_x && valid_y_1)
    {
        mouse_location = PLAYER_1;
    }
    else if (valid_x && valid_y_2)
    {
        mouse_location = PLAYER_2;
    }

    valid_click = (valid_x && valid_y_1) || (valid_x && valid_y_2);

    return mouse_location;
}

void start_game(int choice)
{
    switch (choice)
    {
    case PLAYER_1:
        start_single_player_session();
        break;
    case PLAYER_2:
        /* two player */
        break;
    }
}
