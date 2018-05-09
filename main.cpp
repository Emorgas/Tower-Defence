#include "EngineRunner.h"
using namespace Engine;

int main(int, char**)
{
	if (!EngineRunner::GetInstance().Init())
	{
		return 1;
	}

	return EngineRunner::GetInstance().Run();
}