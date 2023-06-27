#include <ServerPersistor.h>
#include <curl/curl.h>
#include <iostream>
void ServerPersistor::persist(const std::string& s) const
{
    CURL* server = curl_easy_init();
    try
    {
        if (server) {
            curl_easy_setopt(server, CURLOPT_URL, url.c_str());
            curl_easy_setopt(server, CURLOPT_POST, 1L);
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");
            curl_easy_setopt(server, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(server, CURLOPT_POSTFIELDS, s.c_str());

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
