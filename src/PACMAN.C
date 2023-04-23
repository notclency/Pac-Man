/*
	File Name: PACMAN.C

	Purpose:
			This is the main file for the game. It contains the
			main function and the main game loop.

	Authors: Glenn and Clency

*/

#include "include\GAME.H"

int main()
{
	install_vectors();
	display_splash_screen((char *)get_video_base());
	menu();
	remove_vectors();

	return 0;
}
