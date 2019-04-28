class Chip8
{
public:
	Chip8();
	void reset();
	void load(std::string filename);
	BYTE* getDisplayBuffer();
	
	BYTE getDT();
	void decDT();
	BYTE getST();
	void decST();

	Instr emulate();

	void op0(Instr &ins);
	void op1(Instr &ins);
	void op2(Instr &ins);
	void op3(Instr &ins);
	void op4(Instr &ins);
	void op5(Instr &ins);
	void op6(Instr &ins);
	void op7(Instr &ins);
	void op8(Instr &ins);
	void op9(Instr &ins);
	void opA(Instr &ins);
	void opB(Instr &ins);
	void opC(Instr &ins);
	void opD(Instr &ins);
	void opE(Instr &ins);
	void opF(Instr &ins);

private:
	std::vector<BYTE> MEM;
	std::vector<BYTE> V;
	ADDRESS I;
	ADDRESS PC;
	ADDRESS SP;
	BYTE DT;
	BYTE ST;

}; 