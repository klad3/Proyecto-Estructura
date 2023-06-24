#include <iostream>
#include <string>
#include <algorithm>
#include <locale>
#include <set>

#include "ApiHandler.h"
#include "include/rapidjson/document.h"

using namespace std;

struct Category {
	string category;
	Category* next;
};

struct Book {
    string title;
    string author;
    string category;
    string year;
    string isbn;
    string publisher;
    bool available;
    int sales;
    int stock;
    struct Book *next;
    
    Book(const string& title, const string& author, const string& category, const string& year, const string& isbn, const string& publisher, bool available)
        : title(title), author(author), category(category), year(year), isbn(isbn), publisher(publisher), available(available), sales(0), stock(1), next(nullptr) {}
};

struct User {
    string name;
    string email;
    struct Book *books;
    struct User *next;

    User(const string& name, const string& email) 
		: name(name), email(email), books(nullptr), next(nullptr) {}
};

Book* head = nullptr;
Book* bookCatalogo = nullptr;
Book* vendidos = nullptr;
User* usersHead = nullptr;

void mostrarMenu() { // TERMINADO 
    cout << "========== Biblioteca ==========" << endl;
    cout << "1. Registrar usuario" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Vender libro" << endl;
    cout << "4. Prestar libro" << endl;
    cout << "5. Devolver libro" << endl;
    cout << "6. Ordenar libros por categoría" << endl;
    cout << "7. Recomendar libros" << endl;
    cout << "8. Mostrar reportes" << endl;
    cout << "9. Añadir libro" << endl;
    cout << "0. Salir" << endl;
    cout << "=================================" << endl;
    cout << "Ingrese una opción: ";
}

void encolar(Book* &nodo, Book* &cola) { //TERMINADO
	Book* p = cola;
	if(cola == nullptr)
		cola = nodo;
	else{
		while(p->next != nullptr)
			p = p->next;
		p->next = nodo;	
	}
}

void desencolar(Book* &cola){ //TERMINADO
	Book* p = cola;
	cola = cola->next;
	delete(p);
}

void verLista(Book* lista){ //TERMINADO
    while (lista != nullptr) {
        cout << "Título: " << lista->title << endl;
        cout << "Autor: " << lista->author << endl;
        cout << "Categoría: " << lista->category << endl;
        cout << "ISBN: " << lista->isbn << endl;
        cout << "Stock: " << lista->stock << endl;
        cout << "-------------------------" << endl;
        lista = lista->next;
    }
}

void registrarUsuario(string name, string email) { //TERMINADO
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
    cout << "Usuario registrado exitosamente." << endl;
}

Book* buscarLibro(const string& title, Book*& lista) { // TERMINADO 
    Book* current = lista;
    while (current != nullptr) {
        if (current->title == title) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

User* obtenerUsuario(const string& email) { //TERMINADO
    User* current = usersHead;
    while (current != nullptr) {
        if (current->email == email) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void recomendarLibros() { //SIN REVISIÓN
    if (head == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }

    string categoriaPreferida;
    cout << "Ingrese su categoría preferida: ";
    cin >> categoriaPreferida;

    cout << "Libros recomendados para la categoría " << categoriaPreferida << ":" << endl;

    Book* current = head;
    bool librosRecomendados = false;
    while (current != nullptr) {
        if (current->category == categoriaPreferida) {
            cout << "Título: " << current->title << endl;
            cout << "Autor: " << current->author << endl;
            cout << "Categoría: " << current->category << endl;
            cout << "-------------------------" << endl;
            librosRecomendados = true;
        }
        current = current->next;
    }

    if (!librosRecomendados) {
        cout << "No se encontraron libros recomendados para la categoría " << categoriaPreferida << "." << endl;
    }
}

int contarLibros(Book* &head) { // TERMINADO
    int contador = 0;
    Book* actual = head;

    while (actual != nullptr) {
        contador++;
        actual = actual->next;
    }

    return contador;
}

Book* obtenerLibroMasVendido() { //TERMINADO PROBABLEMENTE
    if (bookCatalogo == nullptr) {
        return nullptr;
    }

    Book* libroMasVendido = bookCatalogo;
    Book* current = bookCatalogo->next;

    while (current != nullptr) {
        if (current->sales > libroMasVendido->sales) {
            libroMasVendido = current;
        }
        current = current->next;
    }

    return libroMasVendido;
}

void mostrarLibrosPrestados(string email) { // TERMINADO
	User* usuario = obtenerUsuario(email);
    if (usuario->books == nullptr) {
        cout << "No hay libros registrados de este usuario." << endl;
    } else {
    	verLista(usuario->books);
    	system("pause");
	} 
}

void mostrarLibrosDisponibles() { // TERMINADO
    if (bookCatalogo == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }
	bool librosDisponibles = false;
    cout << "Libros disponibles para la venta o préstamo:" << endl;
    Book* current = bookCatalogo;

    while (current != nullptr) {
        if (current->stock > 0) {
            cout << "Título: " << current->title << endl;
            cout << "Autor: " << current->author << endl;
            cout << "Categoría: " << current->category << endl;
            cout << "ISBN: " << current->isbn << endl;
            cout << "Stock: " << current->stock << endl;
            cout << "-------------------------" << endl;
            librosDisponibles = true;
        }
        current = current->next;
    }

    if (!librosDisponibles) {
        cout << "No hay libros disponibles para la venta en este momento." << endl;
    }
}

int contarUsuarios() { //TERMINADO
    int contador = 0;
    User* actual = usersHead;

    while (actual != nullptr) {
        contador++;
        actual = actual->next;
    }

    return contador;
}

void mostrarReportes() { // Sin revisión
    cout << "Mostrando reportes:" << endl;
	/*
    // Reporte 1: Cantidad total de libros registrados
    int cantidadLibros = contarLibros();
    cout << "Cantidad total de libros registrados: " << cantidadLibros << endl;

    // Reporte 2: Libro más vendido
    Book* libroMasVendido = obtenerLibroMasVendido();
    if (libroMasVendido != nullptr) {
        cout << "Libro más vendido:" << endl;
        cout << "Título: " << libroMasVendido->title << endl;
        cout << "Autor: " << libroMasVendido->author << endl;
        cout << "Categoría: " << libroMasVendido->category << endl;
        cout << "Cantidad de ventas: " << libroMasVendido->sales << endl;
    } else {
        cout << "No se encontraron libros registrados." << endl;
    }


	int cantidadUsuarios = contarUsuarios();
    // Reporte 3: Libros prestados y no devueltos
    cout << "Libros prestados y no devueltos:" << endl;
    User* currentUser = usersHead;
    
    //FALTA ARREGLAR
    for(int i = 0 ; i < cantidadUsuarios ; i++){
    	while(currentUser->books->next != nullptr){
    		cout << currentUser->books->title << endl;
    		currentUser->books = currentUser->books->next;
		}
		cout << currentUser->books->title << endl;
	    currentUser = currentUser->next;	
	}
    //mostrarLibrosPrestados();

    // Reporte 4: Libros disponibles para la venta
    cout << "Libros disponibles para la venta:" << endl;
    mostrarLibrosDisponibles();

    // Reporte 5: Cantidad de usuarios registrados
    
    cout << "Cantidad de usuarios registrados: " << cantidadUsuarios << endl;
    */
}

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
	    cout << "Libro añadido exitosamente." << endl;
	} else {
		sameBook->stock += 1;
	}

    
}

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
	cout << "Libro añadido exitosamente." << endl; 
}

void agregarLibro(string name) { // TERMINADO
    string bookInfo = GetBookInfo(name);
    string title, author, category, identifier, publishedDate, publisher;

    rapidjson::Document doc;
    doc.Parse(bookInfo.c_str());

    if (doc.HasMember("items") && doc["items"].IsArray()) {
        const rapidjson::Value& items = doc["items"];
        if (items.Size() > 0 && items[0].IsObject()) {
            const rapidjson::Value& volumeInfo = items[0]["volumeInfo"];

            if (volumeInfo.HasMember("title") && volumeInfo["title"].IsString()) {
                title = volumeInfo["title"].GetString();
                cout << "Título: " << title << endl;
            }

            if (volumeInfo.HasMember("authors") && volumeInfo["authors"].IsArray()) {
                const rapidjson::Value& authors = volumeInfo["authors"];
                if (authors.Size() > 0 && authors[0].IsString()) {
                    author = authors[0].GetString();
                    cout << "Autor: " << author << endl;
                }
            }

            if (volumeInfo.HasMember("categories") && volumeInfo["categories"].IsArray()) {
                const rapidjson::Value& categories = volumeInfo["categories"];
                if (categories.Size() > 0 && categories[0].IsString()) {
                    category = categories[0].GetString();
                    cout << "Categoría: " << category << endl;
                }
            }
            
            if (volumeInfo.HasMember("publisher") && volumeInfo["publisher"].IsString()) {
                string publisher = volumeInfo["publisher"].GetString();
                cout << "Editorial: " << publisher << endl;
            }

            if (volumeInfo.HasMember("industryIdentifiers") && volumeInfo["industryIdentifiers"].IsArray()) {
                const rapidjson::Value& identifiers = volumeInfo["industryIdentifiers"];
                if (identifiers.Size() > 0 && identifiers[0].IsObject()) {
                    const rapidjson::Value& identifierObj = identifiers[0];
                    if (identifierObj.HasMember("identifier") && identifierObj["identifier"].IsString()) {
                        identifier = identifierObj["identifier"].GetString();
                        cout << "ISBN: " << identifier << endl;
                    }
                }
            }

            if (volumeInfo.HasMember("publishedDate") && volumeInfo["publishedDate"].IsString()) {
                publishedDate = volumeInfo["publishedDate"].GetString();
                cout << "Fecha de publicación: " << publishedDate << endl;
            }
        }
    }
    
	Book* newBook1 = new Book(title, author, category, publishedDate, identifier, publisher, true);
	Book* newBook2 = new Book(title, author, category, publishedDate, identifier, publisher, true);
    anadirLibro(newBook1, head);
    anadirCatalogo(newBook2, bookCatalogo);
}

void eliminarLibro(Book*& bookToDelete, Book*& lista) { //TERMINADO
    if (lista == nullptr) {
        cout << "La lista está vacía. No se puede eliminar ningún libro." << endl;
        return;
    }
    
    if (lista == bookToDelete) {
        lista = lista->next;
        delete bookToDelete;
        cout << "Libro eliminado exitosamente." << endl;
        return;
    }
    
    Book* current = lista;
    while (current->next != nullptr && current->next != bookToDelete) {
        current = current->next;
    }
    
    if (current->next == nullptr) {
        cout << "El libro no se encontró en la lista." << endl;
        return;
    }
    
    current->next = current->next->next;
    delete bookToDelete;
    cout << "Libro eliminado exitosamente." << endl;
}

void venderLibro(string title, Book*& bookCatalogo, Book*& head) { // TERMINADO AL PARECER
    
    Book* libroCatalogo = buscarLibro(title, bookCatalogo);
    if (libroCatalogo->stock > 0) {
        libroCatalogo->stock -= 1;
        libroCatalogo->sales += 1;
        Book* libro = buscarLibro(title, head);
        anadirLibro(libro, vendidos);
        eliminarLibro(libro, head);
        cout << "Libro vendido exitosamente." << endl;
    } else {
        cout << "El libro no está disponible para la venta." << endl;
    }
}

void prestarLibro(string title, string &mail) { //TERMINADO
	User* email = obtenerUsuario(mail);
    if (email != nullptr){
    	Book* libro = buscarLibro(title, head);
    	Book* libroCatalogo = buscarLibro(title, bookCatalogo);
	    if (libro) {
	        libroCatalogo->stock -= 1;
	        Book* currentBook = new Book(libro->title, libro->author, libro->category, libro->year, libro->isbn, libro->publisher, true);
	        eliminarLibro(libro, head);
			encolar(currentBook, email->books);
	        cout << "Libro prestado exitosamente." << endl;

	    } else {
	        cout << "El libro no se encuentra en la biblioteca." << endl;
	    }
	} else {
		cout << "Usuario no encontrado." << endl;
	}
    
}

void devolverLibro(string &mail) { //TERMINADO
	User* email = obtenerUsuario(mail);
    if (email->books != nullptr) {
        Book* bookCat = buscarLibro(email->books->title, bookCatalogo);
        Book* currentBook = new Book(email->books->title, email->books->author, email->books->category, email->books->year, email->books->isbn, email->books->publisher, true);
        eliminarLibro(email->books, email->books);
        anadirLibro(currentBook, head);
        bookCat->stock += 1;
		cout << "Libro " << bookCatalogo->title << " devuelto exitosamente" << endl;
    } else {
        cout << "No hay libros prestados al usuario." << endl;
    }
}

void ordenarLibrosPorCategoria() { //TERMINADO
    if (bookCatalogo == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }

    set<string> categories;
    Book* current = bookCatalogo;
    while (current != nullptr) {
        categories.insert(current->category);
        current = current->next;
    }

    for (const string& category : categories) {
        cout << "Categoría: " << category << endl;
        cout << "Libros: ";

        current = bookCatalogo;
        while (current != nullptr) {
            if (current->category == category) {
                cout << "Título: " << current->title << endl;
		        cout << "Autor: " << current->author << endl;
		        cout << "ISBN: " << current->isbn << endl;
		        cout << "-------------------------" << endl;
            }
            current = current->next;
        }
        cout << endl;
    }
}

int main() {
	setlocale(LC_ALL, "spanish");
    int opcion;
    string name, email, title, author, category;

    do {
        mostrarMenu();
        cin >> opcion;

        switch (opcion) {
            case 1:
			    cout << "Ingrese el nombre del usuario: ";
			    cin.ignore();
			    getline(cin, name);
			    cout << "Ingrese el email del usuario: ";
			    getline(cin, email);
                registrarUsuario(name, email);
                break;
            case 2: {
                cout << "Ingrese el título del libro a buscar en el catálogo: ";
                cin.ignore();
                getline(cin, title);

                Book* book = buscarLibro(title, bookCatalogo);
                if (book) {
                    cout << "Libro encontrado:" << endl;
                    cout << "Título: " << book->title << endl;
                    cout << "Autor: " << book->author << endl;
                    cout << "Categoría: " << book->category << endl;
                    cout << "Fecha de publicación: " << book->year << endl;
                    cout << "ISBN: " << book->isbn << endl;
                    cout << "Disponible: " << (book->available ? "Sí" : "No") << endl;
                    cout << "Stock: " << book->stock << endl;
                    cout << "Ventas: " << book->sales << endl;
                } else {
                    cout << "El libro no se encuentra en la biblioteca." << endl;
                }
                break;
            }
            case 3:
			    cout << "Ingrese el título del libro a vender: ";
			    cin.ignore();
			    getline(cin, title);
                venderLibro(title, bookCatalogo, head);
                break;
            case 4:
            	
			    cout << "Ingrese el título del libro a prestar: ";
			    cin.ignore();
			    getline(cin, title);
			    cout << "Ingrese el email del usuario: ";
			    getline(cin, email);
	            prestarLibro(title, email);
                break;
            case 5:
            	
			    cout << "Ingrese el título del libro a devolver: ";
			    cin.ignore();
			    getline(cin, title);
			    cout << "Ingrese el email del usuario: ";
			    getline(cin, email);
                devolverLibro(email);
                break;
            case 6:
                ordenarLibrosPorCategoria();
                break;
            case 7:
                recomendarLibros();
                break;
            case 8:
                cout << "Mostrando reportes:" << endl;
			    cout << "Ingrese el nombre del usuario: ";
				cin.ignore();
				getline(cin, email);
			    mostrarLibrosPrestados(email);
                break;
            case 9:
			    cout << "Ingrese el título del libro: ";
			    cin.ignore();
			    getline(cin, title);
                agregarLibro(title);
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                break;
            default:
                cout << "Opción inválida. Intente nuevamente." << endl;
                break;
        }

        cout << endl;
    } while (opcion != 0);

    return 0;     

}

