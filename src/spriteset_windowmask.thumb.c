#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageWindowMask.h"

const SpriteLayer windowmask_layerSet0[] = {
    {windowmask_image0,0,0,SQUARE,LARGE,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet windowmask_layerSet[] = {
    {windowmask_layerSet0,5,1},
};

const SpriteSet windowmask = {windowmask_layerSet,1};
