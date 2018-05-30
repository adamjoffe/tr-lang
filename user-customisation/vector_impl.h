#ifndef VECTOR_IMPL_H
#define VECTOR_IMPL_H

/**
 * Vector Implementation Selection
 *
 * Vector implementation can be changed to support whatever
 * vector class is desired, and allows customisation of operator
 * overloading. If a user doesn't define a vector, a default one
 * will be used. This is useful for changing the dimensions for vectors
 * the default vector is of dimension 2, so for 3D space a dimension 3
 * matrix will need to be provided
 *
 * ========
 * HOW TO:
 * ========
 *
 * To define your own Vector implementation:
 * 1) create the appropriate header and source files.
 * 2) include header below, optionally using ifdef macros
 * 3) type using your vector type to "Vector" (if the name is different) inside of the TR namespace
 * 3) "#define VECTOR_IMPLEMENTATION" to note you are using
 * your own implementation
 *
 * e.g.
 *
 * #ifdef MY_VECTOR
 * #include "my_vector.h"
 * namespace TR {
 * 	using Vector = MyVector;
 * }
 * #define VECTOR_IMPLEMENTATION
 * #endif
 *
 * To properly work, a vector implementation should have all arithmetic
 * operator overloads implemented, including friend operators:
 *
 * - Addition (v + v)
 * - Substraction (v - v)
 * - Dot product (v * v)
 * - Scalar Multiplication (v * s) (s * v)
 * - Scalar Division (v / s)
 *
 * It should also have a constructor that takes 2 doubles as this is what 
 * is used by the TR language. It is also suggested to define a dist() friend
 * function that calculates the difference between two vectors. This
 * then can be used by registering it as a built-in function. 
 *
 * Also, to print a vector using the standard print function with string type
 * parameter, the string static_cast operator must be defined:
 *
 * - operator std::string()
 */

#endif
