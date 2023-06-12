#pragma once

#include <assert.h>
#include "src/GameApplication.h"

#include "src/Settings.h"
#include "src/LoadingManager.h"
#include <iostream>


int main(int argc, char* argv[])
{

	//pt::Settings test("AnimManager");
	//test.openFile("test.xml");

	//test.setAttribute("Hero", "DefaultAnimation", "Walk");

	//test.setAttribute("Hero/Stay", "Speed", 100.f);
	//test.setState("Hero/Stay/framePath" + std::to_string(1), "../ses");
	//test.setState("Hero/Stay/framePath" + std::to_string(2), "../12ses");
	//test.setState("Hero/Stay/framePath" + std::to_string(3), "../43ses");

	//test.setAttribute("Hero/Walk", "Speed", 1010.f);
	//test.setState("Hero/Walk/framePath" + std::to_string(1), "../ses");
	//test.setState("Hero/Walk/framePath" + std::to_string(2), "../12ses");
	//test.setState("Hero/Walk/framePath" + std::to_string(3), "../43ses");
	


	pt::GameApplication* gameApp = new pt::GameApplication(argc, argv);
	assert(NULL != gameApp && "main() Can't create Application");

	gameApp->processArguments(argc, argv);

	int exitCode = gameApp->run();

	delete gameApp;
	gameApp = NULL;	

	return exitCode;
}



