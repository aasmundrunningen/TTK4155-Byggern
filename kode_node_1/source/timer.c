#include "config.h"
#include "avr/io.h"
#include "OLED.h"
#include "OLED_menu.h"

uint8_t pin_toogle = 0;

void timer0_IRQ_handler(){
    set_bit(PORTB, PIN1);
    handle_joystick_movement();
    clear_bit(PORTB, PIN1);

}

void timer0_enable_IRQ(){
    clear_bit(TCCR0, FOC0); //force output compare
    
    //set waveform generation mode to CTC (clear timer on compare match)
    set_bit(TCCR0, WGM00);
    clear_bit(TCCR0, WGM01);

    //dissables OCO which is responsible for sending data to IO
    clear_bit(TCCR0, COM00);
    clear_bit(TCCR0, COM01);

    //enables clkio without 16 in prescaling
    set_bit(TCCR0, CS00);
    set_bit(TCCR0, CS01);
    clear_bit(TCCR0, CS02);

    OCR0 = 0x10; //value the counter counts to

    set_bit(TIMSK, OCIE0); //enables interrupt on compare match


    set_bit(DDRB, PB1);
}

void timer0_dissable_IRQ(){
    clear_bit(TIMSK, OCIE0);
}