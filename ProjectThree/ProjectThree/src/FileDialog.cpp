#include "FileDialog.h"

#include <string>


std::string pt::FileDialog::openFile(const char* filter, HWND owner)
{
    OPENFILENAME ofn;
    char fileName[MAX_PATH] = "";
    ZeroMemory(&ofn, sizeof(ofn));

    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.hwndOwner = owner; 
    ofn.lpstrFilter = filter;
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
    ofn.lpstrDefExt = "";

    std::string fileNameStr;

    if (GetOpenFileName(&ofn)) {
        fileNameStr = fileName;
    }

    return fileNameStr;
}
