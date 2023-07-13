#include "User.h"

User::User(const std::string& name, const std::string& email)
    : name(name), email(email), books(nullptr), next(nullptr) {}

User::~User(){}

void registrarUsuario(const std::string& name, const std::string& email, User*& almacenUsuarios) {
    User* newUser = new User(name, email);
    if (almacenUsuarios == nullptr) {
        almacenUsuarios = newUser;
    } else {
        User* current = almacenUsuarios;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newUser;
    }
    std::cout << "Usuario registrado exitosamente." << std::endl;
}

User* obtenerUsuario(const std::string& email, User*& almacenUsuarios) {
    User* current = almacenUsuarios;
    while (current != nullptr) {
        if (current->email == email) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void mostrarLibrosPrestados(User*& usuario, User*& almacenUsuarios) {
    if (usuario->books == nullptr) {
        std::cout << "No hay libros prestados para usuario: " << usuario->name << std::endl;
    } else {
        std::cout << "Libros prestados al usuario " << usuario->name << ":" << std::endl;
        Book* current = usuario->books;
        while (current != nullptr) {
            std::cout << "Título: " << current->title << std::endl;
            std::cout << "Autor: " << current->author << std::endl;
            std::cout << "Categoría: " << current->category << std::endl;
            std::cout << "-------------------------" << std::endl;
            current = current->next;
        }
    }
}

int contarUsuarios(User*& almacenUsuarios) {
    int contador = 0;
    User* current = almacenUsuarios;

    while (current != nullptr) {
        contador++;
        current = current->next;
    }

    return contador;
}

bool verificarPrestamoMaximo(User*& user){
    if (contarLibros(user->books) <= 4){
        return true;
    } else {
        return false;
    }
}

bool prestarLibro(std::string title, User*& user, Book*& bookCatalogo, Book*& almacenLibros) { //TERMINADO
    Book* libro = buscarLibro(title, almacenLibros);
    Book* libroCatalogo = buscarLibro(title, bookCatalogo);
    if (libro != nullptr && libroCatalogo != nullptr) {
        libroCatalogo->stock -= 1;
        Book* currentBook = new Book(libro->title, libro->author, libro->category, libro->year, libro->isbn, libro->publisher, true);
        eliminarLibro(libro, almacenLibros);
        encolarLibro(currentBook, user->books);
        return true;
    } else {
        return false;
    }
}

void devolverLibro(User*& user, Book*& bookCatalogo, Book*& almacenLibros) { //TERMINADO
        Book* bookCat = buscarLibro(user->books->title, bookCatalogo);
        Book* currentBook = new Book(user->books->title, user->books->author, user->books->category, user->books->year, user->books->isbn, user->books->publisher, true);
        eliminarLibro(user->books, user->books);
        anadirLibro(currentBook, almacenLibros);
        bookCat->stock += 1;
}

bool venderLibro(std::string title, Book*& bookCatalogo, Book*& almacenLibros, Book*& vendidos) { // TERMINADO AL PARECER
    Book* libroCatalogo = buscarLibro(title, bookCatalogo);
    if (libroCatalogo == nullptr){
        return false;
    }
    if (libroCatalogo->stock > 0) {
        libroCatalogo->stock -= 1;
        libroCatalogo->sales += 1;
        Book* libro = buscarLibro(title, almacenLibros);
        anadirLibro(libro, vendidos);
        eliminarLibro(libro, almacenLibros);
        return true;
    } else {
        return false;
    }
}

