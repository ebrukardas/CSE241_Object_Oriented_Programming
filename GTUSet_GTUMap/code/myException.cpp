#include "myException.h"


// initiliaze message
myException::myException(const char* msg):str(msg){/* EMPTY BODY */}

// return the message
const char* myException::what() const throw(){ return str; }