#include "GBAObject.h"
#include "GBAKey.h"
#include "CharacterKankandara.h"
#include  <stdbool.h>
#include  <stdlib.h>

void kankandara_dissappearController(CharacterAttr* character);

void kankandara_controller(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int i;
	EDirections goDirection;
	
	//mprinter_printf("KANAKANDARA\n");
	if (charControl->currentStatus == EKankandaraStatusDissappear) {
		character->controller = &kankandara_dissappearController; 
		kankandara_dissappearController(character);
		return;
	}
	character->nextAction = EKankandaraWait;
	character->nextDirection = EDown;
}

void kankandara_dissappearController(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	int i;
	EDirections goDirection;
	
	//mprinter_printf("KANAKANDARA\n");
	character->nextAction = EKankandaraDissappaer;
	character->nextDirection = EDown;
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
	
	if (isLastFrame) {
		commonRemoveCharacter(character);
	}
}

void kankandara_crawlController(CharacterAttr* character) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	int nextScreenFrame, nextAnimationFrame;
	bool isLastFrame = false;
	int i;
	EDirections goDirection;
	
	if (character->nextDirection != ELeft && character->nextDirection != ERight) {
		character->nextDirection = ELeft;
	}
	//mprinter_printf("KANAKANDARA\n");
	character->nextAction = EKankandaraCrawl;
	if (character->direction== ELeft && charControl->leftBlocked) {
		character->nextDirection = ERight;
		charControl->leftBlocked = false;
	} else if (character->direction == ERight && charControl->rightBlocked){
		character->nextDirection = ELeft;
		charControl->rightBlocked = false;
	}
	
	if (charControl->currentStatus == EKankandaraStatusTurnAround){
		charControl->currentStatus = EKankandaraStatusNormal;
		if (character->direction == ELeft){
			character->nextDirection = ERight;
		} else {
			character->nextDirection = ELeft;
		}
	}
	
	commonGetNextFrame(character, &nextScreenFrame, &nextAnimationFrame, &isLastFrame);
}

void kankandara_setCharacter(CharacterAttr* character) {
    character->controller = &kankandara_controller; 
}

void kankandara_setCrawlCharacter(CharacterAttr* character) {
    character->controller = &kankandara_crawlController; 
}
