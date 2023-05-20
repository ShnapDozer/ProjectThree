#pragma once
#include <memory>

namespace ProjectThree {

	#define ObjectPtr std::shared_ptr <Object>

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


