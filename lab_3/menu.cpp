#include <iostream>
#include "menu.hpp"
// #include "read.hpp"
#include <sstream>
#define menudb 6

using namespace std;

/// For validating input (Menu points must be between 0 and menudb.)
bool check(int a) { return a >= 0 && a <= menudb; }

/* Template function for general input reading, written by Tibor Gregorics, Dr.
 * For the computer-based test, you can use this.
 * You can also find it in the sample code of the second lecture. (read.hpp)
 */
template <typename Item>
Item read( const std::string &msg, const std::string &err, bool valid(Item))
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
        if (wrong) std::cout << err << std::endl;
    } while (wrong);
    return n;
}

void Menu::run()
{
    int v;
    do {
        v = printMenu();
        switch (v) {
            case 1:
                add();
                printPrQueue();
                break;
            case 2:
                remMax();
                printPrQueue();
                break;
            case 3:
                getMax();
                printPrQueue();
                break;
            case 4:
                isEmpty();
                printPrQueue();
                break;
            case 5:
                printPrQueue();
                break;
            case 6:
                loadTest();
                break;
            default:
                cout<<"\nSee you!\n";
                break;

        }
    } while (v != 0);
}

int Menu::printMenu()
{
    int answer;
    cout << "\n****************************************\n";
    cout << "0. Quit\n";
    cout << "1. Add to PrQueue\n";
    cout << "2. Remove maximal element\n";
    cout << "3. Get maximal element\n";
    cout << "4. Empty check\n";
    cout << "5. Print PrQueue\n";
    cout << "6. Load test (maximum number of elements to add to PrQueue)\n";
    cout << "****************************************\n";
    // We can build strings easily with the usage of ostringstream (just like with StringBuilder in Java).
    // This way we don't have to convert variables we want to write to console to strings.
    ostringstream s;
    s << "Number should be between 0 and " << menudb << endl;
    string errorMessage = s.str();
    answer = read<int>(">>>", errorMessage, check);
    
    return answer;
}

void Menu::add()
{
    Item e;
    cout << "Item to add:\n>>>";
    cin >> e;
    Q_.add(e);
}

void Menu::remMax()
{
    Item e;
    bool fail = false;
    try {
        e = Q_.remMax();
    } catch (PrQueue::Exception err) {
        fail = true;
        if (err == PrQueue::EMPTY_PRQUEUE)
            cerr << "remMax failed, empty PrQueue!\n";
        else
            cerr << "The program doesn't work as intended, consult the writer :)\n";
    }
    if (!fail) cout << "Element taken out:\n" << e << endl;
}

void Menu::getMax()
{
    Item e;
    bool fail = false;
    try {
        e = Q_.getMax();
    } catch (PrQueue::Exception err) {
        fail = true;
        if (err == PrQueue::EMPTY_PRQUEUE)
            cerr << "getMax failed, empty PrQueue!\n";
        else
            cerr << "The program doesn't work as intended, consult the writer :)\n";
    }
    if (!fail) cout << "Max element:\n" << e << endl;
}

void Menu::isEmpty()
{
    if (Q_.isEmpty())
        cout << "The PrQueue is empty.\n";
    else
        cout << "The PrQueue is not empty.\n";
}


void Menu::loadTest()
{
    const long int size = 1000000000;
    PrQueue Q_;
    cout << "Current element:\n";
    try {
        for (long int i = 1; i < size; ++i) {
            if (i % 1000000 == 0) cout << i <<endl;
            Q_.add(Item("a", i));
        }
    } catch(...) {
        cerr << "No more memory!\n";
        cerr<<"Size of prQueue: " << Q_.getLength() << endl;
    }
} /// 16777216

void Menu::printPrQueue()
{
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    cout << "PrQueue:\n";
    cout << "Size of PrQueue (only for testing): " << Q_.getLength() << endl;
    for (int i = 0; i < Q_.getLength(); ++i) {
        cout << Q_.getElement(i) << endl;
    }
    cout << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
}


