/*
 * ServerClientUtils.cpp
 *
 *  Created on: 21-Nov-2017
 *      Author: administrator
 */

#include <fstream>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <cstdlib>

#include "ServerClientUtils.h"

ServerClientUtils::ServerClientUtils() {
	// TODO Auto-generated constructor stub

}

ServerClientUtils::~ServerClientUtils() {
	// TODO Auto-generated destructor stub
}

// Function to read file in binary mode
std::string ServerClientUtils::getFileContent(const std::string& filePath)
{
	try
	{
		std::ifstream input(filePath.c_str(),std::ios::binary | std::ios::in);
		input.seekg(0,std::ios::end);
		int length = input.tellg();
		input.seekg(0,std::ios::beg);

		char *buffer = new char[length];
		input.read(buffer,length);

		std::string strBuffer(buffer);

		delete buffer;

		input.close();

		return strBuffer;
	}
	catch(std::exception exce)
	{
		std::cout << "Exception occurred while reading file: "<< exce.what()<< std::endl;
		return "";
	}

	return "";
}

bool ServerClientUtils::getFileContent(const std::string& filePath, std::vector<std::string>& data)
{
	try
	{
		std::ifstream input(filePath.c_str(),std::ios::binary | std::ios::in);
		std::string line;
		data.clear();
		while(std::getline(input,line, '\n'))
		{
			data.push_back(line);
		}
		input.close();

		return true;
	}
	catch(std::exception exce)
	{
		std::cout << "Exception occurred while reading file: "<< exce.what()<< std::endl;
		return false;
	}

	return true;
}

bool ServerClientUtils::splitCharSeparatedString(const std::string& inString,
		std::vector<std::string>& charSeparatedData, char ch)
{
	unsigned int pos = inString.find(ch);
	unsigned int initialPos = 0;
	charSeparatedData.clear();

	// divide string in char separated strings
	while( pos != std::string::npos)
	{
		charSeparatedData.push_back(inString.substr(initialPos, pos - initialPos +1));
		initialPos = pos + 1;

		pos = inString.find(ch,initialPos);
	}

	// Add the last one
	charSeparatedData.push_back(inString.substr(initialPos, std::min(pos, (unsigned int)(inString.size() - initialPos +1))));
}

std::string ServerClientUtils::writeContentToFile(const std::string& data,
		const std::string& dirToStore, const std::string& fileName)
{
	try
	{
		std::string absolutePath = dirToStore + "/" + fileName;

		std::cout << "Absolute file path: "<< absolutePath << std::endl;

		std::ofstream output( absolutePath.c_str(), std::ios::out | std::ios::binary);
		output.write(data.c_str(), data.length());

		return absolutePath;
	}
	catch (std::exception & exce)
	{
		std::cout << "Exception occurred while writing to file: "<< exce.what()<< std::endl;

		return "";
	}
}

std::string ServerClientUtils::createClientInputStream(const ClientInput& clientIn)
{
	std::ostringstream strDataLength;
	strDataLength << clientIn._fileDataLength;
	std::string inputStream = clientIn._fileName + " " + strDataLength.str() + " " + clientIn._data;

	return inputStream;
}

ClientInput ServerClientUtils::parseClientInputStream(const std::string& inputStream)
{
	ClientInput clientIn;
	// Get file name
	unsigned int size = inputStream.find(" ");
	clientIn._fileName = inputStream.substr(0,size);

	std::string remainStr = inputStream.substr(size+1, inputStream.length() - size);

	// get data length
	size = remainStr.find(" ");
	clientIn._fileDataLength = atoi(remainStr.substr(0,size - 1).c_str());

	clientIn._data = remainStr.substr(size+1, remainStr.length() - size);

	return clientIn;
}

int ServerClientUtils::getFileListFromDir(const std::string& directory, std::vector<std::string>& fileList)
{
	DIR *dp;
	struct dirent *dirp;
	if((dp = opendir(directory.c_str())) == NULL)
	{
		std::cout << "Failed to open DIR :" << directory.c_str()<< std::endl;
		return -1;
	}

	while( (dirp = readdir(dp) ) != NULL)
	{
		std::string fileName = dirp->d_name;
		if(fileName.compare(".") != 0 && fileName.compare("..") != 0)
		{
			fileList.push_back(fileName);
		}
	}
	closedir(dp);

	return 0;
}

std::string ServerClientUtils::getRandomNumber()
{
	int randomNum = rand();
	std::ostringstream strRandomNum;
	strRandomNum << randomNum;

	return strRandomNum.str();
}

void ServerClientUtils::createDirectory(const std::string& dirPath)
{
	mkdir(dirPath.c_str(),0777);
}
