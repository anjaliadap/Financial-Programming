#include "VectorInt.h"
#include <stdexcept>
#include <iostream>
using namespace std;

VectorInt::VectorInt(size_t size) : m_size(size) {
    cerr << "\tcalling constructor..." << endl;
    m_data = new int[m_size];
}

VectorInt::~VectorInt() {
    cerr << "\tcalling destructor..." << endl;
    delete[] m_data;
}

VectorInt::VectorInt(const VectorInt &vec) : m_size(vec.m_size) {
    cerr << "\tcalling copy constructor..." << endl;
    m_data = new int[m_size];
    for (size_t i = 0; i < m_size; i++)
        m_data[i] = vec.m_data[i];
}

VectorInt &VectorInt::operator=(const VectorInt &vec) {
    cerr << "\tcalling copy assignment..." << endl;
    if (this == &vec) return *this;
    delete[] m_data;
    m_size = vec.m_size;
    m_data = new int[m_size];
    for (size_t i = 0; i < m_size; i++)
        m_data[i] = vec.m_data[i];
    return *this;
}

VectorInt::VectorInt(VectorInt &&vec) : m_size(vec.m_size), m_data(vec.m_data) {
    cerr << "\tcalling move constructor..." << endl;
    vec.m_data = nullptr;
    vec.m_size = 0;
}

VectorInt &VectorInt::operator=(VectorInt &&vec) {
    cerr << "\tcalling move assignment..." << endl;
    if (this == &vec) return *this;
    delete[] m_data;
    m_size = vec.m_size;
    m_data = vec.m_data;
    vec.m_data = nullptr;
    vec.m_size = 0;
    return *this;
}

size_t VectorInt::size() const { return m_size; }

int &VectorInt::operator[](size_t index) {
    if (index >= m_size) throw runtime_error("Index out of range");
    return m_data[index];
}

const int &VectorInt::operator[](size_t index) const {
    if (index >= m_size) throw runtime_error("Index out of range");
    return m_data[index];
}

ostream &operator<<(ostream &os, const VectorInt &vec) {
    os << "{";
    for (size_t i = 0; i < vec.m_size; i++) {
        os << vec.m_data[i];
        if (i != vec.m_size - 1) os << ",";
    }
    os << "}";
    return os;
}

VectorInt VectorInt::operator+(const VectorInt &vec) const {
    if (m_size != vec.m_size)
        throw runtime_error("Vector sizes do not match");
    VectorInt res(m_size);
    for (size_t i = 0; i < m_size; i++)
        res[i] = m_data[i] + vec.m_data[i];
    return res;
}

VectorInt &VectorInt::operator+=(const VectorInt &vec) {
    if (m_size != vec.m_size)
        throw runtime_error("Vector sizes do not match");
    for (size_t i = 0; i < m_size; i++)
        m_data[i] += vec.m_data[i];
    return *this;
}

// scalar multiplication
VectorInt operator*(int k, const VectorInt &v) {
    VectorInt res(v.m_size);
    for (size_t i = 0; i < v.m_size; i++)
        res[i] = k * v.m_data[i];
    return res;
}