#pragma once

#include <string>

#include "TinyXML2/tinyxml2.h"
#include "Object.h"
#include "Common.h"

namespace pt
{
	class Settings : public Object {
	public:
		Settings();
		virtual ~Settings();

		bool openFile(std::string path);
		bool saveFile(std::string path = "");

		template <typename T>
		void setAttribute(std::string pathToElement, const std::string& name, T value);

		double getDoubleAttribute(const std::string& pathToState, const std::string& name, double defaultState = 0.f) const;
		std::string getStrAttribute(const std::string& pathToState, const std::string& name, const std::string& defaultState = "") const;
		int getIntAttribute(const std::string& pathToState, const std::string& name, int defaultState = 0) const;

		template <typename T>
		void setState(std::string pathToState, T state);

		double getDoubleState(const std::string& pathToState, double defaultState = 0.f) const;
		std::string getStrState(const std::string& pathToState, const std::string& defaultState = "") const;
		int getIntState(const std::string& pathToState, int defaultState = 0) const;

		bool isOpen() const;

	protected:
		tinyxml2::XMLDocument doc;

		std::string _filePath;
		bool _fileOpen;

		const tinyxml2::XMLElement* findElementByPath(const std::string& pathToElement) const;
	};

	
	template<typename T>
	inline void Settings::setState(std::string pathToState, T state)
	{
		tinyxml2::XMLElement* root = doc.FirstChildElement();
		if (root == nullptr) {
			root = doc.NewElement("SettingsFile");
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
	inline void Settings::setAttribute(std::string pathToElement, const std::string &name, T value)
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