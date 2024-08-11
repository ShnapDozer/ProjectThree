#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <windows.h>

namespace pt
{
	class File
	{
	public:

		File() {}


		File(std::string name, std::string way);


		void setName(std::string name);
		void setWay(std::string way);
		void setWayForXML(std::string way);


		std::string GetName();
		std::string GetWay();


		std::string GetWayToPic(int CharDelet = 1);
		std::string GetWayForXML();


		std::string name, name_Without;
	private:
		std::string way;
		std::string WayForXML;
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
}

