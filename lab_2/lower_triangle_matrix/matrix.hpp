#ifndef MATRIX_H
#define MATRIX_H
#include <vector>
#include <fstream>
#include <cmath>

class matrix
{
    public:
        /// Constructors
        matrix();
        matrix(const std::vector<int> &vec);
        matrix(int size);
        matrix(const std::string &fileName);

        /// Getters
        int getSize() const { return m_size; }
        int getElement(int i,int j) const;

        /// Setters
        void setVec(const std::vector<int> &vec);
        void setElement(int i,int j,int e);

        /// Static methods
        static matrix add(const matrix& a,const matrix& b); ///operators come later, static methods are shown on the lecture
        static matrix multiply(const matrix& a,const matrix& b);

        /// Operator overload - this can be shown this week, too
        friend std::ostream &operator<<(std::ostream &os,const matrix& m);

    private:
        /// Private attributes
        std::vector<int> m_vec;
        int m_size;

        /// Private methods
        int ind(int i,int j) const;
        double calcSizeFromLength(unsigned int size);
        bool inLowerTrng(int i,int j) const;
};

#endif // MATRIX_H
