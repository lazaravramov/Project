#pragma once
#include<iostream>
#include <cstring>
#include<vector>
using namespace std;
#pragma warning (disable:4996)
enum   class Rank {
	YOUNGLING,
	INITIATE,
	PADAWAN,
	KNIGHT_ASPIRANT,
	KNIGHT,
	MASTER,
	BATTLE_MASTER,
	GRAND_MASTER
};
class Jedi {
	string  name;
	double power;
	unsigned age;
	Rank rank;
	string colorOfSaber;
public:
	Jedi() = default;
	Jedi(string name, double power, unsigned age, string colorOfSaber,Rank rank);
	string getName()const;
	string getColorOfSaber()const;
	double getPower()const;
	unsigned getAge()const;
	Rank getRank()const;
	void setRank(Rank value);
	void setName(string name);
	void setPower(double power);
	void setColorOfSaber(string colorOfSaber);
	void setAge(unsigned age);
	void print();
	string parseRankToString();
	string toString();	
};