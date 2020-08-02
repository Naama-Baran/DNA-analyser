#ifndef __I_WRITER__
#define __I_WRITER__

class IWriter
{
public:
	virtual	~IWriter(){}
	virtual void	write(std::string&) = 0;
};

#endif //__I_WRITER__
