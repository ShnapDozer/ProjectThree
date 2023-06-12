#pragma once

#include <string>

#include "TinyXML2/tinyxml2.h"

#include "Common.h"
#include "Defines.h"
#include "Object.h"

namespace pt
{
	class Settings : public Object {
	public:
		Settings(const std::string &rootName = "SettingsFile", ObjectPtr parent = nullptr);
		virtual ~Settings();

		bool openFile(const std::string& path);
		bool saveFile(const std::string& path = "");

		template <typename T>
		void setAttribute(const std::string& pathToElement, const std::string& name, T value);

		double getDoubleAttribute(const std::string& pathToState, const std::string& name, double defaultState = 0.f) const;
		std::string getStrAttribute(const std::string& pathToState, const std::string& name, const std::string& defaultState = "") const;
		int getIntAttribute(const std::string& pathToState, const std::string& name, int defaultState = 0) const;

		template <typename T>
		void setState(const std::string& pathToState, T state);

		double getDoubleState(const std::string& pathToState, double defaultState = 0.f) const;
		std::string getStrState(const std::string& pathToState, const std::string& defaultState = "") const;
		int getIntState(const std::string& pathToState, int defaultState = 0) const;

		StringList childGroups(const std::string& path = "");

		bool isOpen() const;

	protected:
		tinyxml2::XMLDocument doc;

		std::string _rootName;
		std::string _filePath;
		bool _fileOpen;

		const tinyxml2::XMLElement* findElementByPath(const std::string& pathToElement) const;
	};

	
	template<typename T>
	inline void Settings::setState(const std::string& pathToState, T state)
	{
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		if (root == nullptr) {
			root = doc.NewElement(_rootName.c_str());
			doc.LinkEndChild(root);
		}



		tinyxml2::XMLElement* curElement = root;
		tinyxml2::XMLElement* prevElement = curElement;

		for (auto groupName : Common::splitByChar(pathToState, '/')) {
			curElement = curElement->FirstChildElement(groupName.c_str());

			if (curElement == nullptr) {
				curElement = prevElement->InsertNewChildElement(groupName.c_str());
			}

			prevElement = curElement;
		}
		curElement->SetText(state);

		
	}

	template<typename T>
	inline void Settings::setAttribute(const std::string& pathToElement, const std::string &name, T value)
	{
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		if (root == nullptr) {
			root = doc.NewElement("SettingsFile");
			doc.LinkEndChild(root);
		}

		tinyxml2::XMLElement* curElement = root;
		tinyxml2::XMLElement* prevElement = curElement;

		for (auto groupName : Common::splitByChar(pathToElement, '/')) {
			curElement = curElement->FirstChildElement(groupName.c_str());

			if (curElement == nullptr) {
				curElement = prevElement->InsertNewChildElement(groupName.c_str());
			}

			prevElement = curElement;
		}
		curElement->SetAttribute(name.c_str(), value);
	}

}