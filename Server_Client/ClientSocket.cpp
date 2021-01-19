// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "SocketException.h"


ClientSocket::ClientSocket (const std::string& host, const int& port )
{
	if ( ! Socket::create() )
	{
		throw SocketException ( "Could not create client socket." );
	}

	if ( ! Socket::connect ( host, port ) )
	{
		throw SocketException ( "Could not bind to port." );
	}
}

const ClientSocket& ClientSocket::operator << ( const std::string& data ) const
{
	if ( ! Socket::send ( data ) )
	{
		throw SocketException ( "Could not write to socket." );
	}

	return *this;
}

const ClientSocket& ClientSocket::operator >> ( std::string& data ) const
{
	if ( ! Socket::recv ( data ) )
	{
		throw SocketException ( "Could not read from socket." );
	}

	return *this;
}
