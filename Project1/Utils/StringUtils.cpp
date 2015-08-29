#include "StringUtils.h"
using std::string;

namespace Utils
{
	string removeWhiteSpace(string s)
	{
		string ret;
		for (auto ch : s)
		{
			//std::cout << ch << " isspace(ch): " << isspace(ch) << std::endl;
			if (isspace(ch) == 0)
			{
				ret.push_back(ch);
				//std::cout << "ret: " << ret << std::endl;
			}
		}
		return ret;
	}

	std::string copyUntilNextWhiteSpace(std::string s, size_t start)
	{
		string ret;
		for (size_t i = start;(i < s.size() && isspace(s[i]) == 0);i++)
		{
			ret.push_back(s[i]);
		}
		return ret;
	}

	float getFloatFromStringWPrefix(string s, string preFix)
	{
		float ret=0;
		string::size_type n = s.find(preFix);
		string str = Utils::copyUntilNextWhiteSpace(s, n + preFix.size());
		try
		{
			ret = std::stof(str);
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (std::out_of_range& e)
		{
			std::cerr << e.what() << std::endl;
		}

		std::cout << ret << std::endl;
		return ret;
	}

	int getIntFromStringWPreFix(std::string s, std::string preFix)
	{
		int ret = 0;
		string::size_type n = s.find(preFix);
		string str = Utils::copyUntilNextWhiteSpace(s, n + preFix.size());
		try
		{
			ret = std::stoi(str);
		}
		catch (std::invalid_argument& e)
		{
			std::cerr << e.what() << std::endl;
		}
		catch (std::out_of_range& e)
		{
			std::cerr << e.what() << std::endl;
		}

		std::cout << ret << std::endl;
		return ret;
	}
}