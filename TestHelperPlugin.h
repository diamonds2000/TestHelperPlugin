#pragma once

#include "PluginInterface.h"


const TCHAR NPP_PLUGIN_NAME[] = TEXT("MSC Test helper");

const int nbFunc = 14;

void pluginInit(HMODULE hModule);

void pluginCleanUp();

void commandMenuInit();

void commandMenuCleanUp();

bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);

void checkout();

void runRTest();

void runSTest();

void runRTestInDir();

void runSTestInDir();

void runRTestCase();

void runSTestCase();

void checkSyntax2x();

void checkSyntax3x();

void openShell();

void getCurrentFilePath(LPTSTR lpszFilePath, int size);

void getCurrentFile(LPTSTR lpszFilePath, int size);

void getCurrentFileDir(LPTSTR lpszDirPath, int size);

void getCurrentWord(LPTSTR lpszWord, int size);

void getTestRunnerPath(LPCTSTR lpszTestCasePath, LPTSTR lpszPath, int size);

void getFilePath(LPCTSTR lpszFilePathName, LPTSTR lpszPath, int size);

void reloadCurrentFile();

bool verifyPath(LPCTSTR lpszPath);

