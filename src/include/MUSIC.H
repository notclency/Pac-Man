#ifndef MUSIC_H
#define MUSIC_H

#include "TYPES.H"
#include "PSG.H"


/*
    struct: SONG
    note: the note to play
    duration: the duration of the note in milliseconds

*/
typedef struct {

    int note;
    int duration;
} SONG;

/*
    function: start_music
    description: starts the music
    parameters: none

*/
void start_music();

/*

    function: update_music
    description: updates the music
    parameters: time_elapsed: the time elapsed since the last update

*/
void update_music(UINT32 time_elapsed);




#endif
