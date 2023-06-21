#include <iostream>
#include <string>
#include <algorithm>
#include <locale>

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
    Book* next;

    Book(const string& title, const string& author, const string& category, const string& year, const string& isbn, const string& publisher, bool available)
        : title(title), author(author), category(category), year(year), isbn(isbn), publisher(publisher), available(available), sales(0), stock(1), next(nullptr) {}
};

struct User {
    string name;
    string email;
    Book* books;
    User* next;

    User(const string& name, const string& email) : name(name), email(email), books(nullptr), next(nullptr) {}
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

void registrarUsuario(string name, string email) {
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

Book* buscarLibro(const string& title, Book* lista) { // TERMINADO 
    Book* current = lista;
    while (current != nullptr) {
        if (current->title == title) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

User* obtenerUsuario(const string& email) {
    User* current = usersHead;
    while (current != nullptr) {
        if (current->email == email) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

void venderLibro(string title) { // En proceso
	//TODO: añadir identificador de usuario
    Book* libro = buscarLibro(title, head);
    if (libro) {
        if (libro->available) {
            libro->stock -= 1;
            cout << "Libro vendido exitosamente." << endl;
        } else {
            cout << "El libro no está disponible para la venta." << endl;
        }
    } else {
        cout << "El libro no se encuentra en la biblioteca." << endl;
    }
}

void prestarLibro(string title, string email) {

	User* currentUser = obtenerUsuario(email);
    Book* libro = buscarLibro(title, currentUser->books);
    
    if (currentUser != nullptr){
	    if (libro) {
	        if (libro->available) {
	            libro->stock -= 1;
	            cout << "Libro vendido exitosamente." << endl;
	
	            // Agregar el libro a la cola
	            if (currentUser->books == nullptr) {
	                currentUser->books = libro;
	            } else {
	                Book* current = currentUser->books;
	                while (current->next != nullptr) {
	                    current = current->next;
	                }
	                current->next = libro;
	            }
	        } else {
	            cout << "El libro no está disponible para préstamo." << endl;
	        }
	    } else {
	        cout << "El libro no se encuentra en la biblioteca." << endl;
	    }
	} else {
		cout << "Usuario no encontrado." << endl;
	}
    
}

void devolverLibro(string title) {
    Book* libro = buscarLibro(title, head);
    if (libro) {
        if (!libro->available) {
            libro->available = true;
            cout << "Libro devuelto exitosamente." << endl;
        } else {
            cout << "El libro no fue prestado." << endl;
        }
    } else {
        cout << "El libro no se encuentra en la biblioteca." << endl;
    }
}

void ordenarLibrosPorCategoria() {
    if (head == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }

    // Crear listas enlazadas temporales para cada categoría
    Book* categorizedBooks[10] = { nullptr };

    // Recorrer la lista de libros y asignar cada libro a su lista enlazada correspondiente
    Book* current = head;
    while (current != nullptr) {
        Book* nextBook = current->next;
        current->next = nullptr;

        int categoryIndex = current->category[0] - '0';
        if (categoryIndex >= 0 && categoryIndex <= 9) {
            if (categorizedBooks[categoryIndex] == nullptr) {
                categorizedBooks[categoryIndex] = current;
            } else {
                Book* temp = categorizedBooks[categoryIndex];
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = current;
            }
        }

        current = nextBook;
    }

    // Mostrar los libros por categoría
    for (int i = 0; i < 10; i++) {
        cout << "Libros de la categoría " << i << ":" << endl;
        if (categorizedBooks[i] == nullptr) {
            cout << "No hay libros registrados en esta categoría." << endl;
        } else {
            Book* temp = categorizedBooks[i];
            while (temp != nullptr) {
                cout << "Título: " << temp->title << endl;
                cout << "Autor: " << temp->author << endl;
                cout << "Categoría: " << temp->category << endl;
                cout << "-------------------------" << endl;
                temp = temp->next;
            }
        }
    }
}

void recomendarLibros() {
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

int contarLibros() {
    int contador = 0;
    Book* actual = head;

    while (actual != nullptr) {
        contador++;
        actual = actual->next;
    }

    return contador;
}

Book* obtenerLibroMasVendido() {
    if (head == nullptr) {
        return nullptr;
    }

    Book* libroMasVendido = head;
    Book* current = head->next;

    while (current != nullptr) {
        if (current->sales > libroMasVendido->sales) {
            libroMasVendido = current;
        }
        current = current->next;
    }

    return libroMasVendido;
}

void mostrarLibrosPrestados() {
    if (head == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }

    bool librosPrestados = false;
    Book* current = head;

    while (current != nullptr) {
        if (!current->available) {
            cout << "Título: " << current->title << endl;
            cout << "Autor: " << current->author << endl;
            cout << "Categoría: " << current->category << endl;
            cout << "-------------------------" << endl;
            librosPrestados = true;
        }
        current = current->next;
    }

    if (!librosPrestados) {
        cout << "No hay libros prestados en este momento." << endl;
    }
}

void mostrarLibrosDisponibles() {
    if (head == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }

    cout << "Libros disponibles para la venta:" << endl;
    Book* current = head;
    bool librosDisponibles = false;

    while (current != nullptr) {
        if (current->available) {
            cout << "Título: " << current->title << endl;
            cout << "Autor: " << current->author << endl;
            cout << "Categoría: " << current->category << endl;
            cout << "-------------------------" << endl;
            librosDisponibles = true;
        }
        current = current->next;
    }

    if (!librosDisponibles) {
        cout << "No hay libros disponibles para la venta en este momento." << endl;
    }
}

int contarUsuarios() {
    int contador = 0;
    User* actual = usersHead;

    while (actual != nullptr) {
        contador++;
        actual = actual->next;
    }

    return contador;
}

void mostrarReportes() {
    cout << "Mostrando reportes:" << endl;

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

    // Reporte 3: Libros prestados y no devueltos
    cout << "Libros prestados y no devueltos:" << endl;
    mostrarLibrosPrestados();

    // Reporte 4: Libros disponibles para la venta
    cout << "Libros disponibles para la venta:" << endl;
    mostrarLibrosDisponibles();

    // Reporte 5: Cantidad de usuarios registrados
    int cantidadUsuarios = contarUsuarios();
    cout << "Cantidad de usuarios registrados: " << cantidadUsuarios << endl;
}

void anadirCatalogo(Book* newBook, Book*& lista) { // TERMINADO AL PARECER
	
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

void anadirLibro(Book* newBook, Book*& lista) { // TERMINADO AL PARECER
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

void agregarLibro(string characterId) { // TERMINADO AL PARECER
    string characterInfo = GetBookInfo(characterId);
    string title, author, category, identifier, publishedDate, publisher;

    rapidjson::Document doc;
    doc.Parse(characterInfo.c_str());

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

	Book* newBook = new Book(title, author, category, publishedDate, identifier, publisher, true);
    anadirLibro(newBook, head);
    anadirCatalogo(newBook, bookCatalogo);
}

void eliminarLibro(Book* bookToDelete, Book*& lista) { //EN PROCESO
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

int main() {
	setlocale(LC_ALL, "spanish");
    int opcion;
    string name, email, title, author, category, characterId;

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
                venderLibro(title);
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
                devolverLibro(title);
                break;
            case 6:
                ordenarLibrosPorCategoria();
                break;
            case 7:
                recomendarLibros();
                break;
            case 8:
                mostrarReportes();
                break;
            case 9:
            
			
			    cout << "Ingrese el isbn del libro: ";
			    cin.ignore();
			    getline(cin, characterId);
			
                agregarLibro(characterId);
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


