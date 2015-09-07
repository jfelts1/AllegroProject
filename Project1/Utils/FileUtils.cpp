#include "FileUtils.h"

using std::string;
using std::ifstream;

namespace Utils
{
	string getGameConstsTagInfo(gameConstsTags tag)
	{
		string ret;
		ifstream fin;
		string gameConstsPath = "Data/gameConsts.txt";
		fin.open(gameConstsPath);
		if (!fin.is_open())
		{
			std::cerr << "Unable to open " << gameConstsPath << std::endl;
		}

		if (tag == Asteroids)
		{
			char astTag[] = "[Asteroids]";
			UtilHelperFunctions::moveIFStreamToTag(astTag, fin);
			ret = UtilHelperFunctions::readUntilNextTagOrEOF(fin);
		}
		else if (tag == Ship)
		{
			char shipTag[] = "[Ship]";
			UtilHelperFunctions::moveIFStreamToTag(shipTag, fin);
			ret = UtilHelperFunctions::readUntilNextTagOrEOF(fin);
		}
		else if (tag == Projectile)
		{
			char projTag[] = "[Projectile]";
			UtilHelperFunctions::moveIFStreamToTag(projTag, fin);
			ret = UtilHelperFunctions::readUntilNextTagOrEOF(fin);
		}
		else
		{
			std::cerr << "Tag not found!" << std::endl;
		}
		fin.close();
		return ret;
	}
}

std::string Utils::UtilHelperFunctions::readUntilNextTagOrEOF(std::ifstream& fin)
{
	string ret;
	char tmp[BUFFERSIZE] = "";
	fin.getline(tmp, BUFFERSIZE);
	while (!fin.eof() && tmp[0] != '[')
	{
		ret.append(removeWhiteSpace(tmp));
		ret.push_back('\n');
		memset(tmp, '\0', BUFFERSIZE);
		fin.getline(tmp, BUFFERSIZE);
	}
	return ret;
}

void Utils::UtilHelperFunctions::moveIFStreamToTag(std::string tagString, std::ifstream & fin)
{
	char tmp[BUFFERSIZE] = "";
	fin.getline(tmp, BUFFERSIZE);
	while (strncmp(tmp, tagString.c_str(), tagString.size()) != 0)
	{
		memset(tmp, '\0', BUFFERSIZE);
		fin.getline(tmp, BUFFERSIZE);
	}
}
