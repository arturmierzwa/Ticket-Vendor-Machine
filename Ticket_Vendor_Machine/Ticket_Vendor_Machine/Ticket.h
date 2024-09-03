#pragma once

#include <string>

using namespace std;

class Ticket
{
private:
	string type;
	double price;
public:
	Ticket(string type, double price);
	string getType();
	void setType(string t);
	double getPrice();
	void setPrice(double p);


};

