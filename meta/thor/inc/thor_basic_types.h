// Copyright (c) 2010, Su Shi <carmack.shi [at] gmail.com>
//
// All rights reserved.

#ifndef THOR_BASIC_TYPES_H_
#define THOR_BASIC_TYPES_H_

#include <cstddef>
// A macro to disallow the evil copy constructor and operator= functions
// This should be used in the private: declarations for a class
#define DISALLOW_EVIL_CONSTRUCTORS(TypeName)    \
  TypeName(const TypeName&);                    \
  void operator=(const TypeName&)

// An alternate name that leaves out the moral judgment... :-)
#define DISALLOW_COPY_AND_ASSIGN(TypeName) DISALLOW_EVIL_CONSTRUCTORS(TypeName)

#endif  // THOR_BASIC_TYPES_H_
