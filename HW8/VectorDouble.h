// VectorDouble.h
// Declaration of a class implementing all special member functions
#pragma once
#include <iostream>
#include <exception>
class VectorDouble {
public:
    VectorDouble(size_t size=0); // default constructor
    ~VectorDouble();             // destructor
    // Copy constructor and assigment operator
    VectorDouble(const VectorDouble &vec);
    VectorDouble &operator=(const VectorDouble &vec);
    // Move copy Constructor and assigment
    VectorDouble(VectorDouble &&vec);
    VectorDouble &operator=(VectorDouble &&vec);
    // utility functions
    friend std::ostream &operator<<(std::ostream &os, const VectorDouble &vec);
    // Indexing Operators
    size_t size() const;
    double &operator[](size_t index);
    const double &operator[](size_t index) const;
    // math operators
    bool operator==(const VectorDouble &vec);
    VectorDouble operator+(const VectorDouble &vec) const;
    VectorDouble operator-(const VectorDouble &vec) const;
    VectorDouble &operator+=(const VectorDouble &vec);
    VectorDouble &operator-=(const VectorDouble &vec);
private:
    std::size_t m_size;
    double *m_data;
};
