#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageKankandara.h"

const SpriteLayer kankandara_wait_layerSet0[] = {
    {kankandara_bottom_image0,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};

const SpriteLayerSet kankandara_wait_layerSet[] = {
    {kankandara_wait_layerSet0,5,2},
};

const SpriteSet kankandara_wait = {kankandara_wait_layerSet,1};
