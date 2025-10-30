// VectorDouble.cpp
// Implementation of the special member functions and a few other operator overloads
#include <iostream>
#include "VectorDouble.h"
using namespace std;
VectorDouble::VectorDouble(size_t size) : m_size(size)
{
    cerr << "\tcalling constructor..." << endl;
    m_data = new double[size];
}
VectorDouble::~VectorDouble()
{
    cerr << "\tcalling destructor..." << endl;
    delete[] m_data;
}

size_t VectorDouble::size() const
{
    return m_size;
}
// Indexing Operators
double &VectorDouble::operator[](size_t index) {
    if (index >= m_size) {
       throw runtime_error(
        "VectorDouble.operator[]: index out of range");
    }
    return m_data[index];
}
// do not delete

const double &VectorDouble::operator[](size_t index) const {
    if (index >= m_size) {
       throw runtime_error(
        "VectorDouble.operator[]: index out of range");
    }
    return m_data[index];
}



// Copy constructor and assignment operator
VectorDouble::VectorDouble(const VectorDouble &vec):
    m_size(vec.size()) {
    cerr << "\tcalling copy constructor..." << endl;
    m_data = new double[m_size];
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        m_data[i1] = vec[i1];
    }
}
// Assigment Operator
VectorDouble &VectorDouble::operator=(
              const VectorDouble &vec) {
    cerr << "\tcalling assigment operator..." << endl;
    if (&vec==this) return *this; // nothing to do
    delete[] m_data; // free all data;
    m_size = vec.size();
    m_data = new double[m_size];
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        m_data[i1] = vec[i1];
    }
    return *this;
}
// move copy constructor and assigment operator
VectorDouble::VectorDouble(VectorDouble &&vec): 
m_size(vec.size()) {
    cerr << "\tcalling move copy constructor..." << endl;
    m_data = vec.m_data; // point to m_data from vec
    vec.m_data=nullptr;  // vec now is empty
}
// Move Assigment Operator
VectorDouble &VectorDouble::operator=(VectorDouble &&vec) {
    cerr << "\tcalling move assigment operator..." << endl;
    delete[] m_data;
    m_data=vec.m_data;  // no copy of data
    vec.m_data=nullptr; // the destructor of vec
    return *this;       // will do nothing
}

// friend stream operator
ostream &operator<<(ostream &os, const VectorDouble &vec)
{
    os << "{";
    for (size_t i1 = 0; i1 < vec.m_size; i1++)
    {
        os << vec.m_data[i1];
        if (i1 != vec.m_size - 1)
        {
            os << ",";
        }
    }
    os << "}";
    return os;
}
// equality operator
bool VectorDouble::operator==(const VectorDouble &vec) {
    if (vec.size()!=m_size) return false;
    for (size_t i1=0;i1<m_size;i1++) {
        if (vec[i1]!=m_data[i1]) return false;
    }
    return true;
}
// addition operator
VectorDouble VectorDouble::operator+(const VectorDouble &vec) 
const {
    cerr << "\tcalling operator+..."<<endl;
    if (m_size != vec.size()) {
        throw runtime_error(
          "Vector.operator+: Sizes do not match.");
    }
    VectorDouble ret(m_size);
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        ret[i1] = m_data[i1] + vec.m_data[i1];
    }
    return ret;
}
// substraction operator
VectorDouble VectorDouble::operator-(const VectorDouble &vec) 
const {
    cerr << "\tcalling operator+..."<<endl;
    if (m_size != vec.size()) {
        throw runtime_error(
          "Vector.operator-: Sizes do not match.");
    }
    VectorDouble ret(m_size);
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        ret[i1] = m_data[i1] - vec.m_data[i1];
    }
    return ret;
}

// increment operator
VectorDouble &VectorDouble::operator+=(const VectorDouble &vec)
{
    cerr << "\tcalling operator+=..." << endl;
    if (m_size != vec.size()) {
        throw runtime_error(
          "Vector.operator+=: Sizes do not match.");
    }
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        m_data[i1] += vec.m_data[i1];
    }
    return *this; 
}
// decrement operator
VectorDouble &VectorDouble::operator-=(const VectorDouble &vec)
{
    cerr << "\tcalling operator+=..." << endl;
    if (m_size != vec.size()) {
        throw runtime_error(
          "Vector.operator+=: Sizes do not match.");
    }
    for (size_t i1 = 0; i1 < m_size; i1++)
    {
        m_data[i1] += vec.m_data[i1];
    }
    return *this; 
}
