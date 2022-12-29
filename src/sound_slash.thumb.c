#include "GBASound.h"

const char slash[] = {  0,10,16,-1,-13,-20,-1,-1,-1,-13,-1,-25,-25,22,-1,-1,-1,-1,-11,-1,-15,-1,-25,-5,-1,
-1,-1,23,21,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-23,-17,-18,-23,
-1,-22,-23,-1,-13,-1,-1,-1,-1,-1,19,23,-1,-1,-1,-15,-1,-1,-1,-17,-12,-1,-17,17,
-1,-25,-1,-1,-1,-12,-5,-23,-1,-25,9,-24,-1,-1,-1,-1,-1,-1,-25,-1,18,-25,-3,-1,
-1,-1,-1,-1,15,-1,-1,-1,-1,-1,24,-21,-1,-25,24,12,-1,-10,-25,-19,-1,-1,24,-1,
20,-1,-1,14,-1,-1,-1,-1,-1,-22,-1,14,-3,19,-1,-1,5,-1,12,-1,-1,-1,-1,-1,
-1,-1,16,-1,-1,-1,8,-1,20,22,-15,24,-23,-1,-1,-1,17,-1,-1,-18,19,-1,19,-1,
13,-1,-1,20,-1,-15,-1,-8,-1,-1,-1,24,-1,-1,24,-1,20,-1,-11,-16,-1,-1,23,-1,
-18,-1,-15,-20,-1,-7,-1,-1,-1,-1,-6,-1,15,16,-21,-1,-1,-1,24,-1,19,24,7,-1,
-1,-1,-16,12,-6,24,-1,-1,24,-1,-9,-9,-1,22,10,-1,-1,-1,18,24,-17,22,-1,-10,
-9,-1,-1,-1,-13,-17,-1,-1,24,16,24,-1,-1,-1,-1,12,-1,-1,-1,-1,-19,-14,-1,16,
-1,-1,8,-1,-1,-1,-1,-1,-1,-1,-1,21,-1,-1,-21,-18,-1,-20,-1,-1,-1,-1,9,-13,
23,-23,-1,-1,17,-1,-1,18,-1,12,24,24,24,21,-1,18,2,-2,-1,-1,-1,-13,4,-19,
-1,-1,12,-17,-24,-23,-1,-1,-17,-18,-1,-1,24,-1,-1,-1,-16,-1,3,-1,-1,-1,-1,-16,
-18,11,-1,-1,-1,-1,6,15,-1,24,-21,-16,-1,-1,-1,-1,-2,-1,-24,-1,-18,-1,6,-1,
-1,22,-15,-1,21,-11,4,-1,-23,22,-1,-1,-1,-1,-24,-1,-12,4,-11,-19,-1,15,-1,-1,
10,-1,-22,-1,-24,-1,-24,-11,-8,-24,14,4,-1,20,-19,-23,-1,-1,-24,-24,-23,-1,-21,-24,
20,-24,-1,-1,-1,22,10,-1,-9,-1,-1,-18,18,-1,-1,11,-1,-1,-1,-1,-1,-1,-10,-1,
-1,-11,-1,-1,-24,-20,-21,-24,-1,20,-12,-1,-24,-1,20,-1,-1,-1,-1,-1,20,16,-1,-1,
-1,-1,-1,7,-16,-18,-22,-1,-1,-1,-1,-1,16,-16,5,-1,6,-1,20,8,-1,-24,-20,-1,
12,-12,-1,-19,-18,-1,-24,-6,-24,-1,-1,-1,-1,19,-21,-1,-24,9,15,22,-19,-1,-1,-1,
-1,20,-1,-1,18,23,-1,-1,-22,-1,-6,-1,-9,5,-1,23,-15,23,-1,-1,-24,-1,12,-1,
-1,-1,-1,-16,-18,-24,-1,-1,-23,-24,20,-1,-1,16,-1,-1,-16,-24,4,-7,-20,-1,-13,-17,
-1,-1,-1,-1,-21,22,20,-20,-1,-1,-23,-1,-1,-1,-1,5,-5,15,-21,18,-18,-1,-18,-1,
-12,23,13,-1,-1,19,-1,-1,-1,15,-1,-1,16,-1,-1,-1,-1,-7,-1,14,-1,12,-1,2,
-1,18,-1,-1,15,-1,-7,-1,-1,-1,5,-19,16,-1,-1,-8,9,-1,-17,-1,-1,20,-1,-11,
23,-21,-11,-1,-1,-1,-1,23,23,-11,-1,23,-1,-1,-1,-1,-11,-23,-1,-1,-1,-1,23,10,
13,-1,23,-20,-1,3,-21,-1,20,3,-1,-19,23,-1,23,12,-9,-1,-1,-14,-1,-1,-1,13,
19,-10,-1,-1,23,-22,-12,-1,20,-4,23,7,-1,-15,22,-15,-16,-1,-1,22,-1,-1,23,-1,
-21,-1,-1,-1,17,-1,19,-1,-1,-1,-1,22,19,-1,-1,23,13,22,-1,23,17,14,23,-22,
23,-1,20,-15,-1,-1,-1,-1,-1,-1,-1,-1,-7,15,-23,-1,-12,-1,-1,19,23,-21,20,14,
-12,23,-1,-7,-1,13,-1,-20,16,-1,-1,-1,-1,-1,-1,-1,-1,-1,23,-1,-1,-1,-10,-12,
-1,-17,-1,7,-1,18,8,-16,1,-1,23,-1,-1,-23,-1,-13,14,-23,17,-16,-1,10,-18,-1,
-4,-1,-1,-1,10,-1,-1,-20,-18,-3,-23,-23,-1,-23,-19,-1,-20,-21,-23,-1,-17,-23,-1,-1,
-1,-3,-1,16,-1,19,-21,-1,-13,-15,22,-1,19,-1,-10,-1,-22,-15,-23,-1,-1,-1,-1,-1,
-19,-1,-1,-1,-1,-1,-10,-9,-23,21,-15,6,-1,13,-17,-1,-5,8,-1,-1,-1,-11,-1,-23,
-1,-18,-1,-22,-4,-1,-23,-1,-22,-1,-1,19,-1,-5,10,-17,7,-1,-23,12,4,-1,13,-1,
-1,-1,-1,22,22,10,22,-1,22,22,14,-1,-5,-18,-1,9,-1,20,19,-1,16,-1,-1,-1,
-1,-18,-1,-1,-1,-1,-12,-12,-3,-1,-1,-1,-1,-1,-15,-1,-1,4,-1,-17,17,-1,-1,-15,
-8,-1,-1,-22,-8,-1,-17,14,-1,-1,-1,21,-4,-1,-1,-1,5,-1,-1,-1,-1,-1,12,-20,
20,5,-1,-1,-1,-1,-1,20,-15,-22,-20,10,-22,9,21,-22,-1,12,-1,-1,-1,-1,21,-21,
-1,-1,-1,18,15,21,21,15,21,-1,-1,-1,-1,-1,21,-18,-1,-1,20,-1,18,-9,6,-15,
-1,17,19,21,19,13,16,-1,-1,20,-1,-1,18,-12,-1,-16,-1,-21,-1,-1,12,-1,18,-21,
-1,-21,-19,-1,-9,11,7,6,-1,-18,-1,12,-1,15,-1,-21,-1,-21,-1,-1,-1,-17,-1,-1,
-1,-14,11,-21,-13,-21,16,-1,-15,15,-1,-1,-1,19,-1,-1,-17,-1,-20,-1,-14,-1,18,17,
-1,6,6,13,-1,15,-1,11,-15,-1,13,-1,11,-1,-1,-20,-1,-13,-1,-18,-7,-1,-14,-5,
-1,-1,13,-1,16,-20,-14,-20,-1,-13,17,-16,6,-1,-20,9,-20,-17,-14,-1,-20,-15,13,15,
18,15,-1,-1,-1,-10,-1,-18,-1,11,12,-1,-1,-6,-1,10,-1,-1,-20,-20,-1,-12,-15,-1,
-16,-17,-1,-1,-9,-1,-1,-1,-7,-1,-15,16,-9,14,-1,-1,19,16,-11,-1,-1,-1,-1,19,
16,19,-1,-1,-1,-13,6,-1,-1,-1,14,19,-1,-8,-18,-19,-18,-1,-9,-1,-1,-1,16,-1,
-1,-1,-9,-1,-17,-14,-1,-19,-1,-19,-1,-19,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,9,-1,
-1,-2,-1,-1,-11,-1,-1,-1,-14,-1,2,-1,17,-12,-1,-1,16,-17,18,-1,12,-7,5,18,
-14,18,-1,10,15,-1,-1,16,-1,18,-12,-1,2,-1,-1,-1,12,-1,8,-1,-5,-15,-1,-17,
-1,-1,-15,-1,13,-1,14,-1,-1,4,11,-1,-1,-1,-1,-18,-18,-18,-11,-7,12,15,-1,-1,
-17,-1,-10,-1,-1,-1,16,16,-12,11,-1,-1,-1,-1,-1,-1,-1,-1,-10,-15,9,-1,10,-1,
-1,17,-1,-1,-1,-1,-1,-1,-1,-3,-15,-14,-1,-1,-17,13,-1,-1,-1,-11,-1,8,-17,-1,
-1,-1,-1,-12,-1,-17,-1,-16,15,-15,-1,4,15,-1,-1,-1,-1,-1,-1,15,6,-1,8,-8,
-1,-7,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,13,-1,-1,10,-8,12,-1,-11,16,7,16,
-1,16,13,-1,14,-9,-1,15,-10,-1,-16,-1,-13,-1,-1,-16,-1,-16,-9,5,3,-1,-12,-1,
6,7,-13,-1,-16,5,-1,-1,-1,-1,-12,-16,12,-4,-1,14,-1,-1,11,-11,-1,-1,-1,-1,
-7,-1,-8,-1,-1,15,-7,15,15,-1,9,-12,-1,-1,-1,4,-1,-8,-6,-1,-1,-1,-1,-1,
6,-1,14,-1,-11,-1,9,-1,-1,-1,-1,-1,-1,-5,-1,13,-15,-1,-1,-1,8,-13,-1,-15,
14,4,14,-1,13,-1,-1,6,14,-10,-6,-1,-1,14,-8,14,14,14,-1,14,-1,14,-1,5,
-11,-1,-1,-14,-1,-12,-1,-13,-1,-1,-1,-1,-11,7,-1,-1,-1,-1,-14,-14,-1,-1,-10,-9,
-14,-1,-1,-11,9,-1,-1,-5,11,-1,13,12,-9,-1,-1,-1,-1,11,-1,-1,13,12,-1,-1,
-1,-1,5,12,6,-1,11,10,9,-1,-1,8,-1,-1,-1,-1,-1,-1,11,-13,-1,-1,-1,-1,
-1,-1,-5,11,-1,-1,-12,-1,-1,4,-1,6,-3,-1,-1,-1,6,-1,-1,-1,-1,11,-1,-1,
-1,-1,12,12,3,-1,-10,-1,-9,-12,-1,-12,-1,-11,-1,-1,-12,-8,-1,-1,-1,-1,-11,-5,
-10,2,-5,6,-1,-1,-11,-1,-8,0,6,-1,-1,-1,-1,11,-1,-1,-1,-1,-1,-1,-6,0,
-11,-1,7,-1,-1,-1,-1,-7,-8,-7,-1,-1,-11,-1,-1,-1,-1,8,-1,-1,-1,3,-1,-5,
-1,-1,-5,-8,-1,3,-1,10,2,10,8,10,-1,10,-9,-1,-1,-4,5,-10,-10,-10,-1,-1,
-4,-5,-10,-7,-1,-10,-6,-1,-3,8,-1,-1,5,-1,4,-1,-1,-1,-1,9,9,2,-1,-6,
-6,8,-7,6,-8,-1,3,-4,-1,4,-1,7,-1,-1,-5,3,2,-1,-3,-1,-1,-1,6,8,
-8,8,-1,8,-1,3,-2,-7,-7,-1,-6,-7,-7,2,3,-1,-1,-1,-1,-1,-1,-5,-1,-1,
-5,-5,5,-1,-1,-7,-5,-1,-1,-1,-2,-1,-7,2,-7,-1,-1,-1,-4,4,-5,6,-1,6,
-1,-1,3,-6,4,-1,-1,-4,-1,-1,4,-1,-1,5,5,4,-1,-1,5,-2,-1,-1,-5,-5,
-5,-5,1,-1,3,-1,0,-4,-2,-2,-1,-1,-1,1,-1,-1,-1,-1,-1,3,-1,-1,-3,-1,
-3,-1,-1,-1,1,-1,-1,-1,-1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,};

const Sound soundeffect_slash = {2359, 10512, 8, slash};