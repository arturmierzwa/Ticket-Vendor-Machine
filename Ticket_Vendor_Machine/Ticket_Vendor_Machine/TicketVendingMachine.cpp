#include "TicketVendingMachine.h"
#include "Ticket.h"
#include "Coin.h"
#include "ITicketPrinter.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <memory>

using namespace std;

TicketVendingMachine::TicketVendingMachine(unique_ptr<ITicketPrinter> printer) : amountPaid(0.0), totalCost(0.0), paperAvailable(true),
	ticketDetails(make_shared<vector<Ticket>>(vector<Ticket>{
		{"1. Normal ticket. City - ZONE 1", 5.00},
		{"2. Half-price ticket. City - ZONE 1", 2.50},
		{"3. Normal ticket. Aglomeration - ZONE 2", 6.00},
		{"4. Half-price ticket. Aglomeration - ZONE 2", 3.00}
		//could be easily extended/reduced for additional ticket types
	})),
	coinDetails(make_shared<vector<Coin>>(vector<Coin>{
		{1,"ZLOTE", 5},
		{1,"ZLOTE", 2},
		{1,"ZLOTE", 1},
		{2,"GROSZE", 50},
		{2,"GROSZE", 20},
		{2,"GROSZE", 10}
		//could be easily extended/reduced for additional currencies/nominals
		})),
	ticketPrinter(std::move(printer)) {}

double TicketVendingMachine::getTotalCost()
{
	return totalCost;
}

void TicketVendingMachine::displayTicketsDetails()
{
	cout << endl;
	cout << "Here is a list of available tickets:" << endl;
	cout << endl;

	for (auto& ticket : *ticketDetails) {
		cout << ticket.getType() << ", Price : " << ticket.getPrice() << " PLN" << endl;
	}
	cout << endl;
}

void TicketVendingMachine::selectTickets()
{
	cout << "How many different ticket types would you like to buy?" << endl;
	int numberOfTypes;
	cin >> numberOfTypes;

	for (int i = 0; i < numberOfTypes; ++i)
	{
		cout << "Enter a number of the corresponding ticket type which you want to buy: " << endl;
		unsigned int numberOfTicket;
		cin >> numberOfTicket;

		if (numberOfTicket < 1 or numberOfTicket > ticketDetails->size())
		{
			cout << "Invalid ticket number. Plese choose a valid ticket number" << endl;
			--i;
			continue;
		}

		cout << "Enter the quantity of tickets for this type: " << endl;
		int quantity;
		cin >> quantity;

		totalCost += (*ticketDetails)[numberOfTicket - 1].getPrice() * quantity;
	}

	cout << "Total cost of selected tickets: " << totalCost << " PLN" << endl;
	cout << endl;
}

void TicketVendingMachine::displayCoinsDetails()
{
	cout << "Machine accepts following coins and nominals:" << endl;
	for (auto& coin : *coinDetails) {
		cout << coin.getNameType() << ". " << coin.getName() << " Nominal: " << coin.getNominal() << endl;
	};
	cout << endl;
}

void TicketVendingMachine::payForTickets()
{
	
	while (amountPaid < totalCost)
	{
		cout << "Insert a coin type (1- ZLOTE, 2- GROSZE) or 0 - QUIT: " << endl;
		int coinType;
		cin >> coinType;

		if (coinType == 0)
		{
			cout << "Transaction cancelled. Returning inserted coins." << endl;
			cout << endl;
			cout << "TVM system will now start from the beginning..." << endl;
			this_thread::sleep_for(chrono::seconds(3));
			cout << endl;
			cout << endl;
			return;
		}

		if (not (coinType == 1 or coinType == 2))
		{
			cout << "Invalid coin type number. Plese try again" << endl;
			continue;
		}

		cout << "Insert a coin nominal: ";
		double coinValue; 
		cin >> coinValue;

		if (!isValidCoinValue(coinType,coinValue))
		{
			cout << "Invalid coin value for the selected coin type. Please insert a valid coin." << endl;
			cout << endl;
			continue;
		}
		
		if (coinType == 2)
		{
			coinValue /= 100.0;
		}
		amountPaid += coinValue;
		cout << "Coin accepted. Current amount: " << amountPaid << " PLN" << endl;

		if (amountPaid >= totalCost)
		{
			returnChange();
		}
	}
}

void TicketVendingMachine::returnChange()
{
	double changeAmount = amountPaid - totalCost;
	
	if (paperAvailable and ticketPrinter->printTickets())
	{
		cout << "Tickets purchased successfully! Your change: " << changeAmount << " PLN" << endl;
		
		giveChangeUsingLargestDenominations(changeAmount);

		cout << "Thank you for using TVM system. Enjoy you travel!" << endl;
		cout << endl;
		cout << "TVM system will now start from the beginning..." << endl;
		this_thread::sleep_for(chrono::seconds(6));
		cout << endl;
		cout << endl;
	}
	else
	{
		cout << endl;
		cout << "ERROR! Unable to print tickets." << endl;
		cout << endl;
		cout << "Returning inserted coins." << endl;
		cout << endl;
		cout << "TVM system will now start from the beginning..." << endl;
		this_thread::sleep_for(chrono::seconds(3));
		cout << endl;
		cout << endl;	
	}

	amountPaid = 0.0;
	totalCost = 0.0;
}

void TicketVendingMachine::giveChangeUsingLargestDenominations(double changeAmount) {
	cout << "Calculating change to use the largest available denominations. Change will be returned with the smallest possible number of coins." << endl;
	
	vector<double> zloteDenominations = {};
	vector<double> groszeDenominations = {};

	for (unsigned int i = 0; i < coinDetails->size(); ++i)
	{
		if ((*coinDetails)[i].getNameType() == 1)
		{
			zloteDenominations.push_back((*coinDetails)[i].getNominal());
		}
		else if ((*coinDetails)[i].getNameType() == 2)
		{
			groszeDenominations.push_back((*coinDetails)[i].getNominal() / 100);
		}
		else 
		{
			cout << "Unknown coin type. Review a implementation of coinDetails vector" << endl;
		}
	}

	sort(zloteDenominations.begin(), zloteDenominations.end(), [](double a, double b) {
		return a > b;
		});

	sort(groszeDenominations.begin(), groszeDenominations.end(), [](double a, double b) {
		return a > b;
		});

	for (unsigned int i = 0; i < zloteDenominations.size(); ++i) {
		int count = static_cast<int>(changeAmount / zloteDenominations[i]);
		if (count > 0) {
			cout << count << " x " << zloteDenominations[i] << " ZLOTE" << endl;
			changeAmount -= count * zloteDenominations[i];
		}
	}

	for (unsigned int i = 0; i < groszeDenominations.size(); ++i) {
		int count = static_cast<int>(changeAmount / groszeDenominations[i]);
		if (count > 0) {
			cout << count << " x " << groszeDenominations[i] *100 << " GROSZE" << endl;
			changeAmount -= count * groszeDenominations[i];
		}
	}
}

bool TicketVendingMachine::isValidCoinValue(int coinType, double coinValue)
{
	for (auto& coin : *coinDetails)
	{
		if (coin.getNameType() == coinType and coin.getNominal() == coinValue)
		{
			return true;
		}
	}
	return false;
}