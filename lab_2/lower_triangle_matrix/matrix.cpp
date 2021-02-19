#include "matrix.hpp"

/// Constructors

matrix::matrix() /// basic 3x3 matrix
{
    m_size = 3;
    m_vec = {1, 2, 3, 4, 5, 6};
}
matrix::matrix(const std::vector<int> &vec) /// matrix with given vector
{
    setVec(vec);
}
matrix::matrix(int size) /// zero matrix with given size
{
    m_size = size;
    m_vec.resize(size * (size + 1) / 2, 0);
}
matrix::matrix(const std::string &fileName) /// matrix read from a file
{
    std::fstream f(fileName);
    if (f.fail())
    {
        m_size = 0;
        m_vec.clear();
    }
    else
    {
        int e;
        while (f >> e)
        {
            m_vec.push_back(e);
        }
        double n = calcSizeFromLength(m_vec.size());
        if (n == floor(n))
        {
            m_size = n;
        }
        else
        {
            m_size = 0;
            m_vec.clear();
        }
    }
}

/// Private methods

int matrix::ind(int i, int j) const ///vector index from matrix indices
{
    return j + i * (i - 1) / 2 - 1; ///indexing from zero
}

double matrix::calcSizeFromLength(unsigned int size) /// calculate the matrix size based on the vector size
{
    return (-1 + sqrt(1 + 8 * size)) / 2; /// root of (x^2+x-2*size=0) as x*(x-1)/2=size
}

bool matrix::inLowerTrng(int i, int j) const /// are they indices of the lower triangular part
{
    return (1 <= j && j <= i && i <= m_size);
}

///Getter

int matrix::getElement(int i, int j) const /// Get matrix element by indices
{
    if (inLowerTrng(i, j)) /// indices pointing to the lower triangle
    {
        return m_vec[ind(i, j)];
    }
    else if (1 <= j && j <= m_size && 1 <= i && i <= m_size) /// other valid indices
    {
        return 0;
    }
    else /// invalid indices
    {
        return -1; /// exception handling comes next week
    }
}

/// Setter

void matrix::setVec(const std::vector<int> &vec) /// Modifying the whole matrix
{
    double n = calcSizeFromLength(vec.size()); /// calculate the matrix size based on the vector length
    if (n == floor(n))                         ///if the supposed matrix size is integer
    {
        m_size = n;
        m_vec = vec;
    }
    else /// invalid vector length
    {
        m_size = 0;
        m_vec.clear();
    }
}

void matrix::setElement(int i, int j, int e)
{
    if (1 <= j && j <= i && i <= m_size) /// indices of the lower part
    {
        m_vec[ind(i, j)] = e; /// vector indexing starts at 0
    }
}

/// Static methods

matrix matrix::add(const matrix &a, const matrix &b)
{
    if (a.getSize() == b.getSize())
    {
        matrix sum(a);
        for (int i = 0; i < a.m_vec.size(); i++)
        {
            sum.m_vec[i] += b.m_vec[i];
        }
        return sum;
    }
    else
    {
        return matrix({}); /// empty matrix
    }
}

matrix matrix::multiply(const matrix &a, const matrix &b)
{
    if (a.getSize() == b.getSize())
    {
        matrix mul(a.getSize());
        for (int i = 1; i <= a.m_size; i++)
        {
            for (int j = 1; j <= a.m_size; j++)
            {
                if (a.inLowerTrng(i, j)) /// only the lower triangular part need calculation
                {
                    for (int k = 1; k <= a.m_size; k++)
                    {
                        mul.setElement(i, j, mul.getElement(i, j) + a.getElement(i, k) * b.getElement(k, j));
                    }
                }
            }
        }
        return mul;
    }
    else
    {
        return matrix({}); /// empty matrix
    }
}

std::ostream &operator<<(std::ostream &os, const matrix &m)
{
    os << m.m_size << "x" << m.m_size << std::endl;
    for (int i = 1; i <= m.m_size; i++)
    {
        for (int j = 1; j <= m.m_size; j++)
        {
            os << m.getElement(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}
