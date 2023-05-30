#pragma once

#include <iostream>
#include <String> 
#include <vector>
#include <map>
#include <ctime>
#include <algorithm>

#include <SFML/Graphics.hpp>
#include "TinyXML2/tinyxml2.h"

#include "Explover.h"
#include "TmxLevel.h"
#include "Entity.h"
#include "Script.h" 
#include "Anim.h"

namespace pt
{

	class Scripts_Manager
	{
	public:

		Scripts_Manager(Ex script)
			:change_An(false), change_Di(false), change_St(false) {}

		std::shared_ptr<AnimManager> Get_Anim_Manager(std::string name);

		std::shared_ptr<Script_Dial> Get_Dial_Script(std::string name);

		std::shared_ptr<Script_Stats> Get_Stats_Script(std::string name);

		void Read_Script_An(File F);

		void Update_Scr_An();

		void Save_Script_An(std::string name_F = "AuthoSave");

		~Scripts_Manager();

	private:
		std::map<std::string, std::shared_ptr<AnimManager>> Script_An;
		std::vector<std::shared_ptr<Script_Dial>> Script_Di;
		std::vector<std::shared_ptr<Script_Stats>> Script_St;

		bool change_An, change_Di, change_St;
	};
}

