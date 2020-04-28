#include "atm.h"

#include "card.h"
#include "center.h"
#include "customer.h"


using namespace std;

void ATM::process(Customer* cust) const
{
    Card* card = cust->giveCard();
    if (card->pinCheck(cust->givePin())) {
        int a = cust->giveAmount();
        if (_center->getBalance(card->_bankCode, card->_cardNo) >= a) {
            _center->transaction(card->_bankCode, card->_cardNo, -a);
        } else
            throw FEW_MONEY;
    } else
        throw WRONG_PIN_CODE;
}
