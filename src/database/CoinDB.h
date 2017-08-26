#ifndef COINDB_H_
#define COINDB_H_

#include <string>

class CoinDB
{
public:
	static void Load();
	static void Add(char delimiter);
	static void Delete();
	static int goldCoin;
	static int silverCoin;
	static int bronzeCoin;
};

#endif
