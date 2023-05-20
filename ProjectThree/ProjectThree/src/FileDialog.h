#pragma once

#include <string>
#include <Windows.h>

namespace ProjectThree {
	class FileDialog {
	public:
		static std::string openFile(const char* filter = "All Files (*.*)\0*.*\0", HWND owner = NULL);
		static std::string saveFile(const char* filter);
	};
}