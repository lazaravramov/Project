using namespace std;
#include"./Jedi.h"
#include<cstring>
#include <sstream>
#include<exception>
#include<stdexcept>
using namespace std;
	bool checkFirstLetterIsCapital(string name) {
	if (name[0] >= 'A' && name[0] <= 'Z') {
		return true;
	}
	else
		return false;
}
Jedi::Jedi(string name, double power, unsigned age, string colorOfSaber,Rank rank) {
	setName(name);
	setPower(power);
	setAge(age);
	setColorOfSaber(colorOfSaber);
	setRank(rank);
}
Rank Jedi::getRank()const {
	return rank;
}
unsigned Jedi::getAge()const {
	return age;
}
double Jedi::getPower()const {
	return power;
}
string Jedi::getName()const {
	return name;
}
string Jedi::getColorOfSaber()const{
	return colorOfSaber;
}
void Jedi::setRank(Rank value) {
	rank = value;
}
void Jedi::setAge(unsigned age) {
	if (age < 18 || age>65) {
		age = 18;
	}
	this->age = age;
}
void Jedi::setName(string name) {
	if (checkFirstLetterIsCapital(name)) {
		this->name = name;
	}
	else {
		name[0] = name[0] - 'a' + 'A';
		this->name = name;
	}
}
void Jedi::setColorOfSaber(string colorOfSaber) {
	if (colorOfSaber == "red") {
		colorOfSaber = "blue";
	}
	this->colorOfSaber = colorOfSaber;
}
void Jedi::setPower(double power) {
	this->power = power;
}
void Jedi::print() {
	cout << "Name of Jedi:" << name << endl;
	cout << "Color Of Lightsaber:" << colorOfSaber << endl;
	cout << "Power of Jedi:" << power << endl;
	cout << "Age of Jedi:" << age << endl;
	cout << "Rank of Jedi:" << parseRankToString() << endl;
}
string Jedi::toString() {
	return name + ' ' + colorOfSaber + ' ' + to_string(age) + ' ' + parseRankToString() +  to_string(power);
}
string Jedi::parseRankToString() {
	string rank;
	switch (this->rank)
	{
		case Rank::YOUNGLING: 
			rank = "Youngling"; 
			break;
		case Rank::INITIATE: 
			rank = "Initiate"; 
			break;
		case Rank::PADAWAN: 
			rank = "Padawan"; 
			break;
		case Rank::KNIGHT_ASPIRANT: 
			rank = "Knight_aspirant"; 
			break;
		case Rank::KNIGHT:
			rank = "Knight";  
			break;
		case Rank::MASTER:
			rank = "Master";  
			break;
		case Rank::BATTLE_MASTER:
			rank = "Battle_master";  
			break;
		case Rank::GRAND_MASTER:
			rank = "Grand_master";  
			break;
		default:
			rank = "Unranked";
			break;
	}
	if (strcmp(rank.c_str(), "Unranked") == 0) {
		throw "Error 404";
	}
	return rank;
}


//TODORANKUNKNOWN