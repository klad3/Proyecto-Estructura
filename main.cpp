#include <iostream>
#include <algorithm>
#include <locale>
#include <set>
#include <queue>


#include "ApiHandler.h"
#include "Book.h"
#include "User.h"
#include "Graph.h"
#include "FileHandler.h"

using namespace std;

Book* head = nullptr;
Book* bookCatalogo = nullptr;
Book* vendidos = nullptr;
User* usersHead = nullptr;

void mostrarMenu() { // TERMINADO
	system("CLS");
    cout << "========== Biblioteca ==========" << endl;
    cout << "1. Registrar usuario" << endl;
    cout << "2. Buscar libro" << endl;
    cout << "3. Vender libro" << endl;
    cout << "4. Prestar libro" << endl;
    cout << "5. Devolver libro" << endl;
    cout << "6. Ordenar libros por categor�a" << endl;
    cout << "7. Recomendar libros" << endl;
    cout << "8. Mostrar reportes" << endl;
    cout << "9. A�adir libro" << endl;
    cout << "0. Salir" << endl;
    cout << "=================================" << endl;
    cout << "Ingrese una opci�n: ";
}

void verLista(Book* lista){ // INSERVIBLE AL PARECER
    while (lista != nullptr) {
        cout << "T�tulo: " << lista->title << endl;
        cout << "Autor: " << lista->author << endl;
        cout << "Categor�a: " << lista->category << endl;
        cout << "ISBN: " << lista->isbn << endl;
        cout << "Stock: " << lista->stock << endl;
        cout << "-------------------------" << endl;
        lista = lista->next;
    }
}

void mostrarLibrosDisponibles() { // TERMINADO
    if (bookCatalogo == nullptr) {
        cout << "No hay libros registrados." << endl;
        return;
    }
	bool librosDisponibles = false;
    cout << "Libros disponibles para la venta o pr�stamo:" << endl;
    Book* current = bookCatalogo;

    while (current != nullptr) {
        if (current->stock > 0) {
            cout << "T�tulo: " << current->title << endl;
            cout << "Autor: " << current->author << endl;
            cout << "Categor�a: " << current->category << endl;
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

void mostrarReportes() { // FALTA
    cout << "Mostrando reportes:" << endl;
    // Reporte 1: Cantidad total de libros registrados
    int cantidadLibros = contarLibros(head);
    cout << "Cantidad total de libros registrados: " << cantidadLibros << endl;

    // Reporte 2: Libro m�s vendido
    Book* libroMasVendido = obtenerLibroMasVendido(bookCatalogo);
    if (libroMasVendido != nullptr) {
        cout << "Libro m�s vendido:" << endl;
        cout << "T�tulo: " << libroMasVendido->title << endl;
        cout << "Autor: " << libroMasVendido->author << endl;
        cout << "Categor�a: " << libroMasVendido->category << endl;
        cout << "Cantidad de ventas: " << libroMasVendido->sales << endl;
    } else {
        cout << "No se encontraron libros registrados." << endl;
    }


	int cantidadUsuarios = contarUsuarios(usersHead);
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
                cout << "T�tulo: " << title << endl;
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
                    cout << "Categor�a: " << category << endl;
                }
            }

            if (volumeInfo.HasMember("publisher") && volumeInfo["publisher"].IsString()) {
                publisher = volumeInfo["publisher"].GetString();
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
                cout << "Fecha de publicaci�n: " << publishedDate << endl;
            }
        }
    }
	Book* newBook1 = new Book(title, author, category, publishedDate, identifier, publisher, true);
	Book* newBook2 = new Book(title, author, category, publishedDate, identifier, publisher, true);
    anadirLibro(newBook1, head);
    anadirCatalogo(newBook2, bookCatalogo);
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
        cout << "Categor�a: " << category << endl;
        cout << "Libros: ";

        current = bookCatalogo;
        while (current != nullptr) {
            if (current->category == category) {
                cout << "T�tulo: " << current->title << endl;
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
	setlocale(LC_ALL, "Spanish");
	cargarLibrosDesdeArchivo(head, "head.json");
	cargarLibrosDesdeArchivo(bookCatalogo, "bookCatalogo.json");

    int opcion;
    string name, email, title, author, category;
    Graph graph;
    User* user;
	vector<string> recommendations;

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
                registrarUsuario(name, email, usersHead);
                system("PAUSE");
                break;
            case 2: {
                cout << "Ingrese el t�tulo del libro a buscar en el cat�logo: ";
                cin.ignore();
                getline(cin, title);

                Book* book = buscarLibro(title, bookCatalogo);
                if (book) {
                    cout << "Libro encontrado:" << endl;
                    cout << "T�tulo: " << book->title << endl;
                    cout << "Autor: " << book->author << endl;
                    cout << "Categor�a: " << book->category << endl;
                    cout << "Fecha de publicaci�n: " << book->year << endl;
                    cout << "ISBN: " << book->isbn << endl;
                    cout << "Disponible: " << (book->available ? "S�" : "No") << endl;
                    cout << "Stock: " << book->stock << endl;
                    cout << "Ventas: " << book->sales << endl;
                } else {
                    cout << "El libro no se encuentra en la biblioteca." << endl;
                }
                system("PAUSE");
                break;
            }
            case 3:
			    cout << "Ingrese el t�tulo del libro a vender: ";
			    cin.ignore();
			    getline(cin, title);
			    if (venderLibro(title, bookCatalogo, head, vendidos)){
                    cout << "Libro vendido exitosamente." << endl;
			    } else {
                    cout << "El libro no est� disponible para la venta." << endl;
			    }
                system("PAUSE");
                break;
            case 4:

			    cout << "Ingrese el email del usuario: ";
			    cin.ignore();
			    getline(cin, email);
			    user = obtenerUsuario(email, usersHead);
			    if (user) {
			        cout << "Ingrese el t�tulo del libro a prestar: ";
                    getline(cin, title);
                    if (prestarLibro(title, user, bookCatalogo, head)) {
                        cout << "Libro prestado exitosamente." << endl;
                    } else {
                        cout << "El libro no se encuentra en la biblioteca." << endl;
                    }
			    } else {
                    cout << "Usuario no encontrado." << endl;
			    }
	            system("PAUSE");
                break;
            case 5:
			    cout << "Ingrese el email del usuario: ";
			    cin.ignore();
			    getline(cin, email);
			    user = obtenerUsuario(email, usersHead);
			    if (user->books != nullptr) {
                    title = user->books->title;
                    devolverLibro(user, bookCatalogo, head);
                    cout << "Libro " << title << " devuelto exitosamente" << endl;
			    } else {
                    cout << "No hay libros prestados al usuario." << endl;
                }
                system("PAUSE");
                break;
            case 6:
                mostrarReportes();
                system("PAUSE");
                break;
            case 7:
                cout << "Ingrese el t�tulo del libro: ";
                cin.ignore();
                getline(cin, title);

                graph.conectarLibrosCatalogo(bookCatalogo);
                recommendations = graph.recomendarLibros(title, bookCatalogo);

                if (recommendations.empty()) {
                    cout << "No se encontraron recomendaciones de libros para '" << title << "'." << endl;
                } else {
                    cout << "Libros recomendados para '" << title << "':" << endl;
                    for (const string& recommendation : recommendations) {
                        cout << "- " << recommendation << endl;
                    }
                }
                system("PAUSE");
                break;
            case 8:
                cout << "Mostrando reportes:" << endl;
			    cout << "Ingrese el nombre del usuario: ";
				cin.ignore();
				getline(cin, email);
			    mostrarLibrosPrestados(email, usersHead);
			    system("PAUSE");
                break;
            case 9:
			    cout << "Ingrese el t�tulo del libro: ";
			    cin.ignore();
			    getline(cin, title);
                agregarLibro(title);
                system("PAUSE");
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                guardarLibroEnArchivo(head, "head.json");
        		guardarLibroEnArchivo(bookCatalogo, "bookCatalogo.json");
                break;
            default:
                cout << "Opci�n inv�lida. Intente nuevamente." << endl;
                system("PAUSE");
                break;
        }
        cout << endl;
    } while (opcion != 0);

    return 0;
}
