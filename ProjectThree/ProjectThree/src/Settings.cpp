#include "Settings.h"

#include "Common.h"

pt::Settings::Settings() 
{

}

pt::Settings::~Settings()
{
    this->saveFile();
}

std::string pt::Settings::getStrState(const std::string& pathToState, const std::string& defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->GetText();
}

double pt::Settings::getDoubleState(const std::string& pathToState, double defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->DoubleText();
}

int pt::Settings::getIntState(const std::string& pathToState, int defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->IntText();
}

std::string pt::Settings::getStrAttribute(const std::string& pathToState, const std::string& name, const std::string& defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->FindAttribute(name.c_str())->Value();
}

double pt::Settings::getDoubleAttribute(const std::string& pathToState, const std::string& name, double defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->FindAttribute(name.c_str())->DoubleValue();
}

int pt::Settings::getIntAttribute(const std::string& pathToState, const std::string& name, int defaultState) const
{
    const tinyxml2::XMLElement* element = findElementByPath(pathToState);

    if (element == nullptr) {
        return defaultState;
    }

    return element->FindAttribute(name.c_str())->IntValue();
}

bool pt::Settings::openFile(std::string path)
{
    _fileOpen = doc.LoadFile(path.c_str()) == tinyxml2::XML_SUCCESS;

    if (!this->isOpen()) {
        doc.Clear();
        return false;
    }

    return true;
}

bool pt::Settings::saveFile(std::string path)
{
    
    if (path.empty()) {
        return doc.SaveFile(_filePath.c_str()) == tinyxml2::XML_SUCCESS;
    }
    
    return doc.SaveFile(path.c_str()) == tinyxml2::XML_SUCCESS;;
}

bool pt::Settings::isOpen() const
{
    return _fileOpen;
}

const tinyxml2::XMLElement* pt::Settings::findElementByPath(const std::string& pathToElement) const 
{
    const tinyxml2::XMLElement* findElement = nullptr;

    if (!this->isOpen()) {
        return findElement;
    }

    findElement = doc.FirstChildElement();
    for (auto groupName : Common::splitByChar(pathToElement, '/')) {
        findElement = findElement->FirstChildElement(groupName.c_str());
    }

    return findElement;
}