
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "WriterThread.h"
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>
#include <curl/curl.h>
WriterThread::WriterThread()
{
    server = nullptr;
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

void WriterThread::writeServer()
{
    nlohmann::json data = {
           {"nombre", "Juan"},
           {"apellido", "Pérez"},
           {"edad", 35}
    };

    std::string json_data = data.dump();
    if (server == nullptr)
        server = curl_easy_init();
    try
    {
        if (server) {
            curl_easy_setopt(server, CURLOPT_URL, "http://example.com/save_json");
            curl_easy_setopt(server, CURLOPT_CUSTOMREQUEST, "POST");
            curl_easy_setopt(server, CURLOPT_HTTPHEADER, "Content-Type: application/json");
            curl_easy_setopt(server, CURLOPT_POSTFIELDS, json_data.c_str());

            CURLcode result = curl_easy_perform(server);
            if (result != CURLE_OK) {
                std::cerr << "Error al enviar los datos al servidor: " << curl_easy_strerror(result) << std::endl;
            }
            else {
                std::cout << "Datos enviados correctamente al servidor." << std::endl;
            }

            curl_easy_cleanup(server);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al enviar los datos al servidor: " << e.what() << std::endl;
    }

}
