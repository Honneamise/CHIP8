#include "headers.hpp"

Chip8::Chip8()
{
	MEM.resize(MAX_MEMORY);
	V.resize(NUM_REGISTERS);
	I = 0;
	PC = BASE_LOAD;
	SP = BASE_STACK;
	DT = 0x00;
	ST = 0x00;

	//load the charset in memory
	Charset charset;

	for (unsigned i = 0; i < CHARSET_SIZE; i++)
	{
		std::vector<BYTE> v = charset[i];

		for (auto j = 0; j < CHARSET_CHAR_DIM; j++)
		{
			MEM[BASE_CHARSET + (i * CHARSET_CHAR_DIM) + j] = v[j];
		};
	};

}

void Chip8::reset()
{
	MEM.resize(0);
	MEM.resize(MAX_MEMORY);

	V.resize(0);
	V.resize(NUM_REGISTERS);
	I = 0;
	PC = BASE_LOAD;
	SP = BASE_STACK;
	DT = 0x00;
	ST = 0x00;

	//reload the charset
	Charset charset;

	for (unsigned i = 0; i < CHARSET_SIZE; i++)
	{
		std::vector<BYTE> v = charset[i];

		for (auto j = 0; j < CHARSET_CHAR_DIM; j++)
		{
			MEM[BASE_CHARSET + (i * CHARSET_CHAR_DIM) + j] = v[j];
		};
	};
}

void Chip8::load(std::string filename)
{
	std::ifstream stream(filename, std::ios::binary);

	stream.seekg(0, stream.end);

	int size = (int)stream.tellg();

	stream.seekg(0, stream.beg);

	stream.read((RAW_PBYTE)&MEM[BASE_LOAD], size);
}


BYTE* Chip8::getDisplayBuffer()
{
	return &MEM[BASE_DISP];
}


BYTE Chip8::getDT()
{
	return DT;
}

void Chip8::decDT()
{
	DT--;
}

BYTE Chip8::getST()
{
	return ST;
}

void Chip8::decST()
{
	ST--;
}

Instr Chip8::emulate()
{
	//fetch the instruction
	Instr ins(MEM[PC], MEM[PC + 1]);

	//decode
	ins.decode();

	//execute
	switch (ins.op)
	{
	case 0x00: op0(ins); break;
	case 0x01: op1(ins); break;
	case 0x02: op2(ins); break;
	case 0x03: op3(ins); break;
	case 0x04: op4(ins); break;
	case 0x05: op5(ins); break;
	case 0x06: op6(ins); break;
	case 0x07: op7(ins); break;
	case 0x08: op8(ins); break;
	case 0x09: op9(ins); break;
	case 0x0A: opA(ins); break;
	case 0x0B: opB(ins); break;
	case 0x0C: opC(ins); break;
	case 0x0D: opD(ins); break;
	case 0x0E: opE(ins); break;
	case 0x0F: opF(ins); break;

	default:
		ins.type = UNKNOW;
		ins.desc = NO_DESC;
		int c = std::getchar();
		break;
	};

	return ins;
}

void Chip8::op0(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	switch (ins.ooo)
	{
		//00E0 	Display 	disp_clear() 
	case 0x00E0:
		ins.type = DISPLAY;
		ins.desc = "disp_clear()";

		//clear the disp mem
		for (auto i = 0; i < DISPLAY_W * DISPLAY_H / BYTE_SIZE; i++)
		{
			MEM[BASE_DISP + i] = 0x00;
		};

		PC += 2;
		break;

		//00EE 	Flow 	return; 
	case 0x00EE:
		ins.type = FLOW;
		ins.desc = "return";

		SP -= 2;
		PC = (MEM[SP] << 8) + MEM[SP + 1];
		PC += 2;

		break;

		//0NNN 	Call	Calls program at address NNN
	default:
		ins.type = CALL;
		ss << std::hex << "call program at " << std::setw(3) << ins.nnn;
		ins.desc = ss.str();

		//halt the emulator
		std::cout << "WARNING : NOT SUPPORTED" << std::endl;
		int c = std::getchar();

		break;
	};

}

void Chip8::op1(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//1NNN 	Flow 	goto NNN;
	ins.type = FLOW;
	ss << std::hex << "goto " << std::setw(3) << ins.nnn;
	ins.desc = ss.str();

	PC = ins.nnn;
}

void Chip8::op2(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//2NNN 	Flow	Calls subroutine at NNN. 
	ins.type = FLOW;
	ss << std::hex << "call " << std::setw(3) << ins.nnn;
	ins.desc = ss.str();

	MEM[SP] = PC >> 8;
	MEM[SP + 1] = static_cast<ADDRESS>(PC << 8) >> 8;
	SP += 2;
	PC = ins.nnn;

}

void Chip8::op3(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//3XNN 	Cond 	if(Vx==NN) 
	ins.type = COND;
	ss << std::hex << "if(V" << (int)ins.x << "==" << std::setw(2) << (int)ins.nn << ")";
	ins.desc = ss.str();

	PC += 2;
	if (V[ins.x] == ins.nn) { PC += 2; };
}

void Chip8::op4(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//4XNN 	Cond 	if(Vx!=NN) 
	ins.type = COND;
	ss << std::hex << "if(V" << (int)ins.x << "!=" << std::setw(2) << (int)ins.nn << ")";
	ins.desc = ss.str();

	PC += 2;
	if (V[ins.x] != ins.nn) { PC += 2; };
}

void Chip8::op5(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//5XY0 	Cond 	if(Vx==Vy)		(su wikipedia c'e' un errore)
	ins.type = COND;
	ss << std::hex << "if(V" << (int)ins.x << "==V" << (int)ins.y << ")";
	ins.desc = ss.str();

	PC += 2;
	if (V[ins.x] == V[ins.y]) { PC += 2; };
}

void Chip8::op6(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//6XNN 	Const 	Vx = NN
	ins.type = CONS;
	ss << std::hex << "V" << (int)ins.x << "=" << std::setw(2) << (int)ins.nn;
	ins.desc = ss.str();

	V[ins.x] = ins.nn;
	PC += 2;
}

void Chip8::op7(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//7XNN 	Const 	Vx += NN
	ins.type = CONS;
	ss << std::hex << "V" << (int)ins.x << "+=" << std::setw(2) << (int)ins.nn;
	ins.desc = ss.str();

	V[ins.x] += ins.nn;
	PC += 2;
}

void Chip8::op8(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	switch (ins.o)
	{

		//8XY0 	Assign 	Vx=Vy
	case 0x00:
		ins.type = ASSIGN;
		ss << std::hex << "V" << (int)ins.x << "=V" << (int)ins.y;
		ins.desc = ss.str();

		V[ins.x] = V[ins.y];
		PC += 2;

		break;

		//8XY1 	BitOp 	Vx = Vx | Vy
	case 0x01:
		ins.type = BITOP;
		ss << std::hex << "V" << (int)ins.x << "=V" << (int)ins.x << "|V" << (int)ins.y;
		ins.desc = ss.str();

		V[ins.x] = V[ins.x] | V[ins.y];
		PC += 2;

		break;

		//8XY2 	BitOp 	Vx=Vx&Vy
	case 0x02:
		ins.type = BITOP;
		ss << std::hex << "V" << (int)ins.x << "=V" << (int)ins.x << "&V" << (int)ins.y;
		ins.desc = ss.str();

		V[ins.x] = V[ins.x] & V[ins.y];
		PC += 2;

		break;

		//8XY3 	BitOp 	Vx=Vx^Vy
	case 0x03:
		ins.type = BITOP;
		ss << std::hex << "V" << (int)ins.x << "=V" << (int)ins.x << "^V" << (int)ins.y;
		ins.desc = ss.str();

		V[ins.x] = V[ins.x] ^ V[ins.y];
		PC += 2;

		break;

		//8XY4 	Math 	Vx += Vy
	case 0x04:
		ins.type = MATH;
		ss << std::hex << "V" << (int)ins.x << "+=V" << (int)ins.y;
		ins.desc = ss.str();

		if ((V[ins.x] + V[ins.y]) > 0xFF) { V[0x0F] = 0x01; }
		else { V[0xF] = 0x00; };

		V[ins.x] += V[ins.y];
		PC += 2;

		break;

		//8XY5 	Math 	Vx -= Vy
	case 0x05:
		ins.type = MATH;
		ss << std::hex << "V" << (int)ins.x << "-=V" << (int)ins.y;
		ins.desc = ss.str();

		if (V[ins.x] > V[ins.y]) { V[0x0F] = 0x01; }
		else { V[0xF] = 0x00; };

		V[ins.x] -= V[ins.y];
		PC += 2;

		break;

		//8XY6 	BitOp 	Vx >>= 1
	case 0x06:
		ins.type = BITOP;
		ss << std::hex << "V" << (int)ins.x << ">>=1";
		ins.desc = ss.str();

		if ((V[ins.x] % 2) == 1) { V[0x0F] = 0x01; }
		else { V[0xF] = 0x00; };

		V[ins.x] = V[ins.x] >> 1;
		PC += 2;

		break;

		//8XY7 	Math 	Vx=Vy-Vx
	case 0x07:
		ins.type = MATH;
		ss << std::hex << "V" << (int)ins.x << "=V" << (int)ins.y << "-V" << (int)ins.x;
		ins.desc = ss.str();

		if (V[ins.y] > V[ins.x]) { V[0x0F] = 0x01; }
		else { V[0xF] = 0x00; };

		V[ins.x] = V[ins.y] - V[ins.x];
		PC += 2;

		break;

		//8XYE 	BitOp 	Vx<<=1
	case 0x0E:
		ins.type = BITOP;
		ss << std::hex << "V" << (int)ins.x << "<<=1";
		ins.desc = ss.str();

		if ( (static_cast<BYTE>(V[ins.x] >> 7) %2)==1) { V[0x0F] = 0x01; }
		else { V[0xF] = 0x00; };

		V[ins.x] = V[ins.x] << 1;
		PC += 2;

		break;

		//default
	default:
		ins.type = UNKNOW;
		ins.desc = NO_DESC;
		int c = std::getchar();
		break;
	};
}

void Chip8::op9(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//9XY0 	Cond 	if(Vx!=Vy)
	ins.type = COND;
	ss << std::hex << "if(V" << (int)ins.x << "!=V" << (int)ins.y << ")";
	ins.desc = ss.str();

	PC += 2;
	if (V[ins.x] != V[ins.y]) { PC += 2; };
}

void Chip8::opA(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//ANNN 	MEM 	I = NNN
	ins.type = MEMORY;
	ss << std::hex << "I=" << std::setw(3) << ins.nnn;
	ins.desc = ss.str();

	I = ins.nnn;
	PC += 2;
}

void Chip8::opB(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//BNNN 	Flow 	PC=V0+NNN
	ins.type = FLOW;
	ss << std::hex << "PC=V0+" << std::setw(3) << ins.nnn;
	ins.desc = ss.str();

	PC = V[0] + ins.nnn;
}

void Chip8::opC(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//CXNN 	Rand 	Vx=rand()&NN
	ins.type = RAND;
	ss << std::hex << "V" << (int)ins.x << "=rand()&" << std::setw(2) << (int)ins.nn;
	ins.desc = ss.str();

	BYTE num = gUnif(gRng);

	V[ins.x] = num & ins.nn;
	PC += 2;
}

void Chip8::opD(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	//DXYN 	Disp 	draw(Vx,Vy,N)
	ins.type = DISPLAY;
	ss << std::hex << "draw(V" << (int)ins.x << ",V" << (int)ins.y << "," << (int)ins.n << ")";
	ins.desc = ss.str();

	//unset collision
	V[0xF] = 0;

	//for each byte in the sprite
	for (auto i = 0; i < ins.n; i++)
	{
		//get the source byte
		BYTE src_byte = MEM[I + i];

		//create a bin vecotr of the source byte
		std::vector<int> src_bin = ByteToBits(src_byte);

		//for each bit of the source bin
		for (auto j = 0; j < BYTE_SIZE; j++)
		{
			//get the source bit
			int src_bit = src_bin[j];

			//if it is set
			if (src_bit==1)
			{
				//get the pixel coordinates of the screen
				int x = V[ins.x] + j;
				int y = V[ins.y] + i;

				if (x < 0 || x >= DISPLAY_W) { x %= DISPLAY_W; };//??
				//if (y < 0 || y >= DISPLAY_H) { y %= DISPLAY_H; };//??

				//if the pixel is off screen, skip it
				if ((x >= 0 && x < DISPLAY_W) && (y >= 0 && y < DISPLAY_H))
				{
					//find the index of the dest byte
					int index = x + y * DISPLAY_W;

					//find the dest byte
					BYTE dst_byte = MEM[BASE_DISP + (index / BYTE_SIZE)];

					//create a bin vector from the dest byte
					std::vector<int> dst_bin = ByteToBits(dst_byte);

					//find the dest bit
					int dst_bit = dst_bin[index % BYTE_SIZE];

					//check for collision
					if (src_bit & dst_bit) { V[0xF] = 1; }

					//do the xor
					dst_bin[index % BYTE_SIZE] ^= src_bit;

					//assign the new created dest byte
					MEM[BASE_DISP + (index / BYTE_SIZE)] = BitsToByte(dst_bin);
				};

			}

		}

	}

	PC += 2;//finally !!!
}



void Chip8::opE(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	switch (ins.oo)
	{
		//EX9E 	KeyOp 	if(key()==Vx)
	case 0x9E:
		ins.type = KEYOP;
		ss << std::hex << "if(key()==V" << (int)ins.x;
		ins.desc = ss.str();

		PC += 2;
		if (gKeyboard.getKey(V[ins.x])) { PC += 2; }

		break;

		//EXA1 	KeyOp 	if(key()!=Vx)
	case 0xA1:
		ins.type = KEYOP;
		ss << std::hex << "if(key()!=V" << (int)ins.x;
		ins.desc = ss.str();

		PC += 2;
		if (!gKeyboard.getKey(V[ins.x])) { PC += 2; }

		break;

		//default
	default:
		ins.type = UNKNOW;
		ins.desc = NO_DESC;
		int c = std::getchar();
		break;
	};
}

void Chip8::opF(Instr &ins)
{
	std::stringstream ss;
	ss << std::internal << std::uppercase << std::setfill('0');

	switch (ins.oo)
	{
		//FX07 	Timer 	Vx = get_delay()
	case 0x07:
		ins.type = TIMER;
		ss << std::hex << "V" << (int)ins.x << "=get_delay()";
		ins.desc = ss.str();

		V[ins.x] = DT;

		PC += 2;

		break;

		//FX0A 	KeyOp 	Vx = get_key()
	case 0x0A:
		ins.type = KEYOP;
		ss << std::hex << "V" << (int)ins.x << "=get_key()";
		ins.desc = ss.str();

		if (gKeyboard.getKeyPressed() >= 0)
		{
			V[ins.x] = gKeyboard.getKeyPressed();
			gKeyboard.unsetKeyPressed();
			PC += 2;
		};
		break;

		//FX15 	Timer 	delay_timer(Vx)
	case 0x15:
		ins.type = TIMER;
		ss << std::hex << "delay_timer(V" << (int)ins.x << ")";
		ins.desc = ss.str();

		DT = V[ins.x];

		PC += 2;

		break;

		//FX18 	Sound 	sound_timer(Vx)
	case 0x18:
		ins.type = SOUND;
		ss << std::hex << "sound_timer(V" << (int)ins.x << ")";
		ins.desc = ss.str();

		ST = V[ins.x];

		PC += 2;

		break;

		//FX1E 	MEM 	I +=Vx
	case 0x1E:
		ins.type = MEMORY;
		ss << std::hex << "I+=V" << (int)ins.x;
		ins.desc = ss.str();

		I += V[ins.x];
		PC += 2;

		break;

		//FX29 	MEM 	I=sprite_addr[Vx]
	case 0x29:
		ins.type = MEMORY;
		ss << std::hex << "I=sprite_addr[V" << (int)ins.x << "]";
		ins.desc = ss.str();

		I = BASE_CHARSET + (V[ins.x] * CHARSET_CHAR_DIM);
		PC += 2;

		break;

		//FX33 	BCD 	set_BCD(Vx)
	case 0x33:
		ins.type = BCD;
		ss << std::hex << "set_BCD(V" << (int)ins.x << ")";
		ins.desc = ss.str();

		MEM[I] = V[ins.x] / 10 / 10;
		MEM[I + 1] = (V[ins.x] / 10) % 10;
		MEM[I + 2] = V[ins.x] % 10;

		PC += 2;

		break;

		//FX55 	MEM 	reg_dump(Vx,&I)
	case 0x55:
		ins.type = MEMORY;
		ss << std::hex << "reg_dump(V" << (int)ins.x << ",&I)";
		ins.desc = ss.str();

		for (int i = 0; i <= ins.x; i++)
		{
			MEM[I + i] = V[i];
		};

		PC += 2;

		break;

		//FX65 	MEM 	reg_load(Vx, &I)
	case 0x65:
		ins.type = MEMORY;
		ss << std::hex << "reg_load(V" << (int)ins.x << ",&I)";
		ins.desc = ss.str();

		for (int i = 0; i <= ins.x; i++)
		{
			V[i] = MEM[I + i];
		};

		PC += 2;

		break;

		//default
	default:
		ins.type = UNKNOW;
		ins.desc = NO_DESC;
		int c = std::getchar();
		break;
	};
}

