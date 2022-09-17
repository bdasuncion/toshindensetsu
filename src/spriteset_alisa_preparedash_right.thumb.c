#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageAlisa.h"

const SpriteLayer alisa_preparedash_right_layerSet0[] = {
    {sword_side_image0,-8,16,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,1},
    {alisa_dashbackwardwithsword_side_image0,0,0,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet alisa_preparedash_right_layerSet[] = {
    {alisa_preparedash_right_layerSet0,10,2},
};

const SpriteSet alisa_preparedash_right = {alisa_preparedash_right_layerSet,1};
