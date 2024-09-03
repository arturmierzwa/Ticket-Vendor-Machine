#pragma once

class ITicketPrinter
{
public:
    virtual bool printTickets() = 0;
    virtual ~ITicketPrinter() = default;
};