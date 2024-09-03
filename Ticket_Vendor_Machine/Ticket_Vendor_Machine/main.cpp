
#include "TicketVendingMachine.h"
#include "TicketPrinter.h"
#include <iostream>
#include <thread>
#include <chrono>
//FOR TESTING PURPOSES COMMENT ABOVE INCLUDES AND APPLICATION'S MAIN. UNCOMMENT BELOW LINE AND MAIN: LINES 58-64
//#include "testTicketVendingMachine.h"

using namespace std;

int main()
{
    unique_ptr<TicketPrinter> printer = make_unique<TicketPrinter>();

    TicketVendingMachine tvm(std::move(printer));

    char choise = 0;

    while (choise != 3)
    {

        cout << "Welcome to the Ticket Vendor Machine System!" << endl;
        cout << "********************************************" << endl;
        cout << endl;
        cout << "Here you can buy a tickets for your travel. Machine accepts payments in coins only.\n"
            << "You can also quit and exit TVM System.\n\n"
            << "1. Buy a ticket.\n"
            << "2. Contact with the service.\n"
            << "3. Exit a Ticket Vendor Machine System.\n\n"
            << "Plese enter the number of option you choose : ";

        cin >> choise;
        switch (choise)
        {
        case '1':
            tvm.displayTicketsDetails();
            tvm.selectTickets();
            tvm.displayCoinsDetails();
            tvm.payForTickets();
            break;
        
        case '2':
            cout << "Contact with the service. Phone number is: 999-666-999." << endl;
            cout << "The system will restart now." << endl;
            this_thread::sleep_for(chrono::seconds(4));
            break;
        case '3':
            cout << "Thank you for using Ticekt Vendon Machine System. Application is closed now." << endl;
            this_thread::sleep_for(chrono::seconds(5));
            break;
        default:
            cout << "Invalid choise. The system will restart now. Please try again." << endl;
            this_thread::sleep_for(chrono::seconds(2));
        }
    }

    return 0;
}

/*int main()
{
    
    
    testTicketVendingMachine();
    return 0;
}*/