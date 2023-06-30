#ifndef BOOK_H
#define BOOK_H

#include <string>

struct Book {
    std::string title;
    std::string author;
    std::string category;
    std::string year;
    std::string isbn;
    std::string publisher;
    bool available;
    int sales;
    int stock;
    struct Book* next;

    Book(const std::string& title, const std::string& author, const std::string& category, const std::string& year, const std::string& isbn, const std::string& publisher, bool available);
};

// Declaración de funciones relacionadas con los libros
Book* buscarLibro(const std::string& title, Book*& lista);
void anadirCatalogo(Book* newBook, Book*& lista);
void anadirLibro(Book* newBook, Book*& lista);

#endif  // BOOK_H
