#pragma once


void encoder_init(void); 
void update_encoder_data(void);
int32_t fetch_encoder_data(void);
void encoder_set_offsett();
void encoder_addjust_offsett(int32_t addjustment);