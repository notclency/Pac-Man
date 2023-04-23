/*

---------------------------------------------------------------------------------------------------
File Name:	GAME.C
---------------------------------------------------------------------------------------------------
Purpose: This file contains the main game loop contianing the game backend and frontend. It
processes all the game asyncronous and syncronous events while rendering the game.
---------------------------------------------------------------------------------------------------
Functions: start_single_player_session, get_base, game_loop,set_screen, display_splash_screen,
process_async_events, process_sync_events.
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\GAME.H"

int player_count;
int player;

char buff[32256];
extern int RENDER_REQUEST;
extern int GAME_TIMER;
extern int CHERRY_TIMER;
extern int MUIC_TIMER;
extern int PACMAN_SUPER_TIMER;

/*
	parameters:
		void

	description:
		starts a single player session

	return:
		void
*/
void start_single_player_session()
{
	player_count = 1;
	player = 0;
	game_loop();
}

/*
	parameters:
		second_buffer: second buffer

	description:
		gets the aligned base address of the second buffer
		for double buffering

	return:
		char *: aligned base address
*/
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

/*
	parameters:
		void

	description:
		processes all game events

	return:
		void
*/
void game_loop()
{
	Model model;
	char *base_1 = (char *)get_video_base();
	char *base_2 = get_base(buff);
	int flip = 1;
	int i;

	/* game backend */
	for (i = 1; player < player_count; i++)
	{
		ini_game_session(&model, player_count, player);
		while (!model.game_over && !model.game_won && GAME_TIMER > 0)
		{
			process_async_events(&model, player);
			process_sync_events(&model, player);

			if (CHERRY_TIMER > (CHERRY_POP_TIME * 70) && CHERRY_TIMER < ((CHERRY_POP_TIME + 1) * 70))
			{
				pop_cherry(&model);
			}

			if (CHERRY_TIMER > (CHERRY_COLLAPSE_TIME * 70) && CHERRY_TIMER < ((CHERRY_COLLAPSE_TIME + 1) * 70))
			{
				collapse_cherry(&model);
			}

			if (model.pacman[player].mode == SUPER && PACMAN_SUPER_TIMER > (PACMAN_SUPER_TIME * 70) && PACMAN_SUPER_TIMER < ((PACMAN_SUPER_TIME + 1) * 70))
			{
				reset_pacman_mode(&model, player);
			}

			if (!model.game_over || !model.game_won)
			{
				if (RENDER_REQUEST)
				{
					if (flip)
					{
						render(&model, base_1, player_count, player);
						set_screen(base_1);
					}
					else
					{
						render(&model, base_2, player_count, player);
						set_screen(base_2);
					}

					flip = !flip;
					RENDER_REQUEST = FALSE;
				}
			}

			start_music();

			if (model.game_over)
			{
				render_game_over_screen((UINT32 *)base_1, &model, player);
				set_screen(base_1);
			}
			else if (model.game_won)
			{
				render_game_won_screen((UINT32 *)base_1, &model, player);
				set_screen(base_1);
			}

			if (model.game_over || model.game_won)
				stop_sound();
		}

		player++;
	}

	return;
}

/*
	parameters:
		base: base address

	description:
		sets the video base address

	return:
		void
*/
void set_screen(char *base)
{
	set_video_base(base);
}

void display_splash_screen(char *base)
{
	plot_screen((UINT32 *)base, (UINT32 *)splash_screen);

	print_string_8((UINT8 *)base, 288, 220, "1 PLAYER");
	print_string_8((UINT8 *)base, 288, 250, "2 PLAYERS");
	print_string_8((UINT8 *)base, 288, 280, "ESC QUIT");
	print_string_8((UINT8 *)base, 208, 360, "MADE BY CLENCY & GLENN - 2023");

	set_screen(base);
}
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
void process_async_events(Model *model, int player)
{
	UINT32 input;

	if (is_ikbd_waiting())
	{
		input = read_from_ikbd();

		if (input != MOUSE_MOVE_CODE)
		{
			if (input == ESC_KEY)
			{
				model->game_over = TRUE;
				return;
			}

			on_pacman_move(model, input, player);
		}
	}
}

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
void process_sync_events(Model *model, int player)
{
	/* ghost move */
	on_ghost_move(model, player);

	/* ghost/pacman collision check & render */
	pacman_collides_with_ghost(model, player);

	/* edible collison check / trigger events */
	pacman_collides_with_snack(model, player);
	pacman_collides_with_cherry(model, player);
	pacman_collides_with_glow_ball(model, player);
	pacman_collides_with_cherry(model, player);
}
