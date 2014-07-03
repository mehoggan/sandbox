#include "WinMain.h"
#include <string>
#include <list>
#include <iterator>

std::string wstrtostr(const std::wstring &wstr) 
{ 
    // Convert a Unicode string to an ASCII string 
    std::string strTo; 
    char *szTo = new char[wstr.length() + 1]; 
    szTo[wstr.size()] = '\0'; 
    ::WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, szTo, (int)wstr.length(), NULL, NULL); 
    strTo = szTo; 
    delete[] szTo; 
    return strTo; 
} 

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// Process Command Line Arguments then Call main()
    LPWSTR *szArgList;
    int argCount;
    szArgList = ::CommandLineToArgvW(GetCommandLine(), &argCount);
    if (szArgList == NULL)
    {
        ::MessageBox(NULL, L"Unable to parse command line", L"Error", MB_OK);
        return 1;
    }

	std::list<std::string> args;

    for(int i = 0; i < argCount; i++)
    {
        args.push_back(wstrtostr(std::wstring(szArgList[i])));
    }
    LocalFree(szArgList);
    
	int argc = args.size();
	char **argv = new char*[argc + 1];
	
	int index = 0;
	for(std::list<std::string>::iterator copy_it = args.begin(); copy_it != args.end(); copy_it++)
	{
		argv[index] = const_cast<char *>(copy_it->c_str());
	}

	main(argc, argv);
	return 0;
}