#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageBoy.h"

const SpriteLayer character_die_right_layerSet0[] = {
    {character_die_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet character_die_right_layerSet[] = {
    {character_die_right_layerSet0,60,1},
};

const SpriteSet character_die_right = {character_die_right_layerSet,1};
