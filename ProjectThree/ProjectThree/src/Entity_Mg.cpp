#include "Entity_Mg.h"

Entity_Manager::Entity_Manager(std::shared_ptr<Level_Manager> L_M, std::shared_ptr<Scripts_Manager> S_M)
	: Lvl_Mg(L_M), Scr_Mg(S_M)
{
	Entity_Objects = Lvl_Mg->Lvl_Other_Vec();
	Solid_Objects = Lvl_Mg->Lvl_Solid_Vec();

	std::string Name, Param;

	Entity_List.resize(Entity_Objects.size() - 1);

	int count = 0;

	for (auto i : Entity_Objects)
	{
		Param = i.name.substr(0, i.name.find('_'));
		Name = i.name.substr(i.name.find('_') + 1);

		if (Param == "Hero") 
		{ 
			GG = std::make_shared<Hero>(Name, i.poss);
			if (Scr_Mg->Get_Anim_Manager(Name) != NULL)
			{
				GG->SetAnim_Mg(*Scr_Mg->Get_Anim_Manager(Name));
			}
			
		}
		else if (Param == "NPC") 
		{ 
			Entity_List[count++] = std::make_shared<NPC>(Name, i.poss);
		}
		else { std::cout << i.name << " - bad object" << std::endl; }
	}
}

void Entity_Manager::Update(float time, const sf::Vector2f& map_Pos, bool ImGui)
{
	GG->Update(time, map_Pos, ImGui, Solid_Objects);
	for (auto i : Entity_List) { if (i != nullptr)i->Update(time, map_Pos, ImGui, Solid_Objects); }
}

void Entity_Manager::Draw(sf::RenderTarget& Target)
{
	GG->Draw(Target);
	for (auto i : Entity_List) { if (i != nullptr)i->Draw(Target); }
}

void Entity_Manager::SetScript()
{
	if (Scr_Mg->Get_Anim_Manager(GG->GetName()) != NULL)
	{
		GG->SetAnim_Mg(*Scr_Mg->Get_Anim_Manager(GG->GetName()));
	}

	for (auto i : Entity_List)
	{
		if (Scr_Mg->Get_Anim_Manager(i->GetName()) != NULL)
		{
			i->SetAnim_Mg(*Scr_Mg->Get_Anim_Manager(GG->GetName()));
		}
	}
}

std::shared_ptr<Hero> Entity_Manager::GetHero()
{
	if (GG != NULL)return GG;
	
	else 
	{
		std::cout << "Hero is empty!!!" << std::endl;
		return std::shared_ptr<Hero>();
	}
}

sf::Vector2f Entity_Manager::GetHeroPos() const
{
	if (GG != NULL) return GG->GetPoss();
	else
	{
		std::cout << "Hero is empty!!!" << std::endl;
		return{ 0.f,0.f };
	}
}
