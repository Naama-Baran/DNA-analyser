#ifndef __I_READER__
#define __I_READER__

class IReader
{
public:
	virtual		~IReader(){}
	virtual std::string	read() = 0;
};

#endif //__I_READER__
