#ifndef DEFAULT_VECTOR_H
#define DEFAULT_VECTOR_H

#include <cmath>
#include <iostream>
#include <string>

class DefaultVector {

public:

    /**
     * Default constructor
     */
    DefaultVector();

    /**
     * Value constructor
     *
     * @param x X vector value
     * @param y Y vector value
     */
    DefaultVector(const double x, const double y);

    /**
     * Copy constructor
     *
     * @param v Default Vector to copy
     */
    DefaultVector(const DefaultVector& v);

    /**
     * Move constructor
     *
     * @param v DefaultVector to move
     */
    DefaultVector(DefaultVector&& v);

    /**
     * Destructor
     */
    ~DefaultVector();

    /**
     *
     */
    operator std::string() const {
        return std::string("{"+std::to_string(_x)+","+std::to_string(_y)+"}");
    };


    /**
     * Copy Assignment
     *
     * @param rhs DefaultVector to copy
     * @return New copied DefaultVector
     */
    DefaultVector& operator=(const DefaultVector& rhs);

    /**
     * Move Assignment
     *
     * @param rhs DefaultVector to move
     * @return New moved DefaultVector
     */
    DefaultVector& operator=(DefaultVector&& rhs);

    /**
     * Function Value Getter
     *
     * @param dim Getter where 0 => X and 1 => Y
     * @return Value of specified dimension
     */
    const double get(const unsigned int dim) const;

    /**
     * Operator Value Getter
     *
     * @param i Getter where 0 => X and 1 => Y
     * @return Value of specified dimension
     */
    const double& operator[] (const unsigned int i) const;
    double& operator[] (const unsigned int i);

    /**
     * Addition Operator
     *
     * @param rhs Other vector to add to this
     * @return Resultant vector
     */
    DefaultVector& operator+=(const DefaultVector& rhs);

    /**
     * Subtraction Operator
     *
     * @param rhs Other vector to subtract from this
     * @return Resultant vector
     */
    DefaultVector& operator-=(const DefaultVector& rhs);

    /**
     * Scalar Multiplication Operator
     *
     * @param rhs Scalar value to multiply with this
     * @return Resultant vector
     */
    DefaultVector& operator*=(const double rhs);

    /**
     * Scalar Division Operator
     *
     * @param rhs Scalar value to divide with this
     * @return Resultant vector
     */
    DefaultVector& operator/=(const double rhs);

    // Friend operations
    /**
     * Equality Friend Operator
     *
     * @param lhs Left hand vector
     * @param rhs Right hand vector
     * @return Resultant boolean
     */
    friend bool operator==(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Inequality Friend Operator
     *
     * @param lhs Left hand vector
     * @param rhs Right hand vector
     * @return Resultant boolean
     */
    friend bool operator!=(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Addition Friend Operator
     *
     * @param lhs Left hand vector
     * @param rhs Right hand vector
     * @return Resultant vector
     */
    friend const DefaultVector operator+(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Subtraction Friend Operator
     *
     * @param lhs Left hand vector
     * @param rhs Right hand vector
     * @return Resultant vector
     */
    friend const DefaultVector operator-(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Multiplication Friend Operator
     *
     * @param lhs Left hand vector
     * @param rhs Right hand vector
     * @return Resultant vector
     */
    friend double operator*(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Scalar Multiplication Friend Operator
     *
     * V * scalar
     *
     * @param v LHS Vector
     * @param i RHS Scalar
     * @return Resultant vector
     */
    friend const DefaultVector operator*(const DefaultVector& v, const double i);

    /**
     * Scalar Multiplication Friend Operator
     *
     * scalar * V
     *
     * @param i LHS Scalar
     * @param v RHS Vector
     * @return Resultant vector
     */
    friend const DefaultVector operator*(const double i, const DefaultVector& v);

    /**
     * Scalar Division Friend Operator
     *
     * V / scalar
     *
     * @param v LHS Vector
     * @param i RHS Scalar
     * @return Resultant vector
     */
    friend const DefaultVector operator/(const DefaultVector& v, const double i);

    /**
     * Distance Friend Function
     *
     * dist = sqrt(V1^2 + V2^2)
     *
     * @param lhs LHS Vector
     * @param rhs RHS Vector
     * @return Resultant value
     */
    friend const double dist(const DefaultVector& lhs, const DefaultVector& rhs);

    /**
     * Outstream Friend Operator
     *
     * @param os Output stream
     * @param v Vector to output
     * @return Resultant vector
     */
    friend std::ostream& operator<<(std::ostream& os, const DefaultVector& v);

private:
    double _x;
    double _y;
};

#endif