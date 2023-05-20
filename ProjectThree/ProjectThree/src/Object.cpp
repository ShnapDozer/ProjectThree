#include "Object.h"


namespace ProjectThree {

	ProjectThree::Object::Object(ObjectPtr parent)
	{
		_parent = parent;
	}

	ProjectThree::Object::~Object()
	{
	}

	ObjectPtr ProjectThree::Object::getParent()
	{
		return _parent;
	}
	void Object::setParent(ObjectPtr parent)
	{
		_parent = parent;
	}
}
