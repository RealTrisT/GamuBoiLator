#include "Disas.h"

void strFrom16(char* string, unsigned short yeet) {
	for (unsigned char i = 0; i < 4; i++) {
		string[i] = ((yeet >> (16 - (i + 1) * 4)) & 0xF) + 0x30; if (string[i] > 0x39)string[i] += 0x7;
	}
}

const char * Disassembler::Disassemble(unsigned char * op){
	if (*op == 0xCB) {
		return opcodes[(unsigned short)(*op) + 0x100].Str;
	} else {
		Opcode thisOP = opcodes[*op];
		if (thisOP.Fixer)return thisOP.Fixer(op, thisOP.Str);
		else if (thisOP.Str)return thisOP.Str;
		else return invalid;
	}
}

char * Disassembler::Fix16_After8(unsigned char * CurrInstruction, char * string){
	strFrom16(string + 8, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix16_After7(unsigned char * CurrInstruction, char * string) {
	strFrom16(string + 7, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix16_After6(unsigned char * CurrInstruction, char * string) {
	strFrom16(string + 6, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix16_After5(unsigned char * CurrInstruction, char * string) {
	strFrom16(string + 5, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix16_After4(unsigned char * CurrInstruction, char * string) {
	strFrom16(string + 4, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix16_After3(unsigned char * CurrInstruction, char * string) {
	strFrom16(string + 3, *(unsigned short*)(CurrInstruction + 1));
	return string;
}

void strFrom8(char* string, unsigned char yeet) {
	for (unsigned char i = 0; i < 2; i++) {
		string[i] = ((yeet >> (8 - (i + 1) * 4)) & 0xF) + 0x30; if (string[i] > 0x39)string[i] += 0x7;
	}
}

char * Disassembler::Fix8_After3(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 3, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8_After4(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 4, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8_After5(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 5, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8_After6(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 6, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8_After7(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 7, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8_After8(unsigned char * CurrInstruction, char * string) {
	strFrom8(string + 8, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

void strFrom8s(char* string, unsigned char yeet) {
	if (yeet >> 7) {
		string++[0] = '-'; yeet = ~yeet + 1;
	}else string++[0] = '+';
	for (unsigned char i = 0; i < 2; i++) {
		string[i] = ((yeet >> (8 - (i + 1) * 4)) & 0xF) + 0x30; if (string[i] > 0x39)string[i] += 0x7;
	}
}

char * Disassembler::Fix8s_After9(unsigned char * CurrInstruction, char * string) {
	strFrom8s(string + 9, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8s_After7(unsigned char * CurrInstruction, char * string) {
	strFrom8s(string + 7, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8s_After6(unsigned char * CurrInstruction, char * string) {
	strFrom8s(string + 6, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8s_After5(unsigned char * CurrInstruction, char * string) {
	strFrom8s(string + 5, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char * Disassembler::Fix8s_After3(unsigned char * CurrInstruction, char * string) {
	strFrom8s(string + 3, *(unsigned char*)(CurrInstruction + 1));
	return string;
}

char Disassembler::invalid[8] = "INVALID";

const Disassembler::Opcode Disassembler::opcodes[0x200] = {
	{               0, 1, _00}, {    Fix16_After6, 3, _01}, {               0, 1, _02}, {               0, 1, _03}, {               0, 1, _04}, {               0, 1, _05}, {     Fix8_After5, 2, _06}, {               0, 1, _07}, {    Fix16_After4, 3, _08}, {               0, 1, _09}, {               0, 1, _0a}, {               0, 1, _0b}, {               0, 1, _0c}, {               0, 1, _0d}, {     Fix8_After5, 2, _0e}, {               0, 1, _0f}, 
	{               0, 1, _10}, {    Fix16_After6, 3, _11}, {               0, 1, _12}, {               0, 1, _13}, {               0, 1, _14}, {               0, 1, _15}, {     Fix8_After5, 2, _16}, {               0, 1, _17}, {    Fix8s_After3, 2, _18}, {               0, 1, _19}, {               0, 1, _1a}, {               0, 1, _1b}, {               0, 1, _1c}, {               0, 1, _1d}, {     Fix8_After5, 2, _1e}, {               0, 1, _1f}, 
	{    Fix8s_After6, 2, _20}, {    Fix16_After6, 3, _21}, {               0, 1, _22}, {               0, 1, _23}, {               0, 1, _24}, {               0, 1, _25}, {     Fix8_After5, 2, _26}, {               0, 1, _27}, {    Fix8s_After5, 2, _28}, {               0, 1, _29}, {               0, 1, _2a}, {               0, 1, _2b}, {               0, 1, _2c}, {               0, 1, _2d}, {     Fix8_After5, 2, _2e}, {               0, 1, _2f}, 
	{    Fix8s_After6, 2, _30}, {    Fix16_After6, 3, _31}, {               0, 1, _32}, {               0, 1, _33}, {               0, 1, _34}, {               0, 1, _35}, {     Fix8_After8, 2, _36}, {               0, 1, _37}, {    Fix8s_After5, 2, _38}, {               0, 1, _39}, {               0, 1, _3a}, {               0, 1, _3b}, {               0, 1, _3c}, {               0, 1, _3d}, {     Fix8_After5, 2, _3e}, {               0, 1, _3f}, 
	{               0, 1, _40}, {               0, 1, _41}, {               0, 1, _42}, {               0, 1, _43}, {               0, 1, _44}, {               0, 1, _45}, {               0, 1, _46}, {               0, 1, _47}, {               0, 1, _48}, {               0, 1, _49}, {               0, 1, _4a}, {               0, 1, _4b}, {               0, 1, _4c}, {               0, 1, _4d}, {               0, 1, _4e}, {               0, 1, _4f}, 
	{               0, 1, _50}, {               0, 1, _51}, {               0, 1, _52}, {               0, 1, _53}, {               0, 1, _54}, {               0, 1, _55}, {               0, 1, _56}, {               0, 1, _57}, {               0, 1, _58}, {               0, 1, _59}, {               0, 1, _5a}, {               0, 1, _5b}, {               0, 1, _5c}, {               0, 1, _5d}, {               0, 1, _5e}, {               0, 1, _5f}, 
	{               0, 1, _60}, {               0, 1, _61}, {               0, 1, _62}, {               0, 1, _63}, {               0, 1, _64}, {               0, 1, _65}, {               0, 1, _66}, {               0, 1, _67}, {               0, 1, _68}, {               0, 1, _69}, {               0, 1, _6a}, {               0, 1, _6b}, {               0, 1, _6c}, {               0, 1, _6d}, {               0, 1, _6e}, {               0, 1, _6f}, 
	{               0, 1, _70}, {               0, 1, _71}, {               0, 1, _72}, {               0, 1, _73}, {               0, 1, _74}, {               0, 1, _75}, {               0, 1, _76}, {               0, 1, _77}, {               0, 1, _78}, {               0, 1, _79}, {               0, 1, _7a}, {               0, 1, _7b}, {               0, 1, _7c}, {               0, 1, _7d}, {               0, 1, _7e}, {               0, 1, _7f}, 
	{               0, 1, _80}, {               0, 1, _81}, {               0, 1, _82}, {               0, 1, _83}, {               0, 1, _84}, {               0, 1, _85}, {               0, 1, _86}, {               0, 1, _87}, {               0, 1, _88}, {               0, 1, _89}, {               0, 1, _8a}, {               0, 1, _8b}, {               0, 1, _8c}, {               0, 1, _8d}, {               0, 1, _8e}, {               0, 1, _8f}, 
	{               0, 1, _90}, {               0, 1, _91}, {               0, 1, _92}, {               0, 1, _93}, {               0, 1, _94}, {               0, 1, _95}, {               0, 1, _96}, {               0, 1, _97}, {               0, 1, _98}, {               0, 1, _99}, {               0, 1, _9a}, {               0, 1, _9b}, {               0, 1, _9c}, {               0, 1, _9d}, {               0, 1, _9e}, {               0, 1, _9f}, 
	{               0, 1, _a0}, {               0, 1, _a1}, {               0, 1, _a2}, {               0, 1, _a3}, {               0, 1, _a4}, {               0, 1, _a5}, {               0, 1, _a6}, {               0, 1, _a7}, {               0, 1, _a8}, {               0, 1, _a9}, {               0, 1, _aa}, {               0, 1, _ab}, {               0, 1, _ac}, {               0, 1, _ad}, {               0, 1, _ae}, {               0, 1, _af}, 
	{               0, 1, _b0}, {               0, 1, _b1}, {               0, 1, _b2}, {               0, 1, _b3}, {               0, 1, _b4}, {               0, 1, _b5}, {               0, 1, _b6}, {               0, 1, _b7}, {               0, 1, _b8}, {               0, 1, _b9}, {               0, 1, _ba}, {               0, 1, _bb}, {               0, 1, _bc}, {               0, 1, _bd}, {               0, 1, _be}, {               0, 1, _bf}, 
	{               0, 1, _c0}, {               0, 1, _c1}, {    Fix16_After6, 3, _c2}, {    Fix16_After3, 3, _c3}, {    Fix16_After8, 3, _c4}, {               0, 1, _c5}, {     Fix8_After6, 2, _c6}, {               0, 1, _c7}, {               0, 1, _c8}, {               0, 1, _c9}, {    Fix16_After5, 3, _ca}, {               0, 1, _cb}, {    Fix16_After7, 3, _cc}, {    Fix16_After5, 3, _cd}, {     Fix8_After6, 2, _ce}, {               0, 1, _cf}, 
	{               0, 1, _d0}, {               0, 1, _d1}, {    Fix16_After6, 3, _d2}, {               0, 0,   0}, {    Fix16_After8, 3, _d4}, {               0, 1, _d5}, {     Fix8_After4, 2, _d6}, {               0, 1, _d7}, {               0, 1, _d8}, {               0, 1, _d9}, {    Fix16_After5, 3, _da}, {               0, 0,   0}, {    Fix16_After7, 3, _dc}, {               0, 0,   0}, {     Fix8_After6, 2, _de}, {               0, 1, _df}, 
	{     Fix8_After5, 2, _e0}, {               0, 1, _e1}, {               0, 1, _e2}, {               0, 0,   0}, {               0, 0,   0}, {               0, 1, _e5}, {     Fix8_After4, 2, _e6}, {               0, 1, _e7}, {    Fix8s_After7, 2, _e8}, {               0, 1, _e9}, {    Fix16_After4, 3, _ea}, {               0, 0,   0}, {               0, 0,   0}, {               0, 0,   0}, {     Fix8_After4, 2, _ee}, {               0, 1, _ef}, 
	{     Fix8_After7, 2, _f0}, {               0, 1, _f1}, {               0, 1, _f2}, {               0, 1, _f3}, {               0, 0,   0}, {               0, 1, _f5}, {     Fix8_After3, 2, _f6}, {               0, 1, _f7}, {    Fix8s_After9, 2, _f8}, {               0, 1, _f9}, {    Fix16_After6, 3, _fa}, {               0, 1, _fb}, {               0, 0,   0}, {               0, 0,   0}, {     Fix8_After3, 2, _fe}, {               0, 1, _ff},
	//-----------------------------------------------------------------------------------------------------------------------CB PREFIXED---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	{               0, 1,__00}, {               0, 1,__01}, {               0, 1,__02}, {               0, 1,__03}, {               0, 1,__04}, {               0, 1,__05}, {               0, 1,__06}, {               0, 1,__07}, {               0, 1,__08}, {               0, 1,__09}, {               0, 1,__0a}, {               0, 1,__0b}, {               0, 1,__0c}, {               0, 1,__0d}, {               0, 1,__0e}, {               0, 1,__0f}, 
	{               0, 1,__10}, {               0, 1,__11}, {               0, 1,__12}, {               0, 1,__13}, {               0, 1,__14}, {               0, 1,__15}, {               0, 1,__16}, {               0, 1,__17}, {               0, 1,__18}, {               0, 1,__19}, {               0, 1,__1a}, {               0, 1,__1b}, {               0, 1,__1c}, {               0, 1,__1d}, {               0, 1,__1e}, {               0, 1,__1f}, 
	{               0, 1,__20}, {               0, 1,__21}, {               0, 1,__22}, {               0, 1,__23}, {               0, 1,__24}, {               0, 1,__25}, {               0, 1,__26}, {               0, 1,__27}, {               0, 1,__28}, {               0, 1,__29}, {               0, 1,__2a}, {               0, 1,__2b}, {               0, 1,__2c}, {               0, 1,__2d}, {               0, 1,__2e}, {               0, 1,__2f}, 
	{               0, 1,__30}, {               0, 1,__31}, {               0, 1,__32}, {               0, 1,__33}, {               0, 1,__34}, {               0, 1,__35}, {               0, 1,__36}, {               0, 1,__37}, {               0, 1,__38}, {               0, 1,__39}, {               0, 1,__3a}, {               0, 1,__3b}, {               0, 1,__3c}, {               0, 1,__3d}, {               0, 1,__3e}, {               0, 1,__3f}, 
	{               0, 1,__40}, {               0, 1,__41}, {               0, 1,__42}, {               0, 1,__43}, {               0, 1,__44}, {               0, 1,__45}, {               0, 1,__46}, {               0, 1,__47}, {               0, 1,__48}, {               0, 1,__49}, {               0, 1,__4a}, {               0, 1,__4b}, {               0, 1,__4c}, {               0, 1,__4d}, {               0, 1,__4e}, {               0, 1,__4f}, 
	{               0, 1,__50}, {               0, 1,__51}, {               0, 1,__52}, {               0, 1,__53}, {               0, 1,__54}, {               0, 1,__55}, {               0, 1,__56}, {               0, 1,__57}, {               0, 1,__58}, {               0, 1,__59}, {               0, 1,__5a}, {               0, 1,__5b}, {               0, 1,__5c}, {               0, 1,__5d}, {               0, 1,__5e}, {               0, 1,__5f}, 
	{               0, 1,__60}, {               0, 1,__61}, {               0, 1,__62}, {               0, 1,__63}, {               0, 1,__64}, {               0, 1,__65}, {               0, 1,__66}, {               0, 1,__67}, {               0, 1,__68}, {               0, 1,__69}, {               0, 1,__6a}, {               0, 1,__6b}, {               0, 1,__6c}, {               0, 1,__6d}, {               0, 1,__6e}, {               0, 1,__6f}, 
	{               0, 1,__70}, {               0, 1,__71}, {               0, 1,__72}, {               0, 1,__73}, {               0, 1,__74}, {               0, 1,__75}, {               0, 1,__76}, {               0, 1,__77}, {               0, 1,__78}, {               0, 1,__79}, {               0, 1,__7a}, {               0, 1,__7b}, {               0, 1,__7c}, {               0, 1,__7d}, {               0, 1,__7e}, {               0, 1,__7f}, 
	{               0, 1,__80}, {               0, 1,__81}, {               0, 1,__82}, {               0, 1,__83}, {               0, 1,__84}, {               0, 1,__85}, {               0, 1,__86}, {               0, 1,__87}, {               0, 1,__88}, {               0, 1,__89}, {               0, 1,__8a}, {               0, 1,__8b}, {               0, 1,__8c}, {               0, 1,__8d}, {               0, 1,__8e}, {               0, 1,__8f}, 
	{               0, 1,__90}, {               0, 1,__91}, {               0, 1,__92}, {               0, 1,__93}, {               0, 1,__94}, {               0, 1,__95}, {               0, 1,__96}, {               0, 1,__97}, {               0, 1,__98}, {               0, 1,__99}, {               0, 1,__9a}, {               0, 1,__9b}, {               0, 1,__9c}, {               0, 1,__9d}, {               0, 1,__9e}, {               0, 1,__9f}, 
	{               0, 1,__a0}, {               0, 1,__a1}, {               0, 1,__a2}, {               0, 1,__a3}, {               0, 1,__a4}, {               0, 1,__a5}, {               0, 1,__a6}, {               0, 1,__a7}, {               0, 1,__a8}, {               0, 1,__a9}, {               0, 1,__aa}, {               0, 1,__ab}, {               0, 1,__ac}, {               0, 1,__ad}, {               0, 1,__ae}, {               0, 1,__af}, 
	{               0, 1,__b0}, {               0, 1,__b1}, {               0, 1,__b2}, {               0, 1,__b3}, {               0, 1,__b4}, {               0, 1,__b5}, {               0, 1,__b6}, {               0, 1,__b7}, {               0, 1,__b8}, {               0, 1,__b9}, {               0, 1,__ba}, {               0, 1,__bb}, {               0, 1,__bc}, {               0, 1,__bd}, {               0, 1,__be}, {               0, 1,__bf}, 
	{               0, 1,__c0}, {               0, 1,__c1}, {               0, 1,__c2}, {               0, 1,__c3}, {               0, 1,__c4}, {               0, 1,__c5}, {               0, 1,__c6}, {               0, 1,__c7}, {               0, 1,__c8}, {               0, 1,__c9}, {               0, 1,__ca}, {               0, 1,__cb}, {               0, 1,__cc}, {               0, 1,__cd}, {               0, 1,__ce}, {               0, 1,__cf}, 
	{               0, 1,__d0}, {               0, 1,__d1}, {               0, 1,__d2}, {               0, 1,__d3}, {               0, 1,__d4}, {               0, 1,__d5}, {               0, 1,__d6}, {               0, 1,__d7}, {               0, 1,__d8}, {               0, 1,__d9}, {               0, 1,__da}, {               0, 1,__db}, {               0, 1,__dc}, {               0, 1,__dd}, {               0, 1,__de}, {               0, 1,__df}, 
	{               0, 1,__e0}, {               0, 1,__e1}, {               0, 1,__e2}, {               0, 1,__e3}, {               0, 1,__e4}, {               0, 1,__e5}, {               0, 1,__e6}, {               0, 1,__e7}, {               0, 1,__e8}, {               0, 1,__e9}, {               0, 1,__ea}, {               0, 1,__eb}, {               0, 1,__ec}, {               0, 1,__ed}, {               0, 1,__ee}, {               0, 1,__ef}, 
	{               0, 1,__f0}, {               0, 1,__f1}, {               0, 1,__f2}, {               0, 1,__f3}, {               0, 1,__f4}, {               0, 1,__f5}, {               0, 1,__f6}, {               0, 1,__f7}, {               0, 1,__f8}, {               0, 1,__f9}, {               0, 1,__fa}, {               0, 1,__fb}, {               0, 1,__fc}, {               0, 1,__fd}, {               0, 1,__fe}, {               0, 1,__ff}
};


char Disassembler::_00[4] = "NOP";
char Disassembler::_01[11] = "LD BC,XXXX";
char Disassembler::_02[10] = "LD (BC),A";
char Disassembler::_03[7] = "INC BC";
char Disassembler::_04[6] = "INC B";
char Disassembler::_05[6] = "DEC B";
char Disassembler::_06[8] = "LD B,XX";
char Disassembler::_07[5] = "RLCA";
char Disassembler::_08[13] = "LD (XXXX),SP";
char Disassembler::_09[10] = "ADD HL,BC";
char Disassembler::_0a[10] = "LD A,(BC)";
char Disassembler::_0b[7] = "DEC BC";
char Disassembler::_0c[6] = "INC C";
char Disassembler::_0d[6] = "DEC C";
char Disassembler::_0e[8] = "LD C,XX";
char Disassembler::_0f[5] = "RRCA";
char Disassembler::_10[7] = "STOP 0";
char Disassembler::_11[11] = "LD DE,XXXX";
char Disassembler::_12[10] = "LD (DE),A";
char Disassembler::_13[7] = "INC DE";
char Disassembler::_14[6] = "INC D";
char Disassembler::_15[6] = "DEC D";
char Disassembler::_16[8] = "LD D,XX";
char Disassembler::_17[4] = "RLA";
char Disassembler::_18[7] = "JR XXX";
char Disassembler::_19[10] = "ADD HL,DE";
char Disassembler::_1a[10] = "LD A,(DE)";
char Disassembler::_1b[7] = "DEC DE";
char Disassembler::_1c[6] = "INC E";
char Disassembler::_1d[6] = "DEC E";
char Disassembler::_1e[8] = "LD E,XX";
char Disassembler::_1f[4] = "RRA";
char Disassembler::_20[10] = "JR NZ,XXX";
char Disassembler::_21[11] = "LD HL,XXXX";
char Disassembler::_22[11] = "LD (HL+),A";
char Disassembler::_23[7] = "INC HL";
char Disassembler::_24[6] = "INC H";
char Disassembler::_25[6] = "DEC H";
char Disassembler::_26[8] = "LD H,XX";
char Disassembler::_27[4] = "DAA";
char Disassembler::_28[9] = "JR Z,XXX";
char Disassembler::_29[10] = "ADD HL,HL";
char Disassembler::_2a[11] = "LD A,(HL+)";
char Disassembler::_2b[7] = "DEC HL";
char Disassembler::_2c[6] = "INC L";
char Disassembler::_2d[6] = "DEC L";
char Disassembler::_2e[8] = "LD L,XX";
char Disassembler::_2f[4] = "CPL";
char Disassembler::_30[10] = "JR NC,XXX";
char Disassembler::_31[11] = "LD SP,XXXX";
char Disassembler::_32[11] = "LD (HL-),A";
char Disassembler::_33[7] = "INC SP";
char Disassembler::_34[9] = "INC (HL)";
char Disassembler::_35[9] = "DEC (HL)";
char Disassembler::_36[11] = "LD (HL),XX";
char Disassembler::_37[4] = "SCF";
char Disassembler::_38[9] = "JR C,XXX";
char Disassembler::_39[10] = "ADD HL,SP";
char Disassembler::_3a[11] = "LD A,(HL-)";
char Disassembler::_3b[7] = "DEC SP";
char Disassembler::_3c[6] = "INC A";
char Disassembler::_3d[6] = "DEC A";
char Disassembler::_3e[8] = "LD A,XX";
char Disassembler::_3f[4] = "CCF";
char Disassembler::_40[7] = "LD B,B";
char Disassembler::_41[7] = "LD B,C";
char Disassembler::_42[7] = "LD B,D";
char Disassembler::_43[7] = "LD B,E";
char Disassembler::_44[7] = "LD B,H";
char Disassembler::_45[7] = "LD B,L";
char Disassembler::_46[10] = "LD B,(HL)";
char Disassembler::_47[7] = "LD B,A";
char Disassembler::_48[7] = "LD C,B";
char Disassembler::_49[7] = "LD C,C";
char Disassembler::_4a[7] = "LD C,D";
char Disassembler::_4b[7] = "LD C,E";
char Disassembler::_4c[7] = "LD C,H";
char Disassembler::_4d[7] = "LD C,L";
char Disassembler::_4e[10] = "LD C,(HL)";
char Disassembler::_4f[7] = "LD C,A";
char Disassembler::_50[7] = "LD D,B";
char Disassembler::_51[7] = "LD D,C";
char Disassembler::_52[7] = "LD D,D";
char Disassembler::_53[7] = "LD D,E";
char Disassembler::_54[7] = "LD D,H";
char Disassembler::_55[7] = "LD D,L";
char Disassembler::_56[10] = "LD D,(HL)";
char Disassembler::_57[7] = "LD D,A";
char Disassembler::_58[7] = "LD E,B";
char Disassembler::_59[7] = "LD E,C";
char Disassembler::_5a[7] = "LD E,D";
char Disassembler::_5b[7] = "LD E,E";
char Disassembler::_5c[7] = "LD E,H";
char Disassembler::_5d[7] = "LD E,L";
char Disassembler::_5e[10] = "LD E,(HL)";
char Disassembler::_5f[7] = "LD E,A";
char Disassembler::_60[7] = "LD H,B";
char Disassembler::_61[7] = "LD H,C";
char Disassembler::_62[7] = "LD H,D";
char Disassembler::_63[7] = "LD H,E";
char Disassembler::_64[7] = "LD H,H";
char Disassembler::_65[7] = "LD H,L";
char Disassembler::_66[10] = "LD H,(HL)";
char Disassembler::_67[7] = "LD H,A";
char Disassembler::_68[7] = "LD L,B";
char Disassembler::_69[7] = "LD L,C";
char Disassembler::_6a[7] = "LD L,D";
char Disassembler::_6b[7] = "LD L,E";
char Disassembler::_6c[7] = "LD L,H";
char Disassembler::_6d[7] = "LD L,L";
char Disassembler::_6e[10] = "LD L,(HL)";
char Disassembler::_6f[7] = "LD L,A";
char Disassembler::_70[10] = "LD (HL),B";
char Disassembler::_71[10] = "LD (HL),C";
char Disassembler::_72[10] = "LD (HL),D";
char Disassembler::_73[10] = "LD (HL),E";
char Disassembler::_74[10] = "LD (HL),H";
char Disassembler::_75[10] = "LD (HL),L";
char Disassembler::_76[5] = "HALT";
char Disassembler::_77[10] = "LD (HL),A";
char Disassembler::_78[7] = "LD A,B";
char Disassembler::_79[7] = "LD A,C";
char Disassembler::_7a[7] = "LD A,D";
char Disassembler::_7b[7] = "LD A,E";
char Disassembler::_7c[7] = "LD A,H";
char Disassembler::_7d[7] = "LD A,L";
char Disassembler::_7e[10] = "LD A,(HL)";
char Disassembler::_7f[7] = "LD A,A";
char Disassembler::_80[8] = "ADD A,B";
char Disassembler::_81[8] = "ADD A,C";
char Disassembler::_82[8] = "ADD A,D";
char Disassembler::_83[8] = "ADD A,E";
char Disassembler::_84[8] = "ADD A,H";
char Disassembler::_85[8] = "ADD A,L";
char Disassembler::_86[11] = "ADD A,(HL)";
char Disassembler::_87[8] = "ADD A,A";
char Disassembler::_88[8] = "ADC A,B";
char Disassembler::_89[8] = "ADC A,C";
char Disassembler::_8a[8] = "ADC A,D";
char Disassembler::_8b[8] = "ADC A,E";
char Disassembler::_8c[8] = "ADC A,H";
char Disassembler::_8d[8] = "ADC A,L";
char Disassembler::_8e[11] = "ADC A,(HL)";
char Disassembler::_8f[8] = "ADC A,A";
char Disassembler::_90[6] = "SUB B";
char Disassembler::_91[6] = "SUB C";
char Disassembler::_92[6] = "SUB D";
char Disassembler::_93[6] = "SUB E";
char Disassembler::_94[6] = "SUB H";
char Disassembler::_95[6] = "SUB L";
char Disassembler::_96[9] = "SUB (HL)";
char Disassembler::_97[6] = "SUB A";
char Disassembler::_98[8] = "SBC A,B";
char Disassembler::_99[8] = "SBC A,C";
char Disassembler::_9a[8] = "SBC A,D";
char Disassembler::_9b[8] = "SBC A,E";
char Disassembler::_9c[8] = "SBC A,H";
char Disassembler::_9d[8] = "SBC A,L";
char Disassembler::_9e[11] = "SBC A,(HL)";
char Disassembler::_9f[8] = "SBC A,A";
char Disassembler::_a0[6] = "AND B";
char Disassembler::_a1[6] = "AND C";
char Disassembler::_a2[6] = "AND D";
char Disassembler::_a3[6] = "AND E";
char Disassembler::_a4[6] = "AND H";
char Disassembler::_a5[6] = "AND L";
char Disassembler::_a6[9] = "AND (HL)";
char Disassembler::_a7[6] = "AND A";
char Disassembler::_a8[6] = "XOR B";
char Disassembler::_a9[6] = "XOR C";
char Disassembler::_aa[6] = "XOR D";
char Disassembler::_ab[6] = "XOR E";
char Disassembler::_ac[6] = "XOR H";
char Disassembler::_ad[6] = "XOR L";
char Disassembler::_ae[9] = "XOR (HL)";
char Disassembler::_af[6] = "XOR A";
char Disassembler::_b0[5] = "OR B";
char Disassembler::_b1[5] = "OR C";
char Disassembler::_b2[5] = "OR D";
char Disassembler::_b3[5] = "OR E";
char Disassembler::_b4[5] = "OR H";
char Disassembler::_b5[5] = "OR L";
char Disassembler::_b6[8] = "OR (HL)";
char Disassembler::_b7[5] = "OR A";
char Disassembler::_b8[5] = "CP B";
char Disassembler::_b9[5] = "CP C";
char Disassembler::_ba[5] = "CP D";
char Disassembler::_bb[5] = "CP E";
char Disassembler::_bc[5] = "CP H";
char Disassembler::_bd[5] = "CP L";
char Disassembler::_be[8] = "CP (HL)";
char Disassembler::_bf[5] = "CP A";
char Disassembler::_c0[7] = "RET NZ";
char Disassembler::_c1[7] = "POP BC";
char Disassembler::_c2[11] = "JP NZ,XXXX";
char Disassembler::_c3[8] = "JP XXXX";
char Disassembler::_c4[13] = "CALL NZ,XXXX";
char Disassembler::_c5[8] = "PUSH BC";
char Disassembler::_c6[9] = "ADD A,XX";
char Disassembler::_c7[8] = "RST 00H";
char Disassembler::_c8[6] = "RET Z";
char Disassembler::_c9[4] = "RET";
char Disassembler::_ca[10] = "JP Z,XXXX";
char Disassembler::_cb[10] = "PREFIX CB";
char Disassembler::_cc[12] = "CALL Z,XXXX";
char Disassembler::_cd[10] = "CALL XXXX";
char Disassembler::_ce[9] = "ADC A,XX";
char Disassembler::_cf[8] = "RST 08H";
char Disassembler::_d0[7] = "RET NC";
char Disassembler::_d1[7] = "POP DE";
char Disassembler::_d2[11] = "JP NC,XXXX";
char Disassembler::_d4[13] = "CALL NC,XXXX";
char Disassembler::_d5[8] = "PUSH DE";
char Disassembler::_d6[7] = "SUB XX";
char Disassembler::_d7[8] = "RST 10H";
char Disassembler::_d8[6] = "RET C";
char Disassembler::_d9[5] = "RETI";
char Disassembler::_da[10] = "JP C,XXXX";
char Disassembler::_dc[12] = "CALL C,XXXX";
char Disassembler::_de[9] = "SBC A,XX";
char Disassembler::_df[8] = "RST 18H";
char Disassembler::_e0[16] = "LDH (XX+FF00),A";
char Disassembler::_e1[7] = "POP HL";
char Disassembler::_e2[14] = "LD (FF00+C),A";
char Disassembler::_e5[8] = "PUSH HL";
char Disassembler::_e6[7] = "AND XX";
char Disassembler::_e7[8] = "RST 20H";
char Disassembler::_e8[11] = "ADD SP,XXX";
char Disassembler::_e9[8] = "JP (HL)";
char Disassembler::_ea[12] = "LD (XXXX),A";
char Disassembler::_ee[7] = "XOR XX";
char Disassembler::_ef[8] = "RST 28H";
char Disassembler::_f0[16] = "LDH A,(XX+FF00)";
char Disassembler::_f1[7] = "POP AF";
char Disassembler::_f2[14] = "LD A,(FF00+C)";
char Disassembler::_f3[3] = "DI";
char Disassembler::_f5[8] = "PUSH AF";
char Disassembler::_f6[6] = "OR XX";
char Disassembler::_f7[8] = "RST 30H";
char Disassembler::_f8[13] = "LD HL,SP+XXX";
char Disassembler::_f9[9] = "LD SP,HL";
char Disassembler::_fa[12] = "LD A,(XXXX)";
char Disassembler::_fb[3] = "EI";
char Disassembler::_fe[6] = "CP XX";
char Disassembler::_ff[8] = "RST 38H";


char Disassembler::__00[6] = "RLC B";
char Disassembler::__01[6] = "RLC C";
char Disassembler::__02[6] = "RLC D";
char Disassembler::__03[6] = "RLC E";
char Disassembler::__04[6] = "RLC H";
char Disassembler::__05[6] = "RLC L";
char Disassembler::__06[9] = "RLC (HL)";
char Disassembler::__07[6] = "RLC A";
char Disassembler::__08[6] = "RRC B";
char Disassembler::__09[6] = "RRC C";
char Disassembler::__0a[6] = "RRC D";
char Disassembler::__0b[6] = "RRC E";
char Disassembler::__0c[6] = "RRC H";
char Disassembler::__0d[6] = "RRC L";
char Disassembler::__0e[9] = "RRC (HL)";
char Disassembler::__0f[6] = "RRC A";
char Disassembler::__10[5] = "RL B";
char Disassembler::__11[5] = "RL C";
char Disassembler::__12[5] = "RL D";
char Disassembler::__13[5] = "RL E";
char Disassembler::__14[5] = "RL H";
char Disassembler::__15[5] = "RL L";
char Disassembler::__16[8] = "RL (HL)";
char Disassembler::__17[5] = "RL A";
char Disassembler::__18[5] = "RR B";
char Disassembler::__19[5] = "RR C";
char Disassembler::__1a[5] = "RR D";
char Disassembler::__1b[5] = "RR E";
char Disassembler::__1c[5] = "RR H";
char Disassembler::__1d[5] = "RR L";
char Disassembler::__1e[8] = "RR (HL)";
char Disassembler::__1f[5] = "RR A";
char Disassembler::__20[6] = "SLA B";
char Disassembler::__21[6] = "SLA C";
char Disassembler::__22[6] = "SLA D";
char Disassembler::__23[6] = "SLA E";
char Disassembler::__24[6] = "SLA H";
char Disassembler::__25[6] = "SLA L";
char Disassembler::__26[9] = "SLA (HL)";
char Disassembler::__27[6] = "SLA A";
char Disassembler::__28[6] = "SRA B";
char Disassembler::__29[6] = "SRA C";
char Disassembler::__2a[6] = "SRA D";
char Disassembler::__2b[6] = "SRA E";
char Disassembler::__2c[6] = "SRA H";
char Disassembler::__2d[6] = "SRA L";
char Disassembler::__2e[9] = "SRA (HL)";
char Disassembler::__2f[6] = "SRA A";
char Disassembler::__30[7] = "SWAP B";
char Disassembler::__31[7] = "SWAP C";
char Disassembler::__32[7] = "SWAP D";
char Disassembler::__33[7] = "SWAP E";
char Disassembler::__34[7] = "SWAP H";
char Disassembler::__35[7] = "SWAP L";
char Disassembler::__36[10] = "SWAP (HL)";
char Disassembler::__37[7] = "SWAP A";
char Disassembler::__38[6] = "SRL B";
char Disassembler::__39[6] = "SRL C";
char Disassembler::__3a[6] = "SRL D";
char Disassembler::__3b[6] = "SRL E";
char Disassembler::__3c[6] = "SRL H";
char Disassembler::__3d[6] = "SRL L";
char Disassembler::__3e[9] = "SRL (HL)";
char Disassembler::__3f[6] = "SRL A";
char Disassembler::__40[8] = "BIT 0,B";
char Disassembler::__41[8] = "BIT 0,C";
char Disassembler::__42[8] = "BIT 0,D";
char Disassembler::__43[8] = "BIT 0,E";
char Disassembler::__44[8] = "BIT 0,H";
char Disassembler::__45[8] = "BIT 0,L";
char Disassembler::__46[11] = "BIT 0,(HL)";
char Disassembler::__47[8] = "BIT 0,A";
char Disassembler::__48[8] = "BIT 1,B";
char Disassembler::__49[8] = "BIT 1,C";
char Disassembler::__4a[8] = "BIT 1,D";
char Disassembler::__4b[8] = "BIT 1,E";
char Disassembler::__4c[8] = "BIT 1,H";
char Disassembler::__4d[8] = "BIT 1,L";
char Disassembler::__4e[11] = "BIT 1,(HL)";
char Disassembler::__4f[8] = "BIT 1,A";
char Disassembler::__50[8] = "BIT 2,B";
char Disassembler::__51[8] = "BIT 2,C";
char Disassembler::__52[8] = "BIT 2,D";
char Disassembler::__53[8] = "BIT 2,E";
char Disassembler::__54[8] = "BIT 2,H";
char Disassembler::__55[8] = "BIT 2,L";
char Disassembler::__56[11] = "BIT 2,(HL)";
char Disassembler::__57[8] = "BIT 2,A";
char Disassembler::__58[8] = "BIT 3,B";
char Disassembler::__59[8] = "BIT 3,C";
char Disassembler::__5a[8] = "BIT 3,D";
char Disassembler::__5b[8] = "BIT 3,E";
char Disassembler::__5c[8] = "BIT 3,H";
char Disassembler::__5d[8] = "BIT 3,L";
char Disassembler::__5e[11] = "BIT 3,(HL)";
char Disassembler::__5f[8] = "BIT 3,A";
char Disassembler::__60[8] = "BIT 4,B";
char Disassembler::__61[8] = "BIT 4,C";
char Disassembler::__62[8] = "BIT 4,D";
char Disassembler::__63[8] = "BIT 4,E";
char Disassembler::__64[8] = "BIT 4,H";
char Disassembler::__65[8] = "BIT 4,L";
char Disassembler::__66[11] = "BIT 4,(HL)";
char Disassembler::__67[8] = "BIT 4,A";
char Disassembler::__68[8] = "BIT 5,B";
char Disassembler::__69[8] = "BIT 5,C";
char Disassembler::__6a[8] = "BIT 5,D";
char Disassembler::__6b[8] = "BIT 5,E";
char Disassembler::__6c[8] = "BIT 5,H";
char Disassembler::__6d[8] = "BIT 5,L";
char Disassembler::__6e[11] = "BIT 5,(HL)";
char Disassembler::__6f[8] = "BIT 5,A";
char Disassembler::__70[8] = "BIT 6,B";
char Disassembler::__71[8] = "BIT 6,C";
char Disassembler::__72[8] = "BIT 6,D";
char Disassembler::__73[8] = "BIT 6,E";
char Disassembler::__74[8] = "BIT 6,H";
char Disassembler::__75[8] = "BIT 6,L";
char Disassembler::__76[11] = "BIT 6,(HL)";
char Disassembler::__77[8] = "BIT 6,A";
char Disassembler::__78[8] = "BIT 7,B";
char Disassembler::__79[8] = "BIT 7,C";
char Disassembler::__7a[8] = "BIT 7,D";
char Disassembler::__7b[8] = "BIT 7,E";
char Disassembler::__7c[8] = "BIT 7,H";
char Disassembler::__7d[8] = "BIT 7,L";
char Disassembler::__7e[11] = "BIT 7,(HL)";
char Disassembler::__7f[8] = "BIT 7,A";
char Disassembler::__80[8] = "RES 0,B";
char Disassembler::__81[8] = "RES 0,C";
char Disassembler::__82[8] = "RES 0,D";
char Disassembler::__83[8] = "RES 0,E";
char Disassembler::__84[8] = "RES 0,H";
char Disassembler::__85[8] = "RES 0,L";
char Disassembler::__86[11] = "RES 0,(HL)";
char Disassembler::__87[8] = "RES 0,A";
char Disassembler::__88[8] = "RES 1,B";
char Disassembler::__89[8] = "RES 1,C";
char Disassembler::__8a[8] = "RES 1,D";
char Disassembler::__8b[8] = "RES 1,E";
char Disassembler::__8c[8] = "RES 1,H";
char Disassembler::__8d[8] = "RES 1,L";
char Disassembler::__8e[11] = "RES 1,(HL)";
char Disassembler::__8f[8] = "RES 1,A";
char Disassembler::__90[8] = "RES 2,B";
char Disassembler::__91[8] = "RES 2,C";
char Disassembler::__92[8] = "RES 2,D";
char Disassembler::__93[8] = "RES 2,E";
char Disassembler::__94[8] = "RES 2,H";
char Disassembler::__95[8] = "RES 2,L";
char Disassembler::__96[11] = "RES 2,(HL)";
char Disassembler::__97[8] = "RES 2,A";
char Disassembler::__98[8] = "RES 3,B";
char Disassembler::__99[8] = "RES 3,C";
char Disassembler::__9a[8] = "RES 3,D";
char Disassembler::__9b[8] = "RES 3,E";
char Disassembler::__9c[8] = "RES 3,H";
char Disassembler::__9d[8] = "RES 3,L";
char Disassembler::__9e[11] = "RES 3,(HL)";
char Disassembler::__9f[8] = "RES 3,A";
char Disassembler::__a0[8] = "RES 4,B";
char Disassembler::__a1[8] = "RES 4,C";
char Disassembler::__a2[8] = "RES 4,D";
char Disassembler::__a3[8] = "RES 4,E";
char Disassembler::__a4[8] = "RES 4,H";
char Disassembler::__a5[8] = "RES 4,L";
char Disassembler::__a6[11] = "RES 4,(HL)";
char Disassembler::__a7[8] = "RES 4,A";
char Disassembler::__a8[8] = "RES 5,B";
char Disassembler::__a9[8] = "RES 5,C";
char Disassembler::__aa[8] = "RES 5,D";
char Disassembler::__ab[8] = "RES 5,E";
char Disassembler::__ac[8] = "RES 5,H";
char Disassembler::__ad[8] = "RES 5,L";
char Disassembler::__ae[11] = "RES 5,(HL)";
char Disassembler::__af[8] = "RES 5,A";
char Disassembler::__b0[8] = "RES 6,B";
char Disassembler::__b1[8] = "RES 6,C";
char Disassembler::__b2[8] = "RES 6,D";
char Disassembler::__b3[8] = "RES 6,E";
char Disassembler::__b4[8] = "RES 6,H";
char Disassembler::__b5[8] = "RES 6,L";
char Disassembler::__b6[11] = "RES 6,(HL)";
char Disassembler::__b7[8] = "RES 6,A";
char Disassembler::__b8[8] = "RES 7,B";
char Disassembler::__b9[8] = "RES 7,C";
char Disassembler::__ba[8] = "RES 7,D";
char Disassembler::__bb[8] = "RES 7,E";
char Disassembler::__bc[8] = "RES 7,H";
char Disassembler::__bd[8] = "RES 7,L";
char Disassembler::__be[11] = "RES 7,(HL)";
char Disassembler::__bf[8] = "RES 7,A";
char Disassembler::__c0[8] = "SET 0,B";
char Disassembler::__c1[8] = "SET 0,C";
char Disassembler::__c2[8] = "SET 0,D";
char Disassembler::__c3[8] = "SET 0,E";
char Disassembler::__c4[8] = "SET 0,H";
char Disassembler::__c5[8] = "SET 0,L";
char Disassembler::__c6[11] = "SET 0,(HL)";
char Disassembler::__c7[8] = "SET 0,A";
char Disassembler::__c8[8] = "SET 1,B";
char Disassembler::__c9[8] = "SET 1,C";
char Disassembler::__ca[8] = "SET 1,D";
char Disassembler::__cb[8] = "SET 1,E";
char Disassembler::__cc[8] = "SET 1,H";
char Disassembler::__cd[8] = "SET 1,L";
char Disassembler::__ce[11] = "SET 1,(HL)";
char Disassembler::__cf[8] = "SET 1,A";
char Disassembler::__d0[8] = "SET 2,B";
char Disassembler::__d1[8] = "SET 2,C";
char Disassembler::__d2[8] = "SET 2,D";
char Disassembler::__d3[8] = "SET 2,E";
char Disassembler::__d4[8] = "SET 2,H";
char Disassembler::__d5[8] = "SET 2,L";
char Disassembler::__d6[11] = "SET 2,(HL)";
char Disassembler::__d7[8] = "SET 2,A";
char Disassembler::__d8[8] = "SET 3,B";
char Disassembler::__d9[8] = "SET 3,C";
char Disassembler::__da[8] = "SET 3,D";
char Disassembler::__db[8] = "SET 3,E";
char Disassembler::__dc[8] = "SET 3,H";
char Disassembler::__dd[8] = "SET 3,L";
char Disassembler::__de[11] = "SET 3,(HL)";
char Disassembler::__df[8] = "SET 3,A";
char Disassembler::__e0[8] = "SET 4,B";
char Disassembler::__e1[8] = "SET 4,C";
char Disassembler::__e2[8] = "SET 4,D";
char Disassembler::__e3[8] = "SET 4,E";
char Disassembler::__e4[8] = "SET 4,H";
char Disassembler::__e5[8] = "SET 4,L";
char Disassembler::__e6[11] = "SET 4,(HL)";
char Disassembler::__e7[8] = "SET 4,A";
char Disassembler::__e8[8] = "SET 5,B";
char Disassembler::__e9[8] = "SET 5,C";
char Disassembler::__ea[8] = "SET 5,D";
char Disassembler::__eb[8] = "SET 5,E";
char Disassembler::__ec[8] = "SET 5,H";
char Disassembler::__ed[8] = "SET 5,L";
char Disassembler::__ee[11] = "SET 5,(HL)";
char Disassembler::__ef[8] = "SET 5,A";
char Disassembler::__f0[8] = "SET 6,B";
char Disassembler::__f1[8] = "SET 6,C";
char Disassembler::__f2[8] = "SET 6,D";
char Disassembler::__f3[8] = "SET 6,E";
char Disassembler::__f4[8] = "SET 6,H";
char Disassembler::__f5[8] = "SET 6,L";
char Disassembler::__f6[11] = "SET 6,(HL)";
char Disassembler::__f7[8] = "SET 6,A";
char Disassembler::__f8[8] = "SET 7,B";
char Disassembler::__f9[8] = "SET 7,C";
char Disassembler::__fa[8] = "SET 7,D";
char Disassembler::__fb[8] = "SET 7,E";
char Disassembler::__fc[8] = "SET 7,H";
char Disassembler::__fd[8] = "SET 7,L";
char Disassembler::__fe[11] = "SET 7,(HL)";
char Disassembler::__ff[8] = "SET 7,A";