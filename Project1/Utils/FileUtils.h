#ifndef FILEUTILS_H
#define FILEUTILS_H
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
//#include <ctype.h>
#include "StringUtils.h"
#define BUFFERSIZE 100
namespace Utils
{
	enum gameConstsTags
	{
		Asteroids
	};
	std::string getGameConstsTagInfo(gameConstsTags tag);

	namespace UtilHelperFunctions
	{
		std::string readUntilNextTagOrEOF(std::ifstream& fin);
		void moveIFStreamToTag(std::string tagString, std::ifstream& fin);
	}
}


#endif
