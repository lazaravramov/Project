#pragma once
#include"Planet.h"
class PlanetList {
	Planet* planetList;
	size_t size;
	size_t cap;
	void copyFrom(const PlanetList& other);
	void free();
	void resize();
public:
	PlanetList();
	PlanetList(const PlanetList& other);
	PlanetList& operator=(const PlanetList& other);
	~PlanetList();
};