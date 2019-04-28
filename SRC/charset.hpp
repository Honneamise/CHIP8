class Charset
{
public:
	Charset();
	std::vector<BYTE> operator[](int idx);

private:
	std::vector< std::vector<BYTE> > data;
};