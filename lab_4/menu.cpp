#include <iostream>
#include "menu.hpp"
#include <sstream>
#define menudb 6

/// For validating input (Menu points must be between 0 and menudb.)
bool check(int a) { return a >= 0 && a <= menudb; }

/* Template function for general input reading, written by Tibor Gregorics, Dr.
 * For the computer-based test, you can use this.
 * You can also find it in the sample code of the second lecture. (read.hpp)
 */
template <typename Item>
Item read(const std::string &msg, const std::string &err, bool valid(Item))
{
    Item n;
    bool wrong;
    do {
        std::cout << msg;
        std::cin >> n;
        if ((wrong = std::cin.fail())) std::cin.clear();
        std::string tmp;
        getline(std::cin, tmp);
        wrong = wrong || tmp.size() != 0 || !valid(n);
        if (wrong) std::cerr << err << std::endl;
    } while (wrong);
    return n;
}

void Menu::Run()
{
    int v;
    do {
        v = printMenu();
        switch (v) {
            case 1:
                putIn();
                printMap();
                break;
            case 2:
                takeOut();
                printMap();
                break;
            case 3:
                count();
                printMap();
                break;
            case 4:
                isIn();
                printMap();
                break;
            case 5:
                printMap();
                break;
            case 6:
                loadTest();
                break;
            default:
                std::cout << "\nSee you!\n";
                break;
        }
    } while (v != 0);
}

int Menu::printMenu()
{
    int answer;
    std::cout << "\n****************************************\n";
    std::cout << "0. Exit\n";
    std::cout << "1. Put in\n";
    std::cout << "2. Take out\n";
    std::cout << "3. Count the elements\n";
    std::cout << "4. IsIn\n";
    std::cout << "5. Print Map\n";
    std::cout << "6. Load test (maximum number of elements to add to Map)\n";
    std::cout << "****************************************\n";
    // We can build std::strings easily with the usage of ostd::stringstream (just like with std::stringBuilder in Java).
    // This way we don't have to convert variables we want to write to console to std::strings.
    std::ostringstream s;
    s << "Number should be between 0 and " << menudb << '\n';
    std::string errorMessage = s.str();
    answer = read<int>(">>> ", errorMessage, check);

    return answer;
}

void Menu::putIn()
{
    bool error = false;
    try {
        Item e;
        std::cout << "Item: ";
        std::cin >> e;
        m_M.insert(e);
    } catch (Map::Error err) {
        error = true;
        if (err == Map::EXISTING_KEY) {
            std::cerr << "Insert is unsuccessful. The key already exists!\n";
        } else {
            std::cerr << "Unknown error.\n";
        }
    }
    if (!error) {
        std::cout << "Success!\n\n";
    }
}

void Menu::takeOut()
{
    int key;
    std::cout << "Key: ";
    std::cin >> key;
    bool error = false;
    try {
        m_M.erase(key);
    } catch (Map::Error err) {
        error = true;
        if (err == Map::MISSING_KEY) {
            std::cerr << "Take out is unsuccessful, the key does not exist!\n";
        } else {
            std::cerr << "Unknown error.\n";
        }
    }
    if (!error) {
        std::cout << "Success!\n\n";
    }
}

void Menu::isIn()
{
    int key;
    std::cout << "Key: ";
    std::cin >> key;

    if (m_M.isIn(key)) {
        std::cout << "It is in!\n\n";
    } else {
        std::cout << "It is NOT in!\n\n";
    }
}

void Menu::count()
{
    std::cout << "There are " << m_M.getLength() << " items in the map.\n";
}

void Menu::printMap()
{
    std::cout << m_M;
}

void Menu::loadTest()
{
    const int size = 1000000000;
    Map m_M;
    std::cout << "Follow the current size of the map:\n";
    try {
        for (int i = 1; i < size; ++i) {
            if (i % 1000000 == 0) {
                std::cout << i << std::endl;
            }
            m_M.insert(Item("a", i));
        }
    } catch (...) {
        std::cerr << "Run out of memory!\n";
        std::cerr << "The size of the vector: " << m_M.getLength() << std::endl;
    }
}
