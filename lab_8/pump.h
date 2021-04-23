#pragma once

#include "cash.h"

class Pump
{
public:
    Pump() : _display(0) {}
    void fill(int l) { _display = l; }
    int getQuantity() const { return _display; }
    friend Cash; // class Cash can now see Pump's private members and methods

private:
    int _display;
    void resetQuantity() { _display = 0; }
};
