#include "TicketPrinter.h"
#include <iostream>

using namespace std;

bool TicketPrinter::printTickets()
{   
    bool printingAllowed = true;

    if (printingAllowed)
    {
        cout << endl;
        cout << "PRINTING TICKETS FROM TICKETPRINTER INTERFACE" << endl;
        cout << endl;
        return true;
    }
    else
    {
        cout << endl;
        cout << "PRINTING FROM TICKETPRINTER INTERFACE NOT ALLOWED. CONTACT WITH THE SERVICE" << endl;
        cout << endl;
        return false;
    }

    // Printing is always successful for this example, but another printing logic
    // can be implemented here. What is important - this is independent from TicketVendingMachine.
    // Strategy Design Pattern has been used to separate these implementations.
}
