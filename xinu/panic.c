#include "u.h"
#include "fns.h"

void
panic(const char *msg)
{
	int ps;

	ps = disable();
	kprintf("%s\n", msg);
	kprintf("ps = %04x\n", ps);
//	prdump();
	for (;;) { stop(); }
	restore(ps);
}

void
panic0(void)
{
	panic("zero");
}

void
strayint(void)
{
	panic("unhandled exception");
}

volatile void *intrargs[256];

void lowcore2(void);

void
lowcore(void)
{
	volatile uword *vectors = (uword *)0;

	for (int k = 0; k < 256; k++) {
		vectors[k] = (uword)strayint;
		intrargs[k] = (void *)0;
	}
	lowcore2();
	vectors[0] = 0x100000 - 4;
	vectors[1] = (uword)panic0;
}

void panic1(void) { panic("panic 1"); }
void panic2(void) { panic("panic 2"); }
void panic3(void) { panic("panic 3"); }
void panic4(void) { panic("panic 4"); }
void panic5(void) { panic("panic 5"); }
void panic6(void) { panic("panic 6"); }
void panic7(void) { panic("panic 7"); }
void panic8(void) { panic("panic 8"); }
void panic9(void) { panic("panic 9"); }
void panic10(void) { panic("panic 10"); }
void panic11(void) { panic("panic 11"); }
void panic12(void) { panic("panic 12"); }
void panic13(void) { panic("panic 13"); }
void panic14(void) { panic("panic 14"); }
void panic15(void) { panic("panic 15"); }
void panic16(void) { panic("panic 16"); }
void panic17(void) { panic("panic 17"); }
void panic18(void) { panic("panic 18"); }
void panic19(void) { panic("panic 19"); }
void panic20(void) { panic("panic 20"); }
void panic21(void) { panic("panic 21"); }
void panic22(void) { panic("panic 22"); }
void panic23(void) { panic("panic 23"); }
void panic24(void) { panic("panic 24"); }
void panic25(void) { panic("panic 25"); }
void panic26(void) { panic("panic 26"); }
void panic27(void) { panic("panic 27"); }
void panic28(void) { panic("panic 28"); }
void panic29(void) { panic("panic 29"); }
void panic30(void) { panic("panic 30"); }
void panic31(void) { panic("panic 31"); }
void panic32(void) { panic("panic 32"); }
void panic33(void) { panic("panic 33"); }
void panic34(void) { panic("panic 34"); }
void panic35(void) { panic("panic 35"); }
void panic36(void) { panic("panic 36"); }
void panic37(void) { panic("panic 37"); }
void panic38(void) { panic("panic 38"); }
void panic39(void) { panic("panic 39"); }
void panic40(void) { panic("panic 40"); }
void panic41(void) { panic("panic 41"); }
void panic42(void) { panic("panic 42"); }
void panic43(void) { panic("panic 43"); }
void panic44(void) { panic("panic 44"); }
void panic45(void) { panic("panic 45"); }
void panic46(void) { panic("panic 46"); }
void panic47(void) { panic("panic 47"); }
void panic48(void) { panic("panic 48"); }
void panic49(void) { panic("panic 49"); }
void panic50(void) { panic("panic 50"); }
void panic51(void) { panic("panic 51"); }
void panic52(void) { panic("panic 52"); }
void panic53(void) { panic("panic 53"); }
void panic54(void) { panic("panic 54"); }
void panic55(void) { panic("panic 55"); }
void panic56(void) { panic("panic 56"); }
void panic57(void) { panic("panic 57"); }
void panic58(void) { panic("panic 58"); }
void panic59(void) { panic("panic 59"); }
void panic60(void) { panic("panic 60"); }
void panic61(void) { panic("panic 61"); }
void panic62(void) { panic("panic 62"); }
void panic63(void) { panic("panic 63"); }
void panic64(void) { panic("panic 64"); }
void panic65(void) { panic("panic 65"); }
void panic66(void) { panic("panic 66"); }
void panic67(void) { panic("panic 67"); }
void panic68(void) { panic("panic 68"); }
void panic69(void) { panic("panic 69"); }
void panic70(void) { panic("panic 70"); }
void panic71(void) { panic("panic 71"); }
void panic72(void) { panic("panic 72"); }
void panic73(void) { panic("panic 73"); }
void panic74(void) { panic("panic 74"); }
void panic75(void) { panic("panic 75"); }
void panic76(void) { panic("panic 76"); }
void panic77(void) { panic("panic 77"); }
void panic78(void) { panic("panic 78"); }
void panic79(void) { panic("panic 79"); }
void panic80(void) { panic("panic 80"); }
void panic81(void) { panic("panic 81"); }
void panic82(void) { panic("panic 82"); }
void panic83(void) { panic("panic 83"); }
void panic84(void) { panic("panic 84"); }
void panic85(void) { panic("panic 85"); }
void panic86(void) { panic("panic 86"); }
void panic87(void) { panic("panic 87"); }
void panic88(void) { panic("panic 88"); }
void panic89(void) { panic("panic 89"); }
void panic90(void) { panic("panic 90"); }
void panic91(void) { panic("panic 91"); }
void panic92(void) { panic("panic 92"); }
void panic93(void) { panic("panic 93"); }
void panic94(void) { panic("panic 94"); }
void panic95(void) { panic("panic 95"); }
void panic96(void) { panic("panic 96"); }
void panic97(void) { panic("panic 97"); }
void panic98(void) { panic("panic 98"); }
void panic99(void) { panic("panic 99"); }
void panic100(void) { panic("panic 100"); }
void panic101(void) { panic("panic 101"); }
void panic102(void) { panic("panic 102"); }
void panic103(void) { panic("panic 103"); }
void panic104(void) { panic("panic 104"); }
void panic105(void) { panic("panic 105"); }
void panic106(void) { panic("panic 106"); }
void panic107(void) { panic("panic 107"); }
void panic108(void) { panic("panic 108"); }
void panic109(void) { panic("panic 109"); }
void panic110(void) { panic("panic 110"); }
void panic111(void) { panic("panic 111"); }
void panic112(void) { panic("panic 112"); }
void panic113(void) { panic("panic 113"); }
void panic114(void) { panic("panic 114"); }
void panic115(void) { panic("panic 115"); }
void panic116(void) { panic("panic 116"); }
void panic117(void) { panic("panic 117"); }
void panic118(void) { panic("panic 118"); }
void panic119(void) { panic("panic 119"); }
void panic120(void) { panic("panic 120"); }
void panic121(void) { panic("panic 121"); }
void panic122(void) { panic("panic 122"); }
void panic123(void) { panic("panic 123"); }
void panic124(void) { panic("panic 124"); }
void panic125(void) { panic("panic 125"); }
void panic126(void) { panic("panic 126"); }
void panic127(void) { panic("panic 127"); }
void panic128(void) { panic("panic 128"); }
void panic129(void) { panic("panic 129"); }
void panic130(void) { panic("panic 130"); }
void panic131(void) { panic("panic 131"); }
void panic132(void) { panic("panic 132"); }
void panic133(void) { panic("panic 133"); }
void panic134(void) { panic("panic 134"); }
void panic135(void) { panic("panic 135"); }
void panic136(void) { panic("panic 136"); }
void panic137(void) { panic("panic 137"); }
void panic138(void) { panic("panic 138"); }
void panic139(void) { panic("panic 139"); }
void panic140(void) { panic("panic 140"); }
void panic141(void) { panic("panic 141"); }
void panic142(void) { panic("panic 142"); }
void panic143(void) { panic("panic 143"); }
void panic144(void) { panic("panic 144"); }
void panic145(void) { panic("panic 145"); }
void panic146(void) { panic("panic 146"); }
void panic147(void) { panic("panic 147"); }
void panic148(void) { panic("panic 148"); }
void panic149(void) { panic("panic 149"); }
void panic150(void) { panic("panic 150"); }
void panic151(void) { panic("panic 151"); }
void panic152(void) { panic("panic 152"); }
void panic153(void) { panic("panic 153"); }
void panic154(void) { panic("panic 154"); }
void panic155(void) { panic("panic 155"); }
void panic156(void) { panic("panic 156"); }
void panic157(void) { panic("panic 157"); }
void panic158(void) { panic("panic 158"); }
void panic159(void) { panic("panic 159"); }
void panic160(void) { panic("panic 160"); }
void panic161(void) { panic("panic 161"); }
void panic162(void) { panic("panic 162"); }
void panic163(void) { panic("panic 163"); }
void panic164(void) { panic("panic 164"); }
void panic165(void) { panic("panic 165"); }
void panic166(void) { panic("panic 166"); }
void panic167(void) { panic("panic 167"); }
void panic168(void) { panic("panic 168"); }
void panic169(void) { panic("panic 169"); }
void panic170(void) { panic("panic 170"); }
void panic171(void) { panic("panic 171"); }
void panic172(void) { panic("panic 172"); }
void panic173(void) { panic("panic 173"); }
void panic174(void) { panic("panic 174"); }
void panic175(void) { panic("panic 175"); }
void panic176(void) { panic("panic 176"); }
void panic177(void) { panic("panic 177"); }
void panic178(void) { panic("panic 178"); }
void panic179(void) { panic("panic 179"); }
void panic180(void) { panic("panic 180"); }
void panic181(void) { panic("panic 181"); }
void panic182(void) { panic("panic 182"); }
void panic183(void) { panic("panic 183"); }
void panic184(void) { panic("panic 184"); }
void panic185(void) { panic("panic 185"); }
void panic186(void) { panic("panic 186"); }
void panic187(void) { panic("panic 187"); }
void panic188(void) { panic("panic 188"); }
void panic189(void) { panic("panic 189"); }
void panic190(void) { panic("panic 190"); }
void panic191(void) { panic("panic 191"); }
void panic192(void) { panic("panic 192"); }
void panic193(void) { panic("panic 193"); }
void panic194(void) { panic("panic 194"); }
void panic195(void) { panic("panic 195"); }
void panic196(void) { panic("panic 196"); }
void panic197(void) { panic("panic 197"); }
void panic198(void) { panic("panic 198"); }
void panic199(void) { panic("panic 199"); }
void panic200(void) { panic("panic 200"); }
void panic201(void) { panic("panic 201"); }
void panic202(void) { panic("panic 202"); }
void panic203(void) { panic("panic 203"); }
void panic204(void) { panic("panic 204"); }
void panic205(void) { panic("panic 205"); }
void panic206(void) { panic("panic 206"); }
void panic207(void) { panic("panic 207"); }
void panic208(void) { panic("panic 208"); }
void panic209(void) { panic("panic 209"); }
void panic210(void) { panic("panic 210"); }
void panic211(void) { panic("panic 211"); }
void panic212(void) { panic("panic 212"); }
void panic213(void) { panic("panic 213"); }
void panic214(void) { panic("panic 214"); }
void panic215(void) { panic("panic 215"); }
void panic216(void) { panic("panic 216"); }
void panic217(void) { panic("panic 217"); }
void panic218(void) { panic("panic 218"); }
void panic219(void) { panic("panic 219"); }
void panic220(void) { panic("panic 220"); }
void panic221(void) { panic("panic 221"); }
void panic222(void) { panic("panic 222"); }
void panic223(void) { panic("panic 223"); }
void panic224(void) { panic("panic 224"); }
void panic225(void) { panic("panic 225"); }
void panic226(void) { panic("panic 226"); }
void panic227(void) { panic("panic 227"); }
void panic228(void) { panic("panic 228"); }
void panic229(void) { panic("panic 229"); }
void panic230(void) { panic("panic 230"); }
void panic231(void) { panic("panic 231"); }
void panic232(void) { panic("panic 232"); }
void panic233(void) { panic("panic 233"); }
void panic234(void) { panic("panic 234"); }
void panic235(void) { panic("panic 235"); }
void panic236(void) { panic("panic 236"); }
void panic237(void) { panic("panic 237"); }
void panic238(void) { panic("panic 238"); }
void panic239(void) { panic("panic 239"); }
void panic240(void) { panic("panic 240"); }
void panic241(void) { panic("panic 241"); }
void panic242(void) { panic("panic 242"); }
void panic243(void) { panic("panic 243"); }
void panic244(void) { panic("panic 244"); }
void panic245(void) { panic("panic 245"); }
void panic246(void) { panic("panic 246"); }
void panic247(void) { panic("panic 247"); }
void panic248(void) { panic("panic 248"); }
void panic249(void) { panic("panic 249"); }
void panic250(void) { panic("panic 250"); }
void panic251(void) { panic("panic 251"); }
void panic252(void) { panic("panic 252"); }
void panic253(void) { panic("panic 253"); }
void panic254(void) { panic("panic 254"); }
void panic255(void) { panic("panic 255"); }

void
lowcore2()
{
	volatile uword *vectors = (uword *)0;
	vectors[1] = (uword)panic1;
	vectors[2] = (uword)panic2;
	vectors[3] = (uword)panic3;
	vectors[4] = (uword)panic4;
	vectors[5] = (uword)panic5;
	vectors[6] = (uword)panic6;
	vectors[7] = (uword)panic7;
	vectors[8] = (uword)panic8;
	vectors[9] = (uword)panic9;
	vectors[10] = (uword)panic10;
	vectors[11] = (uword)panic11;
	vectors[12] = (uword)panic12;
	vectors[13] = (uword)panic13;
	vectors[14] = (uword)panic14;
	vectors[15] = (uword)panic15;
	vectors[16] = (uword)panic16;
	vectors[17] = (uword)panic17;
	vectors[18] = (uword)panic18;
	vectors[19] = (uword)panic19;
	vectors[20] = (uword)panic20;
	vectors[21] = (uword)panic21;
	vectors[22] = (uword)panic22;
	vectors[23] = (uword)panic23;
	vectors[24] = (uword)panic24;
	vectors[25] = (uword)panic25;
	vectors[26] = (uword)panic26;
	vectors[27] = (uword)panic27;
	vectors[28] = (uword)panic28;
	vectors[29] = (uword)panic29;
	vectors[30] = (uword)panic30;
	vectors[31] = (uword)panic31;
	vectors[32] = (uword)panic32;
	vectors[33] = (uword)panic33;
	vectors[34] = (uword)panic34;
	vectors[35] = (uword)panic35;
	vectors[36] = (uword)panic36;
	vectors[37] = (uword)panic37;
	vectors[38] = (uword)panic38;
	vectors[39] = (uword)panic39;
	vectors[40] = (uword)panic40;
	vectors[41] = (uword)panic41;
	vectors[42] = (uword)panic42;
	vectors[43] = (uword)panic43;
	vectors[44] = (uword)panic44;
	vectors[45] = (uword)panic45;
	vectors[46] = (uword)panic46;
	vectors[47] = (uword)panic47;
	vectors[48] = (uword)panic48;
	vectors[49] = (uword)panic49;
	vectors[50] = (uword)panic50;
	vectors[51] = (uword)panic51;
	vectors[52] = (uword)panic52;
	vectors[53] = (uword)panic53;
	vectors[54] = (uword)panic54;
	vectors[55] = (uword)panic55;
	vectors[56] = (uword)panic56;
	vectors[57] = (uword)panic57;
	vectors[58] = (uword)panic58;
	vectors[59] = (uword)panic59;
	vectors[60] = (uword)panic60;
	vectors[61] = (uword)panic61;
	vectors[62] = (uword)panic62;
	vectors[63] = (uword)panic63;
	vectors[64] = (uword)panic64;
	vectors[65] = (uword)panic65;
	vectors[66] = (uword)panic66;
	vectors[67] = (uword)panic67;
	vectors[68] = (uword)panic68;
	vectors[69] = (uword)panic69;
	vectors[70] = (uword)panic70;
	vectors[71] = (uword)panic71;
	vectors[72] = (uword)panic72;
	vectors[73] = (uword)panic73;
	vectors[74] = (uword)panic74;
	vectors[75] = (uword)panic75;
	vectors[76] = (uword)panic76;
	vectors[77] = (uword)panic77;
	vectors[78] = (uword)panic78;
	vectors[79] = (uword)panic79;
	vectors[80] = (uword)panic80;
	vectors[81] = (uword)panic81;
	vectors[82] = (uword)panic82;
	vectors[83] = (uword)panic83;
	vectors[84] = (uword)panic84;
	vectors[85] = (uword)panic85;
	vectors[86] = (uword)panic86;
	vectors[87] = (uword)panic87;
	vectors[88] = (uword)panic88;
	vectors[89] = (uword)panic89;
	vectors[90] = (uword)panic90;
	vectors[91] = (uword)panic91;
	vectors[92] = (uword)panic92;
	vectors[93] = (uword)panic93;
	vectors[94] = (uword)panic94;
	vectors[95] = (uword)panic95;
	vectors[96] = (uword)panic96;
	vectors[97] = (uword)panic97;
	vectors[98] = (uword)panic98;
	vectors[99] = (uword)panic99;
	vectors[100] = (uword)panic100;
	vectors[101] = (uword)panic101;
	vectors[102] = (uword)panic102;
	vectors[103] = (uword)panic103;
	vectors[104] = (uword)panic104;
	vectors[105] = (uword)panic105;
	vectors[106] = (uword)panic106;
	vectors[107] = (uword)panic107;
	vectors[108] = (uword)panic108;
	vectors[109] = (uword)panic109;
	vectors[110] = (uword)panic110;
	vectors[111] = (uword)panic111;
	vectors[112] = (uword)panic112;
	vectors[113] = (uword)panic113;
	vectors[114] = (uword)panic114;
	vectors[115] = (uword)panic115;
	vectors[116] = (uword)panic116;
	vectors[117] = (uword)panic117;
	vectors[118] = (uword)panic118;
	vectors[119] = (uword)panic119;
	vectors[120] = (uword)panic120;
	vectors[121] = (uword)panic121;
	vectors[122] = (uword)panic122;
	vectors[123] = (uword)panic123;
	vectors[124] = (uword)panic124;
	vectors[125] = (uword)panic125;
	vectors[126] = (uword)panic126;
	vectors[127] = (uword)panic127;
	vectors[128] = (uword)panic128;
	vectors[129] = (uword)panic129;
	vectors[130] = (uword)panic130;
	vectors[131] = (uword)panic131;
	vectors[132] = (uword)panic132;
	vectors[133] = (uword)panic133;
	vectors[134] = (uword)panic134;
	vectors[135] = (uword)panic135;
	vectors[136] = (uword)panic136;
	vectors[137] = (uword)panic137;
	vectors[138] = (uword)panic138;
	vectors[139] = (uword)panic139;
	vectors[140] = (uword)panic140;
	vectors[141] = (uword)panic141;
	vectors[142] = (uword)panic142;
	vectors[143] = (uword)panic143;
	vectors[144] = (uword)panic144;
	vectors[145] = (uword)panic145;
	vectors[146] = (uword)panic146;
	vectors[147] = (uword)panic147;
	vectors[148] = (uword)panic148;
	vectors[149] = (uword)panic149;
	vectors[150] = (uword)panic150;
	vectors[151] = (uword)panic151;
	vectors[152] = (uword)panic152;
	vectors[153] = (uword)panic153;
	vectors[154] = (uword)panic154;
	vectors[155] = (uword)panic155;
	vectors[156] = (uword)panic156;
	vectors[157] = (uword)panic157;
	vectors[158] = (uword)panic158;
	vectors[159] = (uword)panic159;
	vectors[160] = (uword)panic160;
	vectors[161] = (uword)panic161;
	vectors[162] = (uword)panic162;
	vectors[163] = (uword)panic163;
	vectors[164] = (uword)panic164;
	vectors[165] = (uword)panic165;
	vectors[166] = (uword)panic166;
	vectors[167] = (uword)panic167;
	vectors[168] = (uword)panic168;
	vectors[169] = (uword)panic169;
	vectors[170] = (uword)panic170;
	vectors[171] = (uword)panic171;
	vectors[172] = (uword)panic172;
	vectors[173] = (uword)panic173;
	vectors[174] = (uword)panic174;
	vectors[175] = (uword)panic175;
	vectors[176] = (uword)panic176;
	vectors[177] = (uword)panic177;
	vectors[178] = (uword)panic178;
	vectors[179] = (uword)panic179;
	vectors[180] = (uword)panic180;
	vectors[181] = (uword)panic181;
	vectors[182] = (uword)panic182;
	vectors[183] = (uword)panic183;
	vectors[184] = (uword)panic184;
	vectors[185] = (uword)panic185;
	vectors[186] = (uword)panic186;
	vectors[187] = (uword)panic187;
	vectors[188] = (uword)panic188;
	vectors[189] = (uword)panic189;
	vectors[190] = (uword)panic190;
	vectors[191] = (uword)panic191;
	vectors[192] = (uword)panic192;
	vectors[193] = (uword)panic193;
	vectors[194] = (uword)panic194;
	vectors[195] = (uword)panic195;
	vectors[196] = (uword)panic196;
	vectors[197] = (uword)panic197;
	vectors[198] = (uword)panic198;
	vectors[199] = (uword)panic199;
	vectors[200] = (uword)panic200;
	vectors[201] = (uword)panic201;
	vectors[202] = (uword)panic202;
	vectors[203] = (uword)panic203;
	vectors[204] = (uword)panic204;
	vectors[205] = (uword)panic205;
	vectors[206] = (uword)panic206;
	vectors[207] = (uword)panic207;
	vectors[208] = (uword)panic208;
	vectors[209] = (uword)panic209;
	vectors[210] = (uword)panic210;
	vectors[211] = (uword)panic211;
	vectors[212] = (uword)panic212;
	vectors[213] = (uword)panic213;
	vectors[214] = (uword)panic214;
	vectors[215] = (uword)panic215;
	vectors[216] = (uword)panic216;
	vectors[217] = (uword)panic217;
	vectors[218] = (uword)panic218;
	vectors[219] = (uword)panic219;
	vectors[220] = (uword)panic220;
	vectors[221] = (uword)panic221;
	vectors[222] = (uword)panic222;
	vectors[223] = (uword)panic223;
	vectors[224] = (uword)panic224;
	vectors[225] = (uword)panic225;
	vectors[226] = (uword)panic226;
	vectors[227] = (uword)panic227;
	vectors[228] = (uword)panic228;
	vectors[229] = (uword)panic229;
	vectors[230] = (uword)panic230;
	vectors[231] = (uword)panic231;
	vectors[232] = (uword)panic232;
	vectors[233] = (uword)panic233;
	vectors[234] = (uword)panic234;
	vectors[235] = (uword)panic235;
	vectors[236] = (uword)panic236;
	vectors[237] = (uword)panic237;
	vectors[238] = (uword)panic238;
	vectors[239] = (uword)panic239;
	vectors[240] = (uword)panic240;
	vectors[241] = (uword)panic241;
	vectors[242] = (uword)panic242;
	vectors[243] = (uword)panic243;
	vectors[244] = (uword)panic244;
	vectors[245] = (uword)panic245;
	vectors[246] = (uword)panic246;
	vectors[247] = (uword)panic247;
	vectors[248] = (uword)panic248;
	vectors[249] = (uword)panic249;
	vectors[250] = (uword)panic250;
	vectors[251] = (uword)panic251;
	vectors[252] = (uword)panic252;
	vectors[253] = (uword)panic253;
	vectors[254] = (uword)panic254;
	vectors[255] = (uword)panic255;
}
