#include "Loader.h"

#include <fstream>
#include "../Exception.h"

Address Loader::m_loadAddress = 0;;

void Loader::load(Processor &processor, const string &name_file)
{
	Address RC = m_loadAddress;
	ifstream file(name_file, ios::binary);

	if (!file.is_open()) {
		throw ExecutableFileNotFound();
	}

	while (!file.eof())
	{
		char prefix = ' ';
		file.read((char *)&prefix, sizeof(prefix));
		if (file.eof()) return;

		switch (prefix)
		{
			case 'k': // Двоичная команда
			{
				Word data;
				file.read((char *)&data, sizeof(data));

				if (CommandSizeRecognizer::getCommandSize((CommandCode)data.mc.code) == LONG)
					data.mc.cmd32.a += m_loadAddress;
				processor.m_memory[RC++] = data;
			} break;
			case 'i': // Целое число
			case 'f': // Дробное число
			{
				int argumentsAmount = 0;
				file.read((char *)&argumentsAmount, sizeof(argumentsAmount));
				for (int i = 0; i < argumentsAmount; i++) 
					file.read((char *)&processor.m_memory[RC++], sizeof(Word));
			} break;
			case 'a':
			{
				Address adr;
				file.read((char *)&adr, sizeof(adr));
				m_loadAddress = RC = adr;
			} break;
			case 's':
			{
				Address adr;
				file.read((char *)&adr, sizeof(adr));
				processor.setIP(m_loadAddress + adr);
			} break;
			default:
			{
				throw LoadingError();
			} break;
		}
	}
	file.close();
}
