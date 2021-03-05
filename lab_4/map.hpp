#ifndef MAP_H
#define MAP_H
#include <string>
#include <iostream>
#include <vector>

struct Item {
    std::string data;
    int key;

    Item() {};
    Item(std::string data, int key) : data(data), key(key) {}

    friend std::istream &operator>>(std::istream &s, Item &e);
    friend std::ostream &operator<<(std::ostream &s, const Item &e);

    // For the sake of testing
    bool operator==(const Item& b);
};

class Map {
public:
    enum Error {
        MISSING_KEY,
        EXISTING_KEY
    };

    int count() const;
    void insert(Item a);
    void erase(int key);
    bool isIn(int key) const;
    std::string &operator[](int key);
    bool isEmpty() const { return m_vec.size() == 0; }
    friend std::ostream &operator<<(std::ostream &s, const Map &m);

    // For the sake of testing
    unsigned int getLength() const { return m_vec.size(); }
    unsigned int getCapacity() const { return m_vec.capacity(); }
    std::vector<Item> getItems() const;
    std::pair<bool, int> getLogSearch(int key) const { return logSearch(key); }

private:
    std::vector<Item> m_vec;

    std::pair<bool, int> logSearch(int key) const;
};

#endif
