#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "GBACharacterType.h"
#include "CharacterWindowMask.h"
#include "ImageWindowMask.h"

#define WINDOWMASK_PAL_CNT 1

#define WINDOWMASK_SCRCNVRTWIDTH 64
#define WINDOWMASK_SCRCNVRTHEIGHT 40

const u8 windowmask_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	WINDOWMASK_SCRCNVRTWIDTH,
	WINDOWMASK_SCRCNVRTHEIGHT
};
void windowmask_getBounds(const CharacterAttr* alisa, 
	int *count, CharBoundingBox *boundingBox);
	
void windowmask_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);

void windowmask_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox);

void windowmask_checkMapCollision(CharacterAttr* alisa, const MapInfo *mapInfo);

void windowmask_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);

int windowmask_setPosition(CharacterAttr* alisa,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim);

void windowmask_checkActionEventCollision(CharacterAttr *alisa, CharacterActionCollection *actionEvents);
void windowmask_controller(CharacterAttr* character);

void windowmask_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection);
	
Position* findCharWindowMaskType(CharacterCollection *characterCollection, int fromType, int toType);

extern const SpriteSet windowmask;

void windowmask_init(CharacterAttr* character, ControlTypePool* controlPool) {
//use library to get id
	character->id = 0;
	//use enum of character type
	character->type = WINDOWMASK;
	
	character->spriteDisplay.baseImageId = sprite_vram_findId();
	character->spriteDisplay.imageUpdateStatus = EUpdate;
	character->spriteDisplay.basePalleteId = sprite_palette_findId(WINDOWMASK, WINDOWMASK_PAL_CNT);
	//if (1) {
	    sprite_palette_copy32_ID(windowmask_pal, character->spriteDisplay.basePalleteId);
	    //sprite_palette_copy32_ID(windowmask_pal, character->spriteDisplay.basePalleteId + 1);
	//}
	//character->spriteDisplay.palleteUpdateStatus = EUpdate;	
	
	
	commonCharacterInit(character, EWindowMaskInitialize, EWindowMaskFollow, EDown);
	commonCharacterSetPosition(character, 0, 0, 0, EDown);
	character->controller = &windowmask_controller;
	character->doAction = &windowmask_doAction;
	character->setPosition = &windowmask_setPosition;
	character->getBounds = &windowmask_getBoundingBoxStanding;
	character->checkCollision = &windowmask_checkCollision;
	character->checkMapCollision = &windowmask_checkMapCollision;
	character->checkActionCollision = &windowmask_checkActionEventCollision;
	
	CharacterPlayerControl *charControl = mchar_getControlType(controlPool);
	charControl->type = EControlAiType;
	character->free = charControl;
	//alisa->free = NULL;
	/*CharacterPlayerControl *charControl = mchar_getControlType(controlPool);
	charControl->type = EControlControlType;
	charControl->currentStatus = EAlisaStatusNormal;
	charControl->buttonB_PressInterval = 0;
	charControl->buttonA_PressInterval = 0;
	charControl->buttonL_Ready = true;
	charControl->buttonR_Ready = true;
	charControl->controlMap.buttonB = &alisa_slashController;
	charControl->controlMap.buttonA = &alisa_prepareDashController;
	charControl->controlMap.buttonL = NULL;
	charControl->controlMap.buttonR = NULL;
	alisa->free = charControl;
	alisa->stats.maxLife = 10;
	alisa->stats.currentLife = 10;*/
}

void windowmask_actionFollow(CharacterAttr* character,
	const MapInfo *mapInfo, CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection) {
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	charControl->target = *findCharWindowMaskType(characterCollection,
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
		
	character->spriteDisplay.spriteSet = &windowmask;
}

void windowmask_doAction(CharacterAttr* character,
	const MapInfo *mapInfo, CharacterCollection *characterCollection, 
	CharacterActionCollection *charActionCollection) {
	windowmask_actionFollow(character, mapInfo, characterCollection, charActionCollection);
}

int windowmask_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(charControl->target.y, 
		scr_pos->y, windowmask_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(charControl->target.x, 
		scr_pos->x, windowmask_scrConversionMeasurements);
	
	//TODO add in screen check
	commonSetToOamBufferAsObjWindow(&character->spriteDisplay, oamBuf);
	character->spriteDisplay.isInScreen = true;
	
    return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers;
}

void windowmask_getBoundingBoxMoving(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
	/**count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = alisa->direction;
	boundingBox->isMoving = true;
	boundingBox->isMovable = false;*/
}

void windowmask_getBoundingBoxStanding(const CharacterAttr* alisa, 
	int *count, BoundingBox *boundingBox) {
	/**count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(alisa->position.x, alisa_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(alisa->position.y, alisa_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + alisa_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + alisa_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = alisa_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = alisa->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;*/
}

void windowmask_checkMapCollision(CharacterAttr* alisa, const MapInfo* mapInfo) {
    /*commonCharacterMapEdgeCheck(alisa, mapInfo);
	alisa_mapCollision[alisa->direction](alisa, mapInfo, 
	    alisa_mapCollisionReactions[alisa->direction]);*/
}

void windowmask_checkCollision(CharacterAttr* alisa, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	/*int count;
	BoundingBox alisaBoundingBox, otherCharBoundingBox;
	alisa->getBounds(alisa, &count, &alisaBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	
	*checkNext = common_checkNext(isOtherCharBelow, &alisaBoundingBox, &otherCharBoundingBox);
	if (!*checkNext) {
		return;
	}
	
	alisa_collisionReactions[alisaBoundingBox.isMoving][alisa->direction]
	    (alisa, &alisaBoundingBox, &otherCharBoundingBox);*/
}

void windowmask_checkActionEventCollision(CharacterAttr *alisa, CharacterActionCollection *actionEvents) {
    /*int i, j, count;
	BoundingBox charBoundingBox;
	bool isHit = false;
	CharacterPlayerControl *charControl = (CharacterAIControl*)alisa->free;
	if (alisa->stats.currentStatus == EStatusNoActionCollision) {
		return;
	}
	
	alisa->getBounds(alisa, &count, &charBoundingBox);
	for (i = 0; i < actionEvents->count; ++i) {
		CharacterActionEvent *charActionEvent = &actionEvents->currentActions[i];

		for (j = 0; j < charActionEvent->count; ++j) {
			isHit |= commonPositionInBounds(&charActionEvent->collisionPoints[j], &charBoundingBox);
		}
		if (isHit) {
			alisa->stats.currentLife -= 1;
			charControl->currentStatus = EAlisaStatusStunned;
			if (alisa->stats.currentLife <= 0) {
				//gameover
			}
			//break;
		}
	}*/
}

Position* findCharWindowMaskType(CharacterCollection *characterCollection, int fromType, int toType) {
	int i;
	for (i = 0; i < characterCollection->currentSize; ++i) {
		if (characterCollection->characters[i]->type >= fromType && 
			characterCollection->characters[i]->type <= toType) {
				return &characterCollection->characters[i]->position;
		}
	}
	return NULL;
}