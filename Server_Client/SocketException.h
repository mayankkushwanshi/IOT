// SocketException class


#ifndef SocketException_class
#define SocketException_class

#include <string>

class SocketException
{
public:
	SocketException ( const std::string& what ) : _exceptionDesc ( what ) {};
	~SocketException (){};

	std::string description() { return _exceptionDesc; }

private:

	std::string _exceptionDesc;

};

#endif
