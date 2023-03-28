/*

Purpose: Music for the game, it basically gets the notes and allows PSG.C to play them in the correct order.
This allows music to happen while the game is in session.

Song Name: Toshio Kai "Pac-Man Fever 

*/

#include "MUSIC.H"
#include <osbind.h>
#include <stdio.h>

/*

Purpose: To keep the notes and how long the note should be played for. 

*/
const SONG main_song[] = {

    /*LINE 1*/
    {NOTE_B, 0},
    {NOTE_B, 0},
    {NOTE_F_FLAT,0},
    {NOTE_D_FLAT,0},
    {NOTE_B, 0}, /*supposed to be B*/ 
    {NOTE_F_FLAT,0},
    {NOTE_D_FLAT,0},
    {NOTE_C,0},
    {NOTE_C,0},
    {NOTE_G,0},
    {NOTE_F_FLAT,0}, /*supposed to be E*/
    {NOTE_C,0},
    {NOTE_G,0},
    {NOTE_F_FLAT,0}, /*supposed to be E*/
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_F_FLAT,0},
    {NOTE_D_FLAT,0},
    {NOTE_B,0},
    {NOTE_F_FLAT,0},
    {NOTE_D_FLAT,0},
    {NOTE_D_FLAT,0},
    {NOTE_F_FLAT,0}, /*supposed to be E*/
    {NOTE_F,0},
    {NOTE_F,0},
    {NOTE_F_FLAT,0},
    {NOTE_G,0},
    {NOTE_G,0},
    {NOTE_B,0},
    {NOTE_C,0},
    {NOTE_B,0},

    /*LINE 2*/
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_C,0},
    {NOTE_C,0},
    {NOTE_C,0},
    {NOTE_C,0},
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_B,0},
    {NOTE_B,0}, 
    {NOTE_F_FLAT,0},
    {NOTE_G_FLAT,0},
    {NOTE_A_FLAT,0},
    {NOTE_B,0},
};

/*

Purpose: To start the song and play it.

*/
void start_music()
{
    int vol;
    int sustain = 0;
}

