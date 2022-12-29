const unsigned short pallette_highway[] = {0x0000,0x5294,0x7FFD,0x3DEF,0x294A,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,};
const unsigned short pallette_car[] = {0x0000,0x5294,0x7FFD,0x3DEF,0x294A,0x6720,0x5280,0x3DE0,0x0421,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,};

const unsigned int tile_highway[128] = 
{
	0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,
	0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,
	0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,
	0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,
	0x11111144,0x11111111,0x11111111,0x43111111,0x11111111,0x11111111,0x11114411,0x11111111,
	0x11331111,0x11111111,0x11111111,0x11111113,0x41111111,0x11111113,0x11111111,0x11111111,
	0x11141111,0x11111111,0x11111111,0x11111111,0x11111143,0x11111111,0x11111111,0x11111111,
	0x11131111,0x11111111,0x11111111,0x11111111,0x11111131,0x11144111,0x11111111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11111111,0x11113311,0x11143111,0x11111111,0x14311111,
	0x11111141,0x11111111,0x31111111,0x11111111,0x11111111,0x11111111,0x11131111,0x11113111,
	0x11111111,0x13411111,0x11111113,0x11111111,0x11111111,0x11111111,0x11111111,0x14411111,
	0x11111111,0x11111111,0x11111141,0x11111111,0x11111113,0x11111111,0x11134111,0x11311111,
	0x11111111,0x11111111,0x11111111,0x11311111,0x34111111,0x11111111,0x11111111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11111111,0x11131111,0x11111111,0x11111111,0x11111441,
	0x11111111,0x11111343,0x11111111,0x11111111,0x31111111,0x11111111,0x11111111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x14411111,0x11111114,0x11111111,0x11111111,0x11331111,
};
const unsigned int tile_car[256] = 
{
	0x11111111,0x11111111,0x11143111,0x41111111,0x11111111,0x11111111,0x11111111,0x11111111,
	0x11113331,0x11111111,0x11111111,0x11111144,0x11331111,0x11133311,0x11111111,0x66611111,
	0x11111111,0x66666661,0x55556226,0x55562226,0x55622226,0x56222226,0x62222226,0x62222226,
	0x11111411,0x66666666,0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,0x66666666,
	0x11111111,0x66666666,0x65555555,0x55555555,0x55555555,0x55555555,0x55555555,0x66666666,
	0x11111111,0x11144433,0x11111177,0x11111776,0x11117765,0x11177655,0x14776555,0x17766666,
	0x11111111,0x11111111,0x11111111,0x43111111,0x11111111,0x11111111,0x11111111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11111143,0x13311111,0x11111111,0x11111111,0x11111111,
	0x11111144,0x11111111,0x11111111,0x43111111,0x11111111,0x11111111,0x11114411,0x11111111,
	0x55566661,0x55556661,0x55556221,0x55556223,0x55556221,0x55556221,0x55566661,0x66666551,
	0x62222265,0x62222655,0x62226555,0x62265555,0x62655555,0x66555555,0x65555555,0x66666666,
	0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x22222222,0x66666666,
	0x22222622,0x22222622,0x22222622,0x22222622,0x22222622,0x22222622,0x22222622,0x66666666,
	0x17662222,0x17622222,0x17222222,0x76222222,0x76222222,0x66222222,0x66222222,0x76666666,
	0x13311111,0x11111111,0x11111111,0x11111113,0x11111111,0x11143117,0x11111117,0x11111117,
	0x11344111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11431111,
	0x11111111,0x11111111,0x11111111,0x11111111,0x11113311,0x11143111,0x11111111,0x14311111,
	0x55562661,0x55562261,0x55562261,0x55566261,0x55556661,0x55555511,0x85555611,0x88556611,
	0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,0x55588888,0x58888888,0x88888888,
	0x55555555,0x55555555,0x66555555,0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,
	0x55555655,0x55555655,0x55555656,0x55555655,0x55555655,0x55555655,0x55555665,0x85555566,
	0x65555555,0x55565555,0x55665555,0x55555555,0x55655555,0x55888855,0x88888888,0x88288888,
	0x11114117,0x11111116,0x11111166,0x11111165,0x33111165,0x11111165,0x11111165,0x11114465,
	0x11111111,0x11111114,0x11111111,0x11111111,0x11111113,0x11331111,0x11311111,0x11111111,
	0x11111111,0x11111111,0x11111111,0x11311111,0x34111111,0x11111111,0x11111111,0x11111111,
	0x88661111,0x88111111,0x88111111,0x88111111,0x81131111,0x11111111,0x11111111,0x11111441,
	0x88288888,0x88282288,0x82882288,0x82822288,0x38888888,0x18888888,0x11188881,0x11111111,
	0x55555555,0x66666666,0x11111111,0x14411111,0x11111114,0x11111111,0x11111111,0x11331111,
	0x85555556,0x86666666,0x81111111,0x81111111,0x18111111,0x11111111,0x11111111,0x11111110,
	0x82882288,0x88822288,0x88222888,0x88228888,0x88888888,0x18888881,0x11888811,0x11111111,
	0x41111168,0x41111168,0x11111118,0x13311118,0x11111114,0x14111111,0x11111111,0x11111111,
	0x11111111,0x11111114,0x11111111,0x11111111,0x11111111,0x11111111,0x11111111,0x11444111,
};