#ifndef __CMD_COLLECTION__
#define __CMD_COLLECTION__

#include <iostream>
#include <map>
#include "../Controller/i_command.h"


typedef std::map<const std::string, ICommand*> cmd_collection;

class CmdCollection
{
public:
	CmdCollection();
	~CmdCollection();
	ICommand*	createCommand(std::string&);
	
private:
	cmd_collection	m_cmd_co;
	static const unsigned short s_num_of_command = 2;
};

inline ICommand* CmdCollection::createCommand(std::string& str)
{
	return m_cmd_co[str];
}



#endif //__CMD_COLLECTION__
