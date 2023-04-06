
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "BaseClass.h"
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>
BaseClass::BaseClass()
{
	std::cout << "Base constructor\n";
	id = -1;
}

int BaseClass::returnID() const
{
	return id;
}

void BaseClass::writeFile()
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
