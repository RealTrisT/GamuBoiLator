#include "LR35902.h"
#include <stdio.h>

void LR35902::RunInstruction() {
	__RunInstruction(RealPtr(registers.PC));
}

void LR35902::__RunInstruction(unsigned char* CurrInstruction){
	registers.PC += opcodes[*(CurrInstruction)].Length;
	(this->*(this->opcodes[*(CurrInstruction)].Handler))(CurrInstruction);
}

void LR35902::push(unsigned char val){
	registers.SP--;
	*(unsigned char*)RealPtr(registers.SP) = val;
}

void LR35902::push(unsigned short val){
	registers.SP -= 2;
	*(unsigned short*)RealPtr(registers.SP) = val;
}

void LR35902::PFCB(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("CB PREFIX:");
	registers.PC++;
	(this->*(this->opcodes[(*(++CurrInstruction))+0x100].Handler))(CurrInstruction);
}


unsigned char registerIndexes[8] = {3, 2, 5, 4, 7, 6, -1, 1};
unsigned char registerIndexes_16[4] = { 1, 2, 3, 0 };


void LR35902::RLC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RLC");
	unsigned char lastBit;
	unsigned char* LeByte;
	if (*CurrInstruction == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*CurrInstruction]];
	}
	lastBit = *LeByte >> 7;
	(*LeByte <<= 1) |= lastBit;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::RRC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RRC");
	unsigned char lastBit;
	unsigned char* LeByte;
	if ((*CurrInstruction - 8) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 8]];
	}
	lastBit = *LeByte & 1;
	(*LeByte >>= 1) |= lastBit << 7;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::RL(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RL");
	unsigned char lastBit;
	unsigned char* LeByte;
	if ((*CurrInstruction - 16) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 16]];
	}
	lastBit = *LeByte >> 7;
	(*LeByte <<= 1) |= (registers.r8.F_ >> 4 & 1);
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::RR(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RR");
	unsigned char lastBit;
	unsigned char* LeByte;
	if ((*CurrInstruction - 24) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 24]];
	}
	lastBit = *LeByte & 1;
	(*LeByte >>= 1) |= ((registers.r8.F_ >> 4 & 1) << 7);
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::SLA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SLA");
	unsigned char lastBit;
	unsigned char* LeByte;
	if ((*CurrInstruction - 32) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 32]];
	}
	lastBit = *LeByte >> 7;
	*LeByte <<= 1;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::SRA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SRA");
	unsigned char lastBit_left;
	unsigned char* LeByte;
	if ((*CurrInstruction - 40) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 40]];
	}
	lastBit_left = *LeByte & 0x7F;
	(*LeByte >>= 1) |= lastBit_left;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::SWAP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SWAP");
	unsigned char* LeByte;
	if ((*CurrInstruction - 48) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 48]];
	}
	unsigned char left_out = *LeByte >> 4;
	(*LeByte <<= 4) |= left_out;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::SRL(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SRL");
	unsigned char lastBit;
	unsigned char* LeByte;
	if ((*CurrInstruction - 56) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) - 56]];
	}
	lastBit = *LeByte & 1;
	*LeByte >>= 1;
	registers.r8.F_ &= 0x0F;
	registers.r8.F_ |= (lastBit << 4);
	registers.r8.F_ |= ((!(*LeByte)) << 7);
}

void LR35902::BIT(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("BIT");
	unsigned char* LeByte;
	if ((*CurrInstruction % 8) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) % 8]];
	}
	unsigned char bit = 1 << ((*CurrInstruction - 64) / 8); 
	unsigned char result = *LeByte & bit;
	registers.r8.F_ &= 0x1F; 
	registers.r8.F_ |= 0x20;
	registers.r8.F_ |= ((!result) << 7);
}

void LR35902::RES(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RES");
	unsigned char* LeByte;
	if ((*CurrInstruction % 8) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	} else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) / 8]];
	}
	unsigned char mask = ~(1 << ((*CurrInstruction - 128) % 8));
	*LeByte &= mask;
}

void LR35902::SET(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SET");
	unsigned char* LeByte;
	if ((*CurrInstruction % 8) == 0x06) {
		LeByte = RealPtr(registers.r16.HL);
	}
	else {
		LeByte = &registers.ra[registerIndexes[*(CurrInstruction) / 8]];
	}
	unsigned char bit = 1 << ((*CurrInstruction - 128) % 8);
	*LeByte |= bit;
}


void LR35902::NOP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("NOP");
	return;
}

void LR35902::STOP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("STOP");
	Stopped = true;
}

void LR35902::HALT(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("HALT");
	Halting = true;
}

void LR35902::EI(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("EI");
	InterruptsActive = true;
}

void LR35902::DI(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("DI");
	InterruptsActive = false;
}


void LR35902::JR(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("JR");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	bool conditionMet = true;

	if (leftNibble == 0x2) {			//zero  flag
		conditionMet = (registers.r8.F_ & 0x80);
		if (!rightNibble) conditionMet = !conditionMet;
	} else if (leftNibble == 0x3) {	//carry flag
		conditionMet = (registers.r8.F_ & 0x10);
		if (!rightNibble) conditionMet = !conditionMet;
	}
	if(conditionMet) registers.PC += *(signed char*)(CurrInstruction + 1);
}

void LR35902::JP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("JP");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	bool conditionMet = true;

	if (rightNibble == 0x2) {			//NOT conditional
		conditionMet = !(leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	} else if (rightNibble == 0xA) {	//YES conditional
		conditionMet =  (leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	} else if (rightNibble == 0x9) {	//HL dereference unconditional
		registers.PC = *(unsigned short*)RealPtr(registers.r16.HL);
		return;
	}
	if(conditionMet) registers.PC = *(unsigned short*)(CurrInstruction + 1);
}

void LR35902::CALL(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("CALL");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	bool conditionMet = true;

	if (rightNibble == 0x4) {			//NOT conditional
		conditionMet = !(leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	}
	else if (rightNibble == 0xC) {		//YES conditional
		conditionMet =  (leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	}

	if (conditionMet) {
		push(registers.PC);
		registers.PC = *(unsigned short*)(CurrInstruction + 1);
	}
}

void LR35902::RST(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RST");
	push(registers.PC);
	registers.PC = (((*CurrInstruction >> 4)-0xC) << 4) + (((*CurrInstruction & 0x0F) == 0xF)?0x8:0x0);
}

void LR35902::RET(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RET");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	bool conditionMet = true;

	if (!rightNibble) {					//NOT conditional
		conditionMet = !(leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	}
	else if (rightNibble == 0x8) {		//YES conditional
		conditionMet =  (leftNibble == 0xC ? registers.r8.F_ & 0x80 : registers.r8.F_ & 0x10);
	}

	if (conditionMet) {
		registers.PC = *(unsigned short*)RealPtr(registers.SP);
		registers.SP += 2;
	}
}

void LR35902::RETI(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RETI");
}

void LR35902::LD(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("LD");
	unsigned char* From = 0;
	unsigned char* To   = 0;
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;


	if (leftNibble < 0x4) {		//0-3
		if (rightNibble == 0x6 || rightNibble == 0xE) {
			if (((*CurrInstruction) / 8) == 0x06)		To = RealPtr(registers.r16.HL);
			else										To = &registers.ra[registerIndexes[((*CurrInstruction) / 8)]];
			*To = *(CurrInstruction + 1);
		} else if (rightNibble == 0x1) {
			*(unsigned short*)((leftNibble < 3) ? &registers.rb[registerIndexes_16[leftNibble]] : &registers.SP) = *(unsigned short*)(CurrInstruction+1);
		} else if (rightNibble == 0x2){
			if (leftNibble < 2)	registers.rb[registerIndexes_16[leftNibble]] = registers.r8.A;
			else					*(unsigned char*)RealPtr(((leftNibble == 2) ? registers.r16.HL++ : registers.r16.HL--)) = registers.r8.A;
		} else if (rightNibble == 0xA){
			if (leftNibble < 2)	registers.r8.A = *(unsigned char*)RealPtr(registers.rb[registerIndexes_16[leftNibble]]);
			else				registers.r8.A = *(unsigned char*)RealPtr(((leftNibble == 2) ? registers.r16.HL++ : registers.r16.HL--));
		} else if (rightNibble == 0x8){
			*(unsigned short*)RealPtr(*(unsigned short*)(CurrInstruction + 1)) = registers.SP;
		}
	}else if (leftNibble < 0x8){	//4-7
		if ((*CurrInstruction % 8) == 0x06)			From = RealPtr(registers.r16.HL);
		else										From = &registers.ra[registerIndexes[*(CurrInstruction) % 8]];
		if (((*CurrInstruction - 64) / 8) == 0x06)	To = RealPtr(registers.r16.HL);
		else										To = &registers.ra[registerIndexes[((*CurrInstruction - 64) / 8)]];
		*To = *From;
	}else{							//E-F
		if (rightNibble == 0xA) {
			if (leftNibble == 0xE)		*(unsigned char*)RealPtr(*(unsigned short*)(CurrInstruction + 1)) = registers.r8.A;
			else						registers.r8.A = *(unsigned char*)RealPtr(*(unsigned short*)(CurrInstruction + 1));
		}else if (rightNibble == 0x9) {
			registers.SP = registers.r16.HL;
		}else if(rightNibble == 0x2){
			if (leftNibble == 0xE)	*(unsigned char*)RealPtr(0xFF00 + registers.r8.C) = registers.r8.A;
			else					registers.r8.A = *(unsigned char*)RealPtr(0xFF00 + registers.r8.C);
		}else if(rightNibble == 0x8){																								//TODO: set flags
			
			signed char immediate = *(signed char*)(CurrInstruction + 1);
			registers.r16.HL = registers.SP + immediate;

			registers.r8.F_ = 0;
			if (immediate < 0) { //negative
				registers.r8.F.c = registers.r16.HL > registers.SP; // if it's negative, the carry should be set if the number is bigger, cuz that'd mean stack ptr underflow
				registers.r8.F.h = (registers.r16.HL&0x0FFF) > (registers.SP&0x0FFF);
			} else {
				registers.r8.F.c = registers.r16.HL < registers.SP; // if it's positive, the carry should be set if the number is smaller, cuz that'd mean stack ptr overflow
				registers.r8.F.h = (registers.r16.HL & 0x0FFF) < (registers.SP & 0x0FFF);
			}
		}else if (!rightNibble) {
			if (leftNibble == 0xE)	*(unsigned char*)RealPtr(0xFF00 + *(CurrInstruction + 1)) = registers.r8.A;
			else					registers.r8.A = *(unsigned char*)RealPtr(0xFF00 + *(CurrInstruction + 1));
		}
	}
}

void LR35902::POP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("POP");
	unsigned char leftNibble = *CurrInstruction >> 4;
	registers.rb[registerIndexes_16[leftNibble - 0xC]] = *(unsigned short*)RealPtr(registers.SP);
	registers.SP += 2;
}

void LR35902::PUSH(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("PUSH");
	unsigned char leftNibble = *CurrInstruction >> 4;
	registers.SP -= 2;
	*(unsigned short*)RealPtr(registers.SP) = registers.rb[registerIndexes_16[leftNibble - 0xC]];
}

void LR35902::INC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("INC");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	if (rightNibble == 0x3) {
		((leftNibble == 0x3) ? registers.SP : registers.rb[registerIndexes_16[leftNibble]])++;
	} else {
		unsigned char InstructionOperandID = (*CurrInstruction) >> 3;
		unsigned char* LeByte = ((InstructionOperandID == 6) ? RealPtr(registers.r16.HL) : &registers.ra[registerIndexes[InstructionOperandID]]);
		unsigned char after = ++(*LeByte);
		registers.r8.F_ &= 0x10;
		registers.r8.F_ |= (!after) << 7;
		registers.r8.F_ |= (!(after & 0x0F)) << 5;
	}
}

void LR35902::DEC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("DEC");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	if (rightNibble == 0x8) {
		((leftNibble == 0x3) ? registers.SP : registers.rb[registerIndexes_16[leftNibble]])--;
	} else {
		unsigned char InstructionOperandID = (*CurrInstruction) >> 3;
		unsigned char* LeByte = ((InstructionOperandID == 6) ? RealPtr(registers.r16.HL) : &registers.ra[registerIndexes[InstructionOperandID]]);
		unsigned char after = --(*LeByte);
		registers.r8.F_ &= 0x10;
		registers.r8.F_ |= 0x40;
		registers.r8.F_ |= (!after) << 7;
		registers.r8.F_ |= (!(after & 0x0F ^ 0x0F)) << 5;
	}
}

void LR35902::ADD(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("ADD");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	if (leftNibble < 0x4) { //16 bit
		unsigned short before = registers.r16.HL;
		registers.r16.HL += (leftNibble == 0x3) ? registers.SP : registers.rb[registerIndexes_16[leftNibble]];

		registers.r8.F_ &= 0x80;
		registers.r8.F_ |= (before > registers.r16.HL) << 4;
		registers.r8.F_ |= ((before & 0x0FFF) > (registers.r16.HL & 0x0FFF)) << 5;
	} else if(leftNibble < 0xC) {
		unsigned char before = registers.r8.A;
		registers.r8.A += (rightNibble == 0x6) ? *(unsigned char*)RealPtr(registers.r16.HL) : registers.ra[registerIndexes[rightNibble]];

		registers.r8.F_ = 0;
		registers.r8.F_ |= (before > registers.r8.A) << 4;
		registers.r8.F_ |= ((before & 0x0F) > (registers.r8.A & 0x0F)) << 5;
		registers.r8.F_ |= (!registers.r8.A) << 7;
	} else if(leftNibble < 0xD) {
		unsigned char before = registers.r8.A;
		registers.r8.A += *(CurrInstruction + 1);

		registers.r8.F_ = 0;
		registers.r8.F_ |= (before > registers.r8.A) << 4;
		registers.r8.F_ |= ((before & 0x0F) > (registers.r8.A & 0x0F)) << 5;
		registers.r8.F_ |= (!registers.r8.A) << 7;
	} else {
		signed char immediate = *(signed char*)(CurrInstruction + 1);
		unsigned short before = registers.SP;
		registers.SP += immediate;
		registers.r8.F_ = 0;
		if (immediate < 0) { //negative
			registers.r8.F.c = registers.SP > before; // if it's negative, the carry should be set if the number is bigger, cuz that'd mean stack ptr underflow
			registers.r8.F.h = (registers.SP&0x0FFF) > (before&0x0FFF);
		} else {
			registers.r8.F.c = registers.SP < before; // if it's positive, the carry should be set if the number is smaller, cuz that'd mean stack ptr overflow
			registers.r8.F.h = (registers.SP&0x0FFF) < (before&0x0FFF);
		}
	}
}

void LR35902::ADC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("ADC");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	unsigned char before = registers.r8.A;
	if (leftNibble < 0xC)
		registers.r8.A += (rightNibble - 8 == 6) ? *(unsigned char*)RealPtr(registers.r16.HL) : registers.ra[registerIndexes[rightNibble - 8]];
	else
		registers.r8.A += *(CurrInstruction + 1);

	registers.r8.A += (registers.r8.F_ >> 4 & 1); // carry flag

	registers.r8.F_ = 0;
	registers.r8.F_ |= (before > registers.r8.A) << 4;
	registers.r8.F_ |= ((before & 0x0F) > (registers.r8.A & 0x0F)) << 5;
	registers.r8.F_ |= (!registers.r8.A) << 7;
}

void LR35902::SUB(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SUB");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	unsigned char before = registers.r8.A;
	if (leftNibble < 0xC)
		registers.r8.A -= (rightNibble - 8 == 6) ? *(unsigned char*)RealPtr(registers.r16.HL) : registers.ra[registerIndexes[rightNibble - 8]];
	else
		registers.r8.A -= *(CurrInstruction + 1);

	registers.r8.F_ = 0x40;
	registers.r8.F_ |= (before < registers.r8.A) << 4;
	registers.r8.F_ |= ((before & 0x0F) < (registers.r8.A & 0x0F)) << 5;
	registers.r8.F_ |= (!registers.r8.A) << 7;
}

void LR35902::SBC(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SBC");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	unsigned char before = registers.r8.A;
	if (leftNibble < 0xC)
		registers.r8.A -= (rightNibble - 8 == 6) ? *(unsigned char*)RealPtr(registers.r16.HL) : registers.ra[registerIndexes[rightNibble - 8]];
	else
		registers.r8.A -= *(CurrInstruction + 1);

	registers.r8.A -= (registers.r8.F_ >> 4 & 1); // carry flag

	registers.r8.F_ = 0x40;			// 0 1 0 0
	registers.r8.F_ |= (before < registers.r8.A) << 4;
	registers.r8.F_ |= ((before & 0x0F) < (registers.r8.A & 0x0F)) << 5;
	registers.r8.F_ |= (!registers.r8.A) << 7;
}

void LR35902::DAA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("DAA");
	registers.r8.F_ &= 0x40;		// 0 - 0 0
	if (((registers.r8.A & 0x0F) > 9) || registers.r8.F.h)
		registers.r8.A += 0x06;
	if (((registers.r8.A >> 4) > 9) || registers.r8.F.c){
		registers.r8.A += 0x60;
		registers.r8.F.c = 1;
	}
	registers.r8.F.z = !registers.r8.A;

}

void LR35902::SCF(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("SCF");
	registers.r8.F_ &= 0x80;				// - 0 0 0
	registers.r8.F.c = 1;
}

void LR35902::AND(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("AND");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	
	if(leftNibble < 0xC)	registers.r8.A &= (rightNibble == 0x6) ? *(unsigned char*)RealPtr(registers.r8.H) : registers.ra[registerIndexes[rightNibble]];
	else					registers.r8.A &= *(unsigned char*)(CurrInstruction + 1);

	registers.r8.F_ = 0x20;					// 0 0 1 0
	registers.r8.F.z = !registers.r8.A;
}

void LR35902::XOR(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("XOR");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	rightNibble -= 8;

	if(leftNibble < 0xC)	registers.r8.A ^= (rightNibble == 0x6) ? *(unsigned char*)RealPtr(registers.r8.H) : registers.ra[registerIndexes[rightNibble]];
	else					registers.r8.A ^= *(unsigned char*)(CurrInstruction + 1);

	registers.r8.F_ = 0x00;					// 0 0 0 0
	registers.r8.F.z = !registers.r8.A;
}

void LR35902::OR(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("OR");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;

	if(leftNibble < 0xC)	registers.r8.A |= (rightNibble == 0x6) ? *(unsigned char*)RealPtr(registers.r8.H) : registers.ra[registerIndexes[rightNibble]];
	else					registers.r8.A |= *(unsigned char*)(CurrInstruction + 1);

	registers.r8.F_ = 0x00;					// 0 0 0 0
	registers.r8.F.z = !registers.r8.A;
}

void LR35902::RLCA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RLCA");
	registers.r8.F_ = 0;
	registers.r8.F.c = registers.r8.A >> 7;
	registers.r8.A <<= 1;
	registers.r8.A |= registers.r8.F.c;
}

void LR35902::RRCA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RRCA");
	registers.r8.F_ = 0;
	registers.r8.F.c = registers.r8.A & 1;
	registers.r8.A >>= 1;
	registers.r8.A |= registers.r8.F.c << 7;
}

void LR35902::RLA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RLA");
	unsigned char leavingBit = registers.r8.A >> 7;
	registers.r8.A <<= 1;
	registers.r8.A |= registers.r8.F.c;

	registers.r8.F_ = 0;
	registers.r8.F.c = leavingBit;
}

void LR35902::RRA(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("RRA");
	unsigned char leavingBit = registers.r8.A & 1;
	registers.r8.A >>= 1;
	registers.r8.A |= registers.r8.F.c << 7;

	registers.r8.F_ = 0;
	registers.r8.F.c = leavingBit;
}

void LR35902::CPL(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("CPL");
	registers.r8.A = ~registers.r8.A;
	registers.r8.F_ |= 0x60;					// - 1 1 -
}

void LR35902::CCF(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("CCF");
	registers.r8.F_ &= 0x90;					// - 0 0 -
	registers.r8.F.c = !registers.r8.F.c;
}

void LR35902::CP(unsigned char* CurrInstruction){/*debug_instruction_name_print*///puts("CP");
	unsigned char rightNibble = *CurrInstruction & 0x0F;
	unsigned char leftNibble = *CurrInstruction >> 4;
	rightNibble -= 8;

	unsigned char temp = registers.r8.A;

	if (leftNibble < 0xC)	temp -= (rightNibble == 0x6) ? *(unsigned char*)RealPtr(registers.r16.HL) : registers.ra[registerIndexes[rightNibble]];
	else					temp -= *(unsigned char*)(CurrInstruction + 1);

	registers.r8.F_ = 0x40;						// 0 1 0 0
	registers.r8.F.z = !temp;
	registers.r8.F.c = temp > registers.r8.A;
	registers.r8.F.h = (temp&0x0F) > (registers.r8.A&0x0F);
}