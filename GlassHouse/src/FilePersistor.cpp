#include <FilePersistor.h>
#include <iostream>
#include <fstream>
#include <filesystem>
namespace fs = std::filesystem;
void FilePersistor::persist(const std::string& s)
{
    try {
        std::string dump = s;
        dump = dump.substr(1, dump.size() - 2);

        output_file << std::endl << "\t";
        output_file << dump;

        std::cout << "Los datos se han guardado correctamente en el archivo " << directory << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al guardar los datos en el archivo JSON: " << e.what() << std::endl;
    }
}

void FilePersistor::open()
{
    if (!fs::is_directory(directory) || !fs::exists(directory)) { // Check if folder exists
        fs::create_directory(directory); // create folder
    }
    directory = directory + "/GH_session_" + std::to_string(id) + ".json";

    try {
        output_file.open(directory, std::ios::app);
        std::cout << "Archivo abierto en " << directory << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al abrir archivo " << e.what() << std::endl;
    }
  
}

void FilePersistor::close()
{
    try {
        output_file.close();
        std::cout << "Archivo cerrado en " << directory << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al cerrar archivo " << e.what() << std::endl;
    }
}
