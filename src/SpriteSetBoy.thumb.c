#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"

const SpriteSet character_walk_left;
const SpriteSet character_walk_right;

const SpriteSet *boyWalkSet[] = {&character_walk_right, &character_walk_right, &character_walk_right, &character_walk_right,
    &character_walk_left, &character_walk_left, &character_walk_left, &character_walk_left};
	
const SpriteSet character_stand_left;
const SpriteSet character_stand_right;

const SpriteSet *boyStandSet[] = {&character_stand_right, &character_stand_right, &character_stand_right, &character_stand_right,
    &character_stand_left, &character_stand_left, &character_stand_left, &character_stand_left};