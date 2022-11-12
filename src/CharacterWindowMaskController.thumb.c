#include "GBAObject.h"
#include "GBACharacter.h"
#include "CharacterWindowMask.h"
#include  <stdbool.h>
#include  <stdlib.h>

void windowmask_controller(CharacterAttr* character);

void windowmask_setCharacter(CharacterAttr* character) {
	character->controller = &windowmask_controller; 
}

void windowmask_controller(CharacterAttr* character) {
    character->nextAction = EWindowMaskFollow;
}