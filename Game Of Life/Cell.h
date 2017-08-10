#pragma once

#include <vector>

using namespace std;

class Cell {
public:
	//Base
	int x, y;
	int c[3];
	bool state;

	//Traits
	int health;
	int imunity;
	int speed;
	int stenght;
	int viewRange;
	int pickupRange;
	int foodEff;
	int divisionSize;
	int timeWOFood;
	//vector<int> acceptedFood;

	//Brain

	

	Cell();
};

Cell::Cell() {};