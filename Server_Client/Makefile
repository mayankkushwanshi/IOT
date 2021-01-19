# Makefile for the socket programming example
#

simple_server_objects = ServerSocket.o Socket.o simple_server_main.o ServerClientUtils.o
simple_client_objects = ClientSocket.o Socket.o simple_client_main.o ServerClientUtils.o


all : simple_server simple_client

simple_server: $(simple_server_objects)
	g++ -std=c++0x -pthread -o bin/simple_server $(simple_server_objects) 

simple_client: $(simple_client_objects)
	g++ -o bin/simple_client $(simple_client_objects)


Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
ServerClientUtils: ServerClientUtils.cpp
simple_server_main: simple_server_main.cpp
simple_client_main: simple_client_main.cpp


clean:
	rm -rf *.o bin/simple_server bin/simple_client
