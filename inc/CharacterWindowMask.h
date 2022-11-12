#ifndef CHARACTER_WINDWOMASK
#define CHARACTER_WINDWOMASK

#include "GBAObject.h"
#include "GBACharacter.h"

typedef enum WindowMaskAction
{
	EWindowMaskInitialize = -1,
	EWindowMaskFollow,
	EWindowMaskActionCount
} WindowMaskAction;

typedef enum WindowMaskStatus
{
	EWindowMaskStatusNormal
} WindowMaskStatus;


void windowmask_init(CharacterAttr* character, ControlTypePool* controlPool);
void windowmask_setCharacter(CharacterAttr* character);
void windowmask_controller(CharacterAttr* character);
#endif