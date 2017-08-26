#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cstring>
#include "CoinDB.h"

int CoinDB::goldCoin = 0;
int CoinDB::silverCoin = 0;
int CoinDB::bronzeCoin = 0;

/*************************************************************
 *
 * Leitura do arquivo para persistencia dos dados
 *
 *************************************************************/
void CoinDB::Load()
{
	std::ifstream fin;
	fin.open("map/global/coinDB.txt", std::ios::in);
	char delimiter;
	goldCoin = 0;
	silverCoin = 0;
	bronzeCoin = 0;

	while(!fin.eof())
	{
		fin >> delimiter;
		if(delimiter == 'G'){	goldCoin++;		}
		if(delimiter == 'S'){	silverCoin++;	}
		if(delimiter == 'B'){	bronzeCoin++;	}
	}
}

/*************************************************************
 *
 * Add no arquivo texto para persistencia dos dados
 *
 *************************************************************/
void CoinDB::Add(char delimiter)
{
	std::ofstream fout;
	fout.open( "map/global/coinDB.txt", std::ios::app);
	fout << ' ';
	fout << delimiter;
	fout.close();
}

/*************************************************************
 *
 * Limpa o banco de dados (new game)
 *
 *************************************************************/
void CoinDB::Delete()
{
	std::ofstream fin;
	fin.open("map/global/coinDB.txt",std::ios::trunc);
	fin.close();
}
