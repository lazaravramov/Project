#include <iostream>
#include"PlanetRepository.h"
const int PLANET_NOT_FOUND_ERROR = 1;
const int JEDI_NOT_FOUND_ERROR = 1;
const int FILE_STREAM_ERROR = 2;
const int ALREADY_EXSISTS = 3;
vector<string> splitStringToVectorInPlanetRepo(string str, char ch) {
	vector<string> newHome;
	string tempString = "";
	unsigned tempStringIter = 0;
	unsigned strLen = strlen(str.c_str());
	if (strLen == 0) {
		return newHome;
	}
	for (unsigned i = 0; i < strLen; i++) {
		if (str[i] == ch) {
			newHome.push_back(tempString);
			tempString = "";
			tempStringIter = 0;
			continue;
		}
		else {
			tempString += str[i];
		}
	}
	newHome.push_back(tempString);
	return newHome;
}
Planet PlanetRepository::splitStringToPlanet(string str) {
	Planet planet;
	unsigned strLen = strlen(str.c_str());
	vector<string> jediList;
	unsigned tempStringIter=0;
	string tempString = "";
	unsigned stringIter = 0;
	string tempNameOfPlanet = "";
	unsigned tempNameIter = 0;
	bool theStringHasNoPlanets = false;
	for (unsigned i = 0; i < strLen; i++) {
		if (str[i] == '#') {
			theStringHasNoPlanets = true;
		}
	}
	if(theStringHasNoPlanets){
	while (str[tempNameIter] != ' ') {
		tempNameOfPlanet += str[tempNameIter++];
	}
		Planet newPlanet1(tempString, jediList);
		return newPlanet1;
	}
	else {
		while (str[stringIter] != ' ') {
			tempNameOfPlanet += str[stringIter++];
		}
		stringIter++;
		for (unsigned i = stringIter; i < strLen; i++) {
			if (str[i] == ',') {
				jediList.push_back(tempString);
				tempString = "";
				tempStringIter = 0;
				continue;
			}
			else {
				tempString+= str[i];

			}
		}
		jediList.push_back(tempString);
		Planet newPlanet2(tempNameOfPlanet, jediList);
		return newPlanet2;
	}
}
Planet PlanetRepository::create(Planet planet) {
		ofstream outputFile("../DB/Planets.txt.txt", ios::app);
		ifstream file("../DB/Planets.txt.txt");
		bool isFileEmpty = false;
		if (!file.is_open())
		{
			throw FILE_STREAM_ERROR;
		}
		if (file.peek() == std::ifstream::traits_type::eof()) {
			isFileEmpty = true;
		}
		if (!outputFile.is_open()) {
			throw FILE_STREAM_ERROR;
		}
		unsigned sizeOfList = planet.getJediList().size();
		outputFile << planet.getName();
		if (sizeOfList == 0) {
			outputFile << " #";
			outputFile <<'@';
		}
		else {
			outputFile << " ";
			for (unsigned i = 0; i < sizeOfList; i++) {
				outputFile << planet.getJediList()[i];
				if (i == sizeOfList - 1) {
					break;
				}
				else {
					outputFile << ',';
				}
			}
			outputFile <<'@';
		}
	
		file.close();
		outputFile.close();
		return planet;
}
Planet PlanetRepository::getPlanetByName(string name) {
	ifstream file("../DB/Planets.txt.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;
	}
	string planets;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		planets += buff;
	}
	file.close();
	vector<string> planetStrings = splitStringToVectorInPlanetRepo(planets, '\n');
	vector<Planet> planetList;
	for (unsigned i = 0; i < planetStrings.size(); i++) {
		planetList.push_back(splitStringToPlanet(planetStrings[i]));
	}
	if (planetList.size() == 0) {
		throw PLANET_NOT_FOUND_ERROR;
	}
	for (unsigned i = 0; i < planetList.size(); i++) {
		if (planetList[i].getName() == name) {
			return planetList[i];
		}
	}
	throw PLANET_NOT_FOUND_ERROR;
}
vector<Planet> PlanetRepository::getPlanetsByNames(vector<string> planetNames) {
	ifstream file("../DB/Planets.txt.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string planets;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		planets += buff;
	}
	file.close();
	vector<string> planetStrings = splitStringToVectorInPlanetRepo(planets, '\n');
	vector<Planet> planetList;
	for (unsigned i = 0; i < planetStrings.size(); i++) {
		planetList.push_back(splitStringToPlanet(planetStrings[i]));
	}
	if (planetList.size() == 0) {
		throw PLANET_NOT_FOUND_ERROR;
	}
	vector <Planet> foundPlanets;
	for (unsigned i = 0; i < planetList.size(); i++) {
		for (unsigned j = 0; j < planetNames.size(); j++) {
			if (planetList[i].getName() == planetNames[j]) {
				foundPlanets.push_back(planetList[i]);
			}
		}
	}
	if (foundPlanets.size() == 0) {
		throw PLANET_NOT_FOUND_ERROR;
	}

	return foundPlanets;
}
vector<Planet> PlanetRepository::getPlanetsByName() {
	ifstream file("../DB/Planets.txt.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string planets;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		planets += buff;
	}
	file.close();
	vector<string> planetStrings = splitStringToVectorInPlanetRepo(planets, '@');
	vector<Planet> planetList;
	for (unsigned i = 0; i < planetStrings.size(); i++) {
		planetList.push_back(splitStringToPlanet(planetStrings[i]));
	}
	return planetList;
}
Planet PlanetRepository::addJediToPlanet(string jediName, string planetName) {
	Planet updatedPlanet=getPlanetByName(planetName);
	vector<string> jediList = updatedPlanet.getJediList();
	jediList.push_back(jediName);
	updatedPlanet.setJediList(jediList);
	ifstream file("../DB/Planets.txt.txt");
	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string planets;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		planets += buff;
	}
	file.close();
	vector<string> planetStrings = splitStringToVectorInPlanetRepo(planets, '@');
	vector<Planet> planetList;
	for (unsigned i = 0; i < planetStrings.size(); i++) {
		planetList.push_back(splitStringToPlanet(planetStrings[i]));
	}
	ofstream outputFile("../DB/Planets.txt.txt", ios::trunc);
		if (!outputFile.is_open()) {
			throw FILE_STREAM_ERROR;
		}
		for (unsigned i = 0; i < planetList.size(); i++) {
			create(planetList[i]);
		}
		outputFile.close();
		return updatedPlanet;
	
}
Planet PlanetRepository::removeJediFromPlanet(string planetName, string jediName) {
	Planet updatedPlanet;
	vector<Planet> planetList = getPlanetsByName();
	unsigned planetListSize = planetList.size();
	bool jediExsists = false;
	bool planetExsists = false;
	for (unsigned i = 0; i < planetListSize; i++) {
		if (planetName == planetList[i].getName()) {
			planetExsists = true;
			break;
		}
	}
	if (planetExsists) {
		for (unsigned i = 0; i < planetListSize; i++) {
			for (unsigned j = 0; j < planetList[i].getJediList().size(); j++) {
				if (jediName == planetList[i].getJediList()[j]) {
					jediExsists = true;
					return planetList[i];
				}
			}
		}
		if (jediExsists) {
			for (unsigned i = 0; i < planetList.size(); i++) {
				if (planetName == planetList[i].getName()) {
					planetList[i].removeJedi(jediName);
					updatedPlanet = planetList[i];
				}
			}
		}
		else {
			throw JEDI_NOT_FOUND_ERROR;
		}
	}
	else {
		throw PLANET_NOT_FOUND_ERROR;
	}
	ofstream outputFile("../DB/Planets.txt.txt", ios::trunc);
	if (!outputFile.is_open()) {
		throw FILE_STREAM_ERROR;
	}
	for (unsigned i = 0; i < planetListSize; i++) {
		outputFile << planetList[i].getName();
		if (planetList[i].getJediList().size() == 0) {
			outputFile << " #";
			outputFile << '@';
		}
		else {
			outputFile << " ";
			for (unsigned j = 0; i < planetList[i].getJediList().size(); j++) {
				outputFile << planetList[i].getJediList()[j];
				if (j == planetList[i].getJediList().size() - 1) {
					break;
				}
				else {
					outputFile << ',';
				}
			}
			outputFile << '@';
		}
	}
	outputFile.close();
	return updatedPlanet;
}
string PlanetRepository::getThePlanetNameOfTheJedi(string jediName) {
	vector<Planet> planetList = getPlanetsByName();
	unsigned planetListSize = planetList.size();
	string nameOfPlanet;
	for(unsigned i=0;i< planetListSize;i++){
		for (unsigned j = 0; j < planetList[i].getJediList().size(); j++) {
			if (jediName == planetList[i].getJediList()[j]) {
				nameOfPlanet = planetList[i].getName();
			}
		}
	}
	return nameOfPlanet;
}
vector<string> PlanetRepository::getJediNamesByPlanet(string planetName) {
	Planet planet = getPlanetByName(planetName);
	vector<string> jediNames;
	string planetString=planet.planetToString();
	string tempString = "";
	unsigned tempStringIter = 0;
	unsigned planetStringLenght = planetString.size();
	unsigned spacePosition = 0;
	while (planetString[spacePosition] != ' ') {
		spacePosition++;
	}
	spacePosition++;
	if (planetString[spacePosition] == '#') {
		throw JEDI_NOT_FOUND_ERROR;
	}
	for (unsigned i = spacePosition; i < planetStringLenght; i++) {
		if (planetString[i] == ',') {
			jediNames.push_back(tempString);
			tempStringIter = 0;
			tempString = "";
		}
		else {
			tempString[tempStringIter++] = planetString[i];
		}
	}
	jediNames.push_back(tempString);
	return jediNames;
}