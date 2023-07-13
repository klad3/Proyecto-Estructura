#include "User.h"

User::User(const std::string& name, const std::string& email)
    : name(name), email(email), books(nullptr), next(nullptr) {}

User::~User(){}

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

void mostrarLibrosPrestados(User*& usuario, User*& usersHead) {
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

int contarUsuarios(User*& usersHead) {
    int contador = 0;
    User* current = usersHead;

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

bool prestarLibro(std::string title, User*& user, Book*& bookCatalogo, Book*& head) { //TERMINADO
    Book* libro = buscarLibro(title, head);
    Book* libroCatalogo = buscarLibro(title, bookCatalogo);
    if (libro != nullptr && libroCatalogo != nullptr) {
        libroCatalogo->stock -= 1;
        Book* currentBook = new Book(libro->title, libro->author, libro->category, libro->year, libro->isbn, libro->publisher, true);
        eliminarLibro(libro, head);
        encolarLibro(currentBook, user->books);
        return true;
    } else {
        return false;
    }
}

void devolverLibro(User*& user, Book*& bookCatalogo, Book*& head) { //TERMINADO
        Book* bookCat = buscarLibro(user->books->title, bookCatalogo);
        Book* currentBook = new Book(user->books->title, user->books->author, user->books->category, user->books->year, user->books->isbn, user->books->publisher, true);
        eliminarLibro(user->books, user->books);
        anadirLibro(currentBook, head);
        bookCat->stock += 1;
}

bool venderLibro(std::string title, Book*& bookCatalogo, Book*& head, Book*& vendidos) { // TERMINADO AL PARECER
    Book* libroCatalogo = buscarLibro(title, bookCatalogo);
    if (libroCatalogo == nullptr){
        return false;
    }
    if (libroCatalogo->stock > 0) {
        libroCatalogo->stock -= 1;
        libroCatalogo->sales += 1;
        Book* libro = buscarLibro(title, head);
        anadirLibro(libro, vendidos);
        eliminarLibro(libro, head);
        return true;
    } else {
        return false;
    }
}

