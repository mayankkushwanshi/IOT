#include "ServerSocket.h"
#include "SocketException.h"
#include <pthread.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <unistd.h>
#include <sstream>

using namespace std;

//function declaration
std::string dataPath;

void ServerCommunication(ServerSocket& server, std::string dataPath);
void *TimeCounter(void *);

int main ( int argc, char* argv[] )
{	
	try
	{
		pthread_t thread1;
		void *status;
		int rc1;

		if(argc < 3)
		{
			std::cout << " Usage: " << argv[0]<<" port dataPath"<< std::endl;
			return 0;
		}

		ServerSocket server ( atoi(argv[1]) );
                dataPath = argv[2];
		
		rc1 = pthread_create(&thread1, NULL, TimeCounter, NULL);
	        if(rc1)
        	{
                	cout << "Error:unable to create thread," << rc1 << endl;
        	        exit(-1);
	        }

		ServerCommunication(server, dataPath);

		pthread_join(thread1, &status);
		
		
		return 0;

	}
	catch ( SocketException& e )
        {
                std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
        }
	return 0;

}

/* increasing counter after every 500 ms and write into a file in override manner*/
void *TimeCounter(void * unused)
{
	int counter=0;
        while(1)
        {
		//writing counter data in to file witin 500 ms
                usleep(1000*500);
                std::string dataFileAtServer =  dataPath + "/dump.txt";
                std::ofstream myFile1;
                myFile1.open(dataFileAtServer.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
                myFile1 << counter++ ;
		//cout<<"counter=============>"<<counter<<endl;
                myFile1.close();
        }
	
}


/*Writing server data from socket into file which are send by client on socket*/
void ServerCommunication(ServerSocket& server, std::string dataPath)
{
	try
	{
		//ServerSocket server ( atoi(argv[1]) );
               // std::string dataPath = argv[2];
		while ( true )
		{
			
			ServerSocket new_sock;
			server.accept ( new_sock );

			try
			{
				std::string sessionID;
				while ( true )
				{
					std::string data;
					new_sock >> data;

					std::cout << " data received from client: " << data<< std::endl;
					if(data.find("START") != std::string::npos)
					{
						int size = data.find(" ");
						sessionID = data.substr(size +1, data.length() - size);
						std::cout << "Started session with ID:  "<< sessionID << std::endl;
						continue;
					}
					else if(data.find("END") == std::string::npos)
					{
						std::string dataFileAtServer = dataPath + "/ClientInput.txt";
						std::ofstream myFile;
						myFile.open(dataFileAtServer.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
						myFile << data.c_str();
						myFile.close();

						new_sock << "Request for " << data << " handled successfully." ;
					}
					else	//session End
					{
						// Clear out the file at the end
						std::string dataFileAtServer = dataPath + "/ClientInput.txt";
						std::ofstream myFile;
						myFile.open(dataFileAtServer.c_str(), std::ios::out | std::ios::trunc | std::ios::binary);
						myFile << "Welcome";
						myFile.close();

						new_sock << "session ended by Client";
					}
				}
			}
			catch ( SocketException& ){}
		}
	}
	catch ( SocketException& e )
	{
		std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
	}

}
