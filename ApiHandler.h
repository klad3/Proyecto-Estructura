#ifndef APIHANDLER_H
#define APIHANDLER_H

#include <windows.h>
#include <wininet.h>
#include <string>

std::string GetBookInfo(const std::string& isbn);

#endif

