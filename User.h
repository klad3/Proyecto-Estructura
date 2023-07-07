#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include "Book.h"

class User {
    public:
    std::string name;
    std::string email;
    Book* books;
    User* next;

    User(const std::string& name, const std::string& email);
    ~User();
};

void registrarUsuario(const std::string& name, const std::string& email, User*& usersHead);
User* obtenerUsuario(const std::string& email, User*& usersHead);
void mostrarLibrosPrestados(const std::string& email, User*& usersHead);
int contarUsuarios(User*& usersHead);
bool prestarLibro(std::string title, User*& user, Book*& bookCatalogo, Book*& head);
void devolverLibro(User*& user, Book*& bookCatalogo, Book*& head);
bool venderLibro(std::string title, Book*& bookCatalogo, Book*& head, Book*& vendidos);

#endif  // USER_H
