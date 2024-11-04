#include "config.h"

#include "time.h"
#include "adc.h"
#include "game_engine.h"

GAME_DATA game_data = {0, 0};

#define IR_ADC_THREASHOLD 200
#define SCORE_MIN_TIME_MS 100000


uint8_t last_adc_read = 0;
void score_counter(){
    if((adc_read() < IR_ADC_THREASHOLD) & (last_adc_read > IR_ADC_THREASHOLD)){
        game_data.score ++;
    }
    last_adc_read = adc_read();
}

GAME_DATA get_game_data(){
    return game_data;
}

