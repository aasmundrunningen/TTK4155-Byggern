#include "config.h"

#include "time.h"
#include "adc.h"
#include "game_engine.h"

GAME_DATA game_data = {0, 0};

#define IR_ADC_THREASHOLD 50
#define SCORE_MIN_TIME_MS 100000


uint16_t last_adc_read = 0;
uint16_t adc_read_value = 0;
void score_counter(){
    adc_read_value = last_adc_read*1/10 + adc_read() * 9/10;
    if((adc_read_value < IR_ADC_THREASHOLD) & (last_adc_read > IR_ADC_THREASHOLD)){
        game_data.score ++;
    }
    last_adc_read = adc_read_value;
    printf("IR: %d\n", last_adc_read);
}

GAME_DATA get_game_data(){
    return game_data;
}

