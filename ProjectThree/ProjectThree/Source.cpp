#pragma once

#include <assert.h>

#include "src/GameApplication.h"

int main(int argc, char* argv[])
{
	sf::VideoMode mode(1440, 900);

	ProjectThree::GameApplication* gameApp = new ProjectThree::GameApplication(mode);
	assert(NULL != gameApp && "main() Can't create Application");

	gameApp->processArguments(argc, argv);

	int exitCode = gameApp->run();

	delete gameApp;
	gameApp = NULL;	

	return exitCode;
}
