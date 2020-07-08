#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <iostream>
#include <exception>

using namespace std;

class myException : public exception {

	public:

		// will be initiliazed with error message
	    myException(const char* msg);

	    // override what()
	    virtual const char* what() const throw() override;

	private:

		// for error message
	    const char* str;

};

#endif // MYEXCEPTION_H

