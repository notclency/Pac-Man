/*

---------------------------------------------------------------------------------------------------
File Name: PSG.C
---------------------------------------------------------------------------------------------------
Purpose: This file purpose is to write to the register, we also set the tone
and volume of the channel. The file also enables the channel and sets the right channel that we want
the music to play through. Enable the channel also allows us to play noise and
tone at the same time if needed or vice versa.
---------------------------------------------------------------------------------------------------
Functions: write_psg, read_psg, set_tone, set_volume, enable_channel,set_envelope, set_noise,
stop_sound
---------------------------------------------------------------------------------------------------
Issues/Problems:  None
---------------------------------------------------------------------------------------------------
Authors: - CLENCY TABE AND GLENN YEAP
---------------------------------------------------------------------------------------------------

*/

#include "include\PSG.H"

/*

  parameters:
          int reg - register to write to
          UINT8 val - value to write to register

  description:
          This function writes to the register of the PSG.

  return:
          None

*/
void write_psg(int reg, UINT8 val)
{
        long old_ssp;
        if (reg >= 0 && reg <= 15)
        {
                old_ssp = Super(0);

                *PSG_reg_select = reg;
                *PSG_reg_write = val;

                Super(old_ssp);
        }
}

/*

  parameters:
          int reg - register to read from

  description:
          This function reads from the register of the PSG.

  return:
          int - value read from register

*/
int read_psg(int reg)
{
        long old_ssp;
        int val = -1;

        old_ssp = Super(0);

        if (reg >= 0 && reg <= 15)
        {
                *PSG_reg_select = reg;
                val = *PSG_reg_select;
        }

        Super(old_ssp);
        return val;
}

/*

  parameters:
          channel_t channel - channel to set tone on
          int tuning - tuning value

  description:
          This function sets the tone of the channel.

  return:
          None

*/
void set_tone(channel_t channel, int tuning)
{
        int fine_tune = tuning * 0x00FF;
        int coarse_tune = tuning * 0x0FF0;
        switch (channel)
        {
        case ch_a:
                write_psg(CH_A_TONE, fine_tune);
                write_psg(CH_A_ROUGH_TONE, coarse_tune);
                break;
        case ch_b:
                write_psg(CH_B_TONE, fine_tune);
                write_psg(CH_B_ROUGH_TONE, coarse_tune);
                break;
        case ch_c:
                write_psg(CH_C_TONE, fine_tune);
                write_psg(CH_C_ROUGH_TONE, coarse_tune);
                break;
        }
}

/*

  parameters:
          channel_t channel - channel to set volume on
          int volume - volume value

  description:
          This function sets the volume of the channel.

  return:
          None

*/
void set_volume(channel_t channel, int volume)
{
        switch (channel)
        {
        case ch_a:
                write_psg(CH_A_VOL, volume);
                break;
        case ch_b:
                write_psg(CH_B_VOL, volume);
                break;
        case ch_c:
                write_psg(CH_C_VOL, volume);
                break;
        }
}

/*

  parameters:
          channel_t channel - channel to enable
          bool tone_on - true if tone is on
          bool noise_on - true if noise is on

  description:
          This function enables the channel.

  return:
          None

*/
void enable_channel(channel_t channel, bool tone_on, bool noise_on)
{
        UINT8 mixerControl;
        mixerControl = read_psg(MIXER_REG);

        {
                switch (channel)
                {
                case ch_a:
                        if (tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_A_NOISEON_TONEON;
                        }
                        if (noise_on && !tone_on)
                        {
                                mixerControl = mixerControl & IO_A_NOISEON_TONEOFF;
                        }
                        if (!tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_A_NOISEOFF_TONEON;
                        }
                        break;
                case ch_b:
                        if (tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_B_NOISEON_TONEON;
                        }
                        if (noise_on && !tone_on)
                        {
                                mixerControl = mixerControl & IO_B_NOISEON_TONEOFF;
                        }
                        if (!tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_B_NOISEOFF_TONEON;
                        }
                        break;
                case ch_c:
                        if (tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_C_NOISEON_TONEON;
                        }
                        if (noise_on && !tone_on)
                        {
                                mixerControl = mixerControl & IO_C_NOISEON_TONEOFF;
                        }
                        if (!tone_on && noise_on)
                        {
                                mixerControl = mixerControl & IO_C_NOISEOFF_TONEON;
                        }
                        break;
                }
                write_psg(MIXER_REG, mixerControl);
        }
}

/*

  parameters:
          channel_t channel - channel to disable
          bool tone_on - true if tone is on
          bool noise_on - true if noise is on

  description:
          This function sets a envelope shape.

  return:
          None

*/
void set_envelope(shapes Env_shape, unsigned int sustain)
{
        int val;
        write_psg(ENVELOPE_FINE_REG, sustain);
        write_psg(ENVELOPE_ROUGH_REG, sustain);

        switch (Env_shape)
        {
        case saw:
                val = ENV_SAW_SHAPE;
                break;
        case triangle:
                val = ENV_TRIANGLE_SHAPE;
                break;
        case saw_inv:
                val = ENV_SAW_SHAPE_INV;
                break;
        case saw_period:
                val = ENV_SAW_PERIOD_SHAPE;
                break;
        case triangle_inv:
                val = ENV_TRIANGLE_INV_SHAPE;
                break;
        case triangle_period:
                val = ENV_TRIANGLE_PERIOD_SHAPE;
                break;
        case triangle_inv_period:
                val = ENV_TRIANGLE_INV_PERIOD_SHAPE;
                break;
        }
}

/*stops the sounds*/
void stop_sound()
{
        write_psg(CH_A_VOL, 0);
        write_psg(CH_B_VOL, 0);
        write_psg(CH_C_VOL, 0);
}

/*

    parameters:
            int tuning - tuning value

    description:
            This function sets the noise.

    return:
            None

  */
void set_noise(int tuning)
{
        write_psg(NOISE_PERIOD_REG, tuning);
}