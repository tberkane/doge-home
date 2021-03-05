#pragma once
#include <sys/socket.h> //the bridge module

#define PORT_BUTTON 8081

typedef struct
{
  int socket;
} button_t;

void button_init(button_t *button, int socket)
{
    button->socket = socket;
}

int is_button_pressed(button_t *button)
{
  char buffer_button[1024];
  int valread = read(button->socket, buffer_button, 1024);
  printf("Button sent: %s\n", buffer_button);
  return valread > 0;
}