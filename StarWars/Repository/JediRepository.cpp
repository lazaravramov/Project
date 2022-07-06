#include<iostream>
#include"JediRepository.h"
#include <stdlib.h>
//TODO(OPENFILE!!!)
const int NAME_PLACEHOLDER = 0;
const int POWER_PLACEHOLDER = 1;
const int AGE_PLACEHOLDER = 2;
const int COLOR_OF_LIGHTSABER_PLACEHOLDER = 3;
const int RANK_PLACEHOLDER = 4;
const int JEDI_NOT_FOUND_ERROR_CODE = 1;
const int FILE_STREAM_ERROR = 2;
Rank JediRepository::parseStringToRank(string str) {
	Rank rank;
	if (str == "Youngling") {
		rank = Rank::YOUNGLING;
	}
	else if (str == "Initiate") {
		rank = Rank::INITIATE;
	}
	else if (str == "Padawan") {
		rank = Rank::PADAWAN;
	}
	else if (str == "Knight_aspirant") {
		rank = Rank::KNIGHT_ASPIRANT;
	}
	else if (str == "Knight") {
		rank = Rank::KNIGHT;
	}
	else if (str == "Master") {
		rank = Rank::MASTER;
	}
	else if (str == "Battle_master") {
		rank = Rank::BATTLE_MASTER;
	}
	else if (str == "Grand_master") {
		rank = Rank::GRAND_MASTER;
	}
	else {
		rank = Rank::YOUNGLING;
	}
	return rank;
}
vector<string> splitStringToVectorInJediRepo(string str, char ch) {
	vector<string> newHome;
	string tempString = "";
	unsigned tempStringIter = 0;
	unsigned strLen = strlen(str.c_str());
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
	return newHome;
}
Jedi JediRepository::splitStringToJedi(string str) {
	unsigned strLen= strlen(str.c_str());
	string jediProperties[5];
	unsigned jediPropertiesIter = 0;
	string tempString = "";
	unsigned tempStringIter = 0;
	for (unsigned i = 0; i < strLen; i++) {
		if (str[i] == ' ') {
			jediProperties[jediPropertiesIter++] = tempString;
			tempString = "";
			tempStringIter = 0;
			continue;
		}
		else {
			tempString+= str[i];
		}
	}
	Jedi newJedi(
		jediProperties[NAME_PLACEHOLDER],
		atof(jediProperties[POWER_PLACEHOLDER].c_str()),
		atoi(jediProperties[AGE_PLACEHOLDER].c_str()),
		jediProperties[COLOR_OF_LIGHTSABER_PLACEHOLDER],
		parseStringToRank(jediProperties[RANK_PLACEHOLDER])
	);
	return newJedi;
}
Jedi& JediRepository::createJedi(Jedi& jedi) {
	ofstream outputFile("../DB/Jedis.txt.txt", ios::app);
	ifstream file("../DB/Jedis.txt.txt");
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
	if (isFileEmpty) {
		outputFile << jedi.toString();
	}
	else {
		outputFile << "@" + jedi.toString();
	}
	file.close();
	outputFile.close();
	return jedi;
}
Jedi JediRepository::getJediByName(string name) {
	ifstream file("../DB/Jedis.txt.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string jedis;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		jedis += buff;
	}
	file.close();
	vector<string> jediStrings= splitStringToVectorInJediRepo(jedis,'@');
	vector<Jedi> jediList;
	for (unsigned i = 0; i < jediStrings.size(); i++) {
		jediList.push_back(splitStringToJedi(jediStrings[i]));
	}
	if (jediList.size() == 0) {
		throw JEDI_NOT_FOUND_ERROR_CODE;
	}
	for (unsigned i = 0; i < jediList.size(); i++) {
		if (jediList[i].getName() == name) {
			return jediList[i];
		}
	}
	throw JEDI_NOT_FOUND_ERROR_CODE;
}
Jedi& JediRepository::updateJedi(Jedi& jedi) {
	Jedi updatedJedi;
	vector<Jedi> jediList = getJedis();
	bool jediExsists = false;
	for (unsigned i = 0; i < jediList.size();i++) {
		if (jedi.getName() == jediList[i].getName()) {
			jediExsists = true;
			jediList[i] = jedi;
			updatedJedi = jediList[i];
			break;
		}
	}
	if (!jediExsists) {
		throw JEDI_NOT_FOUND_ERROR_CODE;
	}
	ofstream outputFile("../DB/Jedis.txt", ios::trunc);
	if (!outputFile.is_open()) {
		throw FILE_STREAM_ERROR;
	}
	for (unsigned i = 0; i < jediList.size(); i++) {
		if (i == 0) {
			outputFile << jediList[i].toString() << endl;
		}
		else {
			outputFile << "@" + jediList[i].toString() << endl;
		}
	}
	outputFile.close();
	return updatedJedi;
}
void JediRepository::deleteJedi(Jedi& jedi) {
	vector<Jedi> jediList = getJedis();
	bool jediExsists = false;
	for (unsigned i = 0; i < jediList.size(); i++) {
		if (jedi.getName() == jediList[i].getName()) {
			jediExsists = true;
			jediList.erase(jediList.begin()+i);
			break;
		}
	}
	if (!jediExsists) {
		throw JEDI_NOT_FOUND_ERROR_CODE;
	}
	ofstream outputFile("../DB/Jedis.txt", ios::trunc);
	if (!outputFile.is_open()) {
		throw FILE_STREAM_ERROR;
	}
	for (unsigned i = 0; i < jediList.size(); i++) {
		if (i == 0) {
			outputFile << jediList[i].toString() << endl;
		}
		else {
			outputFile << "@" + jediList[i].toString() << endl;
		}
	}
	outputFile.close();
}
vector<Jedi> JediRepository::getJedis() {
	ifstream file("../DB/Jedis.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string jedis;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		jedis += buff;
	}
	file.close();
	vector<string> jediStrings = splitStringToVectorInJediRepo(jedis, '@');
	vector<Jedi> jediList;
	for (unsigned i = 0; i < jediStrings.size(); i++) {
		jediList.push_back(splitStringToJedi(jediStrings[i]));
	}
	return jediList;
}
vector<Jedi> JediRepository::getJedisByNames(vector<string> jediNames) {
	ifstream file("../DB/Jedis.txt");

	if (!file.is_open())
	{
		throw FILE_STREAM_ERROR;

	}
	string jedis;
	while (!file.eof())
	{
		char buff[1024];
		file.getline(buff, 1024);
		jedis += buff;
	}
	file.close();
	vector<string> jediStrings = splitStringToVectorInJediRepo(jedis, '@');
	vector<Jedi> jediList;
	for (unsigned i = 0; i < jediStrings.size(); i++) {
		jediList.push_back(splitStringToJedi(jediStrings[i]));
	}
	if (jediList.size() == 0) {
		throw JEDI_NOT_FOUND_ERROR_CODE;
	}
	vector<Jedi> foundJedis;
	for (unsigned i = 0; i < jediList.size(); i++) {
		for (unsigned j = 0; j < jediNames.size(); j++) {
			if (jediList[i].getName() == jediNames[j]) {
				foundJedis.push_back(jediList[i]);
			}
		}
	}
	if (foundJedis.size() == 0) {
		throw JEDI_NOT_FOUND_ERROR_CODE;
	}

	return foundJedis;
}


	
