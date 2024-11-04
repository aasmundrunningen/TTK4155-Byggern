#pragma once

typedef struct {
    uint32_t data_A;
    uint32_t data_B;
} ENCODER_DATA;


void encoder_init(void); 
void update_encoder_data(void);
ENCODER_DATA fetch_encoder_data(void);