#include "Explover.h"
#include "TinyXML/tinyxml.h"

std::string getName_Without(std::string name) 
{ return name.substr(0, name.find('.')); }

File::File(std::string n, std::string w) : name(n), way(w) 
{
	name_Without = getName_Without(n);
}

void File::setName(std::string name) 
{
	this->name = name; 
	this->name_Without = getName_Without(name);
}
void File::setWay(std::string way) { this->way = way; }

void File::setWayForXML(std::string way) { WayForXML = way; }

std::string File::GetName() { return name; }
std::string File::GetWay() { return  way; }

std::string File::GetWayToPic(int CharDelet)
{
	WayToPic = way;
	WayToPic.erase(WayToPic.end() - CharDelet, WayToPic.end());
	return  WayToPic;
}

std::string File::GetWayForXML() { return WayForXML; }

//------------Explover Class:

Ex::Ex(std::string WayOne, std::string Waytwo)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	char workdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);

	File f;

	std::string WayXML = WayOne;
	WayXML.erase(0, 1);
	WayXML.erase(WayXML.end() - WayXML.begin() - 1, 1);

	std::string s = workdir;
	s = s + WayOne;
	const char* fds[]{ s.c_str() };

	hf = FindFirstFile(s.c_str(), &FindFileData);

	setlocale(LC_ALL, "Russian");

	if (hf != INVALID_HANDLE_VALUE) {
		do
		{
			f.setName(FindFileData.cFileName);
			FileNamesVec.push_back(FindFileData.cFileName);
			f.setWay(Waytwo + FindFileData.cFileName);
			f.setWayForXML(WayXML + FindFileData.cFileName);
			FileVec.push_back(f);
			std::cout << FindFileData.cFileName << std::endl;
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

}




































//------------File Class:
/*
File::File(std::string name, std::string way)
{
	this->name = name;
	this->way = way;
};

void File::setName(std::string name) { this->name = name; }
void File::setWay(std::string way) { this->way = way; }

std::string File::GetName() { return name; }
std::string File::GetWay() { return  way; }

std::string File::GetWayToPic(int CharDelet)
{
	WayToPic = way;
	WayToPic.erase(WayToPic.end() - CharDelet, WayToPic.end());
	return  WayToPic;
}*/


//------------Explover Class:
/*
Ex::Ex(std::string WayOne, std::string Waytwo)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;

	char workdir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, workdir);

	File f;

	std::string s = workdir;
	s = s + WayOne;
	const char* fds[]{ s.c_str() };

	hf = FindFirstFile(s.c_str(), &FindFileData);

	setlocale(LC_ALL, "Russian");

	if (hf != INVALID_HANDLE_VALUE) {
		do
		{
			f.setName(FindFileData.cFileName);
			FileNamesVec.push_back(FindFileData.cFileName);
			f.setWay(Waytwo + FindFileData.cFileName);
			FileVec.push_back(f);
			//FileMap[FindFileData.cFileName] = f;
			std::cout << FindFileData.cFileName << std::endl;
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}

}*/


//------------Working File Function:

/*
void Save(std::vector <AnimManager> &Anim_Manager, std::string Name, std::string Way)
{

	TiXmlDocument doc;
	TiXmlElement* row;
	TiXmlElement* root;
	root = new TiXmlElement("Animation");
	for (int i = 0; i < Anim_Manager.size(); i++)
	{

		for (auto it = Anim_Manager[i].animList.begin(); it != Anim_Manager[i].animList.end(); ++it)
		{
			row = new TiXmlElement("Anim");
			row->SetAttribute("NameAM", Anim_Manager[i].Name.c_str());
			row->SetAttribute("Name", it->first.c_str());
			row->SetAttribute("File", it->second.file.c_str());
			row->SetDoubleAttribute("Frames", it->second.framov);
			row->SetDoubleAttribute("Speed", it->second.speed);
			root->LinkEndChild(row);
		}
	}
	Name = Name + ".xml";
	doc.LinkEndChild(root);
	doc.SaveFile(Name.c_str());
	std::cout << "Save done!)";
}


void Read(std::vector <AnimManager> &Anim_Manager, std::string WayToFile)
{
	int framov;
	float speed;
	std::string file, NameAM, Name;
	std::string NameAM_OLD = "AAAAAAAAAA";

	TiXmlDocument doc(WayToFile.c_str());
	if (!doc.LoadFile())
	{
		std::cout << "Read XML XYU :( ./." << std::endl;
	}

	TiXmlElement* element = doc.FirstChildElement("Animation");
	TiXmlElement* objectel;
	objectel = element->FirstChildElement("Anim");

	int i = 0;

	while (objectel)
	{
		if (objectel->Attribute("NameAM") != NULL)
		{
			NameAM = objectel->Attribute("NameAM");
		}
		if (objectel->Attribute("Name") != NULL)
		{
			Name = objectel->Attribute("Name");
		}
		if (objectel->Attribute("File") != NULL)
		{
			file = objectel->Attribute("File");
		}
		if (objectel->Attribute("Frames") != NULL)
		{
			framov = atoi(objectel->Attribute("Frames"));
		}
		if (objectel->Attribute("Speed") != NULL)
		{
			speed = atoi(objectel->Attribute("Speed"));
		}

		if (NameAM != NameAM_OLD || i == 0)
		{
			AnimManager AM(NameAM);
			AM.create(Name, file, speed / 10000, framov);
			Anim_Manager.push_back(AM);
			NameAM_OLD = NameAM;
		}
		else
		{
			Anim_Manager[Anim_Manager.size() - 1].create(Name, file, speed / 10000, framov);
		}
		i++;


		objectel = objectel->NextSiblingElement("Anim");
	}
}*/