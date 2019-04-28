#include "headers.hpp"

Instr::Instr(BYTE b0, BYTE b1)
{
	this->b0 = b0;
	this->b1 = b1;

	type = UNKNOW;
	desc = NO_DESC;

	op = 0;
	x = 0;
	y = 0;
	n = 0;
	nn = 0;
	nnn = 0;
	o = 0;
	oo = 0;
	ooo = 0;
}

void Instr::decode()
{
	op = b0 >> 4;

	x = static_cast<BYTE>(b0 << 4) >> 4;
	
	y = b1 >> 4;

	n = static_cast<BYTE>(b1 << 4) >> 4;

	nn = b1;

	nnn = (x << 8) + b1;

	o = n;

	oo = nn;

	ooo = nnn;
}

std::ostream & operator<< (std::ostream& stream, Instr ins)
{
	stream << std::internal << std::uppercase << std::setfill('0');

	stream << std::hex << std::setw(2) << (int)ins.b0;
	stream << " ";
	stream << std::hex << std::setw(2) << (int)ins.b1;

	stream << "\t" << ins.type;

	stream << "\t" << ins.desc;

	return stream;
}