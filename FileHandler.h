#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "Book.h"
#include "User.h"
#include "include/rapidjson/document.h"
#include "include/rapidjson/prettywriter.h"
#include "include/rapidjson/stringbuffer.h"

void cargarLibrosDesdeArchivo(Book*& lista, const std::string& archivo);
void guardarLibroEnArchivo(const Book* libro, const std::string& archivo);
void cargarUsuariosDesdeArchivo(User*& lista, const std::string& archivo);
void guardarUsuariosEnArchivo(const User* lista, const std::string& archivo);

#endif // FILEHANDLER_H
