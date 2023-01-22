#include <stdlib.h>
#include "GBAObject.h"
#include "GBACharacter.h"
#include "GBACharacterType.h"

void werewolf_init(CharacterAttr *character, ControlTypePool* controlPool);
void werewolf_setCharacter(CharacterAttr *character);
void ghostlyHand_init(CharacterAttr *character, ControlTypePool* controlPool);
void ghostMan_init(CharacterAttr *character, ControlTypePool* controlPool);
void ghostlyHand_setCharacter(CharacterAttr *character);
void ghostMan_setCharacter(CharacterAttr *character);
void crow_init(CharacterAttr *character, ControlTypePool* controlPool);
void crow_setCharacter(CharacterAttr *character);
void zombie_init(CharacterAttr* character, ControlTypePool* controlPool);
void zombie_setCharacter(CharacterAttr* character);
void kankandara_init(CharacterAttr* character, ControlTypePool* controlPool);
void kankandara_setCharacter(CharacterAttr* character);
void kankandara_crawlInit(CharacterAttr* character, ControlTypePool* controlPool);
void kankandara_setCrawlCharacter(CharacterAttr* character);
void windowmask_init(CharacterAttr* character, ControlTypePool* controlPool);
void windowmask_setCharacter(CharacterAttr* character);

const FuncCharacterInit chacterInit[] = { NULL, NULL, /*&ghostlyHand_init, &ghostMan_init, NULL, &werewolf_init, &crow_init, &zombie_init,*/
	&kankandara_init, &kankandara_crawlInit, &windowmask_init};
const FuncCharacterSet characterSet[] = { NULL, NULL, /*&ghostlyHand_setCharacter, &ghostMan_setCharacter, NULL, 
	&werewolf_setCharacter,  &crow_setCharacter, &zombie_setCharacter, */&kankandara_setCharacter, &kankandara_setCrawlCharacter,
	&windowmask_setCharacter};