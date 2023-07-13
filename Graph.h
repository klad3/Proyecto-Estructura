#ifndef GRAPH_H
#define GRAPH_H

#include "Book.h"
#include <vector>
#include <string>

class Graph {
    public:
    struct arista;
    struct nodo {
        Book* book;
        arista* neighbors;
        nodo* next;
        nodo(Book* bk);
    };

    struct arista {
        nodo* destination;
        arista* next;
        arista(nodo* dest);
    };

    nodo* vertices;

    Graph();
    ~Graph();

    void addNodo(Book* book);
    void addArista(Book* source, Book* destination);
    void removeArista(Book* source, Book* destination);
    bool tieneArista(Book* source, Book* destination);
    void conectarLibrosCatalogo(Book* catalogoLibros);
    arista* getNeighbors(Book* vertex) const;
    std::vector<std::string> recomendarLibros(const std::string& bookTitle, Book* catalogoLibros);


private:
    nodo* buscarNodo(Book* book) const;
};

#endif
