#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageBoy.h"
const SpriteLayer character_stand_left_layerSet0[] = {
    {character_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet character_stand_left_layerSet[] = {
    {character_stand_left_layerSet0,5,1},
};

const SpriteSet character_stand_left = {character_stand_left_layerSet,1};
