#ifndef __DNA_DATA__
#define __DNA_DATA__

#include <sstream>
#include "dna_sequence.h"

class DnaData
{
public:
	DnaData(const std::string& name, const std::string& dna_seq);
	DnaData(const DnaData&);
	~DnaData();
	
	//const DnaData& 	operator=(const DnaData& other);
	size_t 		getId() const;
	std::string	 	getIdAsStr() const;
	void 			setId(size_t);
	const std::string&	getName() const;
	void 			setName(const std::string&);
	std::string 		getDnaSeqAsStr() const;
	const DnaSequence* 	getDnaSeq() const;
	DnaSequence* 		getDnaSeq();
	//void 		setDnaSeq(const std::string& dna_seq);
	
private:
	size_t 	m_id;
	std::string 	m_name;
	DnaSequence* 	m_dna_seq;
	
	static size_t 	s_last_id;				

};

inline DnaData::DnaData(const std::string& name, const std::string& dna_seq)
:m_name(name),
 m_id(++s_last_id ),
 m_dna_seq( new DnaSequence(dna_seq) )
{	
}


inline DnaData::DnaData(const DnaData& other)
:m_id(other.getId()),
 m_name(other.getName()),
 m_dna_seq(other.m_dna_seq)
{
	if (this != &other)
	{
	 	m_dna_seq = new DnaSequence(*(other.m_dna_seq));
	}	
}

inline DnaData::~DnaData()
{
	delete m_dna_seq;
}


inline size_t DnaData::getId() const
{
	return m_id;
}

inline std::string DnaData::getIdAsStr() const
{
	std::stringstream str;
	str << m_id;
	return str.str();
}

inline void DnaData::setId(size_t id)
{
	m_id = id;
}

inline const std::string& DnaData::getName() const
{
	return m_name;
}

inline void DnaData::setName(const std::string& name)
{
	m_name = name;
}	

inline DnaSequence* DnaData::getDnaSeq()
{
	return m_dna_seq;
}

inline const DnaSequence* DnaData::getDnaSeq() const
{
	return m_dna_seq;
}

inline std::string DnaData::getDnaSeqAsStr() const
{
	return m_dna_seq->getSeq();
}


#endif //__DNA_DATA__
