#pragma once

#include "card.h"

class Center;
class Customer;

class ATM
{
private:
	std::string _location;
	Center *_center;

public:
	enum Errors
	{
		FEW_MONEY,
		WRONG_PIN_CODE
	};

	ATM(std::string address, Center *c) : _location(address), _center(c) {}

	void process(Customer *cus) const;
};
