#pragma once

typedef struct {
    uint8_t id;
    uint8_t length;
    char data[];
} CAN_MESSAGE;