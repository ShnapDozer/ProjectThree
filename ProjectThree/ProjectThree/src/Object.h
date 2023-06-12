#pragma once
#include "Defines.h"

namespace pt {

	class Object
	{
	public:
		Object(ObjectPtr parent = nullptr);
		virtual ~Object();

		ObjectPtr getParent();
		void setParent(ObjectPtr parent = nullptr);

	protected:
		ObjectPtr _parent;

	};

}


