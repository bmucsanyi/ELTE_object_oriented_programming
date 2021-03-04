/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2021. 02. 24.                  *
*   Project name: PrQueue and testing    *
*****************************************/

#include <iostream>
#include <vector>
#include "prqueue.hpp"
#include "menu.hpp"

/** On this week's practice we'll be implementing a PrQueue type,
 * which is a priority queue.
 * Most important methods (operations) of the type:
 *    isEmpty, add, remMax, max
 * Other complementary methods, solely for testing purposes:
 *    operator==, getLength, getElement
 * We use std::vector for inner implementation of the type.
 * We make good use of its dynamic nature (there is no max value,
 * as it adapts in size), which is where our type differs from
 * the one you had specified on the lab.
 * This means that the variables 'm' and 'n' are not needed.
 *
 * On the lab:
 * Item = rec(string, int)
 * An Item has a 'data' and a 'priority' field.
 * The 'priority' field is needed for use to be able
 * to set up a priority ordering.
 * The 'data' field contains the real data of the item.
 * 
 * Short descriptions of methods:
 * isEmpty: Checks whether the priority queue is empty.
 *  - Needs to check the internal vector's size().
 * add: Adds an Item to the priority queue.
 *  - Needs to use the internal vector's push_back() method.
 * remMax: Takes the Item with maximal priority out of the queue.
 *  - We implement a maximum selection theorem, after which
 *    we save the maximal element, overwrite it with the last
 *    element of the vector, then use pop_back on the vector
 *    and return the saved maximal element.
 * getMax: Returns the Item with maximal priority in the queue.
 *  - See remMax. The only difference is that we don't take
 *    out the maximal element.
 * 
 * Homework:
 * Implement a type (class) for 2 dimensional vectors.
 * Needed methods: addition, subtraction, length, scalar product.
 * Exercise: 2 dimensional vectors are given in a file. (vector1.x vector1.y vector2.x vector2.y ...)
 * We read in a vector from console, too (cin).
 * Is the sum of the vectors read in from the file perpendicular to the one read in from console?
 * Reminder: Two vectors are perpendicular if, and only if their scalar product is zero.
 * Write 'operator>>' and 'operator<<' too for your vector type.
 */

using namespace std;

#define NORMAL_MODE
#ifdef NORMAL_MODE

vector<Item> setup()
{
    int db;
    vector<Item> v;
    cout << "Please provide the number of contestants. (n)\n>>>";
    cin >> db;
    cout << "Please provide the (n) names and (n) results:\n>>>";
    Item tmp;
    for(int i = 0; i < db; ++i) {
        cin >> tmp;
        // cout << tmp << endl; - Check the values we've read in.
        v.push_back(tmp);
    }
    return v;
}

int main()
{
    /*
    * vector<Item> vec = setup();
    * PrQueue PrQ(vec);
    * cout << PrQ.getMax();
    *
    * return 0;
    */
    cout << "Priority queue" << endl;

    Menu Test;
    Test.run();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("isEmpty")
{
    PrQueue PQ;
    CHECK(PQ.isEmpty());

    Item e("data", 1);
    PQ.add(e);
    CHECK(!PQ.isEmpty());

    e = PQ.remMax();
    CHECK(PQ.isEmpty());
}

TEST_CASE("remMax")
{
    Item e("data1", 1);
    Item e2("data2", 2);
    Item e3("data2", 3);
    Item e4("data2", 4);
    Item e5("data2", 5);
    /// Enumerator-based testing
    SECTION("empty prqueue") /// Empty enumerator
    {
        PrQueue PQ;
        /* We test whether it throws an exception
         * if we want to remove the Item with maximal
         * priority from an empty PrQueue.
         */
        CHECK_THROWS(e = PQ.remMax());
    }
    SECTION("prqueue with one element") /// Empty enumerator
    {
        PrQueue PQ;
        PQ.add(e2);
        e = PQ.remMax();
        /* Notice, that the line below only works correctly, because we've
         * written the 'operator==' operator for the 'Item' type.
         * Without this we would get a compilation error, as the compiler
         * couldn't know by itself what the equality check should be based on.
         */
        CHECK(e == e2);
    }
    SECTION("prqueue with more elements", "max in the beginning of prqueue")
    {
        PrQueue PQ;
        PQ.add(e5);
        PQ.add(e2);
        PQ.add(e3);
        e = PQ.remMax();
        /// We test whether we correctly get the element with the maximal priority.
        CHECK(e == e5);
        CHECK(PQ.getLength() == 2);
        CHECK(PQ.getElement(0) == e3);
        CHECK(PQ.getElement(1) == e2);
    }
    /* Here we could write more test cases, in which we test priority
     * queues with more than one elements where the maximal element
     * is the {last, middle} element of the inner vector.
     */
    SECTION("prqueue with more elements",
            "more than one maximal values, which are in the first positions")
    {
        PrQueue PQ;
        PQ.add(e5);
        PQ.add(e5);
        PQ.add(e3);
        e = PQ.remMax();
        CHECK(e == e5); // Checking of ordering
        CHECK(PQ.getLength() == 2);
        CHECK(PQ.getElement(0) == e3);
        CHECK(PQ.getElement(1) == e5);
    }
    /* Additional test cases (REQUIRED):
     * More than one elements, more maximal elements
     *    that are at the end of the underlying vector.
     * More than one elements, all of them are maximal elements.
     * If we used summation, we would have to do
     *    a loading test, too. We don't have to do it right now.
     *    (See slides of third lecture!)
     */
}

#endif
