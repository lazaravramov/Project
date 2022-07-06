#include "Planet.h"
using namespace std;
#include<cstring>;
#include<iostream>
#pragma warning (disable:4996)
Planet::Planet(string name, vector<string> jediList) {
	setName(name);
	setJediList(jediList);
 }
Planet::Planet(string name) {
	setName(name);
}
string Planet::getName()const {
	return name;
}
void Planet::setName(string name) {
	this->name = name;
}
vector<string> Planet::getJediList()const {
	return jediList;
}
void Planet::setJediList(vector<string> jediList) {
	this->jediList = jediList;
}
void Planet::addJedi(string jediName) {
	jediList.push_back(jediName);
}
void Planet::removeJedi(string jediName){
	for (unsigned i = 0; i < jediList.size(); i++) {
		if (jediList[i] == jediName) {
			jediList.erase(jediList.begin() + i);
		}
	}
}
string Planet::planetToString() {
	{
		unsigned jediListSize = jediList.size();
		string planetString = "";
		planetString += name;
		if (jediListSize == 0) {
			planetString += " #";
		}
		else {
			planetString += ' ';
			for (unsigned i = 0; i < jediListSize; i++) {
				planetString += jediList[i];
				if (i == jediListSize - 1) {
					break;
				}
				planetString += ',';
			}
		}
		return planetString;
	}
}
