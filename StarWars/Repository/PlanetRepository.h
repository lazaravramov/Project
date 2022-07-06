#pragma once
#include"../Model/Planet.h"
#include <vector>
#include<fstream>
#include <exception>
#include<stdexcept>
class PlanetRepository {
public:
	PlanetRepository() = default;
	Planet create(Planet planet);
	Planet getPlanetByName(string name);
	Planet splitStringToPlanet(string str);
	vector<Planet> getPlanetsByName();
	vector<Planet> getPlanetsByNames(vector<string> planetNames);
	Planet addJediToPlanet(string planetName, string jediName);
	Planet removeJediFromPlanet(string planetName, string jediName);
	string getThePlanetNameOfTheJedi(string jediName);
	vector<string> getJediNamesByPlanet(string planet);
	Planet createPlanetWithName(string PlanetName);
};

