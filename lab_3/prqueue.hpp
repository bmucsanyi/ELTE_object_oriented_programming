#ifndef PRQUEUE_H
#define PRQUEUE_H

#include <string>
#include <vector>
#include <iostream>
#include <ostream>

struct Item {
    std::string data;
    int priority;
    /* We can give default parameter values to functions and methods this way.
     * If we provide the corresponding values when invoking the function,
     * then thos are copied into the function's local variables.
     * Otherwise they take on the values specified after the equality sign.
     * This is a lot easier than to write different constructors for
     * all cases where some parameter is missing.
     */
    Item(std::string data = "", int pr = 0) : data(data), priority(pr) {}
    // Overriding the 'operator<<' operator is done in the same way
    // as on the last practice.
    friend std::ostream &operator<<(std::ostream &os, const Item &e) {
        os << "Name and points: " << "<" << e.data << ", " << e.priority << ">";
        return os;
    }
    /* We can also overload the 'operator>>' operator in the same way
     * as the 'operator<<' operator. This way we can write significantly
     * cleaner code, as we can read an Item object directly from a file.
     */
    friend std::istream &operator>>(std::istream &is, Item &e) {
        is >> e.data >> e.priority;  // user-friendly read
        return is;
    }
    // It is significantly easier to test equalities between
    // Item objects with catch.hpp, instead of testing the
    // equalities of each data members.
    bool operator==(const Item &e) {
        return data == e.data && priority == e.priority;
    }
};

class PrQueue {
public:
    enum Exception { EMPTY_PRQUEUE };
    PrQueue() : m_vec(0) {}
    PrQueue(const std::vector<Item> &vec) { m_vec = vec; }
    bool isEmpty() const;
    // Item is a compound structure (struct),
    // so we take it as a constant reference, just as we usually do.
    void add(const Item &e);
    Item remMax();
    Item getMax() const;
    /* A priority queue doesn't have to provide the 'getLength()' method
     * (See Algorithms and data structures I.),
     * but for the sake of testing it is very convenient to use, and
     * easy to implement.
     */
    int getLength() const {return m_vec.size();}
    /* A priority queue also doesn't have to provide the possibility
     * of getting an element by index, but we will make good use of it
     * when testing the type.
     */
    Item getElement(int index) const { return m_vec[index]; }

private:
    std::vector<Item> m_vec;
    int maxIndex() const;
};

#endif
