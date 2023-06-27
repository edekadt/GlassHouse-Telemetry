#include <FilePersistor.h>
#include <iostream>
#include <fstream>
void FilePersistor::persist(const std::string& s) const
{
    try {
        std::ofstream output_file(directory, std::ios::app);
        std::string dump = s;
        dump = dump.substr(1, dump.size() - 2);

        output_file << std::endl << "\t";
        output_file << dump;
        output_file.close();

        std::cout << "Los datos se han guardado correctamente en el archivo " << directory << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al guardar los datos en el archivo JSON: " << e.what() << std::endl;
    }
}
