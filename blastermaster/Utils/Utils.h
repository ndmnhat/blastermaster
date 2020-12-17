#pragma once

#include <Windows.h>
#include <signal.h>
#include <string>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

class CGameObject;

void DebugOut(wchar_t* fmt, ...);

std::vector<std::string> split(std::string line, std::string delimeter = "\t");

std::wstring ToWSTR(std::string st);

LPCWSTR ToLPCWSTR(std::string st);

#define SAFE_DELETE(p) if ((p) != NULL) { delete (p); (p) = NULL; }
