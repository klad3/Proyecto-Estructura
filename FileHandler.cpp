#include "FileHandler.h"

void cargarLibrosDesdeArchivo(Book*& lista, const std::string& archivo) {
    std::ifstream archivoEntrada(archivo);
    if (archivoEntrada.is_open()) {
        std::stringstream buffer;
        buffer << archivoEntrada.rdbuf();
        std::string contenidoArchivo = buffer.str();

        rapidjson::Document document;
        if (document.Parse(contenidoArchivo.c_str()).HasParseError()) {
            std::cout << "Error al parsear el archivo JSON." << std::endl;
            return;
        }

        if (!document.IsArray()) {
            std::cout << "El archivo JSON debe contener un array de libros." << std::endl;
            return;
        }

        for (const auto& libro : document.GetArray()) {
            if (!libro.IsObject()) {
                std::cout << "El archivo JSON contiene elementos no válidos." << std::endl;
                return;
            }

            if (!libro.HasMember("title") || !libro["title"].IsString() ||
                !libro.HasMember("author") || !libro["author"].IsString() ||
                !libro.HasMember("category") || !libro["category"].IsString() ||
                !libro.HasMember("year") || !libro["year"].IsString() ||
                !libro.HasMember("isbn") || !libro["isbn"].IsString() ||
                !libro.HasMember("publisher") || !libro["publisher"].IsString() ||
                !libro.HasMember("available") || !libro["available"].IsBool() ||
                !libro.HasMember("stock") || !libro["stock"].IsInt() ||
                !libro.HasMember("sales") || !libro["sales"].IsInt()) {
                std::cout << "El archivo JSON contiene campos no válidos para un libro." << std::endl;
                return;
            }

            std::string title = libro["title"].GetString();
            std::string author = libro["author"].GetString();
            std::string category = libro["category"].GetString();
            std::string year = libro["year"].GetString();
            std::string isbn = libro["isbn"].GetString();
            std::string publisher = libro["publisher"].GetString();
            bool available = libro["available"].GetBool();
            int stock = libro["stock"].GetInt();
            int sales = libro["sales"].GetInt();

            Book* newBook = new Book(title, author, category, year, isbn, publisher, available);
            newBook->stock = stock;
            newBook->sales = sales;

            anadirLibro(newBook, lista);
        }

        archivoEntrada.close();
        std::cout << "Libros cargados desde el archivo exitosamente." << std::endl;
    } else {
        std::cout << "Error al abrir el archivo." << std::endl;
    }
}

void guardarLibroEnArchivo(const Book* libro, const std::string& archivo) {
    rapidjson::Document document;
    document.SetArray();

    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();

    const Book* current = libro;

    while (current != nullptr) {
        rapidjson::Value libro(rapidjson::kObjectType);
        libro.AddMember("title", rapidjson::Value(current->title.c_str(), current->title.length(), allocator).Move(), allocator);
        libro.AddMember("author", rapidjson::Value(current->author.c_str(), current->author.length(), allocator).Move(), allocator);
        libro.AddMember("category", rapidjson::Value(current->category.c_str(), current->category.length(), allocator).Move(), allocator);
        libro.AddMember("year", rapidjson::Value(current->year.c_str(), current->year.length(), allocator).Move(), allocator);
        libro.AddMember("isbn", rapidjson::Value(current->isbn.c_str(), current->isbn.length(), allocator).Move(), allocator);
        libro.AddMember("publisher", rapidjson::Value(current->publisher.c_str(), current->publisher.length(), allocator).Move(), allocator);
        libro.AddMember("available", current->available, allocator);
        libro.AddMember("stock", current->stock, allocator);
        libro.AddMember("sales", current->sales, allocator);

        document.PushBack(libro, allocator);

        current = current->next;
    }

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    document.Accept(writer);

    std::ofstream archivoSalida(archivo);
    if (archivoSalida.is_open()) {
        archivoSalida << buffer.GetString();
        archivoSalida.close();
        std::cout << "Libros guardados en el archivo exitosamente." << std::endl;
    } else {
        std::cout << "Error al abrir el archivo." << std::endl;
    }
}
