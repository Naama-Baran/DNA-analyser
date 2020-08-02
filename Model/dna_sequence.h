#ifndef DNA_SEQUENCE_H
#define DNA_SEQUENCE_H

#include <iostream>
#include <string>
#include <list>
#include <map>
#include <cstring>
#include <fstream>

#include "exceptions/invalid_nucleotide.h"
#include "exceptions/open_file_failed.h"
#include "exceptions/index_out_of_range.h"
#include "exceptions/not_subseq.h"

static const char *nucleotides="ACTG";

class DnaSequence
{
	class Nucleotide
	{
	public:
		Nucleotide(char);
		Nucleotide(){};
		
		operator 			char();
		DnaSequence::Nucleotide& 	operator=(char);
		void 				changeToPair();
		char 				getChar() const;
		
	private:
		char 	m_nuc;
		
	};
	
public:
	DnaSequence(const std::string&);
	DnaSequence(const char*);
	DnaSequence(const DnaSequence&);
	//DnaSequence(std::fstream& myfile);
	~DnaSequence();

	const DnaSequence& 	operator=(const DnaSequence&);
	friend std::ostream& 	operator<<(std::ostream& ,const DnaSequence&);
	DnaSequence::Nucleotide& operator[](size_t) const;
	bool 			operator==(const DnaSequence&)const;
	bool 			operator!=(const DnaSequence&)const;
	size_t 		sequenceLength() const;
	DnaSequence 		slice(size_t start,size_t end) const;
	DnaSequence 		slice(size_t start) const;
	DnaSequence 		pairing() const;
	size_t 		find(const DnaSequence&)const;
	size_t 		count(const DnaSequence&) const;
	std::list<size_t> 	findAll(const DnaSequence& ) const;
	std::list<DnaSequence> findConsensusSequences()const;
	std::string 		getSeq() const;
	
private:
	void 		initial(const char*);
	void 		initialFromObj(const DnaSequence& dna);
	bool 		seqcmp(const DnaSequence&)const;

	Nucleotide* 	m_seq;
	size_t 	m_length;
};

/*inline DnaSequence::DnaSequence(std::fstream& myfile):m_seq(NULL),m_length(0)
{
	std::string seq;
	std::string line;
	if(!myfile.is_open()) 
		throw OpenFileFailed();
	
	while(std::getline(myfile, line)) 
	{
		seq += line;
	}

	m_length = seq.length();
	initial(seq.c_str());
	myfile.close();
}*/
inline DnaSequence::DnaSequence(const std::string& seq):m_seq(NULL),m_length(seq.length())
{
	initial(seq.c_str());
}
inline DnaSequence::DnaSequence(const char* seq):m_seq(NULL),m_length(strlen(seq))
{
	initial(seq);
}
inline DnaSequence::DnaSequence(const DnaSequence& dna):m_seq(NULL), m_length(dna.sequenceLength())
{
	initialFromObj(dna);
}
inline DnaSequence::~DnaSequence()
{
	delete [] m_seq;
}
inline void DnaSequence::initial(const char* seq)
{
	m_seq = new Nucleotide[m_length];
	try
	{
		for(size_t i=0; i<m_length;i++)
		{
			m_seq[i] = seq[i];
		}
	}
	catch(InvalidNucleotide &e)
	{
		delete [] m_seq;
		throw;
	}
}
inline void DnaSequence::initialFromObj(const DnaSequence& dna) 
{
	Nucleotide *tmp = new Nucleotide[dna.sequenceLength()];
	try
	{
		for(size_t i=0; i<dna.sequenceLength();i++)
		{
			tmp[i] = dna.m_seq[i];
		}
	}
	catch(InvalidNucleotide &e)
	{
		delete [] tmp;
		throw;
	}
	m_seq = tmp;
}
inline DnaSequence::Nucleotide::operator char()
{
	return m_nuc;
}

inline const DnaSequence& DnaSequence::operator=(const DnaSequence& dna)
{
	if(this!=&dna)
	{
		const Nucleotide* tmp = m_seq;
		initialFromObj(dna);
		delete [] tmp;
		m_length = dna.sequenceLength();
	}
	return *this;
}

inline DnaSequence::Nucleotide& DnaSequence::operator[](size_t index) const
{
	return m_seq[index];
}
inline std::ostream& operator<<(std::ostream& os,const DnaSequence& dna)
{
	for(size_t i = 0; i< dna.sequenceLength();i++)
		os<<dna.m_seq[i];
	return os;
}

inline bool DnaSequence::operator!=(const DnaSequence& dna) const
{
	return !seqcmp(dna);
}
inline bool DnaSequence::operator==(const DnaSequence& dna) const
{
	return seqcmp(dna);
}
inline size_t DnaSequence::sequenceLength()const
{
	return m_length;
}
inline DnaSequence DnaSequence::slice(size_t start=0) const
{
	return slice(start,m_length);
}
inline DnaSequence DnaSequence::slice(size_t start,size_t end) const
{
	if(start < 0 || start>=m_length || end < 0 || end>m_length || start >= end)
		throw std::out_of_range("the indexes are out of range");
		 	
	std::string str;
	for(size_t i=start;i<end;i++)
	{
		str+=m_seq[i];
	}
	DnaSequence sliced(str);
	return sliced;
}
inline void DnaSequence::Nucleotide::changeToPair()
{
	if(m_nuc == 'C')
		m_nuc = 'G';
	else if(m_nuc == 'G')
		m_nuc = 'C';
	else if(m_nuc == 'T')
		m_nuc = 'A';
	else
		m_nuc = 'T';
}

inline DnaSequence DnaSequence::pairing() const
{
	DnaSequence pair = *this;
	for(size_t i=0;i<m_length;i++)
	{
		pair[i] = m_seq[m_length-i-1];
		pair[i].changeToPair();	
	}
	return pair;
}
inline size_t DnaSequence::find(const DnaSequence& dna) const
{
	bool flag;
	for(size_t i=0;i<=m_length-dna.sequenceLength();i++)
	{
		flag = true;
		for(size_t j=0	;j<dna.sequenceLength();j++)
		{
			if(m_seq[i+j]!=dna.m_seq[j])
			{
				flag = false;
				break;
			}
		}
		if(flag==true)
			return i;
	}
	throw NotSubseq();	
}
inline size_t DnaSequence::count(const DnaSequence& dna) const
{
	return findAll(dna).size();
}
inline std::list<size_t> DnaSequence::findAll(const DnaSequence& dna) const
{
	std::list<size_t> lst;
	size_t tmp = 0;
	DnaSequence d = slice();
	while(tmp<m_length-dna.sequenceLength())
	{
		try
		{
			tmp += d.find(dna);
			lst.push_back(tmp);
			tmp ++;
			d = slice(tmp);	
		}
		catch(NotSubseq &e)
		{
			return lst;
		}	
	}
	return lst;
}
inline std::list<DnaSequence> DnaSequence::findConsensusSequences()const
{
	std::list<DnaSequence> ConsensusSequences;
	std::list<size_t> start_list = findAll("ATG");
	std::list<size_t> end_list = findAll("TAG");
	end_list.merge(findAll("TAA"));
	end_list.merge(findAll("TGA"));
	
	for(std::list<size_t>::iterator i = start_list.begin();i != start_list.end();i++)
	{
		for(std::list<size_t>::iterator j = end_list.begin();j != end_list.end();j++)
		{
			if((*j - *i)%3 == 0 && (*j - *i)>0)
				ConsensusSequences.push_back(slice(*i,*j+3));
		}
	}
	return ConsensusSequences;
			
}

inline std::string DnaSequence::getSeq() const
{
	std::string sequence;
	
	for(size_t i = 0; i < m_length; i++)
	{
		sequence += (*this)[i].getChar();
	}
	return sequence;
}

inline char DnaSequence::Nucleotide::getChar() const
{
	return m_nuc;
}

#endif
