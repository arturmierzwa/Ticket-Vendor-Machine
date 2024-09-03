#include "Ticket.h"

Ticket::Ticket(string type, double price) : type(type), price(price){
}

string Ticket::getType()
{
	return type;
}

void Ticket::setType(string t)
{
	type = t;
}

double Ticket::getPrice()
{
	return price;
}

void Ticket::setPrice(double p)
{
	price = p;
}
