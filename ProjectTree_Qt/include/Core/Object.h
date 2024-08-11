#pragma once
#include <memory>

namespace pt {

class Object;
typedef std::shared_ptr <pt::Object> ObjectPtr;

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


