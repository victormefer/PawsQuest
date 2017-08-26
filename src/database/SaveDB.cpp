#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include <iostream>
#include "SaveDB.h"

/*************************************************************
 *
 * Construtor
 *
 *************************************************************/
void SaveDB::SaveGame(std::string fase, std::string numero)
{
	std::ofstream fout;
	fout.open( "map/global/saveDB.txt", std::ios::app);
	fout << ' ';
	fout << fase;
	fout << '/';
	fout << numero;
	fout.close();
}
