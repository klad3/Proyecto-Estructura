#include "Graph.h"

Graph::nodo::nodo(Book* bk) : book(bk), neighbors(nullptr), next(nullptr) {}

Graph::arista::arista(nodo* dest) : destination(dest), next(nullptr) {}

Graph::Graph() : vertices(nullptr) {}

Graph::~Graph() {}

void Graph::addNodo(Book* book) {
    nodo* newNodo = new nodo(book);
    newNodo->next = vertices;
    vertices = newNodo;
}

void Graph::addArista(Book* source, Book* destination) {
    nodo* inicioNodo = buscarNodo(source);
    nodo* destinoNodo = buscarNodo(destination);
    if (inicioNodo != nullptr && destinoNodo != nullptr) {
        arista* newArista = new arista(destinoNodo);
        newArista->next = inicioNodo->neighbors;
        inicioNodo->neighbors = newArista;
    }
}

void Graph::removeArista(Book* source, Book* destination) {
    nodo* inicioNodo = buscarNodo(source);
    if (inicioNodo != nullptr) {
        arista* prevEdge = nullptr;
        arista* currEdge = inicioNodo->neighbors;
        while (currEdge != nullptr) {
            if (currEdge->destination->book == destination) {
                if (prevEdge != nullptr) {
                    prevEdge->next = currEdge->next;
                } else {
                    inicioNodo->neighbors = currEdge->next;
                }
                delete currEdge;
                break;
            }
            prevEdge = currEdge;
            currEdge = currEdge->next;
        }
    }
}

bool Graph::tieneArista(Book* source, Book* destination) {
    nodo* inicioNodo = buscarNodo(source);
    if (inicioNodo != nullptr) {
        arista* currEdge = inicioNodo->neighbors;
        while (currEdge != nullptr) {
            if (currEdge->destination->book == destination) {
                return true;
            }
            currEdge = currEdge->next;
        }
    }
    return false;
}

void Graph::conectarLibrosCatalogo(Book* catalogoLibros) {
    for (Book* currentBook = catalogoLibros; currentBook != nullptr; currentBook = currentBook->next) {
        addNodo(currentBook);
    }

    for (Book* currentBook = catalogoLibros; currentBook != nullptr; currentBook = currentBook->next) {
        for (Book* neighborBook = catalogoLibros; neighborBook != nullptr; neighborBook = neighborBook->next) {
            if (neighborBook != currentBook && (currentBook->category == neighborBook->category)) {
                addArista(currentBook, neighborBook);
            }
        }
    }
}

Graph::arista* Graph::getNeighbors(Book* vertex) const {
    nodo* vertexNode = buscarNodo(vertex);
    if (vertexNode != nullptr) {
        return vertexNode->neighbors;
    }
    return nullptr;
}

std::vector<std::string> Graph::recomendarLibros(const std::string& bookTitle, Book* catalogoLibros) {
    std::vector<std::string> recommendations;
    Book* book = nullptr;
    for (Book* currentBook = catalogoLibros; currentBook != nullptr; currentBook = currentBook->next) {
        if (currentBook->title == bookTitle) {
            book = currentBook;
            break;
        }
    }

    if (book != nullptr) {
        arista* neighbors = getNeighbors(book);
        while (neighbors != nullptr) {
            recommendations.push_back(neighbors->destination->book->title);
            neighbors = neighbors->next;
        }
    }

    return recommendations;
}

Graph::nodo* Graph::buscarNodo(Book* book) const {
    nodo* current = vertices;
    while (current != nullptr) {
        if (current->book == book) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
