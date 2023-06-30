#include "User.h"

User::User(const std::string& name, const std::string& email)
    : name(name), email(email), books(nullptr), next(nullptr) {}

void registrarUsuario(const std::string& name, const std::string& email, User*& usersHead) {
    User* newUser = new User(name, email);
    if (usersHead == nullptr) {
        usersHead = newUser;
    } else {
        User* current = usersHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    std::cout << "Usuario registrado exitosamente." << std::endl;
}

User* obtenerUsuario(const std::string& email, User*& usersHead) {
    User* current = usersHead;
    while (current != nullptr) {
        if (current->email == email) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void mostrarLibrosPrestados(const std::string& email, User*& usersHead) {
    User* usuario = obtenerUsuario(email, usersHead);
    if (usuario->books == nullptr) {
        std::cout << "No hay libros registrados para este usuario." << std::endl;
    } else {
        std::cout << "Libros prestados al usuario " << usuario->name << ":" << std::endl;
        Book* current = usuario->books;
        while (current != nullptr) {
            std::cout << "Título: " << current->title << std::endl;
            std::cout << "Autor: " << current->author << std::endl;
            std::cout << "Categoría: " << current->category << std::endl;
            std::cout << "ISBN: " << current->isbn << std::endl;
            std::cout << "Stock: " << current->stock << std::endl;
            std::cout << "-------------------------" << std::endl;
            current = current->next;
        }
    }
}

int contarUsuarios(User*& usersHead) {
    int contador = 0;
    User* current = usersHead;

    while (current != nullptr) {
        contador++;
        current = current->next;
    }

    return contador;
}

