/*****************************************
*   Author: Bálint Mucsányi              *
*   E-mail: mucsanyibalint99@gmail.com   *
*   Date: 2021. 03. 04.                  *
*   Project name: Map and testing        *
*****************************************/

#include <iostream>
#include <vector>
#include "map.hpp"
#include "menu.hpp"

/* On this week's practice we'll be implementing a Map type,
 * which is an associative array.
 * Most important methods (operations) of the type:
 *    count, insert, erase, isIn, operator[], isEmpty
 * Other complementary methods, solely for testing purposes:
 *    getLength, getCapacity, getItems, getLogSearch
 */

// #define NORMAL_MODE
#ifdef NORMAL_MODE

int main()
{
    std::cout << "Map" << std::endl;

    Menu Test;
    Test.Run();

    return 0;
}

#else
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("isEmpty, isIn")
{
    Map M;
    CHECK(M.isEmpty());

    Item e("a", 1);
    CHECK_FALSE(M.isIn(e.key));
    M.insert(e);
    CHECK_FALSE(M.isEmpty());
    CHECK(M.isIn(e.key));

    M.erase(e.key);
    CHECK(M.isEmpty());
    CHECK_FALSE(M.isIn(e.key));
}

TEST_CASE("insert")
{
    Map M;
    Item e1("a", 1);
    Item e2("b", 2);
    Item e3("c", 3);
    Item e4("d", 4);
    Item e5("e", 5);

    M.insert(e2);
    CHECK(M.getLength() == 1);
    std::vector<Item> v = M.getItems();
    CHECK(v[0] == e2);

    M.insert(e5);
    CHECK(M.getLength() == 2);
    v = M.getItems();
    CHECK(v[0] == e2);
    CHECK(v[1] == e5);

    M.insert(e1);
    v = M.getItems();
    CHECK(v[0] == e1);
    CHECK(v[1] == e2);
    CHECK(v[2] == e5);

    M.insert(e3);
    M.insert(e4);
    CHECK(M.getLength() == 5);
    v = M.getItems();
    CHECK(v[0] == e1);
    CHECK(v[1] == e2);
    CHECK(v[2] == e3);
    CHECK(v[3] == e4);
    CHECK(v[4] == e5);
}

TEST_CASE("logSearch")
{
    SECTION("empty map")
    {
        Map M;
        CHECK_FALSE(M.getLogSearch(3).first);
    }

    ///Items for testing
    Item e1("a", 1);
    Item e2("b", 2);
    Item e3("c", 3);
    Item e5("a", 5);
    SECTION("one item")
    {
        Map M;
        M.insert(e1);
        CHECK(M.getLogSearch(e1.key).first);
        CHECK(M.getLogSearch(e1.key).second == 0);
        M.erase(e1.key);
        CHECK(0 == M.getLength());
    }

    SECTION("more items, first is searched")
    {
        Map M;
        M.insert(e5);
        M.insert(e2);
        M.insert(e3);
        CHECK(M.getLogSearch(e2.key).first);
        CHECK(M.getLogSearch(e2.key).second == 0);
        M.erase(e2.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e3);
        CHECK(v[1] == e5);
    }

    SECTION("more items, last is searched")
    {
        Map M;
        M.insert(e5);
        M.insert(e2);
        M.insert(e3);
        CHECK(M.getLogSearch(e5.key).first);
        CHECK(M.getLogSearch(e5.key).second == 2);
        M.erase(e5.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e2);
        CHECK(v[1] == e3);
    }

    SECTION("more items, middle is searched")
    {
        Map M;
        M.insert(e5);
        M.insert(e2);
        M.insert(e3);
        CHECK(M.getLogSearch(e3.key).first);
        CHECK(M.getLogSearch(e3.key).second == 1);
        M.erase(e3.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e2);
        CHECK(v[1] == e5);
    }

    SECTION("more items, searched does not exist")
    {
        Map M;
        M.insert(e5);
        M.insert(e2);
        M.insert(e3);
        CHECK_FALSE(M.getLogSearch(e1.key).first);
        CHECK(2 == M.getLogSearch(4).second);
    }
}
TEST_CASE("erase")
{
    Item e1("a", 1);
    Item e2("b", 2);
    Item e3("c", 3);
    Item e4("d", 4);
    Item e5("e", 5);
    SECTION("erase first")
    {
        Map M;
        M.insert(e2);
        M.insert(e3);
        M.insert(e1);
        M.erase(e1.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e2);
        CHECK(v[1] == e3);
    }
    SECTION("erase last")
    {
        Map M;
        M.insert(e2);
        M.insert(e3);
        M.insert(e1);
        M.erase(e3.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e1);
        CHECK(v[1] == e2);
    }
    SECTION("erase middle")
    {
        Map M;
        M.insert(e2);
        M.insert(e3);
        M.insert(e1);
        M.erase(e2.key);
        CHECK(M.getLength() == 2);
        std::vector<Item> v = M.getItems();
        CHECK(v[0] == e1);
        CHECK(v[1] == e3);
    }
}

TEST_CASE("exceptions")
{
    SECTION("more items, middle is searched")
    {
        Item e1("a", 1);
        Item e2("b", 2);
        Item e3("c", 3);
        Item e5("a", 5);
        Map M;
        CHECK_THROWS(M.erase(2));
        M.insert(e5);
        M.insert(e2);
        M.insert(e3);
        CHECK_THROWS(M.insert(e5));
        CHECK_THROWS(M.insert(e2));
        CHECK_THROWS(M.insert(e3));
        CHECK_THROWS(M.erase(4));
    }
}

#endif
