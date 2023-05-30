#pragma once

#include <assert.h>

#include "src/GameApplication.h"

#include "src/Settings.h"

#include <iostream>

int main(int argc, char* argv[])
{
	pt::GameApplication* gameApp = new pt::GameApplication(argc, argv);
	assert(NULL != gameApp && "main() Can't create Application");

	gameApp->processArguments(argc, argv);

	int exitCode = gameApp->run();

	delete gameApp;
	gameApp = NULL;	

	return exitCode;
}
