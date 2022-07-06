#pragma once
#include"../Model/Jedi.h"
#include <vector>
#include<fstream>
#include <exception>
#include<stdexcept>
class JediRepository {
public:
	JediRepository() = default;
	Jedi& createJedi(Jedi& jedi);
	Jedi& updateJedi(Jedi& jedi);
	void deleteJedi(Jedi& jedi);
	vector<Jedi> getJedis();
	Jedi getJediByName(string name);
	Rank parseStringToRank(string str);
	Jedi splitStringToJedi(string str);
	vector<Jedi> getJedisByNames(vector<string> jediNames);
};
