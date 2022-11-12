#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageKankandara.h"

const SpriteLayer kankandara_layerSet0[] = {
    {kankandara_bottom_image0,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet1[] = {
    {kankandara_bottom_image1,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet2[] = {
    {kankandara_bottom_image2,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet3[] = {
    {kankandara_bottom_image3,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image0,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet4[] = {
    {kankandara_bottom_image4,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image1,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet5[] = {
    {kankandara_bottom_image5,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image2,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet6[] = {
    {kankandara_bottom_image6,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image3,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet7[] = {
    {kankandara_bottom_image7,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image4,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};
const SpriteLayer kankandara_layerSet8[] = {
    {kankandara_bottom_image8,0,8,TALL,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_top_image5,0,0,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,8,0}};

const SpriteLayerSet kankandara_layerSet[] = {
    {kankandara_layerSet0,8,2},
    {kankandara_layerSet1,8,2},
    {kankandara_layerSet2,8,2},
    {kankandara_layerSet3,8,2},
    {kankandara_layerSet4,5,2},
    {kankandara_layerSet5,5,2},
    {kankandara_layerSet6,5,2},
    {kankandara_layerSet7,5,2},
    {kankandara_layerSet8,30,2},
};

const SpriteSet kankandara = {kankandara_layerSet,9};
