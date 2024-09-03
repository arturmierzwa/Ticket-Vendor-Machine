#pragma once

#include "ITicketPrinter.h"

class TicketPrinter : public ITicketPrinter {
public:
    bool printTickets() override; 
};
