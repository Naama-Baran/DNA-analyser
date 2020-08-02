#include "dna_sequence.h"

static bool is_nucleotide(char c)
{
	for( int i=0; i<strlen(nucleotides);i++)
	{
		if(c == nucleotides[i])
			return true;
	}
	return false;
}
DnaSequence::Nucleotide::Nucleotide(char c):m_nuc(c)
{
	if(is_nucleotide(c) == false)
		throw InvalidNucleotide();
}
bool DnaSequence::seqcmp(const DnaSequence& dna) const
{
	if(m_length != dna.sequenceLength())
		return false;
	
	for(size_t i = 0; i<m_length;i++)
	{
		if(!(m_seq[i] == dna.m_seq[i]))
			return false;
	}
	return true;
}
DnaSequence::Nucleotide& DnaSequence::Nucleotide::operator=(char c)
{
	if(is_nucleotide(c) == false)
		throw InvalidNucleotide();
	m_nuc = c;
	return *this;
}
