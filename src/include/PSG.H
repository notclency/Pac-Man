#ifndef PSG_H
#define PSG_H

#include "TYPES.H"
#include "MUSIC.H"

#define CH_A 0
#define CH_B 1
#define CH_C 2

#define CH_A_TONE 0x0
#define CH_B_TONE 0x2
#define CH_C_TONE 0x4

#define CH_A_ROUGH_TONE 0x1
#define CH_B_ROUGH_TONE 0x3
#define CH_C_ROUGH_TONE 0x5

#define CH_A_VOL 0x8
#define CH_B_VOL 0x9
#define CH_C_VOL 0xa

#define IO_A_NOISEON_TONEON 0x36  
#define IO_A_NOISEON_TONEOFF 0x37 
#define IO_A_NOISEOFF_TONEON 0x3E 

#define IO_B_NOISEON_TONEON 0x2D  
#define IO_B_NOISEON_TONEOFF 0x2F 
#define IO_B_NOISEOFF_TONEON 0x3D 

#define IO_C_NOISEON_TONEON 0x1B  
#define IO_C_NOISEON_TONEOFF 0x1F 
#define IO_C_NOISEOFF_TONEON 0x3B

#define MIXER_REG 0x7

#define NOISE_PERIOD_REG 0x6

#define ENV_SAW_SHAPE 0xc
#define ENV_SAW_SHAPE_INV 0x8
#define ENV_SAW_PERIOD_SHAPE  0xf
#define ENV_TRIANGLE_SHAPE 0xe
#define ENV_TRIANGLE_INV_SHAPE 0xa
#define ENV_TRIANGLE_PERIOD_SHAPE  0xd
#define ENV_TRIANGLE_INV_PERIOD_SHAPE 0x00

#define ENVELOPE_FINE_REG 0xb
#define ENVELOPE_ROUGH_REG 0xc
#define ENVELOPE_SHAPE_CONTROL_REG 0xd


typedef enum{
    ch_a,
    ch_b,
    ch_c
} channel_t;

typedef enum{
    saw,
    saw_inv,
    saw_period,
    triangle,
    triangle_inv,
    triangle_period,
    triangle_inv_period
} shapes;

typedef int bool;
#define true 1
#define false 0

extern volatile char *PSG_reg_select = 0xFF8800;
extern volatile char *PSG_reg_write = 0xFF8802;

void write_psg(int reg, UINT8 val);
int read_psg(int reg);
void set_tone(int channel, int tuning);
void set_volume(int channel, int volume);
void enable_channel(channel_t channel, bool tone_on, bool noise_on);
void stop_sound();

void set_noise(int tuning);
void set_envelope(shapes Env_shape, unsigned int sustain);

#endif