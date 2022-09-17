#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageBoy.h"
const SpriteLayer character_walk_left_layerSet0[] = {
    {character_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer character_walk_left_layerSet1[] = {
    {character_image2,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer character_walk_left_layerSet2[] = {
    {character_image0,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};
const SpriteLayer character_walk_left_layerSet3[] = {
    {character_image3,0,0,TALL,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0}};

const SpriteLayerSet character_walk_left_layerSet[] = {
    {character_walk_left_layerSet0,10,1},
    {character_walk_left_layerSet1,10,1},
    {character_walk_left_layerSet2,10,1},
    {character_walk_left_layerSet3,10,1},
};

const SpriteSet character_walk_left = {character_walk_left_layerSet,4};
