#ifndef STATEDATA_H
#define STATEDATA_H

#include <fstream>
#include "../exceptions/Exceptions.h"

class StateData
{
public:
	int stage;

	void Save()
	{
		std::ofstream ofs;

		ofs.open("savedata.sav", std::ofstream::trunc | std::ofstream::binary);
		if (!ofs.is_open())
			throw FileException("Nao foi possivel abrir o arquivo de save.");

		ofs << stage;
	}

	void Load()
	{
		std::ifstream ifs;
		ifs.open("savedata.sav", std::ofstream::in | std::ofstream::binary);
		if (!ifs.is_open())
			throw FileException("Nao foi possivel abrir o arquivo de save.");

		ifs >> stage;
	}
};


#endif // STATEDATA_H