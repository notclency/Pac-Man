#include "include/FONT.H"

/*
    ALL NUMBERS ARE LETTERS AND NUMBERS ARE
    PACMAN CUSTOM FONTS (8x8). AND THE EQUAL
    SIGN IS USED AS THE MENU SELECTOR.
*/

const UINT8 font[] =
{
0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,  /* <space> */
0x08,0x08,0x08,0x08,0x08,0x00,0x08,0x00,  /* ! */
0x14,0x14,0x00,0x00,0x00,0x00,0x00,0x00,  /* " */
0x00,0x24,0x7E,0x24,0x24,0x7E,0x24,0x00,  /* # */
0x10,0x7C,0x50,0x7C,0x14,0x7C,0x10,0x00,  /* $ */
0x00,0x62,0x64,0x08,0x10,0x26,0x46,0x00,  /* % */
0xFF, 0xCF, 0xB7, 0xA7, 0xCF, 0x35, 0x73, 0x8D,  /* & */
0x00,0x08,0x10,0x00,0x00,0x00,0x00,0x00,  /* ' */
0x00,0x08,0x10,0x10,0x10,0x10,0x08,0x00,  /* ( */
0x00,0x10,0x08,0x08,0x08,0x08,0x10,0x00,  /* ) */
0x00,0x00,0x28,0x10,0x7C,0x10,0x28,0x00,  /* * */
0x00,0x00,0x10,0x10,0x7C,0x10,0x10,0x00,  /* + */
0x00,0x00,0x00,0x00,0x00,0x08,0x08,0x10,  /* , */
0xFF, 0xFF, 0xFF, 0x81, 0x81, 0xFF, 0xFF, 0xFF,  /* - */
0x00,0x00,0x00,0x00,0x00,0x18,0x18,0x00,  /* . */
0x00,0x00,0x04,0x08,0x10,0x20,0x40,0x00,  /* / */

0xFF, 0xC7, 0xB3, 0x39, 0x39, 0x39, 0x8B, 0xC7,  /* 0 */
0xFF, 0xE7, 0xC7, 0xE7, 0xE7, 0xE7, 0xE7, 0x81,  /* 1 */
0xFF, 0x83, 0x39, 0xF1, 0xC3, 0x87, 0x1F, 0x01,  /* 2 */
0xFF, 0x01, 0xF3, 0xE7, 0xC3, 0xF9, 0x39, 0x83,  /* 3 */
0xFF, 0xE3, 0xC3, 0x93, 0x33, 0x01, 0xF3, 0xF3,  /* 4 */
0xFF, 0x03, 0x7F, 0x03, 0xF9, 0xF9, 0x39, 0x83,  /* 5 */
0xFF, 0xC3, 0x9F, 0x3F, 0x03, 0x39, 0x39, 0x83,  /* 6 */
0xFF, 0x01, 0x39, 0xF3, 0xE7, 0xCF, 0xCF, 0xCF,  /* 7 */
0xFF, 0x87, 0x3B, 0x1B, 0x87, 0x61, 0x79, 0x83,  /* 8 */
0xFF, 0x83, 0x39, 0x39, 0x81, 0xF9, 0xF3, 0x87,  /* 9 */
0xFF, 0xCF, 0xCF, 0xFF, 0xFF, 0xCF, 0xCF, 0xFF,  /* : */
0x00,0x00,0x10,0x00,0x00,0x10,0x10,0x20,  /* ; */
0x00,0x00,0x08,0x10,0x20,0x10,0x08,0x00,  /* < */
0x3F, 0x0F, 0x03, 0x00, 0x00, 0x03, 0x0F, 0x3F,  /* = */
0x00,0x00,0x20,0x10,0x08,0x10,0x20,0x00,  /* > */
0x00,0x3C,0x42,0x04,0x08,0x00,0x08,0x00,  /* ? */

0x00,0x3C,0x4A,0x56,0x5E,0x40,0x3C,0x00,  /* @ */
0xFF, 0xC7, 0x93, 0x39, 0x39, 0x01, 0x39, 0x39,  /* A */
0xFF, 0x03, 0x79, 0x79, 0x03, 0x79, 0x79, 0x03,  /* B */
0xFF, 0xC3, 0x99, 0x3F, 0x3F, 0x3F, 0x99, 0xC3,  /* C */
0xFF, 0x07, 0x33, 0x39, 0x39, 0x39, 0x33, 0x07,  /* D */
0xFF, 0x01, 0x3F, 0x3F, 0x03, 0x3F, 0x3F, 0x01,  /* E */
0xFF, 0x03, 0x3F, 0x3F, 0x07, 0x3F, 0x3F, 0x3F,  /* F */
0xFF, 0xC1, 0x9F, 0x3F, 0x31, 0x39, 0x99, 0xC1,  /* G */
0xFF, 0x39, 0x39, 0x39, 0x01, 0x39, 0x39, 0x39,  /* H */
0xFF, 0x81, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0x81,  /* I */
0xFF, 0xF9, 0xF9, 0xF9, 0xF9, 0xF9, 0x39, 0x83,  /* J */
0xFF, 0x39, 0x33, 0x27, 0x0F, 0x07, 0x33, 0x39,  /* K */
0xFF, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x01,  /* L */
0xFF, 0x39, 0x11, 0x01, 0x01, 0x29, 0x39, 0x39,  /* M */
0xFF, 0x39, 0x19, 0x09, 0x01, 0x21, 0x31, 0x39,  /* N */
0xFF, 0x83, 0x39, 0x39, 0x39, 0x39, 0x39, 0x83,  /* O */

0xFF, 0x03, 0x39, 0x39, 0x39, 0x03, 0x3F, 0x3F,  /* P */
0xFF, 0x83, 0x39, 0x39, 0x39, 0x21, 0x33, 0x85,  /* Q */
0xFF, 0x07, 0x39, 0x39, 0x31, 0x07, 0x23, 0x31,  /* R */
0xFF, 0x87, 0x33, 0x3F, 0x83, 0xF9, 0x39, 0x83,  /* S */
0xFF, 0x81, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7, 0xE7,  /* T */
0xFF, 0x39, 0x39, 0x39, 0x39, 0x39, 0x39, 0x83,  /* U */
0xFF, 0x39, 0x39, 0x39, 0x11, 0x83, 0xC7, 0xEF,  /* V */
0xFF, 0x39, 0x39, 0x29, 0x01, 0x01, 0x11, 0x39,  /* W */
0xFF, 0x39, 0x11, 0x83, 0xC7, 0x83, 0x11, 0x39,  /* X */
0xFF, 0x99, 0x99, 0x99, 0xC3, 0xE7, 0xE7, 0xE7,  /* Y */
0xFF, 0x01, 0xF1, 0xE3, 0xC7, 0x8F, 0x1F, 0x01,  /* Z */
0x00,0x38,0x20,0x20,0x20,0x20,0x38,0x00,  /* [ */
0x00,0x00,0x40,0x20,0x10,0x08,0x04,0x00,  /* <backslash> */
0x00,0x38,0x08,0x08,0x08,0x08,0x38,0x00,  /* ] */
0x00,0x10,0x28,0x44,0x00,0x00,0x00,0x00,  /* ^ */
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xFE,  /* _ */

0x3C,0x42,0x99,0xA1,0xA1,0x99,0x42,0x3C,  /* ` */
0x00,0x00,0x38,0x04,0x3C,0x44,0x3C,0x00,  /* a */
0x00,0x40,0x40,0x78,0x44,0x44,0x78,0x00,  /* b */
0x00,0x00,0x1C,0x20,0x20,0x20,0x1C,0x00,  /* c */
0x00,0x04,0x04,0x3C,0x44,0x44,0x3C,0x00,  /* d */
0x00,0x00,0x38,0x44,0x78,0x40,0x3C,0x00,  /* e */
0x00,0x0C,0x10,0x18,0x10,0x10,0x10,0x00,  /* f */
0x00,0x00,0x3E,0x42,0x42,0x3E,0x02,0x3C,  /* g */
0x00,0x40,0x40,0x78,0x44,0x44,0x44,0x00,  /* h */
0x00,0x08,0x00,0x18,0x08,0x08,0x1C,0x00,  /* i */
0x00,0x04,0x00,0x04,0x04,0x04,0x24,0x18,  /* j */
0x00,0x40,0x50,0x60,0x60,0x50,0x48,0x00,  /* k */
0x00,0x10,0x10,0x10,0x10,0x10,0x0C,0x00,  /* l */
0x00,0x00,0x68,0x54,0x54,0x54,0x54,0x00,  /* m */
0x00,0x00,0x78,0x44,0x44,0x44,0x44,0x00,  /* n */
0x00,0x00,0x38,0x44,0x44,0x44,0x38,0x00,  /* o */

0x00,0x00,0x78,0x44,0x44,0x78,0x40,0x40,  /* p */
0x00,0x00,0x3C,0x44,0x44,0x3C,0x04,0x06,  /* q */
0x00,0x00,0x1C,0x20,0x20,0x20,0x20,0x00,  /* r */
0x00,0x00,0x38,0x40,0x38,0x04,0x78,0x00,  /* s */
0x00,0x10,0x38,0x10,0x10,0x10,0x0C,0x00,  /* t */
0x00,0x00,0x44,0x44,0x44,0x44,0x38,0x00,  /* u */
0x00,0x00,0x44,0x44,0x28,0x28,0x10,0x00,  /* v */
0x00,0x00,0x44,0x54,0x54,0x54,0x28,0x00,  /* w */
0x00,0x00,0x44,0x28,0x10,0x28,0x44,0x00,  /* x */
0x00,0x00,0x44,0x44,0x44,0x3C,0x04,0x38,  /* y */
0x00,0x00,0x7C,0x08,0x10,0x20,0x7C,0x00,  /* z */
0x00,0x1C,0x10,0x60,0x10,0x10,0x1C,0x00,  /* { */
0x00,0x10,0x10,0x10,0x10,0x10,0x10,0x00,  /* | */
0x00,0x70,0x10,0x0C,0x10,0x10,0x70,0x00,  /* } */
0x00,0x14,0x28,0x00,0x00,0x00,0x00,0x00,  /* ~ */
};
