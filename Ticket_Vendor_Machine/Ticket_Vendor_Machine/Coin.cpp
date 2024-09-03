#include "Coin.h"

Coin::Coin(int nameType, string type, double nominal) : nameType(nameType), name(name), nominal(nominal){
}

int Coin::getNameType()
{
	return nameType;
}

void Coin::setNameType(int n)
{
	nameType = n;
}

string Coin::getName()
{
	return name;
}

void Coin::setName(string t)
{
	name = t;
}

double Coin::getNominal()
{
	return nominal;
}

void Coin::setNominal(double n)
{
	nominal = n;
}
