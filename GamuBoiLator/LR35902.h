#pragma once

struct LR35902 {

	//------------------------------------------------------------------------------------------------------
	struct Registers {
		union {
			unsigned char ra[8];
			unsigned short rb[4];
															#pragma pack(push, 1)
			struct flagRegister { private: unsigned char nothing : 4; public: unsigned char c : 1, h : 1, s : 1, z : 1; };
			struct R8 {
				union {
					flagRegister F;
					unsigned char F_;
				};
				unsigned char A, C, B, E, D, L, H;			//they're switched because windows is little endian so for AF to have the most significant byte in A
			}r8;											//it needs to be switched since the most significant byte will be the second
			struct R16 {
				unsigned short AF, BC, DE, HL;
			}r16;
															#pragma pack(pop)
		};
		unsigned short SP, PC;
	} registers;

	bool InterruptsActive, Halting, Stopped;

	//------------------------------------------------------------------------------------------------------
	struct Opcode {
		void (LR35902::*Handler)(unsigned char*);
		unsigned char Length;
	};


	//------------------------------------------------------------------------------------------------------
	typedef unsigned char* Memory;Memory memory;
	#define RealPtr(x) (memory+x)


	//------------------------------------------------------------------------------------------------------
	void RunInstruction();
	void __RunInstruction(unsigned char*);
private:

	void push(unsigned char);
	void push(unsigned short);


	//control
	void STOP(unsigned char*); //Stop processor & screen until button press
	void HALT(unsigned char*); //Stop processor & screen until interrupt
	void   EI(unsigned char*); // enable interrupts
	void   DI(unsigned char*); //disable interrupts

	//execution
	void  NOP(unsigned char*);	void   JR(unsigned char*);	void   JP(unsigned char*);	void CALL(unsigned char*);	
	void  RST(unsigned char*);	void  RET(unsigned char*);	void RETI(unsigned char*);

	//memory
	void   LD(unsigned char*);	void  POP(unsigned char*);	void PUSH(unsigned char*);
	
	//arithmetic
	void  INC(unsigned char*);	void  DEC(unsigned char*);	void  ADD(unsigned char*);	void  ADC(unsigned char*);
	void  SUB(unsigned char*);	void  SBC(unsigned char*);	void  DAA(unsigned char*);	void  SCF(unsigned char*);

	//bitwise
	void  AND(unsigned char*);	void  XOR(unsigned char*);	void   OR(unsigned char*);	void RLCA(unsigned char*);
	void RRCA(unsigned char*);	void  RLA(unsigned char*);	void  RRA(unsigned char*);	void  CPL(unsigned char*);
	void  CCF(unsigned char*);

	//comparison
	void   CP(unsigned char*);

	//prefix
	void PFCB(unsigned char*);


	//EXTENDED BITWISE INSTRUCTIONS

	void  RLC(unsigned char*);	void  RRC(unsigned char*);	void   RL(unsigned char*);	void   RR(unsigned char*);
	void  SLA(unsigned char*);	void  SRA(unsigned char*);	void SWAP(unsigned char*);	void  SRL(unsigned char*);
	void  BIT(unsigned char*);	void  RES(unsigned char*);	void  SET(unsigned char*);

#define NTHN 0
#define N    0
#define CB	 PFCB
#define LRF &LR35902::
	Opcode opcodes[0x200] = {
		{LRF  NOP, 1 }, {LRF   LD, 3 }, {LRF   LD, 1 }, {LRF  INC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF RLCA, 1 }, {LRF   LD, 3 }, {LRF  ADD, 1 }, {LRF   LD, 1 }, {LRF  DEC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF RRCA, 1 },
		{LRF STOP, 2 }, {LRF   LD, 3 }, {LRF   LD, 1 }, {LRF  INC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  RLA, 1 }, {LRF   JR, 2 }, {LRF  ADD, 1 }, {LRF   LD, 1 }, {LRF  DEC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  RRA, 1 }, 
		{LRF   JR, 2 }, {LRF   LD, 3 }, {LRF   LD, 1 }, {LRF  INC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  DAA, 1 }, {LRF   JR, 2 }, {LRF  ADD, 1 }, {LRF   LD, 1 }, {LRF  DEC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  CPL, 1 }, 
		{LRF   JR, 2 }, {LRF   LD, 3 }, {LRF   LD, 1 }, {LRF  INC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  SCF, 1 }, {LRF   JR, 2 }, {LRF  ADD, 1 }, {LRF   LD, 1 }, {LRF  DEC, 1 }, {LRF  INC, 1 }, {LRF  DEC, 1 }, {LRF   LD, 2 }, {LRF  CCF, 1 }, 
		{LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, 
		{LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, 
		{LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, 
		{LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF HALT, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, {LRF   LD, 1 }, 
		{LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADD, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, {LRF  ADC, 1 }, 
		{LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SUB, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, {LRF  SBC, 1 }, 
		{LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  AND, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, {LRF  XOR, 1 }, 
		{LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   OR, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, {LRF   CP, 1 }, 
		{LRF  RET, 1 }, {LRF  POP, 1 }, {LRF   JP, 3 }, {LRF   JP, 3 }, {LRF CALL, 3 }, {LRF PUSH, 1 }, {LRF  ADD, 2 }, {LRF  RST, 1 }, {LRF  RET, 1 }, {LRF  RET, 1 }, {LRF   JP, 3 }, {LRF   CB, 1 }, {LRF CALL, 3 }, {LRF CALL, 3 }, {LRF  ADC, 2 }, {LRF  RST, 1 }, 
		{LRF  RET, 1 }, {LRF  POP, 1 }, {LRF   JP, 3 }, {NTHN    , N }, {LRF CALL, 3 }, {LRF PUSH, 1 }, {LRF  SUB, 2 }, {LRF  RST, 1 }, {LRF  RET, 1 }, {LRF  RET, 1 }, {LRF   JP, 3 }, {NTHN    , N }, {LRF CALL, 3 }, {NTHN    , N }, {LRF  SBC, 2 }, {LRF  RST, 1 },
		{LRF   LD, 2 }, {LRF  POP, 1 }, {LRF   LD, 2 }, {NTHN    , N }, {NTHN    , N }, {LRF PUSH, 1 }, {LRF  AND, 2 }, {LRF  RST, 1 }, {LRF  ADD, 2 }, {LRF   JP, 1 }, {LRF   LD, 3 }, {NTHN    , N }, {NTHN    , N }, {NTHN    , N }, {LRF  XOR, 2 }, {LRF  RST, 1 },
		{LRF   LD, 2 }, {LRF  POP, 1 }, {LRF   LD, 2 }, {LRF   DI, 1 }, {NTHN    , N }, {LRF PUSH, 1 }, {LRF   OR, 2 }, {LRF  RST, 1 }, {LRF   LD, 2 }, {LRF   LD, 1 }, {LRF   LD, 3 }, {LRF   EI, 1 }, {NTHN    , N }, {NTHN    , N }, {LRF   CP, 2 }, {LRF  RST, 1 },
		//---------------------------------------------------------------------------------------------------CB-PREFIX-------------------------------------------------------------------------------------------------
		{LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RLC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, {LRF  RRC, 1 }, 
		{LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RL, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, {LRF   RR, 1 }, 
		{LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SLA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, {LRF  SRA, 1 }, 
		{LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF SWAP, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, {LRF  SRL, 1 }, 
		{LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, 
		{LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, 
		{LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, 
		{LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, {LRF  BIT, 1 }, 
		{LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, 
		{LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, 
		{LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, 
		{LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, {LRF  RES, 1 }, 
		{LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, 
		{LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, 
		{LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, 
		{LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, {LRF  SET, 1 }, 
	};
};