// TestHelperPlugin.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TestHelperPlugin.h"
#include "menuCmdID.h"
#include <map>



FuncItem funcItem[nbFunc];
NppData nppData;

std::map<std::wstring, std::wstring> g_config;


void pluginInit(HMODULE hModule)
{
    wchar_t modulePath[MAX_PATH];
    GetModuleFileNameW(hModule, modulePath, _countof(modulePath));

    wchar_t configFile[MAX_PATH];
    getFilePath(modulePath, configFile, _countof(configFile));
    wcscat_s(configFile, L"\\Config\\testhelper.ini");

    wchar_t buf[MAX_PATH];
    ZeroMemory(buf, sizeof(buf));
    GetPrivateProfileStringW(L"path", L"python2", L"", buf, _countof(buf), configFile);
    g_config[L"python2"] = buf;

    ZeroMemory(buf, sizeof(buf));
    GetPrivateProfileStringW(L"path", L"python3", L"", buf, _countof(buf), configFile);
    g_config[L"python3"] = buf;
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

void runTestFile(LPCTSTR szType)
{
    TCHAR filePath[MAX_PATH];
    ZeroMemory(filePath, sizeof(filePath));
    getCurrentFilePath(filePath, _countof(filePath));

    TCHAR testRunnerPath[MAX_PATH];
    ZeroMemory(testRunnerPath, sizeof(testRunnerPath));
    getTestRunnerPath(filePath, testRunnerPath, _countof(testRunnerPath));

    if (_tcslen(testRunnerPath) > 0 && _tcslen(filePath) > 0)
    {
        if (verifyPath(testRunnerPath) && verifyPath(filePath))
        {
            TCHAR param[MAX_PATH];
            ZeroMemory(param, sizeof(param));
            _stprintf_s(param, _T("/c \"%s\\testrunner.bat\" --type %s --files %s"), testRunnerPath, szType, filePath);
            ShellExecute(NULL, NULL, _T("cmd.exe"), param, testRunnerPath, SW_SHOW);
        }
    }
    else if (_tcslen(testRunnerPath) == 0)
    {
        MessageBox(nppData._nppHandle, _T("Cannot find TestRunner"), _T("Error"), MB_OK);
    }
    else if (_tcslen(filePath) == 0)
    {
        MessageBox(nppData._nppHandle, _T("Must open a test file first"), _T("Error"), MB_OK);
    }
}

void runRTest()
{
    runTestFile(_T("lrt"));
}

void runSTest()
{
    runTestFile(_T("stest"));
}

void checkSyntax(LPCTSTR szPythonPath)
{
    TCHAR filePath[MAX_PATH];
    ZeroMemory(filePath, sizeof(filePath));
    getCurrentFilePath(filePath, _countof(filePath));

    if (verifyPath(filePath))
    {
        TCHAR param[MAX_PATH];
        ZeroMemory(param, sizeof(param));
        _stprintf_s(param, _T("/k \"%s\\python.exe\" -m pyflakes %s"), szPythonPath, filePath);
        ShellExecute(NULL, NULL, _T("cmd.exe"), param, _T(""), SW_SHOW);
    }
}

void checkSyntax2x()
{
    auto it = g_config.find(L"python2");
    if (it != g_config.end() && it->second.length() > 0)
    {
        checkSyntax(it->second.c_str());
    }
    else
    {
        MessageBox(nppData._nppHandle, _T("Please config path of python2 first"), _T("Error"), MB_OK);
    }
}

void checkSyntax3x()
{
    auto it = g_config.find(L"python3");
    if (it != g_config.end() && it->second.length() > 0)
    {
        checkSyntax(it->second.c_str());
    }
    else
    {
        MessageBox(nppData._nppHandle, _T("Please config path of python3 first"), _T("Error"), MB_OK);
    }
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

void getTestRunnerPath(LPCTSTR lpszTestCasePath, LPTSTR lpszPath, int size)
{
    const TCHAR* szFind = _T("\\qa\\");

    size_t index = 0;
    LPCTSTR lpszFind = lpszTestCasePath;
    while (true)
    {
        lpszFind = _tcsstr(lpszFind, szFind);
        if (!lpszFind)
        {
            break;
        }

        index = lpszFind - lpszTestCasePath;
        lpszFind += _tcslen(szFind);
    }

    if (index > 0)
    {
        _tcsncpy_s(lpszPath, size, lpszTestCasePath, index);
    }
}

void getFilePath(LPCTSTR lpszFilePathName, LPTSTR lpszPath, int size)
{
    LPCTSTR lpszFind = _tcsrchr(lpszFilePathName, _T('\\'));
    if (lpszFind)
    {
        size_t count = lpszFind - lpszFilePathName;
        if (count)
        {
            _tcsncpy_s(lpszPath, size, lpszFilePathName, count);
        }
    }
}

//the path cannot include space
bool verifyPath(LPCTSTR lpszPath)
{
    if (_tcschr(lpszPath, _T(' ')))
    {
        MessageBox(nppData._nppHandle, _T("The path cannot include space character"), _T("Error"), MB_OK);
        return false;
    }
    return true;
}
