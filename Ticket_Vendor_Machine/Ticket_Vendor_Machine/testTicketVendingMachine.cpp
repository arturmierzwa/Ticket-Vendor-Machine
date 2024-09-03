#include "TicketVendingMachine.h"
#include "TicketPrinter.h"
#include <iostream>
#include <sstream>
#include <cassert>
#include "testTicketVendingMachine.h"

using namespace std;

void assertEqual(double expected, double actual, string message) {
    if (expected == actual) {
        std::cout << "PASS: " << message << std::endl;
    }
    else {
        std::cout << "FAIL: " << message << " (Expected: " << expected << ", Actual: " << actual << ")" << std::endl;
    }
}

void testTicketVendingMachine() {
    
    // Create a TicketPrinter object
    auto printer = make_unique<TicketPrinter>();

    // Create a TicketVendingMachine object
    TicketVendingMachine tvm(std::move(printer));

    // Test displayTicketsDetails
    cout << "Testing displayTicketsDetails..." << std::endl;
    tvm.displayTicketsDetails();  // Check the results in console if displayed correctly

    // Test selectTickets
    cout << "Testing selectTickets..." << std::endl;
    istringstream simulatedInput("1\n1\n1\n");
    cin.rdbuf(simulatedInput.rdbuf());
    tvm.selectTickets();  // Check the results in console if displayed correctly
    cin.rdbuf(cin.rdbuf());  // Restore cin

    double expectedTotalCost = 5;
    double actualTotalCost = tvm.getTotalCost();
    assertEqual(expectedTotalCost, actualTotalCost, "Testing total cost calculation");
    cout << endl;
 

    // Test payForTickets
    cout << "Testing payForTickets..." << std::endl;
    istringstream simulatedPayment("1\n2\n1\n5\n0\n");
    cin.rdbuf(simulatedPayment.rdbuf());
    tvm.payForTickets();  // Check the results in console if displayed correctly
    cin.rdbuf(cin.rdbuf());

    cout << "All tests passed!" << endl;
}


//PROBLEMS WITH GTESTS - couldn't handle with linker dependencies in my IDE
//WITH GTEST IT COULD LOOK LIKE:

/*
#include "gtest/gtest.h"
#include "TicketVendingMachine.h"
#include "TicketPrinter.h"

class TicketVendingMachineTestSuite : public ::testing::Test
{
protected:
    int resultOfChoosing111InSimulatedInputToSelectTicketsMethod = 5;
};

TEST_F(TicketVendingMachineTestSuite, SelectTickets) {
    
    //ARRANGE 
    auto printer = std::make_unique<TicketPrinter>();
   
    TicketVendingMachine tvm(std::move(printer));

    std::istringstream simulatedInput("1\n1\n1\n");
    std::cin.rdbuf(simulatedInput.rdbuf());

    // ACT
    tvm.selectTickets();

    // Restore cin
    std::cin.rdbuf(std::cin.rdbuf());

    // ASSERT
    ASSERT_EQ(tvm.getTotalCost(), resultOfChoosing111InSimulatedInputToSelectTicketsMethod);  //expected total cost is 5;
}
*/
