#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <windows.h>


/*
Если эта шлюха ругается на:
char workdir[MAX_PATH];
GetCurrentDirectory(MAX_PATH, workdir);
то надо сменить кодировку на многобайтовую
Свойства Конфигурации => Дополнительно => Наборы Символов
*/


class File 
{
public:

	File(){}


	File(std::string name, std::string way);

	
	void setName(std::string name);
	void setWay(std::string way);


	std::string GetName();
	std::string GetWay();


	std::string GetWayToPic(int CharDelet = 1);	


	std::string name;
private:
	std::string way;
	std::string WayToPic;
};


class Ex 
{
public:
	Ex(std::string WayOne, std::string Waytwo);
	
	
	std::vector<File> FileVec;
	std::vector<std::string> FileNamesVec;

	std::map <std::string, File> FileMap;
};



