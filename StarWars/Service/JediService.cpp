#include <iostream>
#include"JediService.h"
#include"../Repository/JediRepository.h"
#include"../Repository/PlanetRepository.h"
int getRankPowerByRank(Rank rank) {
	int power;
	switch (rank)
	{
	case Rank::YOUNGLING: 
		power = 1;
		break;
	case Rank::INITIATE: 
		power = 2;
		break;
	case Rank::PADAWAN: 
		power = 3;
		break;
	case Rank::KNIGHT_ASPIRANT: 
		power = 4;
		break;
	case Rank::KNIGHT:
		power = 5;
		break;
	case Rank::MASTER:
		power = 6;
		break;
	case Rank::BATTLE_MASTER:
		power = 7;
		break;
	case Rank::GRAND_MASTER:
		power = 8;
		break;
	default:
		power = 0;
		break;
	}
	return power;
}
Rank getRankByPower(int power) {
	Rank rank;
	switch (power)
	{
	case 1:
		rank = Rank::YOUNGLING;
		break;
	case 2:
		rank = Rank::INITIATE;
		break;
	case 3:
		rank = Rank::PADAWAN;
		break;
	case 4:
		rank = Rank::KNIGHT_ASPIRANT;
		break;
	case 5:
		rank = Rank::KNIGHT  ;
		break;
	case 6:
			rank = Rank::MASTER;
		break;
	case 7:
		rank= Rank::BATTLE_MASTER;
		break;
	case 8:
		rank=Rank::GRAND_MASTER;
		break;
	default:
		power = 0;
		break;
	}
	return rank;
}
string parseErrorCode(int errorCode) {
	string errorMessage;
	switch (errorCode) {
	case 1:
		errorMessage = "Jedi not found/Planet not found";
		break;
	case 2:
		errorMessage = "File  error";
		break;
	case 3:
		errorMessage = "Already exsists";
		break;
	default:
		errorMessage = "Error";
		break;
	}
	return errorMessage;
}
	void JediService::promote_jedi(string name, double multipl) {
	JediRepository jediRepository;
	try {
		if (multipl > 0) {
			Jedi jedi = jediRepository.getJediByName(name);
			double power = jedi.getPower() * (1.00 + multipl);
			int rankPower = getRankPowerByRank(jedi.getRank());
			if (rankPower < 8) {
				rankPower++;
				jedi.setRank(getRankByPower(rankPower));
			}
			jedi.setPower(power);
			jedi = jediRepository.updateJedi(jedi);
		}
		else {
			cout << "Multiplier must be positive"<<endl;
		}
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode) << endl;
	}
	
}
void JediService::demoteJedi(string name, double multipl) {
	JediRepository jediRepository;
	try {
		if (multipl > 0) {
			Jedi jedi = jediRepository.getJediByName(name);
			double power = jedi.getPower() * (1.00 - multipl);
			int rankPower = getRankPowerByRank(jedi.getRank());
			if (rankPower > 1) {
				rankPower--;
				jedi.setRank(getRankByPower(rankPower));
			}
			jedi.setPower(power);
			jedi = jediRepository.updateJedi(jedi);
		}
		else {
			cout << "Multiplier must be positive" << endl;
		}
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode) << endl;
	}

}
bool JediService::doesJediAlreadyExist(string name) {
	JediRepository jediRepository;
	try {
		Jedi jedi = jediRepository.getJediByName(name);
		return true;
	}
	catch (int errorCode) {
		return false;
	}
}
bool JediService::doesPlanetAlreadyExist(string name) {
	PlanetRepository planetRepository;
	try {
		Planet planet = planetRepository.getPlanetByName(name);
		return true;
	}
	catch (int errorCode) {
		return false;
	}
	catch (std::bad_alloc& exception) {
		std::cerr << "bad_alloc detected: " << exception.what();
	}
}
void JediService::create_jedi(Jedi jedi, string planetName) {
	PlanetRepository planetRepository;
	JediRepository jediRepository;
	try {
		if (!doesJediAlreadyExist(jedi.getName()) && doesPlanetAlreadyExist(planetName)) {
			jediRepository.createJedi(jedi);
			planetRepository.addJediToPlanet(jedi.getName(), planetName);
			cout << "Jedi added succesfully";
		}
	} 
	catch (int errorCode) {
		cout << parseErrorCode(errorCode);
	}
}
void JediService::removeJedi(Jedi jedi, string planetName) {
	PlanetRepository planetRepository;
	try {
		if (doesPlanetAlreadyExist(planetName) && doesJediAlreadyExist(jedi.getName())) {
			planetRepository.removeJediFromPlanet(planetName, jedi.getName());
		}
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode);
	}
}
void JediService::get_strongest_jedi(string planetName) {
	JediRepository jediRepository;
	PlanetRepository planetRepository;
	try{
	vector<string> jediNames = planetRepository.getJediNamesByPlanet(planetName);
	vector<Jedi> jediList = jediRepository.getJedisByNames(jediNames);
	unsigned jediListSize = jediList.size();
	Jedi strongestJedi = jediList[0];
	for (unsigned i = 0; i < jediListSize; i++) {
		if (strongestJedi.getPower() < jediList[i].getPower()) {
			strongestJedi = jediList[i];
		}
	}
	strongestJedi.print();
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode);
	}
}
vector<Jedi> JediService::getJedisWithSameRankOnSamePlanet(string planetName, Rank rank) {
	PlanetRepository planetRepository;
	JediRepository jediRepository;
	vector<Jedi> jedisWithDesiredRank;
	try {
		int rankToInt = getRankPowerByRank(rank);
		vector<string> jediNames = planetRepository.getJediNamesByPlanet(planetName);
		vector<Jedi> jediList = jediRepository.getJedisByNames(jediNames);
		unsigned jediListSize = jediList.size();
		for (unsigned i = 0; i < jediListSize; i++) {
			if (getRankPowerByRank(jediList[i].getRank()) == rankToInt) {
				jedisWithDesiredRank.push_back(jediList[i]);
			}
		}
		return jedisWithDesiredRank;
	}
	catch (int errorCode) {
		return  jedisWithDesiredRank;
	}
}
void JediService::get_youngest_jedi(string planetName, Rank rank) {
		vector<Jedi> jediWithDesiredRank = getJedisWithSameRankOnSamePlanet(planetName, rank);
		unsigned minInd;
		unsigned jediWithDesiredRankSize = jediWithDesiredRank.size();
		if (jediWithDesiredRankSize == 0) {
			cout << "There are not any Jedis with the desired Rank on the Planet: " << planetName;
		}
		else {
			for (unsigned i = 0; i < jediWithDesiredRankSize-1; i++) {
				minInd = i;
				for (unsigned j = i + 1; j < jediWithDesiredRankSize; j++) {
					if (jediWithDesiredRank[minInd].getAge() > jediWithDesiredRank[j].getAge()) {
						minInd =j;
					}
					iter_swap(jediWithDesiredRank.begin() + minInd, jediWithDesiredRank.begin() + i);
				}
			}
		}
		unsigned counterOfJediWithSmallestAge = 0;
		unsigned smallestAge = jediWithDesiredRank[0].getAge();
		for (unsigned i = 0; i < jediWithDesiredRankSize; i++) {
			if  (jediWithDesiredRank[i].getAge() == smallestAge ) {
				counterOfJediWithSmallestAge++;
			}
		}
		if (counterOfJediWithSmallestAge == 1) {
			jediWithDesiredRank[0].print();
		}
		else {
			for (unsigned i = 0; i < counterOfJediWithSmallestAge-1; i++) {
				minInd = i;
				for (unsigned j = i + 1; j < counterOfJediWithSmallestAge; j++) {
					if (strcmp((jediWithDesiredRank[minInd].getName()).c_str(), jediWithDesiredRank[j].getName().c_str()) == 1) {
						minInd = j;
					}
					iter_swap(jediWithDesiredRank.begin() + minInd, jediWithDesiredRank.begin() + i);
				}
			}
			jediWithDesiredRank[0].print();
		}
		
}
void JediService::add_planet(string planetName) {
	PlanetRepository planetRepository;
	try{
		if (!doesPlanetAlreadyExist(planetName)) {
			Planet planet(planetName);
			planetRepository.create(planet);
			cout << "Added successfully";
		}
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode);
	}
}
void JediService::print_jedi(string jediName) {
	PlanetRepository planetRepository;
	JediRepository jediRepository;
	try {
		if (doesJediAlreadyExist(jediName)) {
			string planetName = planetRepository.getThePlanetNameOfTheJedi(jediName);
			cout << "PlanetName:" << planetName << endl;
			Jedi jedi = jediRepository.getJediByName(jediName);
			jedi.print();
		}
	}
	catch (int errorCode) {
		parseErrorCode(errorCode);
	}
}
void JediService::print_planet(string planetName) {
	PlanetRepository planetRepository;
	JediRepository jediRepository;
	try {
		if (doesPlanetAlreadyExist(planetName)) {
			vector<string> jediNames = planetRepository.getJediNamesByPlanet(planetName);
			vector<Jedi> jedis = jediRepository.getJedisByNames(jediNames);
			cout << "Name of Planet:" << planetName;
			for (unsigned i = 0; i < jedis.size(); i++) {
				jedis[i].print();
				cout << endl;
			}
		}
	}
	catch (int errorCode) {
		cout << parseErrorCode(errorCode);
	}
}


