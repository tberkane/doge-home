#pragma once
#include <sys/socket.h> //the bridge module
#define PORT_DOOR 8080 

typedef struct
{
    int is_open;
    int socket;
} door_t;

#define OPEN_DOOR_MESSAGE "DOOR IS OPENING"
#define CLOSE_DOOR_MESSAGE "DOOR_IS_CLOSE"

void door_init(door_t *door, int socket)
{
    door->is_open = 0;
    door->socket = socket;
}

int is_door_open(door_t* door) {
    return door->is_open;
}

void open_door(door_t *door)
{
    door->is_open = 1;
    send(door->socket, &(OPEN_DOOR_MESSAGE), sizeof(OPEN_DOOR_MESSAGE), 0);
}

void close_door(door_t *door)
{
    door->is_open = 0;
    send(door->socket, &(CLOSE_DOOR_MESSAGE), sizeof(CLOSE_DOOR_MESSAGE), 0);
}