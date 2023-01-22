#include <stdlib.h>
#include <stdbool.h>
#include "GBATypes.h"
#include "GBAObject.h"
#include "GBAVideo.h"
#include "GBADMA.h"
#include "GBACharacterActionEvent.h"
#include "UtilCommonValues.h"
#include "SpriteSetKankandara.h"
#include "ImageKankandara.h"
#include "ManagerVram.h"
#include "ManagerSound.h"
#include "ManagerCharacterActionEvents.h"
#include "CharacterKankandara.h"
#include "CharacterAlisa.h"
#include "CharacterCommon.h"
#include "MapCommon.h"
#include "GBAMap.h"
#include "GBACharacterType.h"

#define KANKANDARA_LENGTH 16
#define KANKANDARA_WIDTH 16
#define KANKANDARA_HEIGHT 24

#define KANKANDARA_SCRCNVRTWIDTH 16
#define KANKANDARA_SCRCNVRTHEIGHT 26

#define KANKANDARA_SCREENDISPLAYOFFSET_X 10
#define KANKANDARA_SCREENDISPLAYOFFSET_Y 28

#define KANKANDARA_PAL_CNT 1

const u8 kankandara_scrConversionMeasurements[EScrCnvrtMeasureCount] = {
	KANKANDARA_SCRCNVRTWIDTH,
	KANKANDARA_SCRCNVRTHEIGHT
};

const u8 kankandara_boundingBoxMeasurements[EBBCnvrtMeasurementCount] = {
	KANKANDARA_LENGTH,
	KANKANDARA_WIDTH,
	KANKANDARA_HEIGHT,
};

void kankandara_controller(CharacterAttr* character);
void kankandara_crawlController(CharacterAttr* character);
void kankandara_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
int kankandara_setPosition(CharacterAttr* character, OBJ_ATTR *oamBuf, 
	const Position *scr_pos, const ScreenDimension *scr_dim);
void kankandara_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox);
void kankandara_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter);
void kankandara_checkMapCollision(const CharacterAttr* character, const MapInfo* mapInfo);	
void kankandara_checkActionEventCollision(CharacterAttr *character, CharacterActionCollection *actionEvents);
void kankandara_actionWait(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void kankandara_actionDissappear(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);
void kankandara_actionCrawl(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection);

extern const Sound soundeffect_slither;
extern const Sound soundeffect_kankandarascream;

const CharFuncAction kankandara_actions[] = {
	&kankandara_actionWait,
	&kankandara_actionDissappear,
	&kankandara_actionCrawl
};

#define DISTANCETURNAROUND 80
const OffsetPoints kankandara_collision_offsetValues[5] = {
    {15, 0},{15, 10},{15, 20},{0, -10}, {0, -20}
};


void kankandara_init(CharacterAttr* kankandara, ControlTypePool* controlPool) {	
	CharacterAIControl *charControl = mchar_getControlType(controlPool);
	//use library to get id
	kankandara->id = 0;
	//use enum of character type
	kankandara->type = KANKANDARA;
	
	kankandara->spriteDisplay.baseImageId = sprite_vram_findId();
	kankandara->spriteDisplay.imageUpdateStatus = EUpdate;
	kankandara->spriteDisplay.basePalleteId = sprite_palette_findId(KANKANDARA, KANKANDARA_PAL_CNT);
	
	sprite_palette_copy32_ID(kankandara_crawl_pal, kankandara->spriteDisplay.basePalleteId);
	    	
	commonCharacterInit(kankandara, EKankandaraInitialize, EKankandaraWait, EDown);
	commonCharacterSetPosition(kankandara, 0, 0, 0, EDown);
	kankandara->controller = &kankandara_controller;
	kankandara->doAction = &kankandara_doAction;
	kankandara->setPosition = &kankandara_setPosition;
	kankandara->getBounds = &kankandara_getBoundingBoxStanding;
	kankandara->checkCollision = &kankandara_checkCollision;
	kankandara->checkMapCollision = &kankandara_checkMapCollision;
	kankandara->checkActionCollision = &kankandara_checkActionEventCollision;
	charControl->type = EControlAiType;
	charControl->currentStatus = EKankandaraStatusWaiting;
	charControl->countAction = 0;
	charControl->currentAction = MAXACTIONS;
	charControl->rightBlocked = false;
	charControl->leftBlocked = false;
	charControl->upBlocked = false;
	charControl->downBlocked = false;
	kankandara->free = charControl;
}
void kankandara_crawlInit(CharacterAttr* kankandara, ControlTypePool* controlPool) {
	kankandara_init(kankandara, controlPool);
	kankandara->controller = &kankandara_crawlController;
	
	kankandara->movementCtrl.maxFrames = 220;
	kankandara->movementCtrl.currentFrame = 0;
}
void kankandara_doAction(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	
	if (character->nextAction < EKankandaraActionCount) {
		kankandara_actions[character->nextAction](character, mapInfo, characterCollection, charActionCollection);
	}
}

int kankandara_setPosition(CharacterAttr* character,
	OBJ_ATTR *oamBuf, 
	const Position *scr_pos,
	const ScreenDimension *scr_dim) 
{

	int charStartX, charStartY, charEndX, charEndY;
	
	character->spriteDisplay.baseY = CONVERT_TO_SCRYPOS(character->position.y, 
		scr_pos->y, kankandara_scrConversionMeasurements);
	character->spriteDisplay.baseX = CONVERT_TO_SCRXPOS(character->position.x, 
		scr_pos->x, kankandara_scrConversionMeasurements);
	
	charStartX = CONVERT_2POS(character->position.x) - KANKANDARA_SCREENDISPLAYOFFSET_X;
	charStartY = CONVERT_2POS(character->position.y);
	charEndX = CONVERT_2POS(character->position.x) + KANKANDARA_SCREENDISPLAYOFFSET_X;
	charEndY = CONVERT_2POS(character->position.y) - KANKANDARA_SCREENDISPLAYOFFSET_Y;
	
	if (commonIsInScreen(charStartX, charEndX, charStartY, charEndY, scr_pos, scr_dim)) {
		character->spriteDisplay.imageUpdateStatus = ((!character->spriteDisplay.isInScreen)*EUpdate) + 
		    (character->spriteDisplay.isInScreen*character->spriteDisplay.imageUpdateStatus);
		character->spriteDisplay.isInScreen = true;
		commonSetToOamBuffer(&character->spriteDisplay, oamBuf);
		return character->spriteDisplay.spriteSet->set[character->spriteDisplay.currentAnimationFrame].numberOflayers;
	}
	
	character->spriteDisplay.isInScreen = false;
	return 0;
}

void kankandara_getBoundingBoxStanding(const CharacterAttr* character, 
	int *count, BoundingBox *boundingBox) {
	*count = 1;
	u16 x = CONVERT_TO_BOUNDINGBOX_X(character->position.x, kankandara_boundingBoxMeasurements);
	u16 y = CONVERT_TO_BOUNDINGBOX_Y(character->position.y, kankandara_boundingBoxMeasurements);
	boundingBox->startX = x;
	boundingBox->startY = y;
	boundingBox->endX = x + kankandara_boundingBoxMeasurements[EBBCnvrtLength];
	boundingBox->endY = y + kankandara_boundingBoxMeasurements[EBBCnvrtWidth];
	//boundingBox->height = kankandara_boundingBoxMeasurements[EBBCnvrtHeight];
	boundingBox->direction = character->direction;
	boundingBox->isMoving = false;
	boundingBox->isMovable = false;
}

void kankandara_checkCollision(const CharacterAttr* character, bool isOtherCharBelow,
	bool *checkNext, const CharacterAttr* otherCharacter) {
	
	*checkNext = false;
	/*int count;
	BoundingBox charBoundingBox, otherCharBoundingBox;
	character->getBounds(character, &count, &charBoundingBox);
	otherCharacter->getBounds(otherCharacter, &count, &otherCharBoundingBox);
	 
	*checkNext = common_checkNext(isOtherCharBelow, &charBoundingBox, &otherCharBoundingBox);
	if (!*checkNext) {
		return;
	}*/
}

void kankandara_checkMapCollision(const CharacterAttr* character, const MapInfo* mapInfo) {
	commonCharacterMapEdgeCheck(character, mapInfo);
}

void kankandara_checkActionEventCollision(CharacterAttr *character, CharacterActionCollection *actionEvents) {
}

void kankandara_actionWait(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection){
	
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(character) == EUpdate) {
		character->spriteDisplay.currentAnimationFrame = 0;
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->delta.x = 0;
	character->delta.y = 0;
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->movementCtrl.maxFrames = 0;
	character->movementCtrl.currentFrame = 0;
		
	character->spriteDisplay.spriteSet = &kankandara_wait;
	
	boundingBox.startX = CONVERT_2POS(character->position.x) - 32;
	boundingBox.endX = CONVERT_2POS(character->position.x) + 32;
	boundingBox.startY = CONVERT_2POS(character->position.y) + 32;
	boundingBox.endY = CONVERT_2POS(character->position.y) + 80;
	charControl->target = *commonFindCharTypeInBoundingBox(characterCollection, &boundingBox, 
		STARTPLAYABLECHARTYPE, ENDPLAYABLECHARACTERTYPE);
	
	//mprinter_printf("%d %d %d ");
	if (commonIsFoundPosition(&charControl->target)) {
//		mprinter_printf("FOUND TARGET");
		charControl->currentStatus = EKankandaraStatusDissappear;
	}
}

void kankandara_actionDissappear(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection){
	
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(character) == EUpdate) {
		character->spriteDisplay.currentAnimationFrame = 0;
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	character->delta.x = 0;
	character->delta.y = 0;
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->movementCtrl.maxFrames = 0;
	character->movementCtrl.currentFrame = 0;
	
	character->spriteDisplay.spriteSet = &kankandara;
}

void kankandara_actionCrawl(CharacterAttr* character, const MapInfo *mapInfo, 
    const CharacterCollection *characterCollection, CharacterActionCollection *charActionCollection) {
	
	CharacterAIControl *charControl = (CharacterAIControl*)character->free;
	BoundingBox boundingBox;
	
	charControl->currentStatus = EKankandaraStatusNormal;
	character->spriteDisplay.imageUpdateStatus = ENoUpdate;
	character->spriteDisplay.palleteUpdateStatus = ENoUpdate;
	if (commonInitializeAction(character) == EUpdate) {
		character->spriteDisplay.currentAnimationFrame = 0;
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	if (commonUpdateAnimation(character) == EUpdate) {
		character->spriteDisplay.imageUpdateStatus = EUpdate;
		character->spriteDisplay.palleteUpdateStatus = EUpdate;
	}
	
	bool isMovingLeft = (character->nextDirection == ELeft);
	character->delta.x = CONVERT_2MOVE(isMovingLeft*(-1) + !isMovingLeft*1);
	character->delta.y = 0;
	character->position.x += character->delta.x;
	character->action = character->nextAction;
	character->direction = character->nextDirection;
	
	character->movementCtrl.maxFrames = 45;
	++character->movementCtrl.currentFrame;
	
	character->spriteDisplay.spriteSet = isMovingLeft ? &kankandara_crawl_left : &kankandara_crawl_right;
	
	Position collisionPoints[5];
	int attackVal = 1, countPoints = 5, offSetDirection = (isMovingLeft*(-1) + !isMovingLeft*(1));
	 
	collisionPoints[0].x = CONVERT_2POS(character->position.x) + kankandara_collision_offsetValues[0].x*offSetDirection;
	collisionPoints[0].y = CONVERT_2POS(character->position.y) + kankandara_collision_offsetValues[0].y;
	collisionPoints[1].x = CONVERT_2POS(character->position.x) + kankandara_collision_offsetValues[1].x*offSetDirection;
	collisionPoints[1].y = CONVERT_2POS(character->position.y) + kankandara_collision_offsetValues[1].y;
	collisionPoints[2].x = CONVERT_2POS(character->position.x) + kankandara_collision_offsetValues[2].x*offSetDirection;
	collisionPoints[2].y = CONVERT_2POS(character->position.y) + kankandara_collision_offsetValues[2].y;	
	collisionPoints[3].x = CONVERT_2POS(character->position.x) + kankandara_collision_offsetValues[3].x*offSetDirection;
	collisionPoints[3].y = CONVERT_2POS(character->position.y) + kankandara_collision_offsetValues[3].y;	
	collisionPoints[4].x = CONVERT_2POS(character->position.x) + kankandara_collision_offsetValues[4].x*offSetDirection;
	collisionPoints[4].y = CONVERT_2POS(character->position.y) + kankandara_collision_offsetValues[4].y;	

	mchar_actione_add(charActionCollection, EActionAttack, attackVal, countPoints, &collisionPoints);
	
	CharacterAttr *targetCharacter = mchar_findCharacterType(characterCollection, ALISA);
	
	 if (targetCharacter) {
	    //mprinter_printf("FOUND TARGET\n");
		charControl->target = targetCharacter->position;
		int distance = CONVERT_2POS(charControl->target.x) - CONVERT_2POS(character->position.x), rightPhaseDelay, leftPhaseDelay;
	
		if (character->movementCtrl.currentFrame >= character->movementCtrl.maxFrames) {
			character->movementCtrl.currentFrame = 0;
			//rightPhaseDelay = 6*(distance < 0);
			//leftPhaseDelay = 6*(distance > 0);
			//distance = distance >> 4;
			//if (distance < 15 && distance > -15) {
				//msound_setChannel3d(&soundeffect_slither, false, rightPhaseDelay, leftPhaseDelay, distance);
				msound_setChannelStereo(&soundeffect_slither, false, distance);
			//}
		}
		
		int checkIfBehindDistance = DISTANCETURNAROUND + 1;
		if (isMovingLeft) {
			checkIfBehindDistance = CONVERT_2POS(charControl->target.x) - CONVERT_2POS(character->position.x);
		} else {
			checkIfBehindDistance = CONVERT_2POS(character->position.x) - CONVERT_2POS(charControl->target.x);
		}
		int distY = CONVERT_2POS(character->position.y) - CONVERT_2POS(charControl->target.y);
		if (checkIfBehindDistance < DISTANCETURNAROUND && checkIfBehindDistance >= 0 && distY <= 20 && distY >= -20) {
			charControl->currentStatus = EKankandaraStatusTurnAround;
			character->movementCtrl.currentFrame = 0;
			//rightPhaseDelay = 6*(distance < 0);
			//leftPhaseDelay = 6*(distance > 0);
			//distance = distance >> 4;
			//mprinter_printf("distance %d\n", distance);
			CharacterPlayerControl *targetControl = (CharacterAIControl*)targetCharacter->free;
			if (targetControl->currentStatus != EAlisaStatusStunned) {
				msound_setChannelStereo(&soundeffect_kankandarascream, false, distance);
				//msound_setChannel3d(&soundeffect_kankandarascream, false, rightPhaseDelay, leftPhaseDelay, distance);
			}
		}
    }
	
	
}

