#include "dna_collection.h"	
	
std::map<size_t, std::string> DnaCollection::s_id_to_name;
std::map<std::string, DnaData*> DnaCollection::s_name_to_dna;

