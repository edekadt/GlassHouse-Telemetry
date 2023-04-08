
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "WriterThread.h"
#include <iostream>

#include <nlohmann/json.hpp>
#include <fstream>
#include <curl/curl.h>
using namespace nlohmann;
WriterThread::WriterThread()
{
    serverUrl = "http://localhost:3000/data";
    filePath = "datos.json";
}

void WriterThread::writeFile()
{
    try {
        nlohmann::json data = {
            {"nombre", "Juan"},
            {"apellido", "Perez"},
            {"edad", 35}
        };

        std::ofstream output_file(filePath);
        output_file << data.dump();
        output_file.close();

        std::cout << "Los datos se han guardado correctamente en el archivo 'datos.json'" << std::endl;
    }
    catch (std::exception& e) {
        std::cerr << "Error al guardar los datos en el archivo JSON: " << e.what() << std::endl;
    }
}

void WriterThread::readFile()
{
    std::ifstream input_file(filePath);
    json data;
    if (input_file.is_open()) {
        input_file >> data;
    }
}

void WriterThread::writeServer()
{
    nlohmann::json data = {
           {"nombre", "Juan"},
           {"apellido", "Perez"},
           {"edad", 35}
    };
    CURL* server = server = curl_easy_init();
    std::string json_data = data.dump();      
    try
    {
        if (server) {
            curl_easy_setopt(server, CURLOPT_URL, serverUrl);
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

void WriterThread::readServer()
{
    CURL*server;
    CURLcode res;
    std::string response;
    server = curl_easy_init();
    if (server) {
        curl_easy_setopt(server, CURLOPT_URL, serverUrl);
        curl_easy_setopt(server, CURLOPT_WRITEFUNCTION, [](char* data, int size, int nmemb, std::string* writerData) -> int {
            writerData->append(data, size * nmemb);
            return size * nmemb;
            });
        curl_easy_setopt(server, CURLOPT_WRITEDATA, &response);
        res = curl_easy_perform(server);
        if (res != CURLE_OK) {
            std::cout << "Error al enviar la solicitud: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(server);
    }
    json response_json = json::parse(response);
}
