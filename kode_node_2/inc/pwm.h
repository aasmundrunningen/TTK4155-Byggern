#pragma once

void pwm_init();
void pwm_print_status();
void pwm_set_duty(int8_t duty_cycle);
void pwm_motor_controll(int8_t duty_cycle);