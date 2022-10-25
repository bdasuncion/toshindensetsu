#include  <stdarg.h>
#include "GBATypes.h"
#include "GBADMA.h"
#include "GBABG.h"
#include "GBAVideo.h"

#define MAX_LINELENGTH 30

u16 mprinter_textEntry[32][32];
int mprinter_lineNumber = 0;
int mprinter_lineIndex = 0;
int delay = 0;


const unsigned short character_pal[16] = 
{
	//0x20A8,0x7E40,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x20A8,0x700F,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
	0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
};
const unsigned int character_tiles[1504] = 
{
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00000000,0x00000000,0x00000000,0x00001000,0x00000000,
	0x00000000,0x00100100,0x00100100,0x00100100,0x00100100,0x00100100,0x01111110,0x00100100,
	0x00100100,0x01111110,0x00100100,0x00100100,0x00100100,0x00100100,0x00100100,0x00000000,
	0x00000000,0x00010000,0x00111100,0x01000010,0x00000010,0x00000010,0x00000010,0x00001100,
	0x00110000,0x01001000,0x01000100,0x01000010,0x01000010,0x00111100,0x00001000,0x00000000,
	0x00000000,0x01000000,0x01000110,0x01000110,0x00100000,0x00100000,0x00100000,0x00010000,
	0x00001000,0x00000100,0x00000100,0x01100100,0x01100010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00000000,0x00111100,0x01000010,0x00000010,0x00000010,0x00000100,0x00000100,
	0x00001010,0x00010010,0x01010010,0x00100010,0x00100010,0x01010010,0x01001100,0x00000000,
	0x00000000,0x00011000,0x00010000,0x00010000,0x00001000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x01100000,0x00011000,0x00000100,0x00000100,0x00000010,0x00000010,0x00000010,
	0x00000010,0x00000010,0x00000010,0x00000100,0x00000100,0x00011000,0x01100000,0x00000000,
	0x00000000,0x00000110,0x00011000,0x00100000,0x00100000,0x01000000,0x01000000,0x01000000,
	0x01000000,0x01000000,0x01000000,0x00100000,0x00100000,0x00011000,0x00000110,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00001000,0x00101010,0x00011100,0x00001000,
	0x00010100,0x00100010,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00001000,0x00001000,0x00111110,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00001100,0x00001000,0x00001000,0x00000100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x01111110,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00001100,0x00001100,0x00000000,
	0x00000000,0x01000000,0x01000000,0x01000000,0x00100000,0x00100000,0x00010000,0x00010000,
	0x00001000,0x00001000,0x00000100,0x00000100,0x00000010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00011000,0x00100100,0x01000010,0x01000010,0x01100010,0x01010010,0x01001010,
	0x01000110,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x00011000,0x00010100,0x00010010,0x00010000,0x00010000,0x00010000,0x00010000,
	0x00010000,0x00010000,0x00010000,0x00010000,0x00010000,0x00010000,0x01111110,0x00000000,
	0x00000000,0x00111000,0x01000100,0x01000010,0x01000010,0x01000000,0x00100000,0x00010000,
	0x00010000,0x00001000,0x00000100,0x00000100,0x00000010,0x00000010,0x01111110,0x00000000,
	0x00000000,0x00011100,0x00100010,0x01000000,0x01000000,0x01000000,0x00100000,0x00011000,
	0x00100000,0x01000000,0x01000000,0x01000000,0x01000000,0x00100010,0x00011100,0x00000000,
	0x00000000,0x00100000,0x00110000,0x00101000,0x00100100,0x00100010,0x00100010,0x01111110,
	0x00100000,0x00100000,0x00100000,0x00100000,0x00100000,0x00100000,0x00100000,0x00000000,
	0x00000000,0x01111100,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00011110,
	0x00100000,0x01000000,0x01000000,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x00000010,0x00000010,0x00011110,
	0x00100010,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x01111110,0x01000000,0x01000000,0x00100000,0x00100000,0x00010000,0x00111100,
	0x00001000,0x00001000,0x00000100,0x00000100,0x00000100,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00100100,
	0x00100100,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01100010,
	0x01011100,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00001100,0x00001100,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00001100,0x00001100,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00001100,0x00001100,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00001100,0x00001000,0x00001000,0x00000100,0x00000000,
	0x00000000,0x01000000,0x00100000,0x00010000,0x00001000,0x00000100,0x00000010,0x00000010,
	0x00000010,0x00000010,0x00000100,0x00001000,0x00010000,0x00100000,0x01000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111110,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00111110,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000010,0x00000100,0x00001000,0x00010000,0x00100000,0x01000000,0x01000000,
	0x01000000,0x01000000,0x00100000,0x00010000,0x00001000,0x00000100,0x00000010,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000000,0x01000000,0x00100000,0x00010000,
	0x00001000,0x00001000,0x00001000,0x00000000,0x00000000,0x00000000,0x00001000,0x00000000,
	0x00000000,0x00111100,0x01000010,0x00000010,0x00110010,0x00101010,0x00101010,0x00101010,
	0x00101010,0x00101010,0x01001010,0x01101010,0x01010010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01111110,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00011110,0x00100010,0x01000010,0x01000010,0x01000010,0x00100010,0x00011110,
	0x00100010,0x01000010,0x01000010,0x01000010,0x01000010,0x00100010,0x00011110,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x00000010,0x00000010,0x00000010,
	0x00000010,0x00000010,0x00000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00001100,0x00010010,0x00100010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x00100010,0x00010010,0x00001100,0x00000000,
	0x00000000,0x01111100,0x00000010,0x00000010,0x00000010,0x00000010,0x00111110,0x00000010,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x01111100,0x00000000,
	0x00000000,0x01111100,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00111110,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00111100,0x01000010,0x01000010,0x01000010,0x00000010,0x00000010,0x00000010,
	0x00000010,0x01110010,0x01000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01111110,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x01111110,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x01111110,0x00000000,
	0x00000000,0x01110000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,
	0x01000000,0x01000000,0x01000010,0x01000010,0x01000010,0x00100010,0x00011100,0x00000000,
	0x00000000,0x01000010,0x01000010,0x00100010,0x00100010,0x00010010,0x00001110,0x00010010,
	0x00100010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x01111110,0x00000000,
	0x00000000,0x01000010,0x01100110,0x01011010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x01000010,0x01000110,0x01001010,0x01001010,0x01010010,0x01100010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00011000,0x00100100,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x00011110,0x00100010,0x01000010,0x01000010,0x00100010,0x00011110,0x00000010,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00011000,0x00100100,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01010010,0x00100100,0x01011000,0x00000000,
	0x00000000,0x00011110,0x00100010,0x01000010,0x01000010,0x00100010,0x00011110,0x00100010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00111000,0x01000100,0x01000010,0x00000010,0x00000100,0x00011000,0x00100000,
	0x01000000,0x01000000,0x01000000,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x01111110,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01011010,0x01100110,0x01000010,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x00100100,0x00100100,0x00011000,0x00011000,
	0x00011000,0x00100100,0x00100100,0x00100100,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x01000010,0x01000010,0x01000010,0x00100010,0x00100100,0x00010100,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,
	0x00000000,0x01111110,0x01000000,0x01000000,0x00100000,0x00100000,0x00010000,0x00010000,
	0x00001000,0x00001000,0x00000100,0x00000100,0x00000010,0x00000010,0x01111110,0x00000000,
	0x00000000,0x01111110,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x01111110,0x00000000,
	0x00000000,0x00000010,0x00000010,0x00000010,0x00000100,0x00000100,0x00001000,0x00001000,
	0x00010000,0x00010000,0x00100000,0x00100000,0x01000000,0x01000000,0x01000000,0x00000000,
	0x00000000,0x01111110,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,
	0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01111110,0x00000000,
	0x00000000,0x00001000,0x00010100,0x00100010,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x11111111,0x00000000,
	0x00000000,0x00010000,0x00010000,0x00010000,0x00001000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x00100010,
	0x00100010,0x00100010,0x00100010,0x00100010,0x01010010,0x01010010,0x01001100,0x00000000,
	0x00000000,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00111110,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000100,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x01000010,
	0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01000000,0x01111100,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x01000010,
	0x01000010,0x01111110,0x00000010,0x00000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00111000,0x01000100,0x01000100,0x00000100,0x00000100,0x00000100,0x00011110,
	0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000000,0x01111100,0x01000010,
	0x01000010,0x01000100,0x01111000,0x01000000,0x01000000,0x01000100,0x00111000,0x00000000,
	0x00000000,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00011010,
	0x00100110,0x00100010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00001000,0x00000000,0x00000000,0x00000000,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x01000000,0x00000000,0x00000000,0x00000000,0x01000000,
	0x01000000,0x01000000,0x01000000,0x01000010,0x01000010,0x00100010,0x00011100,0x00000000,
	0x00000000,0x00000010,0x00000010,0x00000010,0x00000010,0x01000010,0x01000010,0x00100010,
	0x00010010,0x00001110,0x00010010,0x00010010,0x00100010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,
	0x01100110,0x01011010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111010,
	0x01000110,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x01000010,0x01000010,
	0x01000010,0x01000010,0x00111110,0x00000010,0x00000010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x01000010,0x01000010,
	0x01000010,0x01000010,0x01111100,0x01000000,0x01000000,0x01000000,0x01000000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000010,0x00111010,
	0x01000110,0x01000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111100,0x01000010,
	0x00000010,0x00000100,0x00111000,0x01000000,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x01111110,0x00001000,
	0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00001000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01000010,0x00100100,0x00011000,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,
	0x01000010,0x01000010,0x01000010,0x01000010,0x01011010,0x01100110,0x01000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,
	0x01000010,0x00100100,0x00011000,0x00100100,0x01000010,0x01000010,0x01000010,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000010,0x01000010,
	0x01100010,0x01010010,0x01001100,0x01000000,0x01000010,0x01000010,0x00111100,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00111110,0x01000000,
	0x01000000,0x00100000,0x00010000,0x00001000,0x00000100,0x00000010,0x01111100,0x00000000,
	0x00000000,0x01100000,0x00010000,0x00001000,0x00001000,0x00000100,0x00000100,0x00000010,
	0x00000010,0x00000100,0x00000100,0x00001000,0x00001000,0x00010000,0x01100000,0x00000000,
	0x00000000,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,
	0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000100,0x00000000,0x00000000,
	0x00000000,0x00000110,0x00001000,0x00010000,0x00010000,0x00100000,0x00100000,0x01000000,
	0x01000000,0x00100000,0x00100000,0x00010000,0x00010000,0x00001000,0x00000110,0x00000000,
	0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x01000100,
	0x00101010,0x00010000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,0x00000000,
};


void mprinter_init()
{
	dma3_cpy16(&PALETTE_BGMAP->palette[15], character_pal,16);
	dma3_cpy32(&VRAM->block[3].tile[0],character_tiles, 1504);
	
	*REG_BG_CNT2 = BG_PRIO(0)|BG_CBB(3)|BG_SBB(27)|BG_SIZE(0);
	*REG_BG_H2 = 0;
	*REG_BG_V2 = 0;
}

inline void* mprinter_getTextBuf()
{
	return mprinter_textEntry;
}

void mprinter_clear()
{
	u16 filler = 0;
	memFill16(&filler, mprinter_textEntry, 1024);
	mprinter_lineNumber = 0;
	mprinter_lineIndex = 0;
}

void mprinter_string(const char *c)
{	
	int i = 0;

	while(c[i] != '\0')
	{
		if(c[i] - '!' > 0) {
			mprinter_textEntry[mprinter_lineNumber][mprinter_lineIndex] = (c[i] - '!')*2 | SE_PALBANK(15);
			mprinter_textEntry[mprinter_lineNumber+1][mprinter_lineIndex] = ((c[i] - '!')*2 + 1)| SE_PALBANK(15);
		}
		mprinter_lineIndex++;
		
		if(c[i] == '\n') {
			mprinter_lineIndex = 0;
			mprinter_lineNumber+=2;
		}
		
		i++;
		if(mprinter_lineIndex>=MAX_LINELENGTH) {
			mprinter_lineIndex = 0;
			mprinter_lineNumber+=2;
		}
	}
}

void mprinter_convertIntToString(char *converted, int num) {
    int processNum = num, idx = 0, convertedIdx;
	char buffer[30];
    do {
	    buffer[idx] = (processNum%10) + '0';
		++idx;
	    processNum = processNum/10;
	} while(processNum);
	
	for (convertedIdx = 0, --idx; idx >= 0; --idx, ++convertedIdx) {
	    converted[convertedIdx] = buffer[idx];
	}
	converted[convertedIdx] = 0;
}

void mprinter_number(int num)
{
	char numbers[20];
	//sprintf(numbers,"%d",num);
	mprinter_convertIntToString(numbers, num);
	mprinter_string(numbers);	
}


typedef enum EFormatType {
	EString,
	ENumber
}EFormatType;

typedef struct FormatData {
	u16 strIdx;
	EFormatType type;
}FormatData;

void mprinter_printf(const char *str, ...)
{
	char strSegment[512];
	FormatData formatData[10];
	va_list valist;
	int i = 0, argCount = 0, currentIdx = 0;
	
	while (str[i] != '\0') {
		if (str[i] == '%') {
			formatData[argCount].strIdx = i;
			++i;
			if (str[i] == 's') {
				formatData[argCount].type = EString;
			}
			else if (str[i] == 'd') {
				formatData[argCount].type = ENumber;
			}
			++argCount;
		}
		++i;
	}
	
	if (!argCount) {
		mprinter_string(str);
		return;
	}

	va_start(valist, argCount);
	
	for (i = 0; i < argCount; ++i) {
		int strlength = formatData[i].strIdx - currentIdx;
		strncpy(strSegment, &str[currentIdx], strlength);
		strSegment[strlength] = 0;
		mprinter_string(strSegment);
		if (formatData[i].type == EString) {
			mprinter_string(va_arg(valist, char*));
		} else if (formatData[i].type == ENumber) {
			mprinter_number(va_arg(valist, int));
		}
		currentIdx = formatData[i].strIdx + 2;
	}
	va_end(valist);
	mprinter_string(&str[currentIdx]);
}

void mprinter_print()
{
	dma3_cpy32(&SCR_ENTRY->entry[ETileMapPrinter], 
		mprinter_textEntry, SIZE_IN_WORDS(SIZE_MAP_BLOCK));
}