#ifndef __DNA_COLLECTION__
#define __DNA_COLLECTION__

#include "dna_data.h"

class DnaCollection
{
public:
	static const DnaData*				getDna(size_t id);
	static const DnaData*				getDna(const std::string& name);
	static void					addDna(const DnaData& dna_data);
	static std::map<std::string, DnaData*>&	getNameToDnaMap();

private:
	static std::map<size_t, std::string> 		s_id_to_name;
	static std::map<std::string, DnaData*> 	s_name_to_dna;
};

inline const DnaData* DnaCollection::getDna(size_t id)
{
	return getDna(s_id_to_name[id]);
}

inline const DnaData* DnaCollection::getDna(const std::string& name)
{
	return s_name_to_dna[name];
}

inline void DnaCollection::addDna(const DnaData& dna_data)
{
	s_id_to_name[dna_data.getId()] = dna_data.getName();
	s_name_to_dna[dna_data.getName()] = new DnaData(dna_data);
}

inline std::map<std::string, DnaData*>& DnaCollection::getNameToDnaMap()
{
	return s_name_to_dna;
}


#endif //__DNA_COLLECTION__
