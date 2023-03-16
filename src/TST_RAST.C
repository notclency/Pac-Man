/*
	File Name: TST_RAST.C

	Purpose: This file is used to build the bitmaps pixels, and calls
	the functions that will display them on the screen.

	Authors: Glenn and Clency

*/

/* display_splash_screen(base); */

/*
clear_screen(base);
plot_screen((UINT32 *)base, (UINT32 *)map_display);
plot_bitmap_16((UINT16 *)base, 21, 288, (UINT16 *)pacman_left, 16);
plot_bitmap_16((UINT16 *)base, 20, 288, (UINT16 *)snack_sprite, 16);
plot_bitmap_16((UINT16 *)base, 25, 176, (UINT16 *)ghost_sprite, 16);
print_string_8((UINT8 *)base, 100, 20, "SCORE");
print_num((UINT8 *)base, 100, 40, 000000);
print_string_8((UINT8 *)base, 500, 20, "SCORE");
print_num((UINT8 *)base, 500, 40, 000000);

plot_bitmap_16((UINT16 *)base, 6 + (0 * 16), 55, pacman_left, CHARACTER_SIZE);
plot_bitmap_16((UINT16 *)base, 7 + (0 * 16), 55, pacman_left, CHARACTER_SIZE);

plot_bitmap_16((UINT16 *)base, 31 + (0 * 16), 55, pacman_left, CHARACTER_SIZE);
plot_bitmap_16((UINT16 *)base, 32 + (0 * 16), 55, pacman_left, CHARACTER_SIZE);

plot_bitmap_16((UINT16 *)base, 34, 112, (UINT16 *)glow_ball_sprite, 16);
plot_bitmap_16((UINT16 *)base, 7, 112, (UINT16 *)snack_sprite, 16);
plot_bitmap_16((UINT16 *)base, 7, 128, (UINT16 *)snack_sprite, 16);
plot_bitmap_16((UINT16 *)base, 8, 128, (UINT16 *)snack_sprite, 16);
plot_bitmap_16((UINT16 *)base, 9, 128, (UINT16 *)snack_sprite, 16);
*/

/*
clear_screen(base);
plot_bitmap_16_2((UINT16 *)base, 1, 0, (UINT16 *)pacman_left, 16);
*/

/*
		plot_screen((UINT32 *)base, (UINT32 *)map_display);
ini_game_session(&model, player_count, 0);
render_pacman(&model, (UINT16 *)base, 0);
render_scorebox(&model, (UINT8 *)base, 0);
render_snacks(&model, (UINT16 *)base, 0);
render_ghosts(&model, (UINT16 *)base, 0);
render_glow_balls(&model, (UINT16 *)base, 0);
render_livebox(&model, (UINT16 *)base, 0);

model.pacman[0].mode = SUPER;
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
void process_sync_events(Model *model, char *base, int player_count, int player);
void process_async_events(Model *model, int player_count);

int GAMEOVER = 0;

int main()
{
	char *base = Physbase();
	Model model;
	int player_count = 2;
	int i;

	int select = 1;
	UINT32 key = 0x00000000;
	UINT32 prev_key = 0x00000000;

	UINT32 timeThen, timeNow, timePassed;

	UINT32 *timer = (UINT32 *)0x462;
	UINT32 timeNow;
	UINT32 old_ssp = Super(0);
	timeNow = *timer;
	Super(old_ssp);

	timePassed = timeNow - timeThen;

	display_splash_screen(base);

	while (key != ENTER_KEY)
	{

		if (select)
		{
			print_string_8((UINT8 *)base, 272, 220, "=");
			print_string_8((UINT8 *)base, 272, 250, " ");
		}
		else
		{
			print_string_8((UINT8 *)base, 272, 220, " ");
			print_string_8((UINT8 *)base, 272, 250, "=");
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

	ini_game_session(&model, player_count, 0);
	render(&model, base, player_count, 0);

	/* GAME */
	while (!GAMEOVER && timePassed > 0)
	{
		process_async_events(&model, player_count);
		process_sync_events(&model, base, player_count, 0);

		timeThen = timeNow;
	}

	/*
	move_pacman(model.pacman, LEFT, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	*/

	/*
	move_pacman(model.pacman, UP, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);

	move_pacman(model.pacman, RIGHT, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);

	move_pacman(model.pacman, RIGHT, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);

	move_pacman(model.pacman, DOWN, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	render_pacman(&model, (UINT16 *)base, 0);
	*/

	/*
	clear_screen(base);
	plot_bitmap_16((UINT16 *)base, 0, 0, (UINT16 *)pacman_left, 16);
	plot_bitmap_16_2((UINT16 *)base, 2, 16, (UINT16 *)pacman_left, 16);
	plot_bitmap_16_2((UINT16 *)base, 3, 32, (UINT16 *)pacman_left, 16);
	plot_bitmap_16_2((UINT16 *)base, 4, 48, (UINT16 *)pacman_left, 16);
	*/

	/* plot_bitmap_16_2((UINT16 *)base, 0, 0, (UINT16 *)pacman_left, 16); */

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

void process_sync_events(Model *model, char *base, int player_count, int player)
{
	on_ghost_move(model, 0);
	render_pacman(model, (UINT16 *)base, 0);

	render_ghosts(model, (UINT16 *)base, 0);

	if (pacman_collides_with_snack(model, 0))
	{
		on_snack_eat(model, 0);
	}

	if (pacman_collides_with_glow_ball(model, 0))
	{
		on_glow_ball_eat(model, 0);
	}

	render_livebox(model, (UINT16 *)base, 1);
	render_scorebox(model, (UINT8 *)base, 0);
	render_snacks(model, (UINT16 *)base, 0);
	render_glow_balls(model, (UINT16 *)base, 0);
}