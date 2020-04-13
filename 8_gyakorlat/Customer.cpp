#include "Customer.h"

Customer::Customer(const std::string& name, const std::string& fileName)
    : name(name)
{
    std::ifstream f(fileName.c_str());
    if (f.fail())
        throw OPEN_ERROR;
    std::string productName;
    while (f >> productName)
        list.push_back(productName);
    f.close();
}

void Customer::purchase(Shop& shop)
{
    for (const std::string& productName : list) {
        unsigned int ind; /// Fontos az unsigned.
        if (linSearch(productName, shop.food, ind)) {
            putInCart(shop.food->getProduct(ind));
            shop.food->takeOut(ind);
        }
    }
    for (const std::string& productName : list) {
        unsigned int ind;
        if (minSearch(productName, shop.technical, ind)) {
            putInCart(shop.technical->getProduct(ind));
            shop.technical->takeOut(ind);
        }
    }
}

void Customer::putInCart(std::shared_ptr<Product> product)
{
    if (product != nullptr)
        basket.push_back(product);
    else
        throw NULLPTR_ERROR;
}

bool Customer::linSearch(const std::string& prName, std::shared_ptr<Department> d, unsigned int& ind) const
{
    for (ind = 0; ind < d->stockPiece(); ++ind) {
        if (prName == d->getProduct(ind)->getName())
            return true;
    }
    return false;
}

bool Customer::minSearch(const std::string& prName, std::shared_ptr<Department> d, unsigned int& ind) const
{
    bool l = false;
    int minPrice;
    for (unsigned int i = 0; i < d->stockPiece(); ++i) {
        if (l && prName == d->getProduct(i)->getName()) {
            if (minPrice > d->getProduct(i)->getPrice()) {
                minPrice = d->getProduct(i)->getPrice();
                ind = i;
            }
        } else if (!l && prName == d->getProduct(i)->getName()) {
            l = true;
            minPrice = d->getProduct(i)->getPrice();
            ind = i;
        }
    }
    return l;
}

std::ostream& operator<<(std::ostream& os, const Customer& c)
{
    os << c.name << "'s basket contains:\n";
    for (auto p : c.basket) {
        os << " " << p->getName() << " " << p->getPrice() << "USD\n";
    }
    return os;
}
