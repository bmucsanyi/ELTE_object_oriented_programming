#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "map.hpp"

class Menu
{
    public:
        Menu(){};
        void Run();
    private:
        int printMenu();
        void putIn();
        void takeOut();
        void isIn();
        void count();
        void printMap();
        void loadTest();
        Map m_M;
};

#endif // MENU_H_INCLUDED
