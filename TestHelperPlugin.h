#pragma once

#include "PluginInterface.h"


const TCHAR NPP_PLUGIN_NAME[] = TEXT("MSC Test helper");

const int nbFunc = 4;

void pluginInit(HANDLE hModule);

void pluginCleanUp();

void commandMenuInit();

void commandMenuCleanUp();

bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk = NULL, bool check0nInit = false);

void runRTest();

void runSTest();

void checkSyntax2x();

void checkSyntax3x();

void getCurrentFilePath(LPTSTR lpszFilePath, int size);

void getCurrentFile(LPTSTR lpszFilePath, int size);

void getCurrentWord(LPTSTR lpszWord, int size);

