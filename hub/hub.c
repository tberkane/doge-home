// Server side C/C++ program to demonstrate Socket programming
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include "door.h"
#include "button.h"
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

int init_socket(int *new_socket, int port)
{

    int server_fd, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &opt, sizeof(opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,
             sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    if ((*new_socket = accept(server_fd, (struct sockaddr *)&address,
                         (socklen_t *)&addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int main(int argc, char const *argv[])
{
    
    int valread;
    int socket_door;
    int socket_button;
    init_socket(&socket_door, PORT_DOOR);
    init_socket(&socket_button, PORT_BUTTON);
    door_t door;
    door_init(&door, socket_door);
    button_t button;
    button_init(&button, socket_button);

    while (1)
    {
        if (is_button_pressed(&button)) 
        {
            if(is_door_open(&door)){
                close_door(&door);
            }else{
                open_door(&door);
            }
        }
    }
    return 0;
}