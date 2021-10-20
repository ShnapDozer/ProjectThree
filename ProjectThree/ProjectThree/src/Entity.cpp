#include "Entity.h"

//-----------------------------------------------Entity----------------------------------------------------
//---------------------------------------------------------------------------------------------------------

Entity::Entity(std::string name, const sf::Vector2f& posS)
	: life(true), collision(false), posA(posS), Name(name)
{
	Members[name] = &Main;
}

bool Entity::Collision() const 
{ 
	return collision; 
}

bool Entity::Check_Collision(const std::vector<TmxObject> &Solid_Vec) const
{
	for (auto it : Solid_Vec) { if (P_intersectRect(it.Polygon, Main.GetRect())) return true; }

	return false;
}

sf::Vector2f Entity::GetPoss() const 
{
	return posA; 
}

sf::FloatRect Entity::GetRect() const 
{ 
	return Main.GetRect(); 
}

std::string Entity::GetName() const
{
	return Name;
}

void Entity::AddAnim(std::string name, std::string file, float speed, int frames) 
{ 
	Main.create(name, file, speed, frames, true); 
}

void Entity::SetAnim_Mg(AnimManager &A)
{
	Main = std::move(A);
	Members[Name] = &Main;
}

void Entity::ChoiseAnim(std::string Name) 
{ 
	Main.set(Name); 
}

void Entity::Draw(sf::RenderTarget& target) 
{
	Main.draw(target, posA); 
}

std::map<std::string, AnimManager*> Entity::GetMembers() 
{ 
	return Members; 
}


//-----------------------------------------------Hero------------------------------------------------------
//---------------------------------------------------------------------------------------------------------


Hero::Hero(std::string name, const sf::Vector2f& posS)
	: Entity(name, posS)
{}

void Hero::Update(float time, const sf::Vector2f& map_Pos, bool ImGui, const std::vector<TmxObject>& Solid_Vec)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !ImGui)
	{

		rotation_rad = std::atan2(map_Pos.y - posA.y, map_Pos.x - posA.x);
		rotation_grad = rotation_rad * 180.f / 3.1415;
		vector = (pow(map_Pos.y - posA.y, 2)) + (pow(map_Pos.x - posA.x, 2));

		if (false)
		{
			State = state::up_left;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			State = state::up_right;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			State = state::down_left;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			State = state::down_right;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			State = state::left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			State = state::right;

		}
		else if (rotation_grad <= -80 && rotation_grad >= -100) {
			State = state::up;

		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			State = state::down;

		}
		else State = state::stay;

		if (vector < 10000)
		{
			dx = 0.05 * std::cos(std::atan2(map_Pos.y - posA.y, map_Pos.x - posA.x));
			dy = 0.05 * std::sin(std::atan2(map_Pos.y - posA.y, map_Pos.x - posA.x));
		}
		else
		{
			dx = 0.1 * std::cos(std::atan2(map_Pos.y - posA.y, map_Pos.x - posA.x));
			dy = 0.1 * std::sin(std::atan2(map_Pos.y - posA.y, map_Pos.x - posA.x));
		}
	}

	Main.tick(time);

	collision = Check_Collision(Solid_Vec);

	posA.x += dx * time;
	posA.y += dy * time;
	dx = 0;
	dy = 0;
}

std::map<std::string, float> Hero::GetAllState() const
{
	std::map<std::string, float> AllState;
	AllState["X"] = posA.x;
	AllState["Y"] = posA.y;
	AllState["Is Life"] = life;
	AllState["Collision"] = collision;
	AllState["Rotation"] = rotation_grad;
	AllState["Vector"] = vector;

	return AllState;
}

//-----------------------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------------------------