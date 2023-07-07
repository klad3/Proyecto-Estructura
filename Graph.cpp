#include "Graph.h"

Graph::nodo::nodo(Book* bk) : book(bk), neighbors(nullptr), next(nullptr) {}

Graph::arista::arista(nodo* dest) : destination(dest), next(nullptr) {}

Graph::Graph() : vertices(nullptr) {}

Graph::~Graph() {}

void Graph::addVertex(Book* book) {
    nodo* newVertex = new nodo(book);
    newVertex->next = vertices;
    vertices = newVertex;
}

void Graph::addEdge(Book* source, Book* destination) {
    nodo* sourceVertex = findVertex(source);
    nodo* destinationVertex = findVertex(destination);
    if (sourceVertex != nullptr && destinationVertex != nullptr) {
        arista* newEdge = new arista(destinationVertex);
        newEdge->next = sourceVertex->neighbors;
        sourceVertex->neighbors = newEdge;
    }
}

void Graph::removeEdge(Book* source, Book* destination) {
    nodo* sourceVertex = findVertex(source);
    if (sourceVertex != nullptr) {
        arista* prevEdge = nullptr;
        arista* currEdge = sourceVertex->neighbors;
        while (currEdge != nullptr) {
            if (currEdge->destination->book == destination) {
                if (prevEdge != nullptr) {
                    prevEdge->next = currEdge->next;
                } else {
                    sourceVertex->neighbors = currEdge->next;
                }
                delete currEdge;
                break;
            }
            prevEdge = currEdge;
            currEdge = currEdge->next;
        }
    }
}

bool Graph::hasEdge(Book* source, Book* destination) {
    nodo* sourceVertex = findVertex(source);
    if (sourceVertex != nullptr) {
        arista* currEdge = sourceVertex->neighbors;
        while (currEdge != nullptr) {
            if (currEdge->destination->book == destination) {
                return true;
            }
            currEdge = currEdge->next;
        }
    }
    return false;
}

void Graph::conectarLibrosCatalogo(Book* bookCatalogo) {
    for (Book* currentBook = bookCatalogo; currentBook != nullptr; currentBook = currentBook->next) {
        addVertex(currentBook);
    }

    for (Book* currentBook = bookCatalogo; currentBook != nullptr; currentBook = currentBook->next) {
        for (Book* neighborBook = bookCatalogo; neighborBook != nullptr; neighborBook = neighborBook->next) {
            if (neighborBook != currentBook && (currentBook->category == neighborBook->category)) {
                addEdge(currentBook, neighborBook);
            }
        }
    }
}

Graph::arista* Graph::getNeighbors(Book* vertex) const {
    nodo* vertexNode = findVertex(vertex);
    if (vertexNode != nullptr) {
        return vertexNode->neighbors;
    }
    return nullptr;
}

std::vector<std::string> Graph::recomendarLibros(const std::string& bookTitle, Book* bookCatalogo) {
    std::vector<std::string> recommendations;
    Book* book = nullptr;
    for (Book* currentBook = bookCatalogo; currentBook != nullptr; currentBook = currentBook->next) {
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

Graph::nodo* Graph::findVertex(Book* book) const {
    nodo* current = vertices;
    while (current != nullptr) {
        if (current->book == book) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
