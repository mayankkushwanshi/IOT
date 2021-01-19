/*
 * ServerClientUtils.h
 *
 *  Created on: 21-Nov-2017
 *      Author: administrator
 */

#ifndef SERVERCLIENTUTILS_H_
#define SERVERCLIENTUTILS_H_

#include <string>
#include <vector>


struct ClientInput
{
	std::string _fileName;
	int _fileDataLength;
	std::string _data;
};

class ServerClientUtils {
public:
	ServerClientUtils();
	virtual ~ServerClientUtils();

	//Static methods
	static std::string getFileContent(const std::string& filePath);
	static bool getFileContent(const std::string& filePath,
				std::vector<std::string>& data);

	static bool splitCharSeparatedString(const std::string& inString,
				std::vector<std::string>& charSeparatedData, char ch);

	static std::string writeContentToFile(const std::string& data,
				const std::string& dirToStore, const std::string& fileName);

	static std::string createClientInputStream(const ClientInput& clientIn);
	static ClientInput parseClientInputStream(const std::string& inputStream);

	static int getFileListFromDir(const std::string& directory,
				std::vector<std::string>& fileList);

	static std::string getRandomNumber();

	static void createDirectory(const std::string& dirPath);
};

#endif /* SERVERCLIENTUTILS_H_ */
