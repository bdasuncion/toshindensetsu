#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageKankandara.h"

const SpriteLayer kankandara_crawl_left_layerSet0[] = {
    {kankandara_tail_crawl_image0,32,24,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image0,0,0,SQUARE,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_left_layerSet1[] = {
    {kankandara_tail_crawl_image1,32,24,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image1,0,0,SQUARE,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_left_layerSet2[] = {
    {kankandara_tail_crawl_image2,32,24,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image2,0,0,SQUARE,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_left_layerSet3[] = {
    {kankandara_tail_crawl_image3,32,24,WIDE,SMALL_A,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image3,0,0,SQUARE,MEDIUM,DO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet kankandara_crawl_left_layerSet[] = {
    {kankandara_crawl_left_layerSet0,8,2},
    {kankandara_crawl_left_layerSet1,8,2},
    {kankandara_crawl_left_layerSet2,8,2},
    {kankandara_crawl_left_layerSet3,8,2},
};

const SpriteSet kankandara_crawl_left = {kankandara_crawl_left_layerSet,4};
