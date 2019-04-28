class Instr
{
public:

	BYTE b0;
	BYTE b1;

	std::string type;
	std::string desc;

	BYTE op;
	BYTE x;
	BYTE y;
	BYTE n;
	BYTE nn;
	int nnn;
	BYTE o;
	BYTE oo;
	int ooo;

	Instr(BYTE b0, BYTE b1);
	void decode();
	friend std::ostream& operator<< (std::ostream& stream, Instr ins);

};