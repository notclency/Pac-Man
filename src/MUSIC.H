#ifndef MUSIC_H
#define MUSIC_H

#include <osbind.h>
#include "PSG.H"
#include "TYPES.H"

#define NOTE_C_FLAT 478
#define NOTE_C 451
#define NOTE_D_FLAT 428 
#define NOTE_D 402
#define NOTE_E_FLAT 379
#define NOTE_F_FLAT 358
#define NOTE_F 338
#define NOTE_G_FLAT 319
#define NOTE_G 301
#define NOTE_A_FLAT 284
#define NOTE_A 268
#define NOTE_B_FLAT 253
#define NOTE_B 239

typedef struct {

    int note;
    int duration;
} SONG;

/*



*/

void start_music();
void update_music(UINT32 time_elapsed);



#endif
