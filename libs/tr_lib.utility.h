#ifndef TR_LIB_UTILITY_H
#define TR_LIB_UTILITY_H

// System calls
REGISTER_BIND_FUNC(*this,"system",int(std::string),
	[](std::string s){ return system(s.c_str()); },plh::_1);

// Random (to be replaced with C++ rand)
srand(time(NULL));
REGISTER_FUNC(*this,"rand",int(void),&rand);

// Strlen
REGISTER_BIND_FUNC(*this,"strlen",int(std::string),
	[](std::string s){ return static_cast<int>(strlen(s.c_str())); },plh::_1);

#endif