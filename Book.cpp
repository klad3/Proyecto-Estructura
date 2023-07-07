#include "Book.h"

// Constructor de Book
Book::Book(const std::string& title, const std::string& author, const std::string& category, const std::string& year, const std::string& isbn, const std::string& publisher, bool available)
    : title(title), author(author), category(category), year(year), isbn(isbn), publisher(publisher), available(available), sales(0), stock(1), next(nullptr) {}

Book::~Book() {}

// Función para buscar un libro por título
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

// Función para añadir un libro al catálogo
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

// Función para añadir un libro a la lista
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

int contarLibros(Book*& lista) { // TERMINADO
    int contador = 0;
    Book* actual = lista;

    while (actual != nullptr) {
        contador++;
        actual = actual->next;
    }

    return contador;
}

Book* obtenerLibroMasVendido(Book*& lista) { //TERMINADO PROBABLEMENTE
    if (lista == nullptr) {
        return nullptr;
    }

    Book* libroMasVendido = lista;
    Book* current = lista->next;

    while (current != nullptr) {
        if (current->sales > libroMasVendido->sales) {
            libroMasVendido = current;
        }
        current = current->next;
    }

    return libroMasVendido;
}

void encolarLibro(Book* &nodo, Book* &cola) { //TERMINADO
	Book* p = cola;
	if(cola == nullptr)
		cola = nodo;
	else{
		while(p->next != nullptr)
			p = p->next;
		p->next = nodo;
	}
}

void eliminarLibro(Book*& bookToDelete, Book*& lista) { //TERMINADO
    if (lista == nullptr) {
        //cout << "La lista está vacía. No se puede eliminar ningún libro." << endl;
        return;
    }

    if (lista == bookToDelete) {
        lista = lista->next;
        delete bookToDelete;
        //cout << "Libro eliminado exitosamente." << endl;
        return;
    }

    Book* current = lista;
    while (current->next != nullptr && current->next != bookToDelete) {
        current = current->next;
    }

    if (current->next == nullptr) {
        //cout << "El libro no se encontró en la lista." << endl;
        return;
    }

    current->next = current->next->next;
    delete bookToDelete;
    //cout << "Libro eliminado exitosamente." << endl;
}

