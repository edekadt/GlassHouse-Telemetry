
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "WriterThread.h"
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>
WriterThread::WriterThread()
{
}

void WriterThread::writeFile()
{
    try {
        nlohmann::json data = {
            {"nombre", "Juan"},
            {"apellido", "Pérez"},
            {"edad", 35}
        };

        std::ofstream output_file("datos.json");
        output_file << data.dump();
        output_file.close();

        std::cout << "Los datos se han guardado correctamente en el archivo 'datos.json'" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al guardar los datos en el archivo JSON: " << e.what() << std::endl;
    }
}
