#include <iostream>
#include"../Service/JediService.h";
int main()
{
	JediService jediService;
	Jedi jedi("Anakin", 3.2, 19, "Blue", Rank::YOUNGLING);
		string planetName = "Nabu";
		jediService.add_planet(planetName);
		jediService.create_jedi(jedi, planetName);
}