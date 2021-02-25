#ifndef MENU_H
#define MENU_H
#include "prqueue.hpp"

class Menu {
public:
    Menu() {};
    void run();
private:
    int printMenu();
    void add();
    void remMax();
    void getMax();
    void isEmpty();
    void loadTest();
    void printPrQueue();
    PrQueue m_Q;
};

#endif // MENU_H
