#pragma once

#include <string>
#include <Windows.h>


// FileDialog::openFile("All Files (*.*)\0*.*\0", GameApplication::getRenderWindow()->getSystemHandle()); 

namespace pt {
	class FileDialog {
	public:
		static std::string openFile(const char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
		static std::string saveFile(const char* filter);
	};
}