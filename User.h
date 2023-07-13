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

void registrarUsuario(const std::string& name, const std::string& email, User*& almacenUsuarios);
User* obtenerUsuario(const std::string& email, User*& almacenUsuarios);
void mostrarLibrosPrestados(User*& usuario, User*& almacenUsuarios);
int contarUsuarios(User*& almacenUsuarios);
bool verificarPrestamoMaximo(User*& user);
bool prestarLibro(std::string title, User*& user, Book*& catalogoLibros, Book*& almacenLibros);
void devolverLibro(User*& user, Book*& catalogoLibros, Book*& almacenLibros);
bool venderLibro(std::string title, Book*& catalogoLibros, Book*& almacenLibros, Book*& vendidos);

#endif  // USER_H
