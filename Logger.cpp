#include "Logger.h"
#include <string>
#include <SDL.h>

using namespace std;
namespace Engine
{
	void Logger::LogSDLError(std::ostream & os, const std::string & msg)
	{
		os << msg << " error: " << SDL_GetError() << std::endl;
	}

	void Logger::LogError(std::ostream & os, const std::string & msg)
	{
		os << "Error: " << msg << std::endl;
	}

	void Logger::Log(std::ostream &os, const std::string &msg)
	{
		os << msg << std::endl;
	}
}