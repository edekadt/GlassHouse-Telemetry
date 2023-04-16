#include <pch.h> // use stdafx.h in Visual Studio 2017 and earlier
#include <WriterThread.h>
#include <iostream>
#include <fstream>
#include <curl/curl.h>
#include <Events.h>
#include <filesystem>
namespace fs = std::filesystem;


WriterThread::WriterThread(size_t sessionID)
{
    std::string directory = "GlassHouse-data";

    if (!fs::is_directory(directory) || !fs::exists(directory)) { // Check if folder exists
        fs::create_directory(directory); // create folder
    }
    serverUrl = "http://localhost:3000/data";
    filePath = directory + "/GH_session_" + std::to_string(sessionID) + ".json";
	eventQueue = moodycamel::ReaderWriterQueue<Events*>(INITIAL_QUEUE_SIZE);
    data = {};
    numEvents = 0;
	thread = std::thread(&WriterThread::run, this);
}

void WriterThread::close()
{
	thread.join();
}

void WriterThread::writeFile(nlohmann::json& data)
{
    try {
        std::ofstream output_file(filePath, std::ios::app);
        std::string dump = data.dump();
        dump = dump.substr(1, dump.size() - 2);

        output_file << dump << ",";
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
    nlohmann::json data;
    if (input_file.is_open()) {
        input_file >> data;
    }
    std::cout << data;
}

void WriterThread::writeServer(nlohmann::json& data, std::string sever)
{
    CURL* server = curl_easy_init();
    std::string json_data = data.dump();
    try
    {
        if (server) {
            curl_easy_setopt(server, CURLOPT_URL, sever.c_str());
            curl_easy_setopt(server, CURLOPT_POST, 1L);
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(server, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(server, CURLOPT_POSTFIELDS, json_data.c_str());

            CURLcode res = curl_easy_perform(server);
            if (res != CURLE_OK) {
                std::cerr << "Error al enviar los datos al servidor: " << curl_easy_strerror(res) << std::endl;
            }
            else {
                std::cout << "Datos enviados correctamente al servidor." << std::endl;
            }

            curl_easy_cleanup(server);
            curl_slist_free_all(headers);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error al abrir servidor: " << e.what() << std::endl;
    }
}

void WriterThread::readServer()
{
    nlohmann::json response_json;
    std::string response;
    CURL* server = curl_easy_init();
    if (server) {
        curl_easy_setopt(server, CURLOPT_URL, serverUrl.c_str());
        struct curl_slist* headers = NULL; 
        //headers = curl_slist_append(headers, "Accept: text/html");
        //headers = curl_slist_append(headers, "Accept: application/json");
        //headers = curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(server, CURLOPT_FOLLOWLOCATION, 1L);
        //curl_easy_setopt(server, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(server, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(server, CURLOPT_VERBOSE, 1L);
        CURLcode res = curl_easy_perform(server);
        if (res != CURLE_OK) {
            std::cout << "Error al enviar la solicitud: " << curl_easy_strerror(res) << std::endl;
        }
        curl_easy_cleanup(server);
        curl_slist_free_all(headers);
    }
    std::cout << response;
}

void WriterThread::enqueue(Events* e)
{
	// We use emplace instead of try_emplace because try_emplace doesn't allocate additional memory if needed.
	// That would do if we didn't want to excede a fixed number of events.
	eventQueue.emplace(e);
}

void WriterThread::setWriteMode(WriteDestination mode_)
{
    mode = mode_;
}

void WriterThread::run()
{
	while (!exit)
	{
		Events* event;
        
        if (eventQueue.try_dequeue(event)) {
            numEvents++;
            data.push_back({ event->serializeToJSON() });

            if (numEvents >= EVENTS_LIMIT) {
                write(data);
                data.clear();
            }

            if (event->getType() == SESSION_END) {
                if (!data.empty()) write(data);
                exit = true;
            }
            delete event;
        }
	}
}

void WriterThread::write(nlohmann::json& data)
{
    switch (mode)
    {
    case WriteDestination::Local:
        writeFile(data);
        break;
    case WriteDestination::Server:
        writeServer(data, serverUrl);
        break;
    }
}
