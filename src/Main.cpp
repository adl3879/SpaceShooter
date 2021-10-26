#include "Engine.h"
#include "Input.h"

int main( int argc, char *argv[] )
{
	Engine::Instance()->Init();

	while ( Engine::Instance()->IsRunning() )
	{
		Engine::Instance()->Events();
		Engine::Instance()->Render();
		Engine::Instance()->Update();
	}

	Engine::Instance()->Clean();

	return 0;
}

