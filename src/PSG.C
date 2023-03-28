/*

Purpose: To make the song play. This function sets the tone, sets the volume,
sets the channel needed to play the song and ends the song. 

*/


#include <osbind.h>
#include "PSG.H"
#include "TYPES.H"

volatile char *PSG_reg_select = 0xFF8800;
volatile char *PSG_reg_write = 0xFF8802;

/*

Inputs: int reg, UINT8 val
Purpose: To write the register and the value to the PSG.

*/
void write_psg(int reg, UINT8 val)
{
	*PSG_reg_select = reg;
	*PSG_reg_write = val;
}

/*

Inputs: int channel, int tuning
Purpose: To set the tone of the channel.

*/
void set_tone(int channel, int tuning)
{
	
switch (channel)
	{
		case Channel_A:
			write_psg(CH_A_TONE, tuning);
			break;
		case Channel_B:
			write_psg(CH_B_TONE, tuning);
			break;	
		case Channel_C:
			write_psg(CH_C_TONE, tuning);
			break;
}

}

/*

Inputs: int channel, int volume
Purpose: To set the volume of the channel.

*/
void set_volume(int channel, int volume)
{
	switch (channel)
	{
		case Channel_A:
			write_psg(CH_A_VOL, volume);
			break;
		case Channel_B:
			write_psg(CH_B_VOL, volume);
			break;	
		case Channel_C:
			write_psg(CH_C_VOL, volume);
			break;
	}
}

/*

Inputs: int channel, int tone_on, int noise_on
Purpose: To enable the channel.

*/
void enable_channel(int channel, int tone_on, int noise_on)
{
	switch (channel)
	{
		case Channel_A:
			write_psg(CH_A_VOL, (tone_on << 7) | (noise_on << 6));
			break;
		case Channel_B:
			write_psg(CH_B_VOL, (tone_on << 7) | (noise_on << 6));
			break;	
		case Channel_C:
			write_psg(CH_C_VOL, (tone_on << 7) | (noise_on << 6));
			break;
	}
}
/*

Inputs: none
Purpose: To stop the sound.

*/
void stop_sound()
{
	write_psg(CH_A_VOL, 0);
	write_psg(CH_B_VOL, 0);
	write_psg(CH_C_VOL, 0);
}