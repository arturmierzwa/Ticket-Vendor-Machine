#pragma once

#include <string>
#include <vector>
#include <memory>

using namespace std;

class Ticket;
class Coin;
class ITicketPrinter;

class TicketVendingMachine 
{
private:
	double amountPaid;
	double totalCost;
	shared_ptr<vector<Ticket>> ticketDetails;
	shared_ptr<vector<Coin>> coinDetails;
	bool isValidCoinValue(int coinType, double coinValue);
	bool paperAvailable;
	unique_ptr<ITicketPrinter> ticketPrinter;

public:
	TicketVendingMachine(unique_ptr<ITicketPrinter> printer);

	void displayTicketsDetails();
	void selectTickets();
	void displayCoinsDetails();
	void payForTickets();	
	void returnChange();
	void giveChangeUsingLargestDenominations(double changeAmount);
	double getTotalCost();
};
