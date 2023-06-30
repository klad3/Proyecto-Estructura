#include "Book.h"

// Constructor de Book
Book::Book(const std::string& title, const std::string& author, const std::string& category, const std::string& year, const std::string& isbn, const std::string& publisher, bool available)
    : title(title), author(author), category(category), year(year), isbn(isbn), publisher(publisher), available(available), sales(0), stock(1), next(nullptr) {}

// Funci�n para buscar un libro por t�tulo
Book* buscarLibro(const std::string& title, Book*& lista) {
    Book* currentBook = lista;
    while (currentBook != nullptr) {
        if (currentBook->title == title) {
            return currentBook;
        }
        currentBook = currentBook->next;
    }
    return nullptr;  // Si no se encuentra el libro
}

// Funci�n para a�adir un libro al cat�logo
void anadirCatalogo(Book* newBook, Book*& lista) { // TERMINADO

	Book* sameBook = buscarLibro(newBook->title, lista);

	if (sameBook == nullptr) {
	    if (lista == nullptr) {
	        lista = newBook;
	    } else {
	        Book* current = lista;
	        while (current->next != nullptr) {
	            current = current->next;
	        }
	        current->next = newBook;
	    }
	} else {
		sameBook->stock += 1;
	}
}

// Funci�n para a�adir un libro a la lista
void anadirLibro(Book* newBook, Book*& lista) { // TERMINADO
	if (lista == nullptr) {
	    lista = newBook;
	} else {
	    Book* current = lista;
	    while (current->next != nullptr) {
	        current = current->next;
	    }
	    current->next = newBook;
	}
}

