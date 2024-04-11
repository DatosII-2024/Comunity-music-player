#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <glog/logging.h>

void Socket() {
    // Inicializar Glog
    google::InitGoogleLogging("Comunity_music_player");
    FLAGS_logtostderr = true;

    // Crear el socket
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        LOG(ERROR) << "Error al crear el socket";
        google::ShutdownGoogleLogging();
        return;
    }

    // Configurar la dirección del servidor
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY; // Escuchar en todas las interfaces
    serverAddress.sin_port = htons(8080); // Puerto 8080

    // Vincular el socket a la dirección y el puerto
    if (bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress)) == -1) {
        LOG(ERROR) << "Error al vincular el socket";
        close(serverSocket);
        google::ShutdownGoogleLogging();
        return;
    }

    // Escuchar conexiones entrantes
    if (listen(serverSocket, 5) == -1) {
        LOG(ERROR) << "Error al intentar escuchar";
        close(serverSocket);
        google::ShutdownGoogleLogging();
        return;
    }

    LOG(INFO) << "Esperando conexiones entrantes...";

    // Aceptar conexiones entrantes
    sockaddr_in clientAddress;
    socklen_t clientAddressSize = sizeof(clientAddress);
    int clientSocket = accept(serverSocket, (sockaddr*)&clientAddress, &clientAddressSize);
    if (clientSocket == -1) {
        LOG(ERROR) << "Error al aceptar la conexión";
        close(serverSocket);
        google::ShutdownGoogleLogging();
        return;
    }

    LOG(INFO) << "Cliente conectado";

    // Ejemplo de eco: leer del cliente y enviar de vuelta
    char buffer[1024];
    int bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead == -1) {
        LOG(ERROR) << "Error al recibir datos";
        close(clientSocket);
        close(serverSocket);
        google::ShutdownGoogleLogging();
        return;
    }

    LOG(INFO) << "Mensaje del cliente: " << std::string(buffer, bytesRead);

    // Enviar de vuelta al cliente
    if (send(clientSocket, buffer, bytesRead, 0) == -1) {
        LOG(ERROR) << "Error al enviar datos al cliente";
        close(clientSocket);
        close(serverSocket);
        google::ShutdownGoogleLogging();
        return;
    }

    // Cerrar los sockets
    close(clientSocket);
    close(serverSocket);

    google::ShutdownGoogleLogging();
}
