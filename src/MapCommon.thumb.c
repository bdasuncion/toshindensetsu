#include <stdlib.h>
#include  <stdarg.h>
#include  <stdbool.h>
#include "GBAObject.h"
#include "GBAMap.h"
#include "GBATransparency.h"
#include "GBACharacterActionEvent.h"

#include "ManagerScrDisplay.h"
#include "ManagerBG.h"
#include "ManagerVram.h"

#include "CharacterAlisa.h"
#include "CharacterNameless.h"

#define DEFAULT_SCREEN_BOUNDING_BOX 0
#define DELAY 2
#define BLENDVAL_MAX 16

int blendVal = 0;
int current = 0;
bool update = true;

//extern const MapInfo mapTest;

void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo);
void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo);
void mapCommon_defaultEffect(void *screenAttribute, void *characterCollection, MapInfo *mapInfo);

void map_nofunction(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo) {
}

void mapCommon_transferToMap(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, 
        MapInfo *mapInfo, ControlTypePool* controlPool, CharacterActionCollection *charActionCollection,
		Track *track) {

	
    CharacterAttr *alisa;
	EventTransfer *eventTransfer = mapInfo->transferTo;
	
	if (mapInfo->onExitMap) {
		mapInfo->onExitMap(screenAttribute, characterCollection, 
        mapInfo, controlPool, charActionCollection, track);
	}
	
	sprite_vram_init();
	sprite_palette_init();
	mchar_reinit(characterCollection, &alisa);
	
	//TODO change this
	alisa_init(alisa, controlPool);
	//nameless_init(alisa);
    commonCharacterSetPosition(alisa, 
	   eventTransfer->transferToX, eventTransfer->transferToY, 0, eventTransfer->directionOnTransfer);
	alisa->doAction(alisa, mapInfo, characterCollection, charActionCollection);
	
	*mapInfo = *((MapInfo*)eventTransfer->mapInfo);
	mscr_initCharMoveRef(screenAttribute, mapInfo,
		&alisa->position, DEFAULT_SCREEN_BOUNDING_BOX);
	
	//*mapInfo = *((MapInfo*)eventTransfer->mapInfo);
	mapInfo->transferTo = eventTransfer;
	
	if (mapInfo->music && track->musicTrack != mapInfo->music) {
		track->musicTrack = mapInfo->music;
		track->trackIndex = 0;
		track->framesPassed = 0;
	} else if (!mapInfo->music) {
		track->musicTrack = NULL;
		track->trackIndex = 0;
		track->framesPassed = 0;
	}
	
	if (mapInfo->onInitMap) {
		mapInfo->onInitMap(screenAttribute, characterCollection, 
        mapInfo, controlPool, charActionCollection, track);
	}
	
	mbg_init(screenAttribute, mapInfo, characterCollection, controlPool);
	
	mapInfo->mapFunction = &returnToScreen;
	
	mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
}

void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo) {
    ++current;
	if (current >= DELAY) {
	    current = 0;
        ++blendVal;
	}
    if (blendVal >= BLENDVAL_MAX) {
		mapInfo->mapFunction = &mapCommon_transferToMap;
	}
    blendBlack(blendVal);
}

void returnToScreen(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo) {
    
	++current;
	if (current >= DELAY) {
	    current = 0;
		--blendVal;
	}
	
	if (blendVal <= 0) {
		//TODO transfer mapfunc here
		mapInfo->mapFunction = ((MapInfo*)mapInfo->transferTo->mapInfo)->mapFunction;
	    mapInfo->transferTo = NULL;
		
	}
	blendBlack(blendVal);
}

void mapCommon_defaultEffect(void *screenAttribute, void *characterCollection, MapInfo *mapInfo) {
}

void mapCommon_returnToNormal(void *screenAttribute, void *characterCollection, MapInfo *mapInfo) {
    blendBlack(0);
	++mapInfo->screenEffect.currentFrame;
	if (mapInfo->screenEffect.currentFrame >= mapInfo->screenEffect.durationFrames) {
	    mapInfo->screenEffect.durationFrames = 3;
		mapInfo->screenEffect.currentFrame = 0;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	}
}

void mapCommon_goDark(void *screenAttribute, void *characterCollection, MapInfo *mapInfo) {
    blendBlack(BLENDVAL_MAX);
	++mapInfo->screenEffect.currentFrame;
	if (mapInfo->screenEffect.currentFrame >= mapInfo->screenEffect.durationFrames) {
	    mapInfo->screenEffect.durationFrames = 5;
		mapInfo->screenEffect.currentFrame = 0;
		mapInfo->screenEffect.processScreenEffect = &mapCommon_returnToNormal;
	}
}

void mapCommon_initFlashScreen(MapInfo *mapInfo) {
    mapInfo->screenEffect.durationFrames = 5;
    mapInfo->screenEffect.currentFrame = 0;
    mapInfo->screenEffect.processScreenEffect = &mapCommon_goDark;
}

