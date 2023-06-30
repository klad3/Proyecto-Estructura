#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Book.h"

struct User {
    std::string name;
    std::string email;
    Book* books;
    User* next;

    User(const std::string& name, const std::string& email);
};

void registrarUsuario(const std::string& name, const std::string& email, User*& usersHead);
User* obtenerUsuario(const std::string& email, User*& usersHead);
void mostrarLibrosPrestados(const std::string& email, User*& usersHead);
int contarUsuarios(User*& usersHead);

#endif  // USER_H
