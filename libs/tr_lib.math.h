#ifndef TR_LIB_MATH_H
#define TR_LIB_MATH_H

// trig funcs
REGISTER_FUNC(*this,"cos",double(double),&cos);
REGISTER_FUNC(*this,"sin",double(double),&sin);
REGISTER_FUNC(*this,"tan",double(double),&tan);

// inv trig funcs
REGISTER_FUNC(*this,"acos",double(double),&acos);
REGISTER_FUNC(*this,"asin",double(double),&asin);
REGISTER_FUNC(*this,"atan",double(double),&atan);
REGISTER_FUNC(*this,"atan2",double(double,double),&atan2);

// Exp and log funcs
REGISTER_FUNC(*this,"exp",double(double),&exp);
REGISTER_FUNC(*this,"exp2",double(double),&exp2);
REGISTER_FUNC(*this,"log",double(double),&log);
REGISTER_FUNC(*this,"log10",double(double),&log10);

// Power funcs
REGISTER_FUNC(*this,"pow",double(double,double),&pow);
REGISTER_FUNC(*this,"sqrt",double(double),&sqrt);
REGISTER_FUNC(*this,"cbrt",double(double),&cbrt);

// Abs funcs
REGISTER_FUNC(*this,"abs",double(double),&abs);

#endif