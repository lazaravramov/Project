#include <iostream>
#include"PlanetList.h"
void PlanetList::copyFrom(const PlanetList& other) {
	planetList = new Planet[other.cap];
	for (unsigned i = 0; i < other.size; i++) {
		planetList[i] = other.planetList[i];
	}
	size = other.size;
	cap = other.cap;
}
void PlanetList::free() {
	delete[] planetList;
}
void PlanetList::resize() {
	cap *= 2;
	Planet* newPlanetList = new Planet[cap];
	for (unsigned i = 0; i < size; i++) {
		newPlanetList[i] = planetList[i];
	}
	delete[] planetList;
	planetList = newPlanetList;
}