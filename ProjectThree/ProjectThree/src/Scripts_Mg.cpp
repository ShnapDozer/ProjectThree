#include "Scripts_Mg.h"

namespace ProjectThree
{

	std::shared_ptr<AnimManager> Scripts_Manager::Get_Anim_Manager(std::string name)
	{
		auto i = Script_An.find(name);
		if (i != Script_An.end())return i->second;
		std::cout << name << " - is not find in Anim_Scripts" << std::endl;
		return std::shared_ptr<AnimManager>();
	}

	std::shared_ptr<Script_Dial> Scripts_Manager::Get_Dial_Script(std::string name)
	{
		for (auto i : Script_Di) { if (i->Name == name) return i; }
		std::cout << name << " - is not find in Dial_Scripts" << std::endl;
		return std::shared_ptr<Script_Dial>();
	}

	std::shared_ptr<Script_Stats> Scripts_Manager::Get_Stats_Script(std::string name)
	{
		for (auto i : Script_St) { if (i->Name == name) return i; }
		std::cout << name << " - is not find in Stats_Scripts" << std::endl;
		return std::shared_ptr<Script_Stats>();
	}

	void Scripts_Manager::Read_Script_An(File F)
	{
		int framov = 0;
		float speed = 0;
		std::string file_pic = F.GetWayToPic(), NameAM, Name;
		std::string NameAM_OLD = "AAAAAAAAAA";

		using namespace tinyxml2;
		tinyxml2::XMLDocument doc;
		XMLElement* element;
		XMLElement* objectel;

		tinyxml2::XMLError eResult = doc.LoadFile(F.GetWayForXML().c_str());

		if (eResult != tinyxml2::XML_SUCCESS)std::cout << "Read XML XYU :( ./." << std::endl;
		else
		{
			Script_An.clear();

			element = doc.FirstChildElement("Animation");
			objectel = element->FirstChildElement("Anim");

			AnimManager AM;

			if (objectel->Attribute("NameAM") != NULL)
			{
				NameAM_OLD = objectel->Attribute("NameAM");
				AM.Name = NameAM_OLD;
			}
			else std::cout << "First attribute in " << F.GetName() << " is not found! :(";

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
					file_pic = objectel->Attribute("File");
				}
				if (objectel->Attribute("Frames") != NULL)
				{
					framov = atoi(objectel->Attribute("Frames"));
				}
				if (objectel->Attribute("Speed") != NULL)
				{
					speed = atof(objectel->Attribute("Speed"));
				}

				if (NameAM != NameAM_OLD)
				{
					Script_An[NameAM_OLD] = std::make_shared<AnimManager>(std::move(AM));
					NameAM_OLD = NameAM;

					AM.Name = NameAM_OLD;
					AM.create(Name, file_pic, speed / 10000, framov);
				}
				else
				{
					AM.create(Name, file_pic, speed / 10000, framov);
				}

				objectel = objectel->NextSiblingElement("Anim");
			}
			Script_An[NameAM_OLD] = std::make_shared<AnimManager>(std::move(AM));
		}
	}

	void Scripts_Manager::Save_Script_An(std::string name_F)
	{
		/*using namespace tinyxml2;
		tinyxml2::XMLDocument doc;
		XMLElement* row;
		XMLElement* root;
		root = doc.NewElement("Animation");

		for (auto AnimScript : Entity::GetMembers())
		{
			for (auto AnimPair : AnimScript.second->AnimList)
			{

				row = doc.NewElement("Anim");
				row->SetAttribute("NameAM", AnimScript.first.c_str());
				row->SetAttribute("Name", AnimPair.first.c_str());
				row->SetAttribute("File", AnimPair.second.File.c_str());
				row->SetAttribute("Frames", AnimPair.second.Frames);
				row->SetAttribute("Speed", AnimPair.second.Speed * 10000);

				root->LinkEndChild(row);

			}
		}

		doc.LinkEndChild(root);
		doc.SaveFile((name_F + ".xml").c_str());
		std::cout << "Save Anim_Script done! :)";

		change_An = false;*/
	}

	Scripts_Manager::~Scripts_Manager()
	{
		Save_Script_An();
		//Save_Script_Di();
		//Save_Script_St();
	}
}