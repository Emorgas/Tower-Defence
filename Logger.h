#pragma once
#include <iostream>

namespace Engine
{
	class Logger
	{
	public:
		static void LogSDLError(std::ostream &os, const std::string &msg);
		static void LogError(std::ostream &os, const std::string &msg);

	};
}