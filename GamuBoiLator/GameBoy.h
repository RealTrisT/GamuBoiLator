#pragma once
#include "LR35902.h"

#pragma warning (disable: 4200)
struct GameBoy {
	GameBoy();

	struct ROMHeader {
	private:
		unsigned char nothing[0x100];			//0 - 100
	public:
		unsigned char entryPoint[0x4];			//100 - 104
		unsigned char logo[0x30];				//104 - 134
		         char Title[0x10];				//134 - 144
		unsigned char NewLicenseeCode[0x2];		//144 - 146
		unsigned char SGBflag;					//146
		unsigned char CartridgeType;			//147
		unsigned char RomSize;					//148
		unsigned char RamSize;					//149
		unsigned char DestinationCode;			//14A
		unsigned char OldLicenseeCode;			//14B
		unsigned char MaskRomVersionNumber;		//14C					//game version
		unsigned char HeaderChecksum;			//14D
		unsigned char GlobalChecksum[2];		//14E - 150
		unsigned char RestOfMemory[0];
		bool Read(char* romPath, unsigned char* errcode = &unused);
	};

	LR35902 CPU;
	LR35902::Memory& memory = CPU.memory;
	ROMHeader* rom;

	void RunBios();

private:
	static const unsigned char GB_BIOS[256];
	static unsigned char unused;
};