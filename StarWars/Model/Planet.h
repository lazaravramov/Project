#pragma once
#include<cstring>
#include<vector>
#include<iostream>
using namespace std;
#pragma warning (disable:4996)
#include"Jedi.h"
class Planet {
	string name;
	vector<string> jediList;
public:
	Planet() = default;
	Planet(string name);
	Planet(string name, vector<string> jediList);
	string getName()const;
	void setName(string name); 
	void setJediList(vector<string> jediList);
	vector<string> getJediList()const;
	void addJedi(string jedi);
	void removeJedi(string jedi);
	string planetToString();
};