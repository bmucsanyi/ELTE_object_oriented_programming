#include "map.hpp"

void Map::insert(Item e)
{
    std::pair<bool, int> out = logSearch(e.key);
    if (!out.first) {  // Element not found
        m_vec.resize(m_vec.size() + 1);
        for (int i = m_vec.size() - 2; i >= out.second; i--) {
            m_vec[i + 1] = m_vec[i]; // Insert in order
        }
        m_vec[out.second] = e;
    } else {
        throw EXISTING_KEY;
    }
}

void Map::erase(int key)
{
    std::pair<bool, int> out = logSearch(key);
    if (out.first) {  // Element found
        for (unsigned int i = out.second + 1; i < m_vec.size(); i++) {
            m_vec[i - 1] = m_vec[i];
        }
        m_vec.pop_back();
    } else {
        throw MISSING_KEY;
    }
}

bool Map::isIn(int key) const
{
    return logSearch(key).first;
}

std::string &Map::operator[](int key)
{
    std::pair<bool, int> out = logSearch(key);
    if (out.first) {
        return m_vec[out.second].data;
    } else {
        throw MISSING_KEY;
    }
}

std::pair<bool, int> Map::logSearch(int key) const
{
    bool l = false;
    int lowerBound = 0;
    int upperBound = m_vec.size() - 1;
    int ind;
    while (!l && lowerBound <= upperBound) {
        ind = (lowerBound + upperBound) / 2;
        if (m_vec[ind].key > key) {
            upperBound = ind - 1;
        } else if (m_vec[ind].key < key) {
            lowerBound = ind + 1;
        } else {
            l = true;
        }
    }
    if (!l) {
        ind = lowerBound;
    }
    return std::pair<bool, int>(l, ind);
}

std::ostream &operator<<(std::ostream &s, const Map &m)
{
    s << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n";
    s << "Number of elements: " << m.m_vec.size() << "\nContent: " << std::endl;
    for (unsigned i = 0; i < m.m_vec.size(); ++i) {
        s << " (" << m.m_vec[i].key << "," << m.m_vec[i].data << ")";
    }
    s << "\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n\n";
    return s;
}

std::vector<Item> Map::getItems() const
{
    std::vector<Item> v;
    for (unsigned i = 0; i < m_vec.size(); ++i) {
        v.push_back(m_vec[i]);
    }
    return v;
}

std::istream &operator>>(std::istream &s, Item &e)
{
    s >> e.data >> e.key;
    return s;
}

std::ostream &operator<<(std::ostream &s, const Item &e)
{
    s << "key: " << e.key << " data: " << e.data << " ";
    return s;
}

bool Item::operator==(const Item& b) {
    return key == b.key && data == b.data;
}