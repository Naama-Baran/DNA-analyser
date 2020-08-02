#ifndef NOT_SUBSEQ_H
#define NOT_SUBSEQ_H
#include <stdexcept>
class NotSubseq: public std::runtime_error
{
public:
	NotSubseq():std::runtime_error(""){};
	
	virtual const char* what() const throw()
	{
		return "this is not a subsequence";
	}
};
#endif
