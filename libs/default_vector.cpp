#include "default_vector.h"

DefaultVector::DefaultVector() :
        DefaultVector(0.0, 0.0) {
}

DefaultVector::DefaultVector(const double x, const double y) :
        _x(x), _y(y) {
}

DefaultVector::DefaultVector(const DefaultVector& v) :
        _x(v._x), _y(v._y) {
}

DefaultVector::DefaultVector(DefaultVector&& v) :
        _x(v._x), _y(v._y) {
    v._x = 0.0;
    v._y = 0.0;
}

DefaultVector::~DefaultVector() {}

DefaultVector& DefaultVector::operator=(const DefaultVector& rhs) {
    if (this != &rhs) {
        _x = rhs._x;
        _y = rhs._y;
    }
    return *this;
}

DefaultVector& DefaultVector::operator=(DefaultVector&& rhs) {
    if (this != &rhs) {
        _x = rhs._x;
        rhs._x = 0.0;
        _y = rhs._y;
        rhs._y = 0.0;
    }
    return *this;
}

const double DefaultVector::get(const unsigned int dim) const {
    switch(dim) {
        case 0:
            return _x;
        case 1:
            return _y;
        default:
            return 0.0;
    }
}

const double& DefaultVector::operator[] (const unsigned int i) const {
    switch(i) {
        case 0:
            return _x;
        case 1:
            return _y;
    }
}

double& DefaultVector::operator[] (const unsigned int i) {
    switch(i) {
        case 0:
            return _x;
        case 1:
            return _y;
    }
}

DefaultVector& DefaultVector::operator+=(const DefaultVector& rhs) {
    _x += rhs._x;
    _y += rhs._y;
    return *this;
}

DefaultVector& DefaultVector::operator-=(const DefaultVector& rhs) {
    _x -= rhs._x;
    _y -= rhs._y;
    return *this;
}

DefaultVector& DefaultVector::operator*=(const double rhs) {
    _x *= rhs;
    _y *= rhs;
    return *this;
}

DefaultVector& DefaultVector::operator/=(const double rhs) {
    _x /= rhs;
    _y /= rhs;
    return *this;
}

// Friend operations
bool operator==(const DefaultVector& lhs, const DefaultVector& rhs) {
    return lhs._x == rhs._x && lhs._y == rhs._y;
}

bool operator!=(const DefaultVector& lhs, const DefaultVector& rhs) {
    return !(lhs == rhs);
}

const DefaultVector operator+(const DefaultVector& lhs, const DefaultVector& rhs) {
    DefaultVector vv = lhs;
    vv += rhs;
    return vv;
}

const DefaultVector operator-(const DefaultVector& lhs, const DefaultVector& rhs) {
    DefaultVector vv = lhs;
    vv -= rhs;
    return vv;
}

double operator*(const DefaultVector& lhs, const DefaultVector& rhs) {
    return (lhs._x * rhs._x + lhs._y * rhs._y);
}

const DefaultVector operator*(const DefaultVector& v, const double i) {
    DefaultVector vv = v;
    vv *= i;
    return vv;
}

const DefaultVector operator*(const double i, const DefaultVector& v) {
    DefaultVector vv = v;
    vv *= i;
    return vv;
}

const DefaultVector operator/(const DefaultVector& v, const double i) {
    DefaultVector vv = v;
    vv /= i;
    return vv;
}

const double dist(const DefaultVector& lhs, const DefaultVector& rhs) {
    return sqrt(pow(lhs._x - rhs._x, 2) + pow(lhs._y - rhs._y, 2));
}

std::ostream& operator<<(std::ostream& os, const DefaultVector& v) {
    os << "{" << v._x << ", " << v._y << "}";
    return os;
}