const unsigned short pallette_thickgrass[] = {0x7FFF,0x2B40,0x22C0,0x1A40,0x15E0,0x01B2,0x0170,0x012D,0x2700,0x1E80,0x1600,0x0000,0x0000,0x0000,0x0000,0x0000,};
const unsigned short pallette_trees[] = {0x7FFF,0x029A,0x0237,0x01D4,0x0171,0x2800,0x3B40,0x2EE0,0x2280,0x1620,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,};
const unsigned short pallette_treestrunks[] = {0x7FFF,0x029A,0x0237,0x01D4,0x0171,0x2800,0x329A,0x3237,0x31D4,0x3171,0x2B40,0x22C0,0x1A00,0x1180,0x0000,0x0000,};
const unsigned short pallette_treetops[] = {0x7FFF,0x0340,0x02E0,0x0280,0x0220,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,};
const unsigned int tile_thickgrass[32] = 
{
	0x33441432,0x13143443,0x31423341,0x34432323,0x24233213,0x21223431,0x12324412,0x24314342,
	0x13232441,0x43221413,0x43323213,0x31313132,0x34133242,0x14432244,0x43412134,0x24121331,
	0x44331244,0x42132234,0x12242331,0x21231314,0x21334232,0x22314422,0x32123421,0x31412312,
	0x23224321,0x13244122,0x23342142,0x31312344,0x33122314,0x43423321,0x21443242,0x23242242,
};
const unsigned int tile_trees[192] = 
{
	0x55555555,0x55555555,0x66555555,0x55655555,0x65565555,0x66556555,0x66655655,0x66665566,
	0x55555555,0x55555555,0x66666666,0x55666655,0x66666666,0x66666666,0x66666666,0x66666666,
	0x55555555,0x55555555,0x55555556,0x55556665,0x55566556,0x55666666,0x66666666,0x66666666,
	0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,0x55555555,0x55566666,0x55565556,
	0x66665556,0x66666556,0x66666656,0x66666656,0x66666665,0x56665555,0x66666555,0x66666665,
	0x66666666,0x66666666,0x66666666,0x66666666,0x66665555,0x66666666,0x66666666,0x66666666,
	0x66666666,0x66666666,0x66666666,0x66666666,0x66666666,0x66655666,0x66666666,0x56666666,
	0x55666666,0x55656666,0x56556666,0x56566666,0x56566666,0x56666666,0x55566666,0x55566666,
	0x66666565,0x66666565,0x66666665,0x66666665,0x66666655,0x11111555,0x11511555,0x11111555,
	0x66666566,0x66666666,0x66666666,0x66666666,0x66656666,0x66665151,0x65555151,0x55555151,
	0x66566666,0x66665666,0x66666666,0x66666666,0x66666666,0x11515666,0x11515566,0x11515555,
	0x55556666,0x55555666,0x55555516,0x55555511,0x55555511,0x55555511,0x55555511,0x55555511,
	0x11111555,0x11111555,0x11111155,0x11115155,0x11115155,0x11115555,0x15115555,0x11115555,
	0x55555111,0x55555111,0x55555511,0x55555511,0x55555511,0x55555511,0x55555511,0x55555111,
	0x11515555,0x15515555,0x11515555,0x11515555,0x11515555,0x11515555,0x11515555,0x11515555,
	0x55555511,0x55555511,0x55555515,0x55555511,0x55555111,0x55555111,0x55555111,0x55555111,
	0x11115555,0x15115555,0x15115555,0x11115555,0x11115555,0x11115555,0x11115555,0x11115555,
	0x55555111,0x55555111,0x55551111,0x55551111,0x55551511,0x55511111,0x55511115,0x55511111,
	0x11515555,0x11115555,0x11151555,0x11111555,0x11111555,0x11111555,0x11115155,0x11111155,
	0x55555111,0x55555151,0x55555111,0x55551111,0x55551111,0x55511111,0x55511111,0x55511111,
	0x11111555,0x11111555,0x11111555,0x11111555,0x15511555,0x15511555,0x11111155,0x55551555,
	0x55511111,0x55111111,0x51111151,0x51111111,0x55111151,0x55111551,0x51111111,0x51555555,
	0x11111155,0x11151155,0x11151155,0x11111155,0x51115155,0x51111155,0x51151155,0x51115155,
	0x55111511,0x55111111,0x55111111,0x55111111,0x51111115,0x51151555,0x11155555,0x15155555,
};
const unsigned int tile_treestrunks[128] = 
{
	0x55555555,0x55555555,0x55555555,0x55555555,0x55555545,0x55511544,0x11511554,0x11111554,
	0x55555555,0x55555555,0x55555555,0x55555555,0x55335555,0x35435555,0x34445151,0x54445151,
	0x55555555,0x55555555,0x55555555,0x55555555,0x55554555,0x55554555,0x55554455,0x11514455,
	0x55555555,0x55555555,0x55555555,0x45554555,0x45554555,0x45554455,0x45554455,0x45544411,
	0x11111554,0x11111554,0x11111154,0x11215154,0x11215154,0x21125544,0x11125544,0x21115544,
	0x54445112,0x54435112,0x54435512,0x54435521,0x53444511,0x54434511,0x54445511,0x54445111,
	0x31114455,0x21114455,0x21114455,0x11114555,0x11314555,0x11214555,0x11214555,0x31214555,
	0x45554411,0x45554411,0x45554411,0x45554431,0x45554121,0x45554122,0x45554112,0x45544111,
	0x21115444,0x12119443,0x12115439,0x1211D93D,0x1321D9D9,0x11319898,0x11211189,0x1111111D,
	0x54445113,0x44445112,0x44441111,0x43441121,0x339C1121,0x39911211,0x31111212,0x11111111,
	0x21314455,0x21114495,0x21111449,0x221214DD,0x121229C9,0x11112989,0x11112293,0x11111188,
	0x44544111,0x44344111,0x33939121,0x939C1121,0x9D991131,0x98911211,0xD9112311,0x11112111,
	0x11111128,0x22111111,0x32211888,0x11321787,0x17772878,0x77676767,0x76767A76,0xABABABAB,
	0x88811111,0x18132123,0x8C121231,0x73232121,0x877732C1,0x77777777,0x7B76767A,0xA7ABABAB,
	0x11111118,0x12111111,0x12221188,0x31122178,0x77177787,0x67777777,0x767B7676,0xBAB7A7B7,
	0x88111111,0x81113131,0x81113132,0x77131113,0x76777117,0xA6676767,0xB6767B76,0xAABABABA,
};
const unsigned int tile_treetops[128] = 
{
	0x00000000,0x11100000,0x22100000,0x11220200,0x22222220,0x22242220,0x22211222,0x22422222,
	0x00000000,0x11111111,0x22222222,0x22222222,0x11111122,0x12222112,0x11111111,0x23311111,
	0x00000000,0x12211111,0x22222222,0x22222222,0x22211111,0x22211111,0x22112111,0x21121112,
	0x00000000,0x00000001,0x00002222,0x00012222,0x02222222,0x22112111,0x21122222,0x11122222,
	0x21222222,0x22111222,0x32211122,0x21323322,0x32133122,0x33231022,0x11111002,0x11131022,
	0x11111122,0x12111122,0x11111113,0x11111132,0x11111113,0x11111111,0x11111111,0x11111311,
	0x11111111,0x11111111,0x12222111,0x11111111,0x31111111,0x11111111,0x11111111,0x22222111,
	0x22232111,0x21111111,0x11311112,0x11311332,0x11313122,0x22221123,0x22212231,0x11211322,
	0x22222222,0x11133222,0x22232222,0x22222212,0x22222222,0x22112310,0x22322130,0x33133030,
	0x22222222,0x33311131,0x22222222,0x22222222,0x21111222,0x22222222,0x33311311,0x33223333,
	0x31112222,0x22221133,0x22212222,0x22222222,0x22222122,0x33122222,0x41332133,0x34413333,
	0x22222233,0x22222222,0x22222222,0x32222222,0x33132222,0x13331113,0x13333114,0x11333333,
	0x33333330,0x13333330,0x33133330,0x44130130,0x11444444,0x44443330,0x33100000,0x11100000,
	0x33333333,0x33333333,0x33334133,0x43111444,0x22224444,0x41444444,0x44444444,0x44444331,
	0x33333333,0x33311431,0x43333333,0x11444444,0x44444444,0x14443444,0x44444444,0x11111144,
	0x14111333,0x14433333,0x44444324,0x14444444,0x11441414,0x01114433,0x00111114,0x00011111,
};