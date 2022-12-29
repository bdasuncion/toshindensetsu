#include <stdlib.h>
#include "GBAObject.h"
#include "UtilCommonValues.h"
#include "ManagerOAM.h"
#include "ManagerSound.h"
#include "ManagerScrDisplay.h"
#include "ManagerGame.h"
#include "ManagerVram.h"
#include "ManagerCharacterActionEvents.h"
#include "UpdategameStatus.h"
#include "MapCommon.h"

#include "GBATransparency.h"

//TODO move this somewhere else
//#include "CharacterAlisa.h"
//#include "CharacterWerewolf.h"
#include "CharacterCommon.h"

#define DEFAULT_SCREEN_BOUNDING_BOX 0

#define MAX_CHARCOUNT 15
#define MAX_CHARACTIONEVENT 20

//extern const char always[1888512];
//extern const unsigned char sampleSound[6850];
//extern const unsigned char slash[2359];
//extern const unsigned char minamohana[4144320];
//extern const Sound music_minamohana;
//extern const Sound soundeffect_slash;

//TODO: Temporay only
extern const MapInfo mapTest;
extern const MapInfo map_nobinobi_cabin;
extern const MapInfo map_night_street;
extern const MapInfo mapforest;
extern const Sound music_minamohana;
extern const MapInfo mapsnowfield;
extern const MapInfo mapforest;
extern const MapInfo map_graveyard;
extern const EventTransfer transfer_mapforest[];
extern const EventTransfer startat_map_graveyard[];

void fadeToBlack(ScreenAttr *screenAttribute, CharacterCollection *characterCollection, MapInfo *mapInfo);
void mapCommon_goDark(void *screenAttribute, void *characterCollection, MapInfo *mapInfo);

inline void waitForVBlank() {
	asm("swi 0x05");
}

void gameloop(MapInfo *mapInfo, CharacterCollection *characterCollection,
 OAMCollection *oamCollection, ControlTypePool *controlPool, ScreenAttr *screenAttribute, 
    CharacterActionCollection *charActionCollection) {
	
	//mapInfo->transferTo =  &mapInfo->tranfers[0];
	//mapInfo->mapFunction = &fadeToBlack;
	//mapInfo->screenEffect.processScreenEffect = &mapCommon_goDark;
	
	while(1) {	
		mprinter_clear();

        mchar_actione_reinit(charActionCollection);
		//quicksort_oam();
		
		if (!mapInfo->transferTo) {
		    mchar_action(characterCollection);
		    mchar_resolveAction(characterCollection, mapInfo, charActionCollection);
		}
		/*mprinter_printf("%d,%d\n", screenAttribute.position.x,
			screenAttribute.position.y);
		mprinter_printf("%d,%d\n", mapInfo.width, mapInfo.height);*/
		
		//screenAttribute.controller(&screenAttribute, 
		//	&mapInfo);
		screenAttribute->controller(screenAttribute, mapInfo);
		
		mchar_setPosition(characterCollection, 
			oamCollection,
			&screenAttribute->position,
			&screenAttribute->dimension);
		
		mchar_setDraw(characterCollection);
		
		moam_setUpdate(oamCollection);
		
		mscr_setDraw(screenAttribute);
		
		if (mapInfo->mapFunction) {
		    mapInfo->mapFunction(screenAttribute, characterCollection, mapInfo, 
			    controlPool, charActionCollection);
		}
		
		mapInfo->screenEffect.processScreenEffect(screenAttribute, characterCollection, 
		    mapInfo, controlPool, charActionCollection);
			
		//msound_mix();
		//msound_mixStereoASMR();
		msound_mixStereo();
		//msound_mixMono();
		
		waitForVBlank();
	}
}

int main() {
	CharacterCollection characterCollection;
	OAMCollection oamCollection;
	ControlTypePool controlPool;
	//MapInfo mapInfo = mapforest;
	//MapInfo mapInfo = mapsnowfield;
	ScreenAttr screenAttribute;
	CharacterActionCollection charActionCollection;
	//MapInfo mapInfo = map_night_street;
	//MapInfo mapInfo = mapTest;
	MapInfo mapInfo = map_graveyard;
	CharacterAttr *alisa;
	
	sprite_vram_init();
	sprite_palette_init();
	
	mapInfo.screenEffect.processScreenEffect = &mapCommon_defaultEffect;
	
	oamCollection.size = 128;
	oamCollection.previousSize = 0;
	oamCollection.data = malloc(sizeof(OBJ_ATTR)*
		oamCollection.size);
	
	mchar_initControlType(&controlPool);
	
	moam_initBuffer(&oamCollection);
	
	mchar_init(&characterCollection, MAX_CHARCOUNT);
	
	mchar_actione_init(&charActionCollection, MAX_CHARACTIONEVENT);
	
	mchar_getPlayerCharacter(&characterCollection, &alisa, &controlPool);
	//commonCharacterSetPosition(alisa, 430, 185, 0, EDown);
	commonCharacterSetPosition(alisa, 24, 96, 0, EDown);
	
	mscr_initCharMoveRef(&screenAttribute, &mapInfo,
		&alisa->position, DEFAULT_SCREEN_BOUNDING_BOX);
	
	//mbg_init(&screenAttribute, &mapInfo, &characterCollection, &controlPool, &charActionCollection);
	//mapInfo.mapFunction = &fadeToBlack;
	mapInfo.transferTo =  &startat_map_graveyard[0];
	//mapInfo.mapFunction(&screenAttribute, &characterCollection, &mapInfo, &controlPool, &charActionCollection);
	mapCommon_transferToMap(&screenAttribute,  &characterCollection, &mapInfo, &controlPool,  &charActionCollection);
	
	mgame_setUpdater(&updateGameStatus);
	//Initalize display for 2 backgrounds and 1-d sprites
	initDisplay2BG();
	
	msound_init();
	msound_setUpStereo();
	//msound_setUpMono();
	//test only should be called somewhere else
	//msound_setChannel(&music_minamohana, true);
	
	mprinter_init();
	gameloop(&mapInfo, &characterCollection, &oamCollection, &controlPool, 
	   &screenAttribute, &charActionCollection);
	
	return 0;
}