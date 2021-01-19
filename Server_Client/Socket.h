// Definition of the Socket class

#ifndef Socket_class
#define Socket_class


#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string>
#include <arpa/inet.h>

const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 5;
const int MAXRECV = 65535;

class Socket
{
public:
	Socket();
	virtual ~Socket();

	// Server initialization
	bool create();
	bool bind ( const int& port );
	bool listen() const;
	bool accept ( Socket& newSocket) const;

	// Client initialization
	bool connect ( const std::string& host, const int& port );

	// Data Transmission
	bool send ( const std::string& data ) const;
	int recv ( std::string& data) const;

	void setNonBlocking ( const bool& block );

	bool isValid() const { return _socket != -1; }

private:

	int _socket;
	sockaddr_in _socketAddress;
};


#endif
