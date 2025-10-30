#pragma once
#include <iostream>
#include <exception>

class VectorInt {
public:
    VectorInt(size_t size = 0);        // default constructor
    ~VectorInt();                      // destructor
    VectorInt(const VectorInt &vec);   // copy constructor
    VectorInt &operator=(const VectorInt &vec); // copy assignment
    VectorInt(VectorInt &&vec);        // move constructor
    VectorInt &operator=(VectorInt &&vec); // move assignment

    size_t size() const;
    int &operator[](size_t index);
    const int &operator[](size_t index) const;

    friend std::ostream &operator<<(std::ostream &os, const VectorInt &vec);

    // math operators
    VectorInt operator+(const VectorInt &vec) const;
    VectorInt &operator+=(const VectorInt &vec);
    friend VectorInt operator*(int k, const VectorInt &v);

private:
    size_t m_size;
    int *m_data;
};