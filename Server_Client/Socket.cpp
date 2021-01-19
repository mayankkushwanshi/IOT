// Implementation of the Socket class.

#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include "string.h"

#include "Socket.h"

Socket::Socket() :
_socket ( -1 )
{
	memset ( &_socketAddress,
			0,
			sizeof ( _socketAddress ) );
}

Socket::~Socket()
{
	if ( isValid() )
	{
		::close ( _socket );
	}
}

bool Socket::create()
{
	_socket = socket ( AF_INET,
			SOCK_STREAM,
			0 );

	if ( ! isValid() )
	{
		return false;
	}

	// TIME_WAIT - argh
	int on = 1;
	if ( setsockopt ( _socket, SOL_SOCKET, SO_REUSEADDR, ( const char* ) &on, sizeof ( on ) ) == -1 )
	{
		return false;
	}

	return true;
}

bool Socket::bind ( const int& port )
{
	if ( ! isValid() )
	{
		return false;
	}

	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_addr.s_addr = INADDR_ANY;
	_socketAddress.sin_port = htons ( port );

	int bind_return = ::bind ( _socket,
			( struct sockaddr * ) &_socketAddress,
			sizeof ( _socketAddress ) );

	if ( bind_return == -1 )
	{
		return false;
	}

	return true;
}


bool Socket::listen() const
{
	if ( ! isValid() )
	{
		return false;
	}

	int listen_return = ::listen ( _socket, MAXCONNECTIONS );
	if ( listen_return == -1 )
	{
		return false;
	}

	return true;
}


bool Socket::accept ( Socket& newSocket ) const
{
	int addrLength = sizeof ( _socketAddress );

	newSocket._socket = ::accept ( _socket, ( sockaddr * ) &_socketAddress, ( socklen_t * ) &addrLength );
	if ( newSocket._socket <= 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}


bool Socket::send ( const std::string& data ) const
{
	int status = ::send ( _socket, data.c_str(), data.size(), MSG_NOSIGNAL );
	if ( status == -1 )
	{
		return false;
	}
	else
	{
		return true;
	}
}


int Socket::recv ( std::string& data ) const
{
	char buffer [ MAXRECV + 1 ];

	data = "";

	memset ( buffer, 0, MAXRECV + 1 );

	int status = ::recv ( _socket, buffer, MAXRECV, 0 );

	if ( status == -1 )
	{
		std::cout << "status == -1   errno == " << errno << "  in Socket::recv\n";
		return 0;
	}
	else if ( status == 0 )
	{
		return 0;
	}
	else
	{
		data = buffer;
		return status;
	}
}

bool Socket::connect ( const std::string& host, const int& port )
{
	if ( ! isValid() )
	{
		return false;
	}

	_socketAddress.sin_family = AF_INET;
	_socketAddress.sin_port = htons ( port );

	int status = inet_pton ( AF_INET, host.c_str(), &_socketAddress.sin_addr );

	if ( errno == EAFNOSUPPORT ) return false;

	status = ::connect ( _socket, ( sockaddr * ) &_socketAddress, sizeof ( _socketAddress ) );

	if ( status == 0 )
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Socket::setNonBlocking ( const bool& block )
{
	int options;

	options = fcntl ( _socket, F_GETFL );

	if ( options < 0 )
	{
		return;
	}

	if ( block )
	{
		options = ( options | O_NONBLOCK );
	}
	else
	{
		options = ( options & ~O_NONBLOCK );
	}

	fcntl ( _socket,  F_SETFL,options );
}
