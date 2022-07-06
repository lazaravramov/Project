#pragma once
#include"../Model/Jedi.h"
#include"../Model/Planet.h"
class JediService {
	public:
		void promote_jedi(string name, double multipl);
		void add_planet(string name);
		void create_jedi(Jedi jedi, string planetName);
		void removeJedi(Jedi jedi, string planetName);
		void get_strongest_jedi(string planetName);
		void get_youngest_jedi(string planetName, Rank rank);
		string get_most_used_saber_color(string planetName, Rank rank);
		string get_most_used_saber_color(string planetName);
		bool doesJediAlreadyExist(string name);	
		bool doesPlanetAlreadyExist(string name);
		void demoteJedi(string name, double multipl);
		vector<Jedi> getJedisWithSameRankOnSamePlanet(string planetName, Rank rank);
		void print_jedi(string jediName);
		void print_planet(string planetName);
};