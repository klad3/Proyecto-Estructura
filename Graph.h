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

    void addVertex(Book* book);
    void addEdge(Book* source, Book* destination);
    void removeEdge(Book* source, Book* destination);
    bool hasEdge(Book* source, Book* destination);
    void conectarLibrosCatalogo(Book* bookCatalogo);
    arista* getNeighbors(Book* vertex) const;
    std::vector<std::string> recomendarLibros(const std::string& bookTitle, Book* bookCatalogo);

private:
    nodo* findVertex(Book* book) const;
};

#endif
