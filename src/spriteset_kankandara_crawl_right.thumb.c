#include "GBATypes.h"
#include "GBAObject.h"
#include "GBACharacter.h"
#include "ImageKankandara.h"

const SpriteLayer kankandara_crawl_right_layerSet0[] = {
    {kankandara_tail_crawl_image0,-16,24,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image0,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_right_layerSet1[] = {
    {kankandara_tail_crawl_image1,-16,24,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image1,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_right_layerSet2[] = {
    {kankandara_tail_crawl_image2,-16,24,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image2,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};
const SpriteLayer kankandara_crawl_right_layerSet3[] = {
    {kankandara_tail_crawl_image3,-16,24,WIDE,SMALL_A,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,0,0},
    {kankandara_crawl_image3,0,0,SQUARE,MEDIUM,NO_HFLIP,NO_VFLIP,LZSS_COMPRESSION,2,0}};

const SpriteLayerSet kankandara_crawl_right_layerSet[] = {
    {kankandara_crawl_right_layerSet0,8,2},
    {kankandara_crawl_right_layerSet1,8,2},
    {kankandara_crawl_right_layerSet2,8,2},
    {kankandara_crawl_right_layerSet3,8,2},
};

const SpriteSet kankandara_crawl_right = {kankandara_crawl_right_layerSet,4};
