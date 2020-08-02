#ifndef INVALID_NUCLEOTIDE_H
#define INVALID_NUCLEOTIDE_H
#include <stdexcept>
class InvalidNucleotide: public std::runtime_error
{
public:
	InvalidNucleotide():std::runtime_error(""){};
	
	virtual const char* what() const throw()
	{
		return "Not a valid necleotide";
	}
};
#endif
