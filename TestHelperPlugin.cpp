// TestHelperPlugin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TestHelperPlugin.h"
#include "menuCmdID.h"



FuncItem funcItem[nbFunc];
NppData nppData;


void pluginInit(HANDLE hModule)
{
}

void pluginCleanUp()
{
}

void commandMenuInit()
{
	setCommand(0, TEXT("Check Python2.x Syntax"), checkSyntax2x, NULL, false);
	setCommand(1, TEXT("Check Python3.x Syntax"), checkSyntax3x, NULL, false);
	setCommand(2, TEXT("Run RTest"), runRTest, NULL, false);
	setCommand(3, TEXT("Run STest"), runSTest, NULL, false);
}

void commandMenuCleanUp()
{
}

bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit)
{
	if (index >= nbFunc)
		return false;

	if (!pFunc)
		return false;

	lstrcpy(funcItem[index]._itemName, cmdName);
	funcItem[index]._pFunc = pFunc;
	funcItem[index]._init2Check = check0nInit;
	funcItem[index]._pShKey = sk;

	return true;
}


void runRTest()
{
	TCHAR filePath[MAX_PATH];
	getCurrentFilePath(filePath, _countof(filePath));
	MessageBox(NULL, filePath, L"file", MB_OK);

	TCHAR param[MAX_PATH];
	ZeroMemory(param, sizeof(param));
	_stprintf(param, _T("/c testrunner.bat --type lrt --files %s"), filePath);
	ShellExecute(NULL, NULL, _T("cmd.exe"), param, _T(""), SW_SHOW);
}

void runSTest()
{

}

void checkSyntax2x()
{

}

void checkSyntax3x()
{

}

void getCurrentFilePath(LPTSTR lpszFilePath, int size)
{
	::SendMessage(nppData._nppHandle, NPPM_GETFULLCURRENTPATH, (WPARAM)size, (LPARAM)lpszFilePath);
}

void getCurrentFile(LPTSTR lpszFilePath, int size)
{
	::SendMessage(nppData._nppHandle, NPPM_GETFILENAME, (WPARAM)size, (LPARAM)lpszFilePath);
}

void getCurrentWord(LPTSTR lpszWord, int size)
{
	::SendMessage(nppData._nppHandle, NPPM_GETCURRENTWORD, (WPARAM)size, (LPARAM)lpszWord);
}