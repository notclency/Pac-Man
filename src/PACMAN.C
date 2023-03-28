/*
	File Name: TST_RAST.C

	Purpose: This file is used to build the bitmaps pixels, and calls
	the functions that will display them on the screen.

	Authors: Glenn and Clency

*/

#include <osbind.h>
#include <stdio.h>
#include "RASTER.H"
#include "FONT.H"
#include "SPLASH.H"
#include "MAP.H"
#include "SPRITES.H"
#include "MODEL.H"
#include "EVENTS.H"
#include "RENDERER.H"
#include "INPUT.H"

void display_splash_screen(char *base);
void process_sync_events(Model *model, char *base_1, char *base_2, int player_count, int player, int *flip);
void process_async_events(Model *model, int player_count);

char buff[32256];

char *get_base(char *second_buffer)
{
	char *base;
	UINT16 difference;
	base = second_buffer;
	difference = (int)base;
	difference %= 0x100;
	difference = 0x100 - difference;
	return base + difference;
}

int GAMEOVER = 0;

int main()
{
	char *base_1 = Physbase();
	char *base_2 = get_base(buff);

	Model model;

	int player = 0;
	int player_count = 2;
	int i;

	int flip = 0;

	int select = 1;
	UINT32 key = 0x00000000;
	UINT32 prev_key = 0x00000000;

	UINT32 timeThen, timeNow, timePassed;

	UINT32 *timer = (UINT32 *)0x462;

	UINT32 old_ssp = Super(0);
	timeNow = *timer;
	Super(old_ssp);

	timePassed = timeNow - timeThen;

	display_splash_screen(base_1);

	while (key != ENTER_KEY)
	{

		if (select)
		{
			print_string_8((UINT8 *)base_1, 272, 220, "=");
			print_string_8((UINT8 *)base_1, 272, 250, " ");
			Setscreen(-1, base_1, -1);
			Vsync();
		}
		else
		{
			print_string_8((UINT8 *)base_1, 272, 220, " ");
			print_string_8((UINT8 *)base_1, 272, 250, "=");
			Setscreen(-1, base_1, -1);
			Vsync();
		}

		key = Cconis();
		key = Cnecin();

		if (key == DOWN_KEY || key == UP_KEY)
		{
			select = !select;
		}

		if (key == ENTER_KEY)
		{
			if (select)
			{
				player_count = 1;
			}
			else
			{
				player_count = 2;
			}
		}

		if (key == ESC_KEY)
		{
			return 0;
		}
	}

	/* GAME */

	ini_game_session(&model, player_count, player);
	render(&model, base_1, player_count, player);

	Setscreen(-1, base_1, -1);
	Vsync();

	while (player < player_count)
	{

		while (!model.game_over && !model.game_won && timeNow > 1 && model.pacman[i].snacks_eaten < 205 && !GAMEOVER)
		{
			process_async_events(&model, player_count);
			process_sync_events(&model, base_1, base_2, player_count, i, &flip);

			timeThen = timeNow;
		}

		player++;
	}

	if (!model.game_over)
	{
		render_game_over_screen((UINT32 *)base_1, player);
		Setscreen(-1, base_1, -1);
		Vsync();

	} else {
		render_win_screen((UINT32 *)base_1, player);
		Setscreen(-1, base_1, -1);
		Vsync();
	}

	return 0;
}

void display_splash_screen(char *base)
{
	/*clear_screen(base);*/

	plot_screen((UINT32 *)base, (UINT32 *)splash_screen);

	print_string_8((UINT8 *)base, 288, 220, "1 PLAYER");
	print_string_8((UINT8 *)base, 288, 250, "2 PLAYERS");
	print_string_8((UINT8 *)base, 280, 280, "ESC QUIT");
	print_string_8((UINT8 *)base, 212, 360, "MADE BY CLENCY & GLENN - 2023");

	Setscreen(-1, base, -1);
	Vsync();
}

void process_async_events(Model *model, int player_count)
{
	UINT32 key;
	UINT32 prev_key = 0x00000000;

	if (Cconis())
	{
		key = Cnecin();

		if (key == ESC_KEY)
		{
			GAMEOVER = 1;

			return;
		}

		if (key != prev_key)
		{
			on_pacman_move(model, key, 0);
			prev_key = key;
		}
	}
	/* fix - buffered input */
}

void process_sync_events(Model *model, char *base_1, char *base_2, int player_count, int player, int *flip)
{
	/* ghost move */
	on_ghost_move(model, player);

	/* ghost/pacman collision check & render */
	pacman_collides_with_ghost(model, player);

	/* edible collison check */
	pacman_collides_with_snack(model, player);
	pacman_collides_with_glow_ball(model, player);
	/* pacman_collides_with_cherry(model, player); */

	if (*flip)
	{
		render(model, base_1, player_count, player);
		Setscreen(-1, base_1, -1);
		Vsync();
	}
	else
	{
		render(model, base_2, player_count, player);
		Setscreen(-1, base_2, -1);
		Vsync();
	}

	(*flip) = !(*flip);
}