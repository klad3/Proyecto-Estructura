// ApiHandler.cpp


#include "ApiHandler.h"
#include <windows.h>
#include <wininet.h>
#include <string>

#pragma comment(lib, "wininet.lib")

std::string GetBookInfo(const std::string& isbn) {
    HINTERNET hInternet, hConnect;
    DWORD bytesRead;
    char buffer[4096];
    std::string result;

    // Inicializar WinINet
    hInternet = InternetOpenW(L"HTTP Request Example", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        return result;
    }

    // Construir la URL de la API con el código ISBN
    std::string apiUrl = "https://www.googleapis.com/books/v1/volumes?q=" + isbn + "&maxResults=1&filter=partial&orderBy=relevance&printType=books";
	//"https://openlibrary.org/search.json?q=" + isbn + "&fields=*,availability&limit=1&sort=new";
    

    // Abrir la conexión HTTP
    hConnect = InternetOpenUrlW(hInternet, std::wstring(apiUrl.begin(), apiUrl.end()).c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (hConnect == NULL) {
        InternetCloseHandle(hInternet);
        return result;
    }

    // Leer los datos de la respuesta
    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        result.append(buffer, bytesRead);
    }

    // Cerrar las conexiones y liberar recursos
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);

    return result;
}

