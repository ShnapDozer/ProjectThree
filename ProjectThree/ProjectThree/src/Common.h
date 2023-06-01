#pragma once

#include <map>
#include <string>
#include <vector>
#include <thread>

#include "SFML/Graphics.hpp"


#include"GameApplication.h"

namespace Common {

	#define StringList std::vector <std::string>

	class AnimManager;

	template <typename T>
	std::vector <std::string> MapToString(std::map <std::string, T> a);
	bool checNameAnim(StringList animNames, std::string name);

	void PrintState(std::map<std::string, float> a);
	
	sf::Color ParseColor(const std::string& hexRGB); // Parses hex-encoded RGB like "6d9fb9"
	float ParseFloat(const std::string& str);	

	StringList splitByChar(const std::string & text, char separator);

	template <class ClassName>
	void startTimer(long long interval, ClassName* callBackClass, void(ClassName::* callBackFunction)()) {

		std::thread([interval, callBackClass, callBackFunction]() {
			while (true) {
				(callBackClass->*callBackFunction)();
				std::this_thread::sleep_for(std::chrono::milliseconds(interval));
			}

		}).detach();		
	}

}

