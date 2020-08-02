#ifndef __CLI__
#define __CLI__

#include <cstring>
#include <vector>

#include "../Model/cmd_collection.h"
#include "../View/i_reader.h"
#include "../View/i_writer.h"


class CLI
{
public:
	CLI(IWriter*, IReader*);
	CLI();
	
	void 				runCli();
	void				setReader(IReader*);
	void				setWriter(IWriter*);
	
private:
	void 				write(std::string) const;
	std::vector<std::string> 	vecRead();
	
	IWriter*			m_writer;
	IReader*			m_reader;
	CmdCollection*			m_cmd_co;
};

inline CLI::CLI(IWriter* write, IReader* read)
:m_writer(write),
 m_reader(read),
 m_cmd_co(new CmdCollection)
{
}

inline CLI::CLI()
{
	delete m_cmd_co;
}

inline void CLI::setReader(IReader* reader)
{
	m_reader = reader;
}

inline void CLI::setWriter(IWriter* writer)
{
	m_writer = writer;
}

inline void CLI::write(std::string str) const
{
	m_writer->write(str);
}

inline void CLI::runCli()
{
	std::vector<std::string> input = vecRead();
	ICommand* cmd;
	while (true)
	{
		cmd = m_cmd_co->createCommand(input[0]);
		write(cmd->execute(input));
		if (input[0] == "quit")
		{
			if ("Y" == m_reader->read())
			{
				break;
			}
		}
		input = vecRead();
	}
}

	

#endif //__CLI__
