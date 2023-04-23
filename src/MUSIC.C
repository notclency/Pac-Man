/*

---------------------------------------------------------------------------------------------------
File Name: MUSIC.C
---------------------------------------------------------------------------------------------------
Purpose: This file processes sound and music. It contains the functions to play the music in
the game. It contains the main song and the functions to start and update the music.
---------------------------------------------------------------------------------------------------
Functions: const SONG main_song[], start_music, update_music
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\MUSIC.H"

/*

    pararmeters: 
            None

    description: 
            To keep the notes and how long the note should be played for. 

    return:
            None
*/
static int current_note = 0;

const SONG main_song[] = 
    {
     0x0071, 0.5, 
     0x0039, 0.5, 
     0x0097, 0.5, 
     0x00B4, 0.5, 
     0x0039, 0.5, 
     0x0097, 0.5, 
     0x00B4, 0.5, 
     0x00D6, 1, 
     0x006B, 0.5, 
     0x008F, 0.5, 
     0x00AA, 0.5, 
     0x00D6, 0.5, 
     0x008F,0.5, 
     0X00AA, 0.5, 
     0x0071, 0.5, 
     0x0039, 1, 
     0x0097, 0.5, 
     0x00B4, 0.5, 
     0x0039, 0.5, 
     0x0097, 0.5,
     0x00B4, 0.5, 
     0x00B4, 1, 
     0x00AA, 0.5, 
     0x00A0, 0.5, 
     0x00A0, 0.5, 
     0x0097, 0.5, 
     0x008F, 0.5, 
     0x008F, 0.5, 
     0x0071, 0.5, 
     0x00D6, 0.5, 
     0x0071, 0.5, 
     0x038A, 0.5, 
     0x01C5, 0.5, 
     0X038A, 0.5, 
     0x06AE, 1,
     0x0357, 0.5,
     0x06AE, 0.5,
     0x0357, 0.5,
     0x0384, 0.5,
     0x01C5, 0.5,
     0x038A, 0.5,
     0x01C5, 0.5,
     0x04B9, 0.5,
     0x0435, 0.5,
     0x03C0, 0.5,
     0X038A, 0.5,
     };

/*

    pararmeters: 
            None

    description:
        To start the song and play it.
    
    return:
            None

*/
void start_music()
{
    enable_channel(ch_a, true, false);
    set_volume(ch_a, 10);
    set_tone(ch_a, main_song[current_note++].note);

}

/*

    pararmeters: 
            UINT32 time_elapsed

    description: 
            To update the song.

    return:
            None

*/
void update_music(UINT32 time_elapsed)
{
    int time = 0;
    time += time_elapsed;
    if (time >= main_song[current_note++].duration)
    {
        set_tone(ch_a,main_song[current_note++].note);
        if (main_song[current_note++].duration == 0)
        {
            main_song[current_note++].note == 0;
        }
    }
}
