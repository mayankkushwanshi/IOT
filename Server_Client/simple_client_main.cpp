#include "ClientSocket.h"
#include "SocketException.h"
#include <iostream>
#include <string>
#include <stdlib.h>

#include "ServerClientUtils.h"

/*
 * Arguements:
 *
 * hostname port
 */
int main ( int argc, char* argv[] )
{
	try
	{
		if(argc < 3)
		{
			std::cout << " Usage: " << argv[0]<<" hostname port dataPath(Absolute)"<< std::endl;
			return 0;
		}

		ClientSocket clientSocket ( argv[1],atoi(argv[2]));

		std::string dataPath = argv[3];

		std::string replyFromServer;

		try
		{
			std::string strRandomNum = ServerClientUtils::getRandomNumber();
			std::cout << "session ID from Client: "<< strRandomNum<< std::endl;
			std::string startSession = "START " + strRandomNum;
			clientSocket << startSession;

			sleep(5);

			//std::string input;

			//std::cout << "Enter user input:  (-1) input will terminate the client request"<< std::endl;
			//std::cout << "Valid inputs are: \n\tVibration_Sensor\n\tPlasma_Line_Detector\n\tBLDC_Motor\n\tTemperature_Sensor"<< std::endl;

			/*while(true)
			{
				std::cout << "\n\nEnter next user input: "<< std::endl;
				std::string input;
				std::cin >> input;

				if(input.compare("-1") != 0)
				{
					std::cout << "input received: "<< input <<std::endl;
					clientSocket << input;

					clientSocket >> replyFromServer;

					std::cout<< "Server Action: "<< replyFromServer << std::endl;
				}
				else
					break;
			};*/
			do
			{
				std::vector<std::string> fileList;
				std::vector<std::string> fileData;
				ServerClientUtils::getFileListFromDir(dataPath,fileList);

				std::cout<< "file Path: "<< fileList[0] << std::endl;
				ServerClientUtils::getFileContent(dataPath + "/" + fileList[0],fileData);

				std::vector<std::string>::iterator itrfileData = fileData.begin();

			
				for(; itrfileData != fileData.end(); ++itrfileData)
				{
					std::cout<< "Client Request to update Data for: "<< *itrfileData << std::endl;
					clientSocket << *itrfileData;

					sleep(1);

					clientSocket >> replyFromServer;

					std::cout<< "Server Action: "<< replyFromServer << std::endl;

					sleep(1);
				}
			}while(1);

			std::string endSession = "END " + strRandomNum;
			clientSocket << endSession;

			clientSocket >> replyFromServer;

			sleep(1);

		}
		catch ( SocketException& ){	}

		std::cout << "We received this response from the server:\n\"" << replyFromServer << "\"\n";;

	}
	catch ( SocketException& exception )
	{
		std::cout << "Exception was caught:" << exception.description() << "\n";
	}

	return 0;
}
