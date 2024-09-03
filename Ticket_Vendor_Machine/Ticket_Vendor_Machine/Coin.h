#pragma once

#include <string>

using namespace std;

class Coin
{
private:
	int nameType;
	string name;
	double nominal;

public:
	Coin(int nameType, string type, double nominal);
	int getNameType();
	void setNameType(int n);
	string getName();
	void setName(string n);
	double getNominal();
	void setNominal(double n);
};




