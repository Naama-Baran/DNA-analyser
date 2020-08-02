#ifndef INDEX_OUT_OF_RANGE_H
#define INDEX_OUT_OF_RANGE_H
#include <stdexcept>
class IndexOutOfRange: public std::runtime_error
{
public:
	IndexOutOfRange():std::runtime_error(""){};
	
	virtual const char* what() const throw()
	{
		return "indexes are out of range";
	}
};
#endif
