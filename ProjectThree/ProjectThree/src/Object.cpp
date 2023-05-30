#include "Object.h"


namespace pt {

	pt::Object::Object(ObjectPtr parent)
	{
		_parent = parent;
	}

	pt::Object::~Object()
	{
	}

	ObjectPtr pt::Object::getParent()
	{
		return _parent;
	}
	void Object::setParent(ObjectPtr parent)
	{
		_parent = parent;
	}
}
