#include "cmd_collection.h"
#include "../Controller/cmd_list_include.h"



//=================AUXILARY FUNCTIONS====================

inline static void initCmdCollection(cmd_collection& cmd_co)
{
	cmd_co["load"] = new Load;
	cmd_co["quit"] = new Quit;
	cmd_co["new"] = new New;
	/*cmd_co("delete") = new Delete;
	cmd_co("find") = new Find;
	cmd_co("find_all") = new FindAll;
	cmd_co("dup") = new Dup;
	
	cmd_co("list") = new List;
	cmd_co("count") = new Count;
	cmd_co("concat") = new Concat;
	cmd_co("labals") = new Labals;
	cmd_co("rename") = new Rename;
	cmd_co("show") = new Show;*/
}

//===============END AUXILARY FUNCTIONS==================

CmdCollection::CmdCollection()
:m_cmd_co()
{
	initCmdCollection(m_cmd_co);
}

CmdCollection::~CmdCollection()
{
	for (cmd_collection::iterator iter = m_cmd_co.begin(); iter != m_cmd_co.end(); iter++)
	{
		delete (*iter).second;
	}
}
